#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FIFO_NAME "fifo"
#define BUFFER_SIZE 1024

int main(int argc, char * argv[]) {

    if (argc > 1) {

        int fd_fifo = open("fifo", O_WRONLY, 0666);
        if (fd_fifo == -1) {

            perror("fifo");
            exit(1);

        }

        if (write(fd_fifo, argv[1], strlen(argv[1])) <= 0) {
            
            perror("write");
            exit(1);
            
        }

        close(fd_fifo);

    }

    return 0;

}