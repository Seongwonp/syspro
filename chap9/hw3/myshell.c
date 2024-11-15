#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_INPUT 1024
#define MAX_ARGS 100

void parse_input(char *input, char **args, int *background, char **input_file, char **output_file) {
    *background = 0;
    *input_file = NULL;
    *output_file = NULL;
    char *token = strtok(input, " \n");
    int i = 0;

    while (token != NULL) {
        if (strcmp(token, "&") == 0) {
            *background = 1;
        } else if (strcmp(token, "<") == 0) {
            *input_file = strtok(NULL, " \n");
        } else if (strcmp(token, ">") == 0) {
            *output_file = strtok(NULL, " \n");
        } else {
            args[i++] = token;
        }
        token = strtok(NULL, " \n");
    }
    args[i] = NULL;
}


void handle_redirection(char *input_file, char *output_file) {
    //>
	if (input_file != NULL) {
        int fd_in = open(input_file, O_RDONLY);
        if (fd_in == -1) {
            perror("open input file");
            exit(1);
        }
        dup2(fd_in, STDIN_FILENO);  
        close(fd_in);
    }

	//<
    if (output_file != NULL) {
        int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out == -1) {
            perror("open output file");
            exit(1);
        }
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
    }
}

//background "&" or print
int execute_command(char *input) {
    char *args[MAX_ARGS];
    char *input_file, *output_file;
    int background;
    pid_t pid;
    int status;

    parse_input(input, args, &background, &input_file, &output_file);

    if (args[0] == NULL) {
        return 1;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        handle_redirection(input_file, output_file);

        if (execvp(args[0], args) == -1) {
            perror("execvp");
            exit(1);
        }
    } else {
        if (background == 0) {
            waitpid(pid, &status, 0);
            if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                printf("Error executing command\n");
                return 1;
            }
            printf("\n\n");
        } else {
            printf("[%d] Child process created in background\n\n", pid);
        }
    }
    return 0;
}

int main() {
    char input[MAX_INPUT];
    char *cmds[MAX_ARGS];
    pid_t pid;
    int status;

    while (1) {
        printf("[shell] ");
        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            perror("fgets");
            exit(1);
        }


        if (strncmp(input, "exit", 4) == 0) {
            printf("Exit\n");
			break;
        }

        // ;
        int cmd_count = 0;
        char *cmd = strtok(input, ";");
        while (cmd != NULL) {
            cmds[cmd_count++] = cmd;
            cmd = strtok(NULL, ";");
        }

        // Execute each command in sequence
        for (int i = 0; i < cmd_count; i++) {
            if (execute_command(cmds[i]) != 0) {
                break;  // Exit
            }
        }
    }

    return 0;
}

