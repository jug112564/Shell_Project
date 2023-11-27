#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

void main(int argc, char *argv[])
{
    struct stat buf;

    if (argc < 3) {
        fprintf(stderr, "Usage: mv src target\n");
        exit(1);
    }

    if (access(argv[1], F_OK) < 0) {
        fprintf(stderr, "mv: cannot stat '%s': No such file or directory\n", argv[1]);
        exit(1);
    }


    if (access(argv[2], F_OK) == 0) {
        if (lstat(argv[2], &buf) < 0) {
            perror("lstat");
            exit(1);
        }
    }

    if (rename(argv[1], argv[2]) < 0) {
        perror("rename");
        exit(1);
    }
}