#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("Parent process started\n");

    if (fork() == 0) {
        execl("/bin/echo", "echo", "hello", NULL);
        fprintf(stderr, "Execution failed\n");
        exit(1);
    }

    printf("Parent process ended\n");

    return 0;
}
