// printf
#include <stdio.h>
#include <stdlib.h>

// Signal system calls
#include <signal.h>

void sig_handler(int signum)
{
    printf("Received signal %d\n", signum);
}

int main()
{
    printf("PID: %d\n", getpid());

    // Keyboard Interupt: CTRL+C
    signal(SIGINT, sig_handler);

    // Terminate process: kill <pid> or kill -SIGTERM <pid>
    signal(SIGTERM, sig_handler);

    // Terminate process: kill -9 <pid> or kill -SIGKILL <pid>
    // Note: this won't actually work as the process will be killed before running the signal handler
    signal(SIGKILL, sig_handler);

    // Stop and continue program: kill -SIGSTOP <pid>, kill -SIGCONT <pid>
    signal(SIGSTOP, sig_handler);
    signal(SIGCONT, sig_handler);

    // Resize terminal (allows for e.g. redrawing)
    signal(SIGWINCH, sig_handler);

    sleep(600); // 10 min
    return 0;
}