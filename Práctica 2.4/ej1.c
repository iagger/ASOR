#include <unistd.h> // para fork, pipe y dup
#include <sys/types.h> // para fork
#include <string.h>
#include <errno.h>
#include <stdio.h>


int main(int argv, char** argc) {

    // Creamos la tubería

    int descf[2]; // Creamos un descriptor para escritura y otro para lectura

    if (pipe(descf) < 0) {
        printf("Error %i -> %s\n", errno, strerror(errno));
    } else {
        pid_t pid = fork();
        if (pid < 0) {
            printf("Error %i -> %s\n", errno, strerror(errno));
        }
        else if (pid == 0) { // Proceso hijo
            dup2(descf[0], 0);  // Sustituimos la entrada estándar por el descriptor de lectura de la tubería 
            close(descf[0]);    close(descf[1]); // Cerramos los descriptores de la tubería
            execlp(argc[3], argc[3], argc[4], NULL); // ejecutamos cmd2 con arg2
        } else { // Proceso padre
            dup2(descf[1], 1);  //Sustituimos la salida estándar por el descriptor de escritura de la tubería
            close(descf[0]);    close(descf[1]); // Cerramos los descriptores de la tubería
            execlp(argc[1], argc[1], argc[2], NULL);  // ejecutamos cmd1 con arg1
        }
    }

    return 1;
}