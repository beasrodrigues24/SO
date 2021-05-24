#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BUFFER_SIZE 15

int main() {

    int pipe_fd[2];

    int pipe_result = pipe(pipe_fd);

    if (pipe_result == 0) {

        if (fork() == 0) {

            close(pipe_fd[1]);

            dup2(pipe_fd[0], STDIN_FILENO);
            close(pipe_fd[0]);

            execlp("wc", "wc", NULL);
            
            _exit(1);

        }
        else {

            close(pipe_fd[0]);

            ssize_t bytes;
            char * buffer = malloc(BUFFER_SIZE);

            while ((bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) 
                write(pipe_fd[1], buffer, bytes);

            close(pipe_fd[1]);

            wait(NULL);

        }

    }
    else {

        perror("pipe");
        exit(1);

    }

    return 0;

}