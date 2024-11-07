#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[]){
   
    char *ptr;
    extern char **environ;
	if(argc >1){
	//-e
	if(strcmp(argv[1],"-e") ==0){
		if(argc >=3){
			ptr = getenv(argv[2]);
			if(ptr != NULL){
			printf("%s = %s \n",argv[2], ptr);
			}
			else
				printf("%s not found!\n",argv[2]);

		}
		else{
			for(char **env = environ; *env != NULL; env++)
				printf("%s \n", *env);
		}


	}

	//-u
	else if(strcmp(argv[1], "-u") == 0){
		printf("My Realistic User ID: %d(%s) \n", getuid(), getpwuid(getuid())->pw_name);
    	printf("My Valid User ID: %d(%s) \n", geteuid(), getpwuid(geteuid())->pw_name);
	}

	//-g
	else if(strcmp(argv[1], "-g") == 0){
    printf("My Realistic Group ID: %d(%s) \n", getgid(), getgrgid(getgid())->gr_name);
    printf("My Valid Group ID: %d(%s) \n", getegid(), getgrgid(getegid())->gr_name);
	}
	//-i
	else if(strcmp(argv[1], "-i") == 0){
		printf("My process number: [%d] \n", getpid());
	}
	//-p
	else if(strcmp(argv[1], "-p") == 0){
		printf("My parent process number: [%d] \n", getppid());
	}

	else
		printf("No op\n");
	}
	else{
		printf("ERROR\n");
		exit(1);
	}
    exit(0);
}
