#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char cwd[1024];

    // 현재 작업 디렉터리 경로 가져오기
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    return 0;
}
