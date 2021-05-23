#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024

int servidor() {

    int fd_log = open("log.txt", O_TRUNC | O_WRONLY, 0666);
    if (fd_log == -1) {

        perror("open");
        exit(1);

    }

    ssize_t bytes_read, bytes_written;
    char * buffer = malloc(sizeof(char) * BUFFER_SIZE);

    int fd_fifo;
    while((fd_fifo = open("fifo", O_RDONLY))) {

        while ((bytes_read = read(fd_fifo, buffer, BUFFER_SIZE) > 0))
            if ((bytes_written = write(fd_log, buffer, bytes_read)) <= 0) {

                perror("write");
                exit(1);

            }

        close(fd_fifo);

    }

    close(fd_log);
    free(buffer);

    return 0;

}

int main() {

    if (mkfifo("fifo", 0666) < 0) {

        perror("fifo");
        exit(1);

    }

    servidor();
    return 0;

}