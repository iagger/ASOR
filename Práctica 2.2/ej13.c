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
    
    if (dup2(file, 1) == -1 || dup2(file, 2) == -1) {
        printf("Error al redirigir la salida estándar -> (%i) : %s\n", errno, strerror(errno));
    } else {

        // Escribimos en salida estándar
        printf("Cadena de prueba.\n");
        printf("No deberia estar apareciendo en consola, sino en el fichero especificado\n");
        // Escribimos en stderr
        fprintf(stderr, "Este mensaje se ha dirigido a la salida estándar de error\n");

    }

    // El orden en que se hagan los redireccinamientos es indiferente ya que dup2 asigna el fd más bajo disponible 
    // y al borrar 1 y 2 (stdout y stderr) justo antes de duplicar el fd del fichero, se le asignará éste (0 debe estar ocupado siempre (stdin por defecto)) 

    return 1;
}