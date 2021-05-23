#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BUFFER_SIZE 20

int main() {

    int pipe_fd[2];

    int pipe_result = pipe(pipe_fd);

    if (pipe_result == 0) {

        if (fork() == 0) {

            ssize_t bytes_read;

            close(pipe_fd[1]);
            char * buffer = malloc(BUFFER_SIZE);

            while ((bytes_read = read(pipe_fd[0], buffer, BUFFER_SIZE)) > 0)
                write(STDOUT_FILENO, buffer, bytes_read);

            _exit(0);

        }
        else {

            close(pipe_fd[0]);

            char * text = "Text for the test";
            write(pipe_fd[1], text, strlen(text));

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