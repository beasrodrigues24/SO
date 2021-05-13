#include <sys/types.h>

ssize_t readln(int fd, char * line, size_t size) {

    size_t i;

    for (i = 0; i < size && line[i] != '\n'; i++);

    return i + 1;

}