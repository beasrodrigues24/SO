#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define n_lines 5
#define n_columns 5000
#define max 5000

int main(int argc, char * argv[]) {  

    if (argc > 1) {

        pid_t val;
        int ** matriz;

        // Generates matrix
        matriz = (int **) malloc(sizeof(int *) * n_lines);

        for (int i = 0; i < n_lines; i++) {

            matriz[i] = malloc(sizeof(int) * n_columns);

            for (int j = 0; j < n_columns; j++) 
                matriz[i][j] = rand() % max;

        }

        // Searches
        int searched_num = atoi(argv[1]);
        int not_found = 1, i;
        for (i = 0; i < n_lines && not_found; i++) {

            if ((val = fork()) == 0) {

                // Searches line
                for (int j = 0; j < n_columns && not_found; j++)
                    if (matriz[i][j] == searched_num) 
                        not_found = 0;
                
                _exit(i+1);

            }

        }

        for (int l = 0; l < i; l++) {

            int status;
            val = wait(&status);
        }

        if (not_found) 
            printf("Found after %d iterations\n", i);
        

    }
    else 
        fprintf(stderr, "No number was inserted\n");


    return 0;

}