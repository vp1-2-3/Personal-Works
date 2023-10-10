#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

//Parse function to store individual words in an array (Rubric Step 2)
int parse(const char *input, char *argv[]) {
    char inputCopy[MAX_INPUT_SIZE];
    strcpy(inputCopy, input);

    char *token = strtok(inputCopy, " ");
    int argCount = 0;

    while (token != NULL) {
        argv[argCount++] = token;
        token = strtok(NULL, " ");
    }

    return argCount;
}

int main() {
    char input[MAX_INPUT_SIZE];
    //Rubric Step 4: save previous command
    char prevComm[MAX_INPUT_SIZE] = "";

    while (1) {
        // Rubric Step One: Display the prompt
        printf("osh > ");
        fflush(stdout);

        // Get input using fgets() instead of gets()
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // Ruvric Step Two: Place 0's in between words
        input[strcspn(input, "\n")] = '\0';

        // Rubric Step 3: Implement exit command
        if (strcmp(input, "exit") == 0) {
            break; // Exit the shell
        }

        //Implementation of repeat previous command(Rubric Step 4)
        if (strcmp(input, "!!") == 0) {
            if (strlen(prevComm) == 0) {
                printf("No previous command to repeat.\n");
                continue;
            } else {
                strcpy(input, prevComm);
            }
        }

        //Rubric Step 9: Use pipe to redirect outputs
        char *pipe_symbol = strchr(input, '|');
        if (pipe_symbol != NULL) {
            *pipe_symbol = '\0';
            char *command1 = input;
            char *command2 = pipe_symbol + 1;

            // Create pipes for communication
            int pipe_fd[2];
            if (pipe(pipe_fd) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }

            //Rubric Step 5: The usage of fork/exec to use multiple processes
            pid_t child_pid1 = fork();

            if (child_pid1 == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (child_pid1 == 0) {
                //Child Process including redirected pipe
                close(pipe_fd[0]);
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);

                execlp("sh", "sh", "-c", command1, NULL);

                perror("execlp (command1)");
                exit(EXIT_FAILURE);
            } else {
                //Parent Process
                close(pipe_fd[1]);
                int status1;
                waitpid(child_pid1, &status1, 0);

                pid_t child_pid2 = fork();

                if (child_pid2 == -1) {
                    perror("fork");
                    exit(EXIT_FAILURE);
                } else if (child_pid2 == 0) {
                    //Child Process
                    dup2(pipe_fd[0], STDIN_FILENO);
                    close(pipe_fd[0]);

                    execlp("sh", "sh", "-c", command2, NULL);

                    // If execlp fails, print an error message
                    perror("execlp (command2)");
                    exit(EXIT_FAILURE);
                } else {
                    //Parent Process
                    close(pipe_fd[0]);
                    int status2;
                    waitpid(child_pid2, &status2, 0);
                }
            }
        } else {
            //Make array for Rubric Step 2
            char *argv[MAX_INPUT_SIZE / 3];
            int argCount = parse(input, argv);
            argv[argCount] = NULL;

            pid_t child_pid = fork();

            if (child_pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (child_pid == 0) {
                // This is the child process
                execlp("sh", "sh", "-c", input, NULL);

                // If execlp fails, print an error message
                perror("execlp");
                exit(EXIT_FAILURE);
            } else {
                //Parent process
                int status;
                waitpid(child_pid, &status, 0);

                strcpy(prevComm, input);
            }
        }
    }

    return 0;
}

//---------------------------------------- EXAMPLE OUTPUT ----------------------------------------
// vp@MSI:~/C++ Development Root/os$ ./shell3
// osh > ls -l
// total 132
// -rwxr-xr-x  1 vp vp 16320 Sep 11 10:46 a.out
// drwxr-xr-x 11 vp vp  4096 Aug 26 15:12 final-src-osc10e
// -rw-r--r--  1 vp vp    12 Sep 15 23:12 new.txt
// -rw-r--r--  1 vp vp    12 Sep 15 22:37 out.txt
// -rwxr-xr-x  1 vp vp 16304 Sep 15 16:32 shell
// -rwxr-xr-x  1 vp vp 16624 Sep 15 15:28 shell2
// -rw-r--r--  1 vp vp  2324 Sep 15 15:28 shell2.c
// -rwxr-xr-x  1 vp vp 17008 Sep 15 23:13 shell3
// -rw-r--r--  1 vp vp  4262 Sep 15 22:57 shell3.c
// -rw-r--r--  1 vp vp  2348 Sep 15 22:39 shell.c
// drwxr-xr-x  2 vp vp  4096 Aug 23 11:53 start
// -rw-r--r--  1 vp vp  2324 Sep 15 22:29 test.txt
// -rwxr-xr-x  1 vp vp 16560 Sep 13 12:19 third
// -rw-r--r--  1 vp vp  2400 Sep 15 15:10 thrd-posix.c
// osh > !!
// total 132
// -rwxr-xr-x  1 vp vp 16320 Sep 11 10:46 a.out
// drwxr-xr-x 11 vp vp  4096 Aug 26 15:12 final-src-osc10e
// -rw-r--r--  1 vp vp    12 Sep 15 23:12 new.txt
// -rw-r--r--  1 vp vp    12 Sep 15 22:37 out.txt
// -rwxr-xr-x  1 vp vp 16304 Sep 15 16:32 shell
// -rwxr-xr-x  1 vp vp 16624 Sep 15 15:28 shell2
// -rw-r--r--  1 vp vp  2324 Sep 15 15:28 shell2.c
// -rwxr-xr-x  1 vp vp 17008 Sep 15 23:13 shell3
// -rw-r--r--  1 vp vp  4262 Sep 15 22:57 shell3.c
// -rw-r--r--  1 vp vp  2348 Sep 15 22:39 shell.c
// drwxr-xr-x  2 vp vp  4096 Aug 23 11:53 start
// -rw-r--r--  1 vp vp  2324 Sep 15 22:29 test.txt
// -rwxr-xr-x  1 vp vp 16560 Sep 13 12:19 third
// -rw-r--r--  1 vp vp  2400 Sep 15 15:10 thrd-posix.c
// osh > cat < out.txt > new.txt
// osh > ls -l | cat
// total 132
// -rwxr-xr-x  1 vp vp 16320 Sep 11 10:46 a.out
// drwxr-xr-x 11 vp vp  4096 Aug 26 15:12 final-src-osc10e
// -rw-r--r--  1 vp vp    12 Sep 15 23:13 new.txt
// -rw-r--r--  1 vp vp    12 Sep 15 22:37 out.txt
// -rwxr-xr-x  1 vp vp 16304 Sep 15 16:32 shell
// -rwxr-xr-x  1 vp vp 16624 Sep 15 15:28 shell2
// -rw-r--r--  1 vp vp  2324 Sep 15 15:28 shell2.c
// -rwxr-xr-x  1 vp vp 17008 Sep 15 23:13 shell3
// -rw-r--r--  1 vp vp  4262 Sep 15 22:57 shell3.c
// -rw-r--r--  1 vp vp  2348 Sep 15 22:39 shell.c
// drwxr-xr-x  2 vp vp  4096 Aug 23 11:53 start
// -rw-r--r--  1 vp vp  2324 Sep 15 22:29 test.txt
// -rwxr-xr-x  1 vp vp 16560 Sep 13 12:19 third
// -rw-r--r--  1 vp vp  2400 Sep 15 15:10 thrd-posix.c
// osh > 
//---------------------------------------- EXAMPLE OUTPUT ----------------------------------------
