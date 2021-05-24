#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 10

int main(int argc, char * argv[]) { 

    pid_t val;

    for (int i = 0; i < N; i++) {

        if ((val = fork()) == 0) {

            printf("[CHILD] => PID: %d\n", getpid());
            printf("[CHILD] => Parent PID: %d\n", getppid());
            
        }
        else {

            int status;
            val = wait(&status);
            printf("[PARENT] => PID: %d\n", getpid());
            printf("[PARENT] => Child PID: %d . Ending: %d\n", val, WEXITSTATUS(status));            
            _exit(i);
        }

    }

    _exit(N);

    return 0;

}