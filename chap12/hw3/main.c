#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
<<<<<<< HEAD
#include <ctype.h>
#include <sys/wait.h>
#define MAXLINE 1024
#define READ 0
#define WRITE 1

int main(int argc, char* argv[]){
     int n,pid1, pid2, fd[2];
     char str[MAXLINE];
     char *command1, *command2;
     if(argc > 0){
        if(argc == 1){
                printf("[shell]");
                fgets(str,sizeof(str),stdin);
                str[strlen(str)-1]='\0';
                if(strchr(str,'|')!=NULL){
                        command1=strtok(str,"| ");
                        command2= strtok(NULL,"| ");
                }
        }
        else if(argc == 4){
                command1 = argv[1];
                command2 = argv[3];
        }

        pipe(fd);

        if((pid1=fork())==0){
                close(fd[READ]);
                dup2(fd[WRITE],1);
                close(fd[WRITE]);
                execlp(command1, command1, NULL);
                perror("pipe");
        }

        if((pid2=fork())==0){
                close(fd[WRITE]);
                dup2(fd[READ],0);
                close(fd[READ]);
                execlp(command2,command2,NULL);
                perror("pipe");
        }
        close(fd[READ]);
        close(fd[WRITE]);
        waitpid(pid1,NULL,0);
        waitpid(pid2,NULL,0);
        exit(0);
     }
     else{
        perror("Invalid argument count");
        exit(1);
     }
=======
#include <sys/wait.h>

#define MAXLINE 100
#define READ 0
#define WRITE 1

int main(int argc, char* argv[]) {
    int pid1, pid2, fd[2];
 	 char str[1024];
	 char *command1, *command2;
	if(argc == 1 || (argc == 4 && strcmp(argv[2], "|"))){ 
    	if (argc == 1) {
        	printf("[shell] ");
        	fgets(str, sizeof(str), stdin);
        	str[strlen(str) - 1] = '\0';

        	if (strchr(str, '|') != NULL) {
            	command1 = strtok(str, "| ");
            	command2 = strtok(NULL, "| ");
        	}
    	} 
		else if (argc == 4 && strcmp(argv[2], "|") == 0){
			 command1 = argv[1];
             command2 = argv[3];
     
    	}
		pipe(fd);

		if (fork() == 0) {
    		close(fd[READ]);
    		dup2(fd[WRITE], STDOUT_FILENO);
    		close(fd[WRITE]);
    		execlp(command1, command1, NULL);
    		perror("pipe");
    		exit(1);
			} 
		else {
    		close(fd[WRITE]);
    		dup2(fd[READ], STDIN_FILENO);
    		close(fd[READ]);
    		execlp(command2, command2, NULL);
    		perror("pipe");
    		exit(1);
			}
	}
	else {
        fprintf(stderr, "Usage: %s <command1> | <command2>\n", argv[0]);
        exit(1);
    }

    return 0;
>>>>>>> 7bbf99ab45ba1f36d047c1f4054bcb1576f68cb1
}

