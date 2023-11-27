#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024

void cd_command(char *path) {
    if (chdir(path) != 0) {
        perror("chdir");
    }
}

int main(int argc, char *argv[]) {

    if(argc==1)
        cd_command("..");
    else
        cd_command(argv[1]);

    return 0;
}
