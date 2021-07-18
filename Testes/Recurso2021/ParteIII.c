#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>

#define N_EXEC 100 
#define TIME_LIMIT 20

int normal_exit = 0;
int pids[N_EXEC];

void timeout_handler() {

    int status;
    for (int i = 0; i < N_EXEC; i++) {

        if (pids[i] > 0) 
            kill(pids[i], SIGKILL);

    }

    printf("Normal exits: %d\n", normal_exit);
    exit(0);

}

void sigint_handler(int signum) {

    printf("Normal exits: %d\n", normal_exit);
    exit(1);

}

int main() {

    if (signal(SIGALRM, timeout_handler) == SIG_ERR) {

        perror("signal");
        exit(1);

    }

    if (signal(SIGINT, sigint_handler) == SIG_ERR) {

        perror("signal");
        exit(1);

    }

    for (int i = 0; i < N_EXEC; i++) 
        if ((pids[i] = fork()) == 0) {

            execlp("cat", "cat", "beeMovieScript.txt", NULL); // cmd no work in linux F so switched to a cat of a big file
            perror("execlp");
            _exit(1);

        }

    alarm(TIME_LIMIT);
    
    int status;
    for (int i = 0; i < N_EXEC; i++) {

        wait(&status);
        if (WEXITSTATUS(status) == 0) 
            normal_exit++;

    }

    printf("Normal exits: %d\n", normal_exit);

    return 0;

}