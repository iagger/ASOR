#include <stdio.h>  // standard input output
#include <errno.h>  // para errno
#include <unistd.h> // para función setuid()
#include <string.h> // para la función strerror()

int main() {

    char *c;

    if (setuid(0) == -1) {  // si la llamada se resuelve devolviendo código de error (consultar man 2 setuid() para ver la finalidad de la llamada)
        printf("Error code : %d ; Error message: %s\n", errno, strerror(errno)); // strerror devuelve la cadena asociada al numero de error; cuando se produce un error se almacena el codigo en la variable errno
    }

    return -1;
}