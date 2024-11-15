#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_INPUT 1024
#define MAX_ARGS 100

void parse_input(char* input, char** args, char** output_file, char** input_file, int* background) {
    *output_file = NULL;
    *input_file = NULL;
    *background = 0;

    char* token = strtok(input, " \n");
    int i = 0;

    while (token != NULL) {
        if (strcmp(token, "&") == 0) { *background = 1; }  // background
        else if (strcmp(token, ">") == 0) { token = strtok(NULL, " \n"); *output_file = token; }  // output redirection
        else if (strcmp(token, "<") == 0) { token = strtok(NULL, " \n"); *input_file = token; }  // input redirection
        else { args[i++] = token; }  // cmd args
        token = strtok(NULL, " \n");
    }
    args[i] = NULL;  // end
}

int main() {
    char input[MAX_INPUT];
    char* args[MAX_ARGS];
    char* output_file;
    char* input_file;
    int background;
    pid_t pid;
    int status;

    while (1) {
        printf("[shell] ");
        if (fgets(input, MAX_INPUT, stdin) == NULL) { perror("fgets"); exit(1); }

        if (strncmp(input, "exit", 4) == 0) { printf("Exiting shell...\n"); break; }

        char* cmd = strtok(input, ";");  // command split by ';'

        while (cmd != NULL) {
            parse_input(cmd, args, &output_file, &input_file, &background);

            pid = fork();  // create child
            if (pid == -1) { perror("fork"); exit(1); }
            else if (pid == 0) {  // child process

                if (input_file != NULL) {  // input redirection
                    int fd_in = open(input_file, O_RDONLY);
                    if (fd_in == -1) { perror("Input file open failed"); exit(1); }
                    dup2(fd_in, STDIN_FILENO);
                    close(fd_in);
                }

                if (output_file != NULL) {  // output redirection
                    int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (fd_out == -1) { perror("Output file open failed"); exit(1); }
                    dup2(fd_out, STDOUT_FILENO);
                    close(fd_out);
                }

                if (execvp(args[0], args) == -1) { perror("execvp"); exit(1); }
            } else {  // parent process
                if (!background) { waitpid(pid, &status, 0); }  // wait for child
            }

            cmd = strtok(NULL, ";");  // next command
        }
    }

    return 0;
}

