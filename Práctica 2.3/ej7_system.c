#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {

    // system

    /*  Para simplificar la implementación, tomamos solo la primera cadena 
    *   para ser ejecutada por system, por lo que se debe pasar como argumento 
    *   una sola cadena que contenga el programa y sus argumentos
    */ 

    system(argv[1]);

    printf("El comando terminó de ejecutarse\n");

    return 1;
}