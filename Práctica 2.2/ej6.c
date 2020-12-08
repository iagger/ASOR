#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {

    mode_t nueva = 027; // rw-r-x--- (todos los permisos (777) - permisos deseados (750) = 027)

    mode_t anterior = umask(nueva);   // umask establece la máscara especificada y devuelve su valor anterior (18)

    //int file = open("fichero6", O_CREAT, 0777);

    printf("Máscara anterior -> %i\nMáscara nueva -> %i\n", anterior, nueva);

    //close(file);

    return 1;
}