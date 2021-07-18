#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#define BUFFER_SIZE 100

int ctrl_c_counter = 0;
int seconds = 0;

void sigint_handler(int signum) {

    ctrl_c_counter++;
    char * buffer = malloc(BUFFER_SIZE);
    snprintf(buffer, BUFFER_SIZE,"Received SIGINT. Number of times pressed = %d times.\n", ctrl_c_counter);
    write(STDOUT_FILENO, buffer, strlen(buffer));
    free(buffer);

}

void sigquit_handler(int signum) {

    char * buffer = malloc(BUFFER_SIZE);
    snprintf(buffer, BUFFER_SIZE, "Received SIGQUIT. Runtime = %d seconds.\n", seconds);
    write(STDOUT_FILENO, buffer, strlen(buffer));
    free(buffer);
    exit(0);

}

void sigalrm_handler(int signum) {

    char * buffer = strdup("Received SIGALRM.");
    write(STDOUT_FILENO, buffer, strlen(buffer));
    free(buffer);
    seconds++;
    alarm(1);

}

int main() {


    if (signal(SIGINT, sigint_handler) == SIG_ERR) {

        perror("sigint");
        exit(1);

    }

    if (signal(SIGQUIT, sigquit_handler) == SIG_ERR) {

        perror("sigint");
        exit(1);

    }

    if (signal(SIGALRM, sigalrm_handler) == SIG_ERR) {

        perror("sigint");
        exit(1);

    }


    alarm(1);

    while(1) 
        pause();

    return 0;

}