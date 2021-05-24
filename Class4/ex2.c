#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    int input = open("/etc/passwd", O_RDONLY);
    int output = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int errors = open("errors.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    int std_input = dup2(input, STDIN_FILENO);
    int std_output = dup2(output, STDOUT_FILENO);
    int std_errors = dup2(errors, STDERR_FILENO);

    close(input);
    close(output);
    close(errors);

    if (fork() == 0) {

        char * test_string = malloc(15);
        strcpy(test_string, "TesteFilho");

        write(std_input ,test_string, strlen(test_string));
        write(std_output ,test_string, strlen(test_string));
        write(std_errors ,test_string, strlen(test_string));

        free(test_string);

    }
    else {

        int status;
        pid_t val;

        val = wait(&status);

        char * test_string = malloc(10);
        strcpy(test_string, "TestePai");

        write(std_input ,test_string, strlen(test_string));
        write(std_output ,test_string, strlen(test_string));
        write(std_errors ,test_string, strlen(test_string));

        free(test_string);

    }

    close(std_input);
    close(std_output);
    close(std_errors);

    return 0;

}