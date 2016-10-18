/*
 * cat using system calls.
 */

// In order to use system calls directly, we need to include unistd
#include <unistd.h>

// Include fcnt to use the 0_RDONLY flag constant
// http://pubs.opengroup.org/onlinepubs/009695399/basedefs/fcntl.h.html
#include <fcntl.h>

// Required to use the 'stat' type, used by e.g. fstat()
#include <sys/stat.h>

// Required to use mmap and munmap and their flags
#include <sys/mman.h>


// function declarations
void simple_cat(char *[]);

void complex_cat(char *[]);

void mmap_cat(char *[]);


int main(int argc, char *argv[]) {
//    simple_cat(argv);
    complex_cat(argv);
//    mmap_cat(argv);
    return 0;
}

/**
 * Simple cat function that uses a static buffer that can fit the whole file (doesn't work for files larger than 2Kb).
 */
void simple_cat(char *argv[]) {
    write(1, "STATIC\n\n", 8);

    int fd; //file descriptor FTW!
    struct stat stat_buffer; // buffer for reading file stats

    // allocate a 2Kb buffer on the stack (=static buffer size)
    char file_buffer[2048];

    // open the file
    fd = open(argv[1], O_RDONLY);

    // get the file stats, we'll need this to determine the file size
    fstat(fd, &stat_buffer);

    // read the file in the buffer
    read(fd, &file_buffer, stat_buffer.st_size);

    // write a string of length to file descriptor 1 (=stdout)
    write(1, &file_buffer, stat_buffer.st_size);

    // make sure to close our file descriptor at the end
    close(fd);
    // close stdout
    close(1);
}

/**
 * More complex cat function that uses a static buffer size but uses a while loop to read the whole file.
 */
void complex_cat(char *argv[]) {
    write(1, "COMPLEX\n\n", 9);
    int fd; //file descriptor FTW!

    // allocate a 1Kb buffer on the stack (=static buffer size)
    const int BUFFER_SIZE = 1024;
    char file_buffer[BUFFER_SIZE];
    // number of bytes read during the last read iteration.
    int num_bytes_read;

    // open the file
    fd = open(argv[1], O_RDONLY);

    // read the file in the buffer
    num_bytes_read = -1;
    while (num_bytes_read != 0) {
        num_bytes_read = read(fd, &file_buffer, BUFFER_SIZE); // read returns the number of bytes
        // write a string of length to file descriptor 1 (=stdout)
        write(1, &file_buffer, num_bytes_read);
    }

    // make sure to close our file descriptor at the end
    close(fd);
    // close stdout
    close(1);
}


void mmap_cat(char *argv[]) {
    write(1, "MMAP\n\n", 6);
    int fd; //file descriptor FTW!
    struct stat stat_buffer; // buffer for reading file stats

    // allocate a 1Kb buffer on the stack (=static buffer size)
    char *file_buffer;

    // open the file
    fd = open(argv[1], O_RDONLY);

    // get the file stats, we'll need this to determine the file size
    fstat(fd, &stat_buffer);

    // Map the file into memory (all at once), MAP_PRIVATE -> process private memory, not shared memory
    file_buffer = mmap(NULL, stat_buffer.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

    // read the file in the buffer
    read(fd, file_buffer, stat_buffer.st_size);

    // write a string of length to file descriptor 1 (=stdout)
    write(1, file_buffer, stat_buffer.st_size);

    // unmap file from memory
    munmap(file_buffer, stat_buffer.st_size);

    // make sure to close our file descriptor at the end
    close(fd);
    // close stdout
    close(1);
}