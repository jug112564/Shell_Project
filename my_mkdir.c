#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


int main(int argc, char *argv[]) 
{

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <path name>\n", argv[0]);
        exit(1);
    }


    if (mkdir(argv[1], 0755) < 0)
    {
        perror("mkdir");
        exit(1);
    }

}