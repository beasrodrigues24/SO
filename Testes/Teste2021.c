#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>


/*
    DISCLAIMER 

    * Trata-se de uma resolução provisória que provavelmente não está certa
    * Aberto a sugestões de correção

*/

// Exercício 1

#define BUFFER_SIZE 1024
#define ENTRY_SIZE 50

char ** parse_entry (char ** position) {
    return NULL;
}

int servidor() {

    int fd_pipe, fd_write;
    fd_pipe = open("fifo", O_RDONLY);
    if (fd_pipe < 0) {

        perror("open");
        exit(1);

    }

    ssize_t bytes_read;
    char * buffer = malloc(sizeof(char) * BUFFER_SIZE);
    char ** parsed;
    char * write_string = malloc(sizeof(char) * ENTRY_SIZE);

    while((bytes_read = read(fd_pipe, buffer, BUFFER_SIZE)) > 0) {

        while((parsed = parse_entry(&buffer))) {

            snprintf(write_string, ENTRY_SIZE, "%s %s %s\n", parsed[0], parsed[1], parsed[2]);
            fd_write = open(parsed[2], O_CREAT | O_APPEND | O_WRONLY, 0644);
            if (fd_write < 0) {

                perror("open");
                exit(1);

            }
            write(fd_write, buffer, BUFFER_SIZE);
            close(fd_write);

        }

    }

    free(buffer);
    free(write_string);

    return 0;

}


// Exercício 2

#define AGE_SIZE 4

int vacinados(char * regiao, int idade) {

    int pipe_fd[2];

    if (pipe(pipe_fd) < 0) {

        perror("pipe");
        exit(1);

    }

    if (fork() == 0) {

        close(pipe_fd[0]);

        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);

        char idade_string[AGE_SIZE];
        snprintf(idade_string, AGE_SIZE, "%d", idade);

        execlp("grep", "grep", idade_string, regiao, NULL);
        perror("execlp");
        _exit(1);

    }

    close(pipe_fd[0]);

    if (fork() == 0) {

        close(pipe_fd[1]);

        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);

        execlp("wc", "wc", "-l", NULL);
        perror("execlp");
        _exit(1);

    }

    close(pipe_fd[0]);

    int count = 0, status;

    for (int i = 0; i < 2; i++) {

        wait(&status);
        count += WEXITSTATUS(status);

    }

    return count;

}

// Exercício 3

#define N_REGIONS 9

bool vacinado(char * cidadao) {

    pid_t pids[9];
    pid_t pid;
    char * reg[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

    for (int i = 0; i < N_REGIONS; i++) {

        if ((pid = fork()) == 0) {

            execlp("grep", "grep", cidadao, reg[i], NULL);
            perror("execlp");
            _exit(1);

        }

        pids[i] = pid;

    }

    int status;
    bool not_found = true;

    for (int i = 0; not_found && (pid = wait(&status)); i++) 
        if (!WEXITSTATUS(status)) 
            not_found = false;

    if (!not_found) {

        for (int i = 0; i < N_REGIONS; i++) 
            if (pids[i] != pid && pids[i] > 0) 
                kill(pids[i], SIGKILL);

    }
    
    return !not_found;

}


// Main

int main() {

    return 0;

}