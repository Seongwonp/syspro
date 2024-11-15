#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
#define MAX_ARGS 100

void parse_input(char *input, char **args, int *background) {
    *background = 0;
    char *token = strtok(input, " \n");
    int i = 0;

    while (token != NULL) {
        if (strcmp(token, "&") == 0) {
            *background = 1;
        } else {
            args[i++] = token;
        }
        token = strtok(NULL, " \n");
    }
    args[i] = NULL;
}

int main() {
    char input[MAX_INPUT];
    char *args[MAX_ARGS];
    int background;
    pid_t pid;
    int status;

    while (1) {
        printf("Pls input cmd : ");
        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            perror("fgets");
            exit(1);
        }

        if (strncmp(input, "exit", 4) == 0) {
            printf("Exit\n");
            break;
        }

        parse_input(input, args, &background);

        if (args[0] == NULL) {
            continue;
        }

        printf("[%d] Parent process started\n", getpid());

        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {

            if (execvp(args[0], args) == -1) {
				exit(1);
            }
            exit(0);
        }
		else {
            if (background == 0) {
                waitpid(pid, &status, 0);
                if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                    printf("Parent process end\nExit\n");
					exit(1);
                }
                printf("SUCCESS\n\n");

            }
			else {
                printf("[%d] Child process start\n", pid);
                waitpid(pid, &status, 0);
                printf("[%d] child process end %d\nSUCCESS\n\n", getpid(), pid);
            }
        }
    }
	printf("Parent process end\nExit\n");

    return 0;
}

