#include "mycp.h"
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char * argv[]) {

    int r;
    int fd_r, fd_w;
    
    // Checks for the necessary arguments
    if (argc > 2) {

        // Opens source file descriptor 
        fd_r = open(argv[1], O_RDONLY);
        // Checks if opening was successful
        if (fd_r >= 0) {

            // Opens destined file descriptor
            fd_w = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0640);
            // Checks if opening was successful
            if (fd_w >= 0) {

                // Copies from source to destine
                r = mycp(fd_r, fd_w);
                if (r) 
                    perror("Error in mycp");
                
                close(fd_w);

            }
            else 
                perror("Opening destined file error");

            close(fd_r);

        }
        else 
            perror("Opening source file error");

    }
    else 
        perror("No input");


    return 0;

}