#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024

void pwd_command() {
    char cwd[MAX_INPUT_SIZE];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("getcwd");
    }
}

int main(int argc, char *argv[]) 
{
    pwd_command();
    return 0;
}
