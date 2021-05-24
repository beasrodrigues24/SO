#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char * argv[]) {

    if (argc > 4 && !strcmp(argv[1], "-i") && !strcmp(argv[3], "-o")) {

        int input_fd, output_fd;

        input_fd = open(argv[2], O_RDONLY);

        if (input_fd >= 0) {
            
            output_fd = open(argv[4],  O_WRONLY | O_CREAT | O_TRUNC, 0644);

            if (output_fd >= 0) {

                argv[argc] = NULL;

                dup2(input_fd, STDIN_FILENO);
                dup2(output_fd, STDOUT_FILENO);

                close(input_fd);
                close(output_fd);

                if (fork() == 0) {

                    execvp(argv[5], argv + 5);
                    _exit(1);

                }
                else 
                    wait(NULL);

            }
            else {

                perror("Open");
                exit(1);

            }

        }
        else {

            perror("Open");
            exit(1);

        }

    }
    else 
        exit(1);

    return 0;

}