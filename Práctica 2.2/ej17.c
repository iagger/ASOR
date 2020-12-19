#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc, char ** argv) {

    char* path = argv[1];

    struct stat dirStat;

    if (stat(path, &dirStat) == -1) {
        printf("ERROR %i -> %s\n", errno, strerror(errno));
    } else {

        DIR* dir = opendir(path);

        if (S_ISDIR(dirStat.st_mode)) {

            struct dirent *dirStream = readdir(dir);

            while (dirStream != NULL) {

                if (dirStream->d_type == DT_DIR) { // si es directorio
                    printf("%s/\n", dirStream->d_name);
                } else {

                    char* filePath = malloc((strlen(path) + strlen(dirStream->d_name) + 1)*sizeof(char));
                    strcpy(filePath, path); strcat(filePath, "/");  strcat(filePath, dirStream->d_name);

                    struct stat info;
                    if (stat(filePath, &info) == -1) {
                        printf("ERROR (%d -> %s) analizando los atributos del fichero %s", errno, strerror(errno), dirStream->d_name);
                    }

                    if (dirStream->d_type == DT_REG) { // si fichero regular

                        if (info.st_mode & S_IXUSR) { // si es ejecutable
                            printf("%s*\n", dirStream->d_name);
                        } else { // si no es ejecutable
                            printf("%s\n", dirStream->d_name);
                        }

                    }
                    else if (dirStream->d_type == DT_LNK) { // si enlace simbólico

                        char* linkBuf = malloc(sizeof(char)*(info.st_size)); // el enlace tendra el tamaño del fichero

                        if (readlink(filePath, linkBuf, strlen(linkBuf)) == -1) {
                            printf("ERROR (%d -> %s) obteniendo el enlace del fichero %s", errno, strerror(errno), dirStream->d_name);
                        } else {
                            printf("%s->%s\n", dirStream->d_name, linkBuf);
                        }

                        

                        free(linkBuf);
                    } 
                    
                    free(filePath);

                }

                dirStream = readdir(dir);
            }
            
            closedir(dir);

        }

    }

    return 1;

}