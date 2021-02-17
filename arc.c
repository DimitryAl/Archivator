#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int arc(char *filename, char *dirname, char *depth) {

    int arc_file = open(filename, O_WRONLY); //создаём файл для архива
    if (arc_file == -1) {
        printf("Can't create file!");
        return 1;
    }

    DIR *dir = opendir(dirname);    //открываем каталог и формируем его поток
    if (dir == NULL) {
        printf("Can't open directory!");
        return 2;
    }
    chdir(dir);                 //Переходим в директорию

    struct dirent *read_dir;
    struct stat statbuf;
    
    read_dir = readdir(dir);
    while (read_dir != NULL) {
        lstat(read_dir->d_name, &statbuf);
        if (S_ISDIR(statbuf.st_mode)) {
            if (strcmp(".", read_dir->d_name) == 0 || strcmp("..", read_dir->d_name) == 0) continue;
            arc(".tempttar", *read_dir->d_name, depth+1);
            add_to_arc(read_dir->d_name, arc_file, depth+1, read_dir->d_name);
            remove(".tempttar");
        }
        else add_to_arc(read_dir->d_name, arc_file, depth, "");
        read_dir = readdir(dir);
    }
    chdir("..");
    closedir(dir);
    if (close(arc_file) == -1) {
        return 3;
    }
    return 0;
}