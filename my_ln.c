/*
 * 20183063 이호준
 * 파일 이름: my_ln.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char cmd;
    char *src;
    char *target;
    if (argc < 3)
    {
        fprintf(stderr, "Usage: my_ln [l,u,s] ...\n");
        fprintf(stderr, " my_ln l[ink] src target\n");
        fprintf(stderr, " my_ln u[nlink] filename\n");
        fprintf(stderr, " my_ln s[ymlink] src target\n");
        exit(1);
    }
    cmd = (char)*argv[1];
    if (cmd == 'l') //하드링크 모드
    {
        if (argc < 4)
        {
            fprintf(stderr, "my_ln l src target [link]\n");
            exit(1);
        }
        src = argv[2];
        target = argv[3];
        if (link(src, target) < 0)
        {
            perror("link");
            exit(1);
        }
    }
    else if (cmd == 's') //소프트링크 모드
    {
        if (argc < 4)
        {
            fprintf(stderr, "my_ln l src target [link]\n");
            exit(1);
        }
        src = argv[2];
        target = argv[3];
        if (symlink(src, target) < 0)
        {
            perror("symlink");
            exit(1);
        }
    }
    else if (cmd == 'u') //삭제 모드
    {
        src = argv[2];
        if (unlink(src) < 0)
        {
            perror("unlink");
            exit(1);
        }
    }
    else
    {
        fprintf(stderr, "Unknown command...\n");
    }
}
