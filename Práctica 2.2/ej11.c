#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

const char* hardExt = ".hard";
const char* symExt = ".sym";

int main(int argc, char** argv) {

    char* path = argv[1];

    struct stat buf;

    if (stat(path, &buf) == -1) {
        printf("ERROR %i -> %s\n", errno, strerror(errno));
    } else {
        if (S_ISREG(buf.st_mode)) {

            char* hardPath = malloc(sizeof(char)*(strlen(path) + strlen(hardExt)));
            char* symPath = malloc(sizeof(char)*(strlen(path) + strlen(symExt)));

            hardPath = strcat(strcpy(hardPath, path), hardExt);
            symPath = strcat(strcpy(symPath, path), symExt);

            if (link(path, hardPath) == -1) {
                printf("ERROR (%i) CREANDO ENLACE RÍGIDO -> %s\n", errno, strerror(errno));
            } else {
                printf("CREADO ENLACE RÍGIDO -> %s\n", hardPath);
            }
            if (symlink(path, symPath) == -1) {
                printf("ERROR (%i) CREANDO ENLACE SIMBÓLICO -> %s\n", errno, strerror(errno));
            } else {
                printf("CREADO ENLACE SIMBÓLICO -> %s\n", symPath);
            }

            free(hardPath);
            free(symPath);
        }
    } 

    return 1;
}