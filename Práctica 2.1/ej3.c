#include <stdio.h>  // standard input output
#include <errno.h>  // para errno
#include <unistd.h> // para función setuid()
#include <string.h> // para la función strerror()

const int NUM_ERRORS = 255; 

int main() {

    for (int err = 0; err < NUM_ERRORS; ++err) {
        printf("Error code : %d ; Error message: %s\n", err, strerror(err)); // strerror devuelve la cadena asociada al numero de error
    }

    return 1;
}