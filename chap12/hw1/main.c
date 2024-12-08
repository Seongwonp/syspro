#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAXLINE 100

int main(){
    int n, pid, length, fd[2];
    char line[MAXLINE];
    char massage[MAXLINE];
    int child_pid;

    pipe(fd);
    if ((pid = fork()) == 0) {
        close(fd[0]);
        child_pid = getpid();
	printf("Send: [%d] ", child_pid);
	sprintf(massage, "Hello from PID %d\n",child_pid);
	length = strlen(massage)+1;
	write(fd[1],massage,length);
	
	printf("%s", massage);
        close(fd[1]);
        return 0;
    }
    else {
        close(fd[1]);
        wait(NULL);
	n=read(fd[0],line,MAXLINE);
        printf("Recv: [%d] %s\n", getpid(),line);
    }
    exit(0);
    return 0;
}
