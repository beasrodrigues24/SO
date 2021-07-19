#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char * argv[]) {

    if (argc < 4) {
        
        perror("arguments");
        exit(-1);
    }

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {

        perror("pipe");
        exit(-1);

    }

    if (fork() == 0) {

        close(pipe_fd[0]);

        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);

        execlp("procura", "procura", argv[1], argv[3], NULL);
        perror("execlp");
        _exit(-1);

    }

    close(pipe_fd[1]);

    int fd_wrt = open(argv[3], O_WRONLY, 0644);
    if (fd_wrt < 0) {

        perror("open");
        exit(-1);

    }

    int offset;
    while (read(pipe_fd[0], &offset, 8) > 0) {

        lseek(fd_wrt, offset, SEEK_CUR);
        if (write(fd_wrt, argv[2], strlen(argv[2])) <= 0) {

            perror("write");
            exit(-1);

        }

    }

    close(pipe_fd[0]);
    close(fd_wrt);

    return 0;

}