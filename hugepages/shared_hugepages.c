
#define _GNU_SOURCE // https://stackoverflow.com/questions/59537934/map-hugetlb-undefined

// In order to use system calls directly, we need to include unistd
#include <unistd.h>

// Include fcnt to use the 0_RDONLY flag constant
// http://pubs.opengroup.org/onlinepubs/009695399/basedefs/fcntl.h.html
#include <fcntl.h>

// printf, fgets
#include <stdio.h>

// Required to use mmap and munmap and their flags
#include <sys/mman.h>

// exit()
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("Shared Huge pages example program\n");

    // open the file
    int fd = open(argv[1], O_CREAT | O_RDWR, 777);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // MMAP() parameters

    // memory we want to allocate: 5MB
    // on x86, the hugepage size is typically 2MB. This means we'll need 3 hugepages to fit the 5MB.
    // This is one of the disavantages of using hugepages: you can waste some memory in your last page
    //  as you must allocate at the page boundary.
    unsigned long BUFF_SIZE = 1024 * 1024 * 5; // 5MB
    
    // mmap() flags
    // MAP_SHARED   : shared memory
    int FLAGS = MAP_SHARED;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    char* buffer;
    buffer = mmap(NULL                        /* NULL = let kernel decide start address of mapped memory */, 
                    BUFF_SIZE,                /* amount of bytes to map */
                    PROT_READ | PROT_WRITE,   /* read-write memory */
                    FLAGS,
                    fd,                       
                    0);                       /* read offset */

    // file is mapped to memory, we don't need to keep the file descriptor open
    close(fd);

    if (buffer == MAP_FAILED) {
		perror("mmap");
        printf("FATAL ERROR\n");
		exit(1);
	}
    printf("Returned address is %p\n", buffer);

    // you can just use this buffer to do whatever you want now
    for (int i=0; i < BUFF_SIZE; i++){
        buffer[i] = 'a';
    }

    // Wait for user input before exiting
    char str[100];
    printf("Hit [enter] to terminate");
    fgets(str, 100, stdin);
    munmap(buffer, BUFF_SIZE);

    printf("Program exiting...\n");
}