
// Needed before *all* includes to correctly load syscall constants
#define _GNU_SOURCE

#include <stdio.h>  // printf
#include <stdlib.h> // exit
#include <unistd.h>
#include <sched.h> // CLONE_NEWPID

int main(int argc, char *argv[])
{
    printf("IMPORTANT: Make sure to use this program using root privileges!\n\n\n");
    ////////////////////////////////////////////////////////////////////////////
    // REGULAR FORK()
    ////////////////////////////////////////////////////////////////////////////
    printf("### REGULAR FORK() ###\n");
    printf("[PARENT PROCESS] PID: %d\n", getpid());
    pid_t child_pid = fork();
    pid_t mypid = getpid();

    // parent fork() return value = child PID, child return value = 0
    // Without using unshare() the child pid's will be very close to the parent's PID
    if (child_pid > 0)
    {
        printf("[PARENT PROCESS] PID returned by fork(): %i\n", child_pid);
        printf("[PARENT PROCESS] getpid(): %d\n", mypid);
    }
    else
    {
        printf("[CHILD PROCESS]  PID returned by fork(): %i\n", child_pid);
        printf("[CHILD PROCESS]  getpid(): %d\n", mypid);
        printf("[CHILD PROCESS]  exit()\n");
        exit(0); // exit the child process
    }
    sleep(1); // Using sleep() as a hack to synchronize parent and child processes
    printf("--------------------------------------------------------------\n\n");

    ////////////////////////////////////////////////////////////////////////////
    // UNSHARE() + FORK()
    ////////////////////////////////////////////////////////////////////////////
    printf("### UNSHARE() AND FORK() ###\n");
    // By using unshare() (requires root!), the next fork() call will create a child in a new PID namespace
    unshare(CLONE_NEWPID);
    child_pid = fork();
    mypid = getpid();
    if (child_pid > 0)
    {
        printf("[PARENT PROCESS] PID returned by fork(): %i\n", child_pid);
        printf("[PARENT PROCESS] getpid(): %d\n", mypid);
    }
    else
    {
        // child
        printf("[CHILD PROCESS]  PID returned by fork(): %i\n", child_pid);
        printf("[CHILD PROCESS]  getpid(): %d\n", mypid);
    }
    // NOTE: we're not dealing with the error handline here: child_pid_after_unshare == -1
    sleep(1); // Using sleep() as a hack to synchronize parent and child processes

    if (child_pid > 0)
        printf("Hit any key to exit both parent and child\n");

    char *buf;
    read(STDIN_FILENO, buf, 1);
    if (child_pid > 0)
        printf("[PARENT PROCESS] exit()\n");
    else
        printf("[CHILD PROCESS] exit()\n");
    return 0;
}