// printf
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <target PID> <signal number>\n", argv[0]);
        exit(1);
    }
    // send signal to process
    kill(atoi(argv[1]) /* PID */, atoi(argv[2]) /* signal */);
    return 0;
}