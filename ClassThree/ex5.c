#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char * argv[]) {

    for (int i = 1; i < argc; i++) 

        if (fork() == 0) {

            execlp(argv[i], argv[i], NULL);
            perror("execlp");
            _exit(i+1);

        }

    pid_t val;
    int status;

    for (int i = 1; i < argc; i++) {

        val = wait(&status);
        printf("Exec done.\n[PARENT] Child exited. Pid %d , Ending %d\n", val, WEXITSTATUS(status));

    }

    return 0;

}