#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main() {
    char str[128];
    int i = 1;
    pid_t pid;
    do {
        printf("minor5> ");
        scanf(" %99[^\n]", str);
        if (strcmp(str, "quit") == 0) {
            exit(0);
        }
        int fd[2];
        // fd[0] will be fd(file descriptor) for read end of pipe
        // fd[1] will be the fd for the write end of pipe.

        if (pipe(fd) < 0) {
            // Returns : 0 on Success. -1 on error.
            // Pipes behave FIFO like a queue data structure.
            perror("Error: Pipe creation failed!\n");
        }
        pid = fork();
        if (pid < 0) {
            perror("Error: fork() failed!\n");
            exit(1);
        }
        if (pid == 0) {
            // dup2() makes newfd copy of oldfd
            dup2(fd[1], 0);
            close(fd[0]);
            close(fd[1]);

            char *path;
            char *cmd[128];
            char *tok = strtok(str, " ");
            path = tok;
            cmd[0] = tok;
            do {
                tok = strtok(NULL, " ");
                if (tok == NULL) break;
                cmd[i++] = tok;
            } while (1);

            cmd[i] = NULL;
            int ret = execvp(path, cmd);

            // return negative on invalid argument
            if (ret < 0) {
                printf("%s: command not found\n", cmd[0]);
                exit(1);
            }

        } else {
            wait(NULL);
            close(fd[1]);
            do {
                char out[128];
                int line = (int) read(fd[0], out, 128);
                if (line <= 0) break;
                out[line] = '\0';
                printf("%s", out);
            } while (1);

            close(fd[0]);

        }
        getchar();

    } while (1);
}

