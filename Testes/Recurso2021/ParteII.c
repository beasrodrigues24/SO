#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>

#define N_EXECUTIONS 10
#define BUFFER_SIZE 1024

int main(int argc, char * argv[]) {

    if (argc < 2) {

        perror("Arguments");
        exit(1);

    }

    int count[N_EXECUTIONS];

    for (int i = 0; i < N_EXECUTIONS; i++) {

        pid_t pid;
        if ((pid = fork()) == 0) {

            execvp(argv[1], argv + 1);
            perror("execvp");
            _exit(1);

        }

        int pipe_fd[2][2];

        if (pipe(pipe_fd[0]) == -1) {

            perror("Pipe");
            exit(1);

        }

        char * pid_string = malloc(BUFFER_SIZE);

        if (fork() == 0) {

            close(pipe_fd[0][0]);

            dup2(pipe_fd[0][1], STDOUT_FILENO);
            close(pipe_fd[0][1]);

            snprintf(pid_string, BUFFER_SIZE, "/proc/%d/memstats", pid);
            execlp("grep", "grep", "VmPeak", pid_string, NULL);
            perror("Exec");
            _exit(1);

        }

        free(pid_string);
        close(pipe_fd[0][1]);

        if (pipe(pipe_fd[1]) == -1) {

            perror("pipe");
            exit(1);

        }

        if (fork() == 0) {

            close(pipe_fd[0][1]);
            close(pipe_fd[1][0]);

            dup2(pipe_fd[0][0], STDIN_FILENO);
            close(pipe_fd[0][0]);
            dup2(pipe_fd[1][1], STDOUT_FILENO);
            close(pipe_fd[1][1]);
            
            execlp("cut", "cut", "-d\" \"", "-f4", NULL);
            perror("Exec");
            _exit(1);

        }

        close(pipe_fd[0][0]);
        close(pipe_fd[1][1]);

        char * buffer = malloc(BUFFER_SIZE);
        ssize_t bytes_read = read(pipe_fd[1][0], buffer, BUFFER_SIZE);
        close(pipe_fd[1][0]);

        if (!bytes_read) {

            perror("Fail");
            exit(1);

        }

        count[i] = atoi(buffer);

        free(buffer);

    }

    int average, highest = 0, smallest = count[0];

    for (int i = 0; i < N_EXECUTIONS; i++) {

        average += count[i];
        if (count[i] > highest) highest = count[i];
        else if (count[i] < smallest) smallest = count[i];

    }

    char * message = malloc(BUFFER_SIZE);
    snprintf(message, BUFFER_SIZE, "memoria: %d %d %d\n", smallest, average, highest);
    write(STDOUT_FILENO, message, strlen(message));
    free(message);

    return 0;

}