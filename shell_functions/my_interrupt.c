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
    exit(0);
}

// SIGTSTP (Ctrl-Z) 시그널 핸들러
void sigtstp_handler(int signo) {
    printf("\nCaught SIGTSTP (Ctrl-Z)\n");
    // 여기에서 추가적인 동작을 수행할 수 있습니다.

    raise(SIGSTOP);
}
