//shellutil : 명령어 실행 관련 함수 모음
//파일재지향 지원
//파이프 지원
//백그라운드 실행 지원

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int is_background(char **args) {
    int i = 0;
    while (args[i] != NULL) {
        if (strcmp(args[i], "&") == 0) {
            args[i] = NULL;  // "&"를 인식하고 해당 위치를 NULL로 변경
            return 1;
        }
        i++;
    }
    return 0;
}


void execute_command(char **args, int input_fd, int output_fd, int in_background) {
    pid_t child_pid;

    if ((child_pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // 자식 프로세스

        // 표준 입력을 input_fd로 변경
        if (input_fd != STDIN_FILENO) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }

        // 표준 출력을 output_fd로 변경
        if (output_fd != STDOUT_FILENO) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }

        // execvp로 명령어 실행
        if(strcmp(args[0],"ls")==0)
        {
            execvp("./command/ls", args);
        }
        else if(strcmp(args[0],"pwd")==0)
        {
            execvp("./command/pwd", args);
        }
        else if(strcmp(args[0],"cd")==0)
        {
            execvp("./command/cd", args);
        }
        else if(strcmp(args[0],"mkdir")==0)
        {
            execvp("./command/mkdir", args);
        }
        else if(strcmp(args[0],"rmdir")==0)
        {
            execvp("./command/rmdir", args);
        }
        else if(strcmp(args[0],"ln")==0)
        {
            execvp("./command/ln", args);
        }
        else if(strcmp(args[0],"cp")==0)
        {
            execvp("./command/cp", args);
        }
        else if(strcmp(args[0],"rm")==0)
        {
            execvp("./command/rm", args);
        }
        else if(strcmp(args[0],"mv")==0)
        {
            execvp("./command/mv", args);
        }
        else if(strcmp(args[0],"cat")==0)
        {
            execvp("./command/cat", args);
        }
        else
        {
            printf("Command '%s' not found.\n",args[0]);
        }
        exit(EXIT_FAILURE);
    } else {
        // 부모 프로세스에서는 자식 프로세스의 종료를 기다리거나 백그라운드 실행 여부 확인
        if (!in_background) {
            waitpid(child_pid, NULL, 0);  // 백그라운드 실행이 아니면 기다림
        } else {
            // 백그라운드 실행이면 사용자에게 프롬프트 제공 후 루프 재진입
            printf("Background process started with PID %d\n", child_pid);
        }
    }
}

void tokenize_command(char *command, char **args) {
    char *token = strtok(command, " ");
    int arg_count = 0;

    while (token != NULL) {
        args[arg_count++] = token;

        // 최대 10개의 인자까지만 처리
        if (arg_count >= 10) {
            break;
        }

        token = strtok(NULL, " ");
    }

    // 마지막에는 NULL로 배열을 종료
    args[arg_count] = NULL;

        // 파일 재지향을 위한 변수
    int input_redirect = 0;
    int output_redirect = 0;
    char *input_file = NULL;
    char *output_file = NULL;

    for (int i = 0; i < arg_count; ++i) {
        if (strcmp(args[i], "<") == 0) {
            // 입력 재지향
            input_redirect = 1;
            input_file = args[i + 1];
            args[i] = NULL;  // < 를 기준으로 명령어와 파일명을 분리
        } else if (strcmp(args[i], ">") == 0) {
            // 출력 재지향
            output_redirect = 1;
            output_file = args[i + 1];
            args[i] = NULL;  // > 를 기준으로 명령어와 파일명을 분리
        }
    }

    int in_background = is_background(args);
    
    // 파일 재지향 처리
    if (input_redirect) {
        int input_fd = open(input_file, O_RDONLY);
        if (input_fd == -1) {
            perror("open input file");
        }
        execute_command(args, input_fd, STDOUT_FILENO,in_background);
        close(input_fd);
    } else if (output_redirect) {
        int output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if (output_fd == -1) {
            perror("open output file");
        }
        execute_command(args, STDIN_FILENO, output_fd,in_background);
        close(output_fd);
    } else {
        // 일반적인 명령어 실행
        execute_command(args, STDIN_FILENO, STDOUT_FILENO,in_background);
    }
}

void execute_piped_commands(char *input) {
    char *token = strtok(input, "|");
    char *commands[2];  // 두 개의 명령어를 저장하는 배열

    int i = 0;
    while (token != NULL) {
        commands[i++] = token;
        token = strtok(NULL, "|");
    }

    // 파이프 생성
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // 첫 번째 명령어 실행
    char *args1[10];
    tokenize_command(commands[0], args1);
    int in_background1 = is_background(args1);
    execute_command(args1, STDIN_FILENO, pipe_fd[1],in_background1);  // 표준 출력을 파이프에 연결

    // 두 번째 명령어 실행
    char *args2[10];
    tokenize_command(commands[1], args2);
    int in_background2 = is_background(args2);

    // 부모 프로세스에서는 파이프 닫기
    close(pipe_fd[0]);
    close(pipe_fd[1]);
}