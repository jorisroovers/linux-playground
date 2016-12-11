
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv) {

    pid_t mypid = getpid();

    // we can't use write() to easily write the int to screen, see basics/write.c and let's glibc's printf instead.
    printf("Parent PID: %i\n", mypid);

    pid_t child_pid = fork();
    // fork returns PID '0' to the child and the actual child PID to the parent process.
    if (child_pid > 0) {
        printf("Child PID: %i\n", child_pid);
        exit(0);
    }

    // http://man7.org/linux/man-pages/man2/setsid.2.html
    pid_t session_id = setsid();
    printf("Session ID (SID): %i\n", session_id);

    pid_t child2_pid = fork();
    if (child2_pid > 0) {
        printf("Child2 PID: %i\n", child2_pid);
    }

    // For both processes:
    // Read a char on stdin -> wait for user input
    char *buf;
    read(STDIN_FILENO, buf, 1);
}
