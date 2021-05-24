#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "readln.h"
#include <sys/types.h>

#define MAX_BUF 1024

int mynl(int fd) {

    int r = 0;
    ssize_t count = 1;
    size_t bytes_r, bytes_w, line_r;
    void * buf = malloc(MAX_BUF);

    while ((bytes_r = read(fd, buf, MAX_BUF)) > 0 && !r) {
            
        // Checks how many bytes in one line
        line_r = readln(fd, buf, bytes_r);
        // Variable that says how much was already re-read and written
        ssize_t already_read = 0;
        while (line_r > 1 && !r) {
            
            // Write number in a string and write in destine
            void * nbr = malloc(MAX_BUF); 
            sprintf(nbr, "\t%zu: ", count);
            bytes_w = write(STDOUT_FILENO, nbr, sizeof(nbr));

            if (bytes_w <= 0) r = -1;

            // Writes the content of the line
            bytes_w = write(STDOUT_FILENO, buf + already_read, line_r);
            if (bytes_w <= 0) r = -1;

            // Updates what was already written
            already_read += line_r;
            count++;

            // Reads another line
            line_r = readln(fd, buf + already_read, bytes_r - already_read);

            free(nbr);
        }

    }
    
    free(buf);

    return r;

}