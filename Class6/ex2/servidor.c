#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FIFO_NAME "fifo"
#define BUFFER_SIZE 1024

int main() {

    if (mkfifo(FIFO_NAME, 0644) < 0) {

        perror("mkfifo");
        exit(1);

    }

    int fd_log = open("log.txt", O_CREAT | O_APPEND | O_WRONLY, 0644);
    if (fd_log == -1) {

        perror("open");
        exit(1);

    }

    ssize_t bytes_read;
    

    int fd_fifo;
    while((fd_fifo = open(FIFO_NAME, O_RDONLY)) > 0) {

        char * buffer = malloc(sizeof(char) * BUFFER_SIZE);
        while ((bytes_read = read(fd_fifo, buffer, BUFFER_SIZE)) > 0) {


            if (write(fd_log, buffer, bytes_read) <= 0) {

                perror("write");
                exit(1);

            }

        }

        close(fd_fifo);
        free(buffer);

    }

    close(fd_log);
    

    return 0;

}
