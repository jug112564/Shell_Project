#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    DIR *directory;
    struct dirent *entry;

    // 현재 디렉터리 열기
    directory = opendir(".");

    if (directory == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    // 디렉터리 내용 출력
    while ((entry = readdir(directory)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // 디렉터리 닫기
    closedir(directory);

    return 0;
}
