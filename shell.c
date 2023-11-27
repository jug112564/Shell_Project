//기본 라이브러리
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

//커스텀 라이브러리
#include "shell_functions/exit.c"
#include "shell_functions/my_interrupt.c"
#include "shell_functions/shellutil.c"

void main(int argc, char *argv[])
{
    // SIGINT 시그널 핸들러 등록
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("signal(SIGINT) error");
        exit(EXIT_FAILURE);
    }

    // SIGTSTP 시그널 핸들러 등록
    if (signal(SIGTSTP, sigtstp_handler) == SIG_ERR) {
        perror("signal(SIGTSTP) error");
        exit(EXIT_FAILURE);
    }

    printf("shell project program\n");
    while(1)
    {
        char input[100];
        printf("> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0)
        {
            ShellExit();
        }
        else if (strstr(input, "|") != NULL) 
        {
            // '|' 문자가 포함되어 있으면 파이프 실행
            execute_piped_commands(input);
        } 
        else
        {
            // 단일 명령어 실행
            char *args[10];
            tokenize_command(input, args);
        }
    }
    
}