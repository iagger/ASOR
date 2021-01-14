#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <stdlib.h>
#include <sys/time.h>
#include <errno.h>

const size_t BUFFER_SIZE = 256;
const char* PIPE_1_NAME = "pipe1";
const char* PIPE_2_NAME = "pipe2";


int main() {

    char* buff[BUFFER_SIZE + 1];

    mkfifo(PIPE_1_NAME, 0644); // Creamos la tubería
    mkfifo(PIPE_2_NAME, 0644); // Creamos la tubería

    int fd1 = open(PIPE_1_NAME, O_RDONLY | O_NONBLOCK); // Abrimos la tubería
    int fd2 = open(PIPE_2_NAME, O_RDONLY | O_NONBLOCK ); // Abrimos la tubería

    int ret = 0;
    while (ret != -1) {
        fd_set set;
        FD_ZERO(&set);
        FD_SET(fd1, &set);
        FD_SET(fd2, &set);

        ret = select(((fd1 > fd2) ? fd1 : fd2)+1, &set, NULL, NULL, NULL);

        int current_pipe;
        if (ret != -1) {
            if (FD_ISSET(fd1, &set)) {  current_pipe = fd1; }
            if (FD_ISSET(fd2, &set)) {  current_pipe = fd2; }
            int n_current_pipe = (current_pipe == fd1) ? 1 : 2;
        
            int bytes_read = BUFFER_SIZE;
            while (bytes_read == BUFFER_SIZE) {
                bytes_read = read(current_pipe, buff, BUFFER_SIZE);
                buff[bytes_read] = '\0';
                printf("PIPE %i -> %s", n_current_pipe, buff);
            }

            if (n_current_pipe == 1) {
                close(fd1);
                fd1 = open(PIPE_1_NAME, O_RDONLY | O_NONBLOCK);
            }
            if (n_current_pipe == 2) {
                close(fd2);
                fd2 = open(PIPE_2_NAME, O_RDONLY | O_NONBLOCK);
            }

            if (fd1 < 0 || fd2 < 0) {
                printf("Error(%i) al reabrir pipe %i -> %s\n", errno, n_current_pipe, strerror(errno));
                ret = -1; // Si la reapertura de la pipe trada falla, rompemos el bucle para finalizar
            }
        }
    }

    close(fd1);
    close(fd2);

    return 1;
}