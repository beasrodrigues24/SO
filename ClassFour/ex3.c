#include <fcntl.h>
#include <unistd.h>

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

    /*
        Reading and Writing
    */

    execlp("wc", "wc", NULL);
    _exit(1);

    close(std_input);
    close(std_output);
    close(std_errors);

    return 0;

}