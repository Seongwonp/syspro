#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXLINE 100

int main(){
	int n, pid, fd[2];
	char line[MAXLINE];
	int child_pid;

	pipe(fd);

	//Send
	if((pid=fork())==0){
		close(fd[0]);
		child_pid = getpid();
		printf("Send: [%d] ",child_pid);
		dup2(fd[1],1);
		close(fd[1]);
		printf("Hello from PID %d\n",child_pid);
		exit(0);
	}
	
	//Recv
	else{
		close(fd[1]);
		wait(NULL);
		printf("Recv: [%d] ",getpid());	
		while((n=read(fd[0],line,MAXLINE))>0){
			write(STDOUT_FILENO,line,n);
		}
		close(fd[0]);
	}

	exit(0);
}
