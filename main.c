#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "arc.c"
#include "unarc.c"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Wrong number of arguments!");
    }
    if (strcmp(argv[1], "-a") == 0) {
        arc(argv[2], argv[3], 0);
    }
    if (strcmp(argv[1], "-u") == 0) {
        unarc(argv[2], argv[3], 0);
    }
    if (strcmp(argv[1], "-u") != 0 || (strcmp(argv[1], "-a") != 0)) {
        printf("Wrong argument! Need -a or -u.");
    }
    return 0;
}