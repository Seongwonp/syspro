#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAXLINE 100

int main(){
    int n, pid, fd[2];
    char line[MAXLINE] = "Hello from PID ";
    char pid_str[10];
    int child_pid;

    pipe(fd);

    if ((pid = fork()) == 0) {
        close(fd[0]);
        child_pid = getpid();
        printf("Send: [%d] ", child_pid);

        sprintf(pid_str, "%d", child_pid);
        strcat(line, pid_str);
        strcat(line, "\n");
	printf("%s", line);
        dup2(fd[1], STDOUT_FILENO);
        printf("%s", line);

        close(fd[1]);
        return 0;
    }
    else {
        close(fd[1]);
        wait(NULL);

        printf("Recv: [%d] ", getpid());
        fflush(stdout);

        while ((n = read(fd[0], line, MAXLINE)) > 0) {
            write(STDOUT_FILENO, line, n);
        }

        close(fd[0]);
    }

    return 0;
}
