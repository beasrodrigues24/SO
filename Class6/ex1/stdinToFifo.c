#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024

int main() {
    
    int fd = open("fifo", O_WRONLY, 0644);
    if (fd == -1) {

        perror("open");
        exit(1);

    }

    ssize_t bytes_read;
    char * buffer = malloc(sizeof(char) * BUFFER_SIZE);

    while ((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) 
        write(fd, buffer, bytes_read);

    close(fd);
    free(buffer);

    return 0;
}