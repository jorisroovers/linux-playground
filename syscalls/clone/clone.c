
// Needed before *all* includes to correctly load syscall constants
#define _GNU_SOURCE

#include <stdio.h>  // printf
#include <stdlib.h> // exit
#include <unistd.h>
#include <sched.h> // clone()

#define STACK_SIZE (1024 * 1024)

struct ThreadParams
{
    char *foo;
    int mynumber;
};

int my_thread_func(void *myparam)
{
    printf("[THREAD] PID: %d\n", getpid());
    printf("[THREAD] PPID: %d\n", getppid()); // ppid = parent PID

    struct ThreadParams *threadParams = myparam; // cast from void to our struct
    printf("[THREAD] threadParams->foo = \"%s\"\n", threadParams->foo);
    printf("[THREAD] Setting threadParams->foo = \"Changed inside thread\"\n");
    threadParams->foo = "Changed inside thread";


    // Do a bit of sleeping so we can inspect the process tree in linux
    printf("[THREAD] Sleeping for 100 sec\n");
    sleep(100);
    printf("[THREAD] exiting thread %d\n", getpid());
    return 0;
}

int main(int argc, char *argv[])
{
    // clone() has many uses, but most common is to implement threads like shown below
    printf("### CLONE() ###\n");
    printf("[PARENT PROCESS] PID: %d\n", getpid());

    struct ThreadParams threadParams = {"foobar!", 5};
    printf("[PARENT PROCESS] threadParams->foo = \"%s\"\n", threadParams.foo);

    char *childStack = malloc(STACK_SIZE);
    // stack grows downwards on almost all CPUs, so point to the highest address of the stack to start
    char *stackTop = childStack + STACK_SIZE;
    int CLONE_FLAGS = CLONE_VM; // CLONE_VM = share memory between thread and parent process
    pid_t child_pid = clone(&my_thread_func, stackTop, CLONE_FLAGS, &threadParams);
    printf("[PARENT PROCESS] PID returned by clone(): %i\n", child_pid);

    // Only parent continues here (compared with fork() in which case both parent and child continue)

    sleep(1); // hacky way to sync thread with main process, ensuring the thread has had time to set `threadParams.foo`

    // Demonstrate memory sharing by reading the value set by the thread
    printf("[PARENT PROCESS] threadParams.foo = \"%s\"\n", threadParams.foo);

    printf("Hit any key to exit parent (this does NOT kill the thread!)\n");
    char *buf;
    read(STDIN_FILENO, buf, 1);
    if (child_pid > 0)
        printf("[PARENT PROCESS] exit()\n");
    return 0;
}