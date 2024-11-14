#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("Parent process started\n");

    if (fork() == 0) {
        execl("/bin/date", "date", NULL);
        fprintf(stderr, "First execution failed\n");
        exit(1);
    }

    if (fork() == 0) {
        execl("/bin/ls", "ls", "*", "-", NULL);
        fprintf(stderr, "Second execution failed\n");
        exit(2);
    }

    if (fork() == 0) {
        execl("/bin/echo", "echo", "hello", NULL);
        fprintf(stderr, "Third execution failed\n");
        exit(3);
    }

    printf("Parent process ended\n");

    return 0;
}
