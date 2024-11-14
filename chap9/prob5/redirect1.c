#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int fd;

    fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0600);
    dup2(fd, 1);
    close(fd);

    printf("Hello stdout!\n");
    fprintf(stderr, "Hello stderr!\n");

    return 0;
}
