
// In order to use system calls directly, we need to include unistd
#include <unistd.h>

int main(int argc, char **argv) {
    write(0, "Starting the program\n", 21);

    char *const args[] = {"-l"};
    execv("/bin/ls", args);

    // Note how the following output is no longer written because our program switches to running ls
    // If you'd still want to run this output, you'd have to fork and then exec the ls command in the child
    write(0, "test\n", 5);

}