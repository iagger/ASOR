#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/sysmacros.h>
#include <stdio.h>
#include <time.h>

// man 2 stat

int main(int argc, char** argv) {

    char* file = argv[1];
    struct stat buf;

    if (stat(file, &buf) == -1) {
        printf("ERROR %i -> %s\n", errno, strerror(errno));
    } else {
        printf("MAJOR -> %i\n", major(buf.st_dev));
        printf("MINOR -> %i\n", minor(buf.st_dev));
        printf("INODE -> %i\n", buf.st_ino);
        
        if (S_ISLNK(buf.st_mode)) { printf("FILE TYPE -> link\n");    }
        if (S_ISDIR(buf.st_mode)) { printf("FILE TYPE -> dir \n");    }
        if (S_ISREG(buf.st_mode)) { printf("FILE TYPE -> regf\n");    }


        struct tm *tma = localtime(&(buf.st_atime));
        printf("ACCESS -> %d/%d/%d  %d:%d\n", tma->tm_mday, tma->tm_mon +1, tma->tm_year +1900, tma->tm_hour, tma->tm_min);

        struct tm *tmm = localtime(&(buf.st_atime));
        printf("MODIFICATION -> %d/%d/%d  %d:%d\n", tmm->tm_mday, tmm->tm_mon +1, tmm->tm_year +1900, tma->tm_hour, tmm->tm_min);
    }

    return 1;
}

