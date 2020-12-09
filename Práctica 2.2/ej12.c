#include <sys/types.h>     
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // para dup
#include <errno.h>
#include <string.h>
#include <stdio.h>

// man 2 dup 

int main(int argc, char** argv) {

    int file;

    if ((file = open(argv[1], O_CREAT | O_WRONLY, 0777)) == -1) {
        printf("Error al abrir el fichero -> (%i) : %s\n", errno, strerror(errno));
    }
    
    if (dup2(file, 1) == -1) {
        printf("Error al redirigir la salida estándar -> (%i) : %s\n", errno, strerror(errno));
    } else {
        printf("Cadena de prueba.\n");
        printf("No deberia estar apareciendo en consola, sino en el fichero:\n%s\n", argv[1]);
    }

    return 1;
}