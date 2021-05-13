#include "mynl.h"
#include "readln.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, const char * argv[]) {

    int fd, r;

    if (argc > 1) 
        fd = open(argv[1], O_RDONLY);
    else 
        fd = 0;

    if (fd >= 0) {

        r = mynl(fd);
        if (r) 
            perror("Error in mynl");

        close(fd);

    }
    else 
        perror("Error opening source");

    return 0;
}

