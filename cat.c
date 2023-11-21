#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_BUF 2048

int main(int argc, char*argv[])
{
    int fd, read_len, write_len;
    char buf[MAX_BUF];

    if(argc!=2){
        fprintf(stderr, "Usage: cat file_name\n");
        exit(1);
    }

    fd = open(argv[1], O_RDONLY);
    if(fd<0){
        perror("cat:");
        exit(1);
    }

    while(1){
        read_len = read(fd, buf, MAX_BUF);
        if(read_len==0){ 
            break;
        }
        write_len=write(STDOUT_FILENO,buf,read_len);
    }
    close(fd);
    return 0;
}
