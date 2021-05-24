#include "mycat.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char * argv[]) {

    int r;
    int fd_r;

    // Checks if there are enough arguments
    if (argc > 1) {

        fd_r = open(argv[1], O_RDONLY);
        if (fd_r >= 0) {

            r = mycat(fd_r);
            if (!r) 
                perror("Error in mycat");

            close(fd_r);

        }
        else 
            perror("Error opening source file");
    }


    return 0;

}