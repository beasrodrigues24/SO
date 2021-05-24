#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char * argv[]) { 

    pid_t val;

    if ((val = fork()) == 0) {

        printf("[CHILD] => PID: %d\n", getpid());
        printf("[CHILD] => Parent PID: %d\n", getppid());
        _exit(0);

    }
    else {

        printf("[PARENT] => PID: %d\n", getpid());
        printf("[PARENT] => Parent PID: %d\n", getppid());

        int status;
        val = wait(&status);
        printf("[PARENT] => Child PID: %d . Ending: %d\n", val, WEXITSTATUS(status));
        
    }

    return 0;

}