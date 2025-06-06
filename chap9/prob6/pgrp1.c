#include <stdio.h>
#include <unistd.h>

int main() {
    int pid, gid;

    printf("PARENT: PID = %d GID = %d\n", getpid(), getpgrp());
    pid = fork();

    if (pid == 0) {
        printf("CHILD: PID = %d GID = %d\n", getpid(), getpgrp());
    }

    return 0;
}
