#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define N 100

int my_system(char * command) {

    char * argument;
    char * argv[N];
    int i = 0;

    argv[i++] = strdup(strtok(command, " "));
    while((argument = strtok(NULL, " ")))
        argv[i++] = strdup(argument);
    argv[i] = NULL;

    if (fork() == 0) {

        execvp(argv[0], argv);
        perror("execlp");
        _exit(0);

    }
    else {
        
        pid_t val;
        int status;
        val = wait(&status);

        printf("[PARENTS] Child pid: %d ; Child ending: %d\n", val, WEXITSTATUS(status));

    }

    return 0;
}

int main(int argc, char * argv[]) {

    if (argc > 1) 
        my_system(argv[1]);

    return 0;

}