#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv) {

    char current[PATH_MAX];
    getcwd(current, sizeof(current));

    char* pipe_path = strcat(current, "/pipe");

    mkfifo(pipe_path, 0777); // Creamos la tubería

    int fd = open(pipe_path, O_WRONLY); // Abrimos la tubería

    write(fd, argv[1], strlen(argv[1])); // Escribimos el primer argumento

    close(fd); // Cerramos la tubería

    return 1;
}