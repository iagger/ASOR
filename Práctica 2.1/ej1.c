#include <stdio.h>  // standard input output
#include <errno.h>  // para errno
#include <unistd.h> // para función setuid()

int main() {

    char *c;

    if (setuid(0) == -1) {  // si la llamada se resuelve devolviendo código de error (consultar man 2 setuid() para ver la finalidad de la llamada)
        perror(c);  // imprime por por consola el último error producido por una llamada al sistema (recibe una cadena como argumento)
    }

    return -1;
}