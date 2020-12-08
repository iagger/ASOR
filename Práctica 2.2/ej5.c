#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// Consultar man 2 open

int main() {

    int file = open("fichero5", O_CREAT, 0645);
    // O_CREAT crea el fichero si no existiera. Le pasamos los flags como segundo argumento, en este caso en octal como en el ejercicio 3 
    // ls -l para comprobar los flags del fichero

    close(file);

    return 1;
}