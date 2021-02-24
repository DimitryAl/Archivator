//архивируем 
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

//#define MAX_NAME_LENGTH = 100
//#define BLOCK_SIZE = 512

int add_to_arc(char *temp_name, int arc_file, int depth, char *d_name) {

    struct stat stats;
    long int size;

    int temp_file = open(temp_name, O_RDONLY);
    if (temp_file == -1) {
        printf("Can't open file");
        return 1;
    } 
    lstat(temp_name, &stats);
    size = stats.st_size;

    if (strcmp("", d_name) == 0)	{
		if (write(arc_file, temp_name, 100) != 100)	//Запись имени
			perror("");
	}	else
		write(arc_file, d_name, 100);	
    write(arc_file, &size, sizeof(long));	//Запись размера файла
	write(arc_file, &depth, sizeof(int));	//Запись глубины залегания файла
	char a = 0;
	for (int i = 0; i < 512-100 - sizeof(int) - sizeof(long); i++)
		write(arc_file, &a, 1);	
    //Блоки данных
	unsigned char block[512];
	int count = read(temp_file, block, 512);
	while (count == 512) {
		write(arc_file, block, 512);
		count = read(temp_file, block, 512);
	}
	if (count != 0)	{
		write(arc_file, block, count);
		for (int i = 0; i < 512 - count; i++)	//Дописываем блок до BLOCK_SIZE байт
			write(arc_file, &a, 1);
	}
	close(temp_file);
	return 0;

}

int arc(char *filename, char *dirname, char depth) {

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
            arc(".tempttar", read_dir->d_name, depth+1);
            add_to_arc(".tempttar", arc_file, depth+1, read_dir->d_name);
            remove(".tempttar");
        }
	//Блок з
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