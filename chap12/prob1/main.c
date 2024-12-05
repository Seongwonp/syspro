#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAXLINE 100

int main(){
	int n,lengh,fd[2],pid;
	char message[MAXLINE],line[MAXLINE];

	pipe(fd);
	if((pid=fork())==0){
		close(fd[0]);
		sprintf(message,"Hello from PID %d\n",getpid());
		lengh = strlen(message)+1;
		write(fd[1],message,lengh);
	}
	else{
		close(fd[1]);
		n=read(fd[0],line,MAXLINE);
		printf("[%d]%s\n",getpid(),line);
	}

	exit(0);
}

