#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024

void cd_command(char *path) {
    if (chdir(path) != 0) {
        perror("chdir");
    }
}

int main() {
    char input[MAX_INPUT_SIZE];

    while (1) {
        // 사용자 입력 받기
        printf("MyShell> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; // 입력이 더 이상 없으면 종료
        }

        // 개행 문자 제거
        input[strcspn(input, "\n")] = '\0';

        // 'exit' 명령을 입력하면 종료
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // 'cd' 명령어 처리
        if (strncmp(input, "cd", 2) == 0) {
            char *path = input + 3;  // 'cd ' 이후의 경로 추출
            cd_command(path);
        } else {
            // 다른 명령어 처리
            // (실제 프로그램에서는 fork와 exec를 사용하여 외부 명령어 실행이 필요)
            printf("Command not recognized: %s\n", input);
        }
    }

    return 0;
}
