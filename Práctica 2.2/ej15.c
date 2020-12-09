#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char ** argv) {

    int file;
    if ((file = open(argv[1], O_CREAT | O_RDWR, 0777)) == -1) {
        printf("ERROR %i -> %s.\n", errno, strerror(errno));
    }

    // man 2 fcntl

    // struct flock = { l_type, l_whence, l_start, l_len, l_pid }
    struct flock cerrojo = {    F_WRLCK, SEEK_SET, 0, 0, getpid()   };

    if (fcntl(file, F_GETLK, &cerrojo) == -1) {
        printf("ERROR al comprobar el cerrojo -> %i : %s.\n", errno, strerror(errno));
        //return -1;
    }

    if (cerrojo.l_type == F_UNLCK) {

        printf("El cerrojo del fichero %s está DESBLOQUEADO.\n", argv[1]);

        cerrojo.l_type = F_WRLCK;

        if (fcntl(file, F_SETLK, &cerrojo) == -1) {
            printf("ERROR al crear el cerrojo -> %i : %s.\n", errno, strerror(errno));
        }
        else {

            char* c;
            time_t t = time(NULL);
            struct tm *tma = localtime(&(t));
            asprintf(&c, "HORA %d/%d/%d  %d:%d:%d\n", tma->tm_mday, tma->tm_mon +1, tma->tm_year +1900, tma->tm_hour, tma->tm_min, tma->tm_sec);
            
            printf("Se ha creado un cerrojo de escritura (%d/%d/%d  %d:%d:%d).\n", tma->tm_mday, tma->tm_mon +1, tma->tm_year +1900, tma->tm_hour, tma->tm_min, tma->tm_sec);

            write(file, c, strlen(c));

            free(c);

            sleep(10);

            cerrojo.l_type = F_UNLCK;

            if (fcntl(file, F_SETLK, &cerrojo) == -1) {
                
                printf("ERROR al desbloquear el cerrojo -> %i : %s.\n", errno, strerror(errno));
            
            } else {

                if (cerrojo.l_type == F_UNLCK) {

                    t = time(NULL);
                    struct tm *tma = localtime(&(t));
                    printf("Se ha desbloqueado el cerrojo de escritura (%d/%d/%d  %d:%d:%d).\n", tma->tm_mday, tma->tm_mon +1, tma->tm_year +1900, tma->tm_hour, tma->tm_min, tma->tm_sec);
                
                }

            }
        }
    } else {

        printf("El cerrojo del fichero %s está BLOQUEADO.\n", argv[1]);

    }

    return 1;
}