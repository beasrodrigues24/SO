#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, const char * argv[]) {

    if (argc < 3) {

        perror("Lack arguments");
        exit(1);

    }

    int total_files = argc - 2;
    const char ** filenames = argv + 2;
    int pids[total_files];
    pid_t pid;

    for (int i = 0; i < total_files; i++) {

        if ((pid = fork()) == 0) {

            if (execlp("grep", "grep", argv[1], filenames[i], NULL) < 0) {

                perror("execlp");
                exit(1);

            }

        }

        pids[i] = pid;

    }

    int flag = 1;
    int status;

    while (flag && (pid = wait(&status))) 
        flag = WEXITSTATUS(status);

    if (flag) {

        perror("not found");
        exit(1);

    }

    for (int i = 0; i < total_files; i++) {

        if (pid != pids[i] && pids[i] > 0) {

            kill(pids[i], SIGKILL);
            
            if(waitpid(pids[i], &status, 0) > 0) {

                if(WIFEXITED(status)) 
                    printf("grep %d finished.\n", pids[i]);
                else 
                    printf("grep %d was killed.\n", pids[i]);
                
            }

        }

    }

    return 0;

}