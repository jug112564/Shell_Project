//pipe.c
//병합전이라 예시만 구현

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) 
{
    int pipe_fd[2];
    pid_t child_pid;

    // 파이프 생성
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // 자식 프로세스 생성
    if ((child_pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // 자식 프로세스
        close(pipe_fd[1]);  // 쓰기용 파이프 닫음
        dup2(pipe_fd[0], STDIN_FILENO);  // 표준 입력을 파이프로 변경

        // cat_exec 실행
        execlp("./cat", "cat", "test.txt", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // 부모 프로세스
        close(pipe_fd[0]);  // 읽기용 파이프 닫음
        dup2(pipe_fd[1], STDOUT_FILENO);  // 표준 출력을 파이프로 변경

        // mv_exec 실행
        execlp("./mv", "mv", "test.txt", "test123.txt", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    return 0;
}