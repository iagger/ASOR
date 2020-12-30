#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv) {

    // execvp

    /*  En este caso excepv si acepta una serie de cadenas como argumento
    *   por lo que no será necesario juntar el programa y sus args en una 
    *   sola cadena a la hora de ejecutar este programa 
    */

    pid_t pid = fork();

    if (pid == 0) {
        if (execvp(argv[1], argv + 1) == -1) {
            printf("Error(%i) -> %s\n", errno, strerror(errno));
        }
    } else {
        wait();
        printf("El comando terminó de ejecutarse\n");
    }

    return 1;
   
}