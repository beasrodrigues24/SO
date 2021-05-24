#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024

int createFIFO() {

    if(mkfifo("fifo", 0666) < 0) {

        perror("mkfifo");
        exit(1);

    }
    
    return 0;

}

int stdinToFIFO() {

    int fd = open("fifo", O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

int FIFOtoStdout() {

    int fd = open("fifo", O_RDONLY);
    if (fd == -1) {

        perror("open");
        exit(1);

    }

    ssize_t bytes_read;
    char * buffer = malloc(sizeof(char) * BUFFER_SIZE);

    while((bytes_read = read(fd, buffer, BUFFER_SIZE)))
        write(STDOUT_FILENO, buffer, bytes_read);

    close(fd);
    free(buffer);

    return 0;

}


int main() {

    int ret;

    ret = createFIFO();
    if (!ret) printf("FIFO successfully created\n");
    ret = stdinToFIFO();
    ret = FIFOtoStdout();

    return 0;

}