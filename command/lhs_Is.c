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

int main(int argc, char *argv[]) 
{
    ls_command();

    return 0;
}
