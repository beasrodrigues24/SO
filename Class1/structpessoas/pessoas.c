#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "pessoas.h"

int new_person (char * name, int age) {
    int r;

    Person p;
    strcpy(p.name, name);
    p.age = age;

    int fd = open(FILENAME, O_CREAT | O_APPEND | O_WRONLY, 0600);

    if (fd >= 0) {
        int written = write(fd, &p, sizeof(Person));

        if (written == sizeof(Person)) {

            r = lseek(fd, -sizeof(Person), SEEK_CUR);
            if (r < 0) 
                perror("Error using lseek");

        }
        else {

            perror("Error in adding new person");
            r = -1;

        }

        fd = close(fd);
        if (fd == -1) {

            perror("Error closing file");
            r = -1;

        }

    }
    else {

        perror("Error in accessing file");
        r = -1;
        
    }

    return r;
}

int person_change_age (char * name, int age) {

    Person person;
    int r = 1;

    int fd = open(FILENAME, O_CREAT | O_RDWR, 0644);

    if (fd >= 0) {

        while (read(fd, &person, sizeof(Person))) {

            if (!(strcmp(person.name, name))) {

                int pos = lseek(fd, -sizeof(Person), SEEK_CUR);
                if (pos >= 0) {
                    
                    person.age = age;
                    int written = write(fd, &person, sizeof(Person));
                    if (written != sizeof(Person)) {
                        perror("Error writting");
                        r = -1;
                    }
                    else 
                        r = 0;

                }
                else {
                    perror("Error in lseek");
                    r = -1;
                }

            }

        }

        fd = close(fd);
        if (fd == -1) {
            perror("Error closing file");
            r = -1;
        }

    }
    else {
        perror("Error in accessing file");
        r = -1;
    }

    return r;
}

int person_change_age_v2(long pos, int age) {

    long r = 0;
    int fd = open(FILENAME, O_CREAT | O_WRONLY, 0600);
    
    if (fd >= 0) {
        pos += 200;
        r = lseek(fd, pos, SEEK_SET);
        printf("%lu\n", r);
        if (r == pos) {

            int written = write(fd, &age, sizeof(int));
            if (written != sizeof(int)) {
                perror("Error writting new age");
                r = -1;
            } 
            else 
                r = 0;

        }
        else {
            perror("Error in lseek");
            r = -1;
        }

        fd = close(fd);
        if (fd == -1) {
            perror("Error closing file");
            r = -1;
        }

    }
    else {
        perror("Error in accessing file");
        r = -1;
    }

    return r;  
}
