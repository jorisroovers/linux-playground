// O_WRONLY, O_RDONLY
#include <fcntl.h>

// printf
#include <stdio.h>

// write, open, etc. default syscalls
#include <unistd.h>

// SECCOMP_MODE_STRICT
#include <linux/seccomp.h>

// PR_SET_SECCOMP
#include <sys/prctl.h>

// strlen
#include <string.h>


int main(int argc, char **argv) {
    int output = open("output.txt", O_WRONLY);
    const char *val = "test";

    printf("Calling prctl() to set seccomp strict mode...\n");

    // prctl = process control
    // set process in seccomp mode, this allows it to only write() and read() from open files
    // or call exit() (or si
    prctl(PR_SET_SECCOMP, SECCOMP_MODE_STRICT);

    printf("Writing to an already open file...\n");
    write(output, val, strlen(val) + 1);

    printf("Trying to open file for reading...\n");
    int input = open("output.txt", O_RDONLY);

    // process will be killed using SIGKILL because we tried to access a new file
    printf("You will not see this message--the process will be killed first\n");
}