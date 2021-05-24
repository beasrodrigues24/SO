#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include "pessoas.h"
#include <string.h>
#include <time.h>

#define MAX_BUFFER 1024

int isNumber (char * string) {


    int digit = 1;
    
    for (int i = 0; string[i] && digit; i++) 
        digit = (string[i] > 47 && string[i] < 58);

    

    return digit;
}


int main(int argc, char * argv[]) {

    if (argc == 4) {

        char * buffer = malloc(MAX_BUFFER);

        time_t t = clock();

        if (!(strcmp(argv[1], "-i"))) {

            int pos = new_person(argv[2], atoi(argv[3]));
            printf("register %d\n", pos);

        }
        else if (!(strcmp(argv[1], "-u"))) {

            int n_inserted;

            if (isNumber(argv[2])) {
                
                n_inserted = person_change_age_v2(atol(argv[2]), atoi(argv[3])); 
                if (n_inserted) 
                    perror("Problem changing age (version 2)");   
            }
            else {

                n_inserted = person_change_age(argv[2], atoi(argv[3]));
                if (n_inserted) 
                    perror("Problem changing age (version 1)");
            }
        }

        t = clock() - t;

        sprintf(buffer, "Time elapsed %lu\n", t);

        free(buffer);
        
    }
    else 
        perror("Lack of arguments");
    

    return 0;
}