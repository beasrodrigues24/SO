#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define N_PIPES 3

int main() {

    int pipes[N_PIPES][2];

    if (pipe(pipes[0]) == -1) {

        perror("pipe");
        exit(1);

    }

    if (fork() == 0) {

        close(pipes[0][0]);
            
        dup2(pipes[0][1], STDOUT_FILENO);
        close(pipes[0][1]);

        execlp("grep", "grep", "-v", "^#", "/etc/passwd", NULL);
        perror("execlp");
        _exit(1);

    }
        
    close(pipes[0][1]);

    if (pipe(pipes[1]) == -1) {

        perror("pipe");
        exit(1);

    }

    if (fork() == 0) {

        close(pipes[1][0]);

        dup2(pipes[0][0], STDIN_FILENO);
        close(pipes[0][0]);

        dup2(pipes[1][1], STDOUT_FILENO);
        close(pipes[1][1]);

        execlp("cut", "cut", "-f7", "-d:", NULL);
        perror("execlp");
        _exit(1);

    }

    close(pipes[0][0]);
    close(pipes[1][1]);

    if (pipe(pipes[2]) == -1) {

        perror("pipe");
        exit(1);

    }

    if (fork() == 0) {

        close(pipes[2][0]);

        dup2(pipes[1][0], STDIN_FILENO);
        close(pipes[1][0]);

        dup2(pipes[2][1], STDOUT_FILENO);
        close(pipes[2][1]);

        execlp("uniq", "uniq", NULL);
        perror("execlp");
        _exit(1);

    }

    close(pipes[1][0]);
    close(pipes[2][1]);

    if (fork() == 0) {

        dup2(pipes[2][0], STDIN_FILENO);
        close(pipes[2][0]);

        execlp("wc", "wc", "-l", NULL);
        _exit(1);

    }

    close(pipes[2][0]);

    for (int i = 0; i < N_PIPES; i++)
        wait(NULL);
        
    return 0;

}