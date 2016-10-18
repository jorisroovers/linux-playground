// In order to use system calls directly, we need to include unistd
#include <unistd.h>

int main(int argc, char *argv[]) {
    write(1, "Hello World!\n", 13); // write a string of length to file descriptor 1 (=stdout)
    write(2, "STD ERR LINE\n", 13); // write a string of length to file descriptor 2 (=stderr)

    return 0;
}