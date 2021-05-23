#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define N_PIPES 3

int main() {

    int pipeA_fd[2];
    int pipeB_fd[2];
    int pipeC_fd[2];

    if (pipe(pipeA_fd) == -1) {

        perror("pipe");
        exit(1);

    }

    if (fork() == 0) {

        close(pipeA_fd[0]);
            
        dup2(pipeA_fd[1], STDOUT_FILENO);
        close(pipeA_fd[1]);

        execlp("grep", "grep", "-v", "^#", "/etc/passwd", NULL);
        perror("execlp");
        _exit(1);

    }
        
    close(pipeA_fd[1]);

    if (pipe(pipeB_fd) == -1) {

        perror("pipe");
        exit(1);

    }

    if (fork() == 0) {

        close(pipeB_fd[0]);

        dup2(pipeA_fd[0], STDIN_FILENO);
        close(pipeA_fd[0]);

        dup2(pipeB_fd[1], STDOUT_FILENO);
        close(pipeB_fd[1]);

        execlp("cut", "cut", "-f7", "-d", NULL);
        perror("execlp");
        _exit(1);

    }

    close(pipeB_fd[1]);

    if (pipe(pipeC_fd) == -1) {

        perror("pipe");
        exit(1);

    }

    if (fork() == 0) {

        close(pipeC_fd[0]);

        dup2(pipeB_fd[0], STDIN_FILENO);
        close(pipeB_fd[0]);

        dup2(pipeC_fd[1], STDOUT_FILENO);
        close(pipeC_fd[1]);

        execlp("uniq", "uniq", NULL);
        perror("execlp");
        _exit(1);

    }

    close(pipeB_fd[0]);
    close(pipeC_fd[1]);

    if (fork() == 0) {

        dup2(pipeC_fd[0], STDIN_FILENO);
        close(pipeC_fd[0]);

        execlp("wc", "wc", "-l", NULL);
        _exit(1);

    }

    close(pipeC_fd[0]);

    for (int i = 0; i < N_PIPES; i++)
        wait(NULL);
        
    return 0;

}