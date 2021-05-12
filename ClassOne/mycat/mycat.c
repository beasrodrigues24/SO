#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_BUF 1024

int mycat(int fd_r) {

    int r = 0;
    ssize_t bytes_r, bytes_w;
    void * buf = malloc(MAX_BUF);

    // Reads from source and attempts to wirte
    while((bytes_r = read(fd_r, buf, MAX_BUF)) > 0) {

        bytes_w = write(STDOUT_FILENO, buf, MAX_BUF);
        // If nothing was written, notify error        
        if (!bytes_w)
            r = -1;

    }

    free(buf);

    return r;
}