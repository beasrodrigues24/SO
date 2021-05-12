#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <stdlib.h>
#include <sys/types.h>

#define MAX_BUF 1024

int mycp(int fd_r, int fd_w) {

    int r = 0;
    ssize_t bytes_r, bytes_w;
    void * buffer = malloc(MAX_BUF);

    // Reads from the source and attempts to write
    while ((bytes_r = read(fd_r, buffer, MAX_BUF)) && !r) {
        
        bytes_w = write(fd_w, buffer, bytes_r);
        // If nothing was written, notify error
        if (!bytes_w) r = -1;
        
    }

    return r;

}

