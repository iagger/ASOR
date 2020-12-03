#include <unistd.h> // para pathconf(char* path, int nombre)
#include <stdio.h> 

// man 3 pathconf: Devuelve valor asociado al codigo del segundo argumento para la ruta del primer argumento. Devuelve long int. 

const char* path = "/";

int main() {
    // Consultamos los valores propuestos en el enunciado como ejemplo
    printf("Núm máx de enlaces(_PC_LINK_MAX) -> %li\nTamaño máx de una ruta(_PC_PATH_MAX) -> %li\nNúm máx de ficheros(_PC_NAME_MAX) -> %li\n",
            pathconf(path, _PC_LINK_MAX), pathconf(path, _PC_PATH_MAX), pathconf(path, _PC_NAME_MAX));
    
    return 1;
}