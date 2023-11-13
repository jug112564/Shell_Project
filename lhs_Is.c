#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    if (execlp("ls", "ls", (char *)NULL) == -1) {
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    return 0;
}
