#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

void main(int argc, char *argv[])
{
    struct stat buf;
    char *file_name;

    //check arg count
    if (argc < 2) {
        fprintf(stderr, "Usage: rm file_name\n");
        exit(1);
    }
    else{
        file_name=argv[1];
    }

    if (lstat(argv[1], &buf) < 0) {
        perror("lstat error");
    }

    //check access
    if (access(argv[1], F_OK) < 0) {
        fprintf(stderr, "rm : cannot remove '%s' : No such file or directory\n", argv[1]);
        exit(1);
    }

    //check directory
    if(S_ISDIR(buf.st_mode)){
        fprintf(stderr, "rm : cannot remove '%s' : Is a directory\n", argv[1]);
        exit(1);
    }

    //remove file
    if(remove(file_name)<0){
        perror("remove");
        exit(1);
    }
}

