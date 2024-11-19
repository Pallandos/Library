#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_COUNT 100

void parse_input(char *input, char **args) {
    int i = 0;
    args[i] = strtok(input, " \n");
    while (args[i] != NULL) {
        i++;
        args[i] = strtok(NULL, " \n");
    }
}

int main() {
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARG_COUNT];
    int status;

    while (1) {
        printf("interpréteur> ");
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            perror("fgets");
            exit(1);
        }

        // Parse the input into arguments
        parse_input(input, args);

        // If the user types "exit", break the loop and terminate the interpreter
        if (args[0] == NULL) {
            continue;
        }
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        // Fork 
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            // fils : execution
            if (execv(args[0], args) == -1) {
                perror("execv");
                exit(1);
            }
        } else {
            // père : on attends le fils
            wait(&status);
        }
    }

    return 0;
}
