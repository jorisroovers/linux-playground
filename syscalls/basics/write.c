#include <sys/types.h>
#include <unistd.h>


int main(int argc, char **argv) {

    // Note how you can't write integers using the write() syscall.
    // This is because write() is of the form: ssize_t write(int fd, const void *buf, size_t count);
    // Note that second parameter: const void *buf -> a pointer to some memory place
    // This effectively means that write will just write to the file descriptor, the first `count` bytes of whatever
    // is located at `buf`. Now, because in our case, the fd is stdout which is /dev/tty, a character device
    // the device will interpret the data as UTF-8/ASCII and print it as such on the screen.

    // The following example then prints the letter 'A' to the screen
    int test;
    test = 65; // 65 is the ASCII code for the letter A
    write(STDOUT_FILENO, &test, sizeof(test));
}