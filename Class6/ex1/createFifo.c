#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


int main() {

    if(mkfifo("fifo", 0644) < 0) {

        perror("mkfifo");
        exit(1);

    }
    
    return 0;
    
}