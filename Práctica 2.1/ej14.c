#include <time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

const int FIRST_YEAR = 1900;    // tm_year años desde 1900 (consultar man 3 localtime)

int main() {

    time_t tiempo = time(NULL);

    struct tm estructuraTiempo = *localtime(&tiempo);
    printf("Año actual -> %i\n", estructuraTiempo.tm_year + FIRST_YEAR);
    
    return 1;
}