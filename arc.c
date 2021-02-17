#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int arc(char *filename, char *dirname, char *depth) {

    int new_file = open(filename, O_WRONLY); //create файл для  архива

    if (new_file == -1) {
        printf("Can't create file!");
        return 1;
    }

    DIR *dir = opendir(dirname);

    return 0;
}