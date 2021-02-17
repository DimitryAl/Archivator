#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Wrong number of arguments!");
    }
    if (strcam(argv[1], "-a") == 0) {
        arc(argv[2], argv[3], 0);
    }
    if (strcam(argv[1], "-u") == 0) {
        unarc(argv[2], argv[3], 0);
    }
    if (strcam(argv[1], "-u") != 0 || (strcam(argv[1], "-a") != 0)) {
        printf("Wrong argument! Need -a or -u.");
    }
    return 0;
}