#include <unistd.h>

int main() {

    execl("/bin/ls", "ls", "-l", NULL);
    return 0;
    
}