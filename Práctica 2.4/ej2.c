#include <unistd.h> // para fork y pipe
#include <sys/types.h> // para fork
#include <stdlib.h> // malloc y free
#include <string.h>
#include <errno.h>
#include <stdio.h>

const int MSG_MAX_LENGTH = 100;

int main() {

    char flag;

    int p_h[2]; pipe(p_h);
    int h_p[2]; pipe(h_p);

    pid_t pid = fork();

    if (pid == 0) { // Proceso hijo

        char* mensaje = malloc(MSG_MAX_LENGTH*sizeof(char));
        int loops = 10; flag = 'l';
        for (size_t i = 0; i < loops; ++i) {
            size_t length = read(p_h[0], mensaje, MSG_MAX_LENGTH);
            mensaje[length] = '\0';
            printf("HIJO -> Mensaje: %s", mensaje);
            sleep(1);
            if (i == loops - 1) flag = 'q';
            write(h_p[1], &flag, 1);
        }
        free(mensaje);

    } else { // Proceso padre

        char* mensaje = malloc(MSG_MAX_LENGTH*sizeof(char));
        while (flag != 'q') {
            write(1, "PADRE -> Mensaje: ", strlen("PADRE -> Mensaje: "));
            size_t length = read(0, mensaje, MSG_MAX_LENGTH);
            mensaje[length] = '\0';
            write(p_h[1], mensaje, MSG_MAX_LENGTH);
            read(h_p[0], &flag, 1);
        }
        free(mensaje);
        printf("Se ha recibido el flag de parada. Cesan los mensajes.\n");
    }

    close(h_p[0]);
    close(h_p[1]);
    close(p_h[0]);
    close(p_h[1]);

    return 1;
}