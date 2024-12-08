#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#define MAXLINE 100

int main(int argc, char* argv[]){
	int n,pid1, pid2, fd[2];
	char line[MAXLINE];
	char massage[MAXLINE];
	pipe(fd);

	if((pid1=fork())==0){
		close(fd[0]);
		printf("input string: ");
		if(fgets(massage,MAXLINE, stdin) != NULL){
			write(fd[1],massage, strlen(massage)+1);
		}
		close(fd[1]);
		exit(0);
	}
	
	waitpid(pid1,NULL, 0);

	if((pid2=fork())==0){
		close(fd[1]);
		while((n=read(fd[0],line,MAXLINE))>0){
			for(int i=0; i<n; i++){
				line[i]=toupper((unsigned char)line[i]);
			}
		}
		printf("%s",line);
		close(fd[0]);
		exit(0);
	}	
		close(fd[0]);
		close(fd[1]);	 
		return 0; 
}
