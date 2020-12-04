#include <time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <locale.h>

int main() {

    time_t tiempo = time(NULL);
    struct tm estructuraTiempo = *localtime(&tiempo);

    char* c;
    size_t size = 100000;

    setlocale(LC_ALL, "");

    size = strftime(c, size, "%A, %d de %B de %G, %k:%M", &estructuraTiempo);
    printf("%s\n", c);

    return 1;
}