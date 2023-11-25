#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define MAX_BUF 2048

int main(int argc, char* argv[]) {
    int fd, read_len, write_len;
    char buf[MAX_BUF];

    if (argc != 2 && argc != 4) {
        fprintf(stderr, "Usage: %s file_name [> >> <]\n", argv[0]);
        exit(1);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("cat:");
        exit(1);
    }

    if (argc == 4) {
        if (strcmp(argv[3], ">") == 0) {
            // 덮어쓰기
            int out_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            if (out_fd < 0) {
                perror("open:");
                exit(1);
            }
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        } else if (strcmp(argv[3], ">>") == 0) {
            // 추가하기
            int out_fd = open(argv[2], O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            if (out_fd < 0) {
                perror("open:");
                exit(1);
            }
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        } else if (strcmp(argv[3], "<") == 0) {
            // 입력
            close(fd);
            fd = open(argv[2], O_RDONLY);
            if (fd < 0) {
                perror("open:");
                exit(1);
            }
        }
    }

    while (1) {
        read_len = read(fd, buf, MAX_BUF);
        if (read_len == 0) {
            break;
        }
        write_len = write(STDOUT_FILENO, buf, read_len);
    }

    close(fd);
    return 0;
}