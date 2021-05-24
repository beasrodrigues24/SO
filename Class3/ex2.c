#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    pid_t val;

    if (fork() == 0) {

        execl("/bin/ls", "ls", "-l", NULL);
        perror("exec");
        _exit(0);

    }
    else {

        int status;
        val = wait(&status);
        printf("Exec done.\n[PARENT] Child exited. Pid %d , Ending %d\n", val, WEXITSTATUS(status));

    }

    return 0;

}