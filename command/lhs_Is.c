#include <stdio.h>
#include <dirent.h>

void ls_command() {
    DIR *directory;
    struct dirent *entry;

    directory = opendir(".");

    if (directory == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(directory)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(directory);
}

int main() {
    char input[100];

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

        // 'Is' 명령어 처리
        if (strcmp(input, "Is") == 0) {
            ls_command();
        } else {
            // 다른 명령어 처리
            // (실제 프로그램에서는 fork와 exec를 사용하여 외부 명령어 실행이 필요)
            printf("Command not recognized: %s\n", input);
        }
    }

    return 0;
}
