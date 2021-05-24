#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {

    int pipe_fd[2];

    int pipe_result = pipe(pipe_fd);

    if (pipe_result == 0) {

        if (fork() == 0) {

            close(pipe_fd[1]);

            dup2(pipe_fd[0], STDOUT_FILENO);
            close(pipe_fd[0]);

            execlp("ls", "ls", "/exec", NULL);

            _exit(1);

        }
        
        close(pipe_fd[1]);

        if (fork() == 0) {

            dup2(pipe_fd[0], STDIN_FILENO);
            close(pipe_fd[0]);

            execlp("wc", "wc", "-l", NULL);

            _exit(1);

        }

        close(pipe_fd[0]);

        wait(NULL);
        wait(NULL);

    }
    else {

        perror("pipe");
        exit(1);

    }

    return 0;

}