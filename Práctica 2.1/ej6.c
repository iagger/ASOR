#include <unistd.h> // para sysconf(int nombre)
#include <stdio.h> 

// man 3 sysconf: recibe como argumento el código de el valor/limite de sistema (en las constantes _SC_<Macro correspondiente>) a conocer. Devuelve long int. 

int main() {
    // Consultamos los valores propuestos en el enunciado como ejemplo
    printf("Longitud máxima de argumentos(_SC_ARG_MAX) -> %li\nNúm máx de hijos(_SC_CHILD_MAX) -> %li\nNúm máx de ficheros(_SC_OPEN_MAX) -> %li\n",
            sysconf(_SC_ARG_MAX), sysconf(_SC_CHILD_MAX), sysconf(_SC_OPEN_MAX));
    
    return 1;
}