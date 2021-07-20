#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX 1024

int npids = 0;
int pids[MAX];

void sigalrm_handler() {

    for (int i = 0; i < npids; i++)
        if (pids[i] > 0)
            kill(pids[i], SIGKILL);
    
    exit(0);

}

void sigint_handler(int signum) {

    alarm(30);

}


int main(int argc, char * argv[]) {

    if (argc < 4) {

        perror("arguments");
        exit(-1);

    }

    if (signal(SIGINT, sigint_handler) == SIG_ERR) {

        perror("signal");
        exit(-1);

    }

    if (signal(SIGALRM, sigalrm_handler) == SIG_ERR) {

        perror("signal");
        exit(-1);

    }

    npids = argc - 3;
    for (int i = 0; i < npids; i++) 
        if ((pids[i] = fork()) == 0) {

            execlp("substitui", "substitui", argv[1], argv[2], argv[i+3], NULL);
            perror("execlp");
            _exit(i+1);

        }

    int status;
    pid_t pid;
    
    for (int i = 0; i < npids; i++) {

        pid = wait(&status);

        if (WEXITSTATUS(status) == 0) {
            
            int index;
            for (index = 0; pids[index] != pid; index++);
            printf("%s\n", argv[index + 3]);

        }
    }

    return 0;

}