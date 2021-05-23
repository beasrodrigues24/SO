#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char * argv[]) {

    printf("Parent: %d\n", getppid());
    printf("PID: %d\n", getpid());
    return 0;

}