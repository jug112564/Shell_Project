/*
 * 20183063 이호준
 * 파일 이름: my_interrupt.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// SIGINT (Ctrl-C) 시그널 핸들러
void sigint_handler(int signo) {
    printf("\nCaught SIGINT (Ctrl-C)\n");
    // 여기에서 추가적인 동작을 수행할 수 있습니다.
}

// SIGQUIT (Ctrl-Z) 시그널 핸들러
void sigquit_handler(int signo) {
    printf("\nCaught SIGQUIT (Ctrl-Z)\n");
    // 여기에서 추가적인 동작을 수행할 수 있습니다.
}

int main() {
    // SIGINT 시그널 핸들러 등록
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("signal(SIGINT) error");
        exit(EXIT_FAILURE);
    }

    // SIGQUIT 시그널 핸들러 등록
    if (signal(SIGQUIT, sigquit_handler) == SIG_ERR) {
        perror("signal(SIGQUIT) error");
        exit(EXIT_FAILURE);
    }

    // 프로그램이 계속 실행되도록 무한 루프
    while (1) {
        printf("Running...\n");
        sleep(1);
    }

    return 0;
}
