#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int child, pid, status;

    pid = fork();
    if (pid == 0) {
        execvp(argv[1], &argv[1]);
        fprintf(stderr, "%s: execution failed\n", argv[1]);
        exit(1);
    } else {
        child = wait(&status);
        printf("[%d] Child process %d exited\n", getpid(), pid);
        printf("\tExit code %d\n", status >> 8);
    }

    return 0;
}

