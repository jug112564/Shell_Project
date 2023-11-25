#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [&]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int background = 0;

    // 마지막 인자가 "&"로 끝나면 백그라운드로 설정
    if (strcmp(argv[argc - 1], "&") == 0) {
        background = 1;
        argv[argc - 1] = NULL; // "&"는 명령에 포함되지 않도록 설정
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // 자식 프로세스
        // 백그라운드 실행이면 표준 출력, 표준 에러를 /dev/null로 리다이렉션
        if (background) {
            int devnull = open("/dev/null", O_WRONLY);
            dup2(devnull, STDOUT_FILENO);
            dup2(devnull, STDERR_FILENO);
            close(devnull);
        }

        execlp("./cat", "cat", "test.txt", NULL); // 프로그램 실행
        perror("execlp"); // execlp가 실패하면 에러 출력
        exit(EXIT_FAILURE);
    } else { // 부모 프로세스
        if (!background) {
            // 부모 프로세스는 자식 프로세스의 종료를 기다림
            waitpid(pid, NULL, 0);
        }
    }

    return 0;
}