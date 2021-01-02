#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int erase = 1;

void my_handler(int signal) {
    if (signal == SIGUSR1) erase = -1;
}

int main(int argc, char** argv) {

    // man sigaction
    struct sigaction action;

    // Cambiar el handler de SIGINT
    sigaction(SIGUSR1, NULL, &action);
    action.sa_handler = my_handler;
    sigaction(SIGUSR1, &action, NULL);

    int secs = atoi(argv[1]);

    printf("Se eliminará el ejecutable en %i segundos\n", secs);
    sleep(secs);

    if (erase > 0) {
        unlink(argv[0]);
        printf("Se eliminó el ejecutable %s\n", argv[0]);
    } else printf("NO se eliminó el ejecutable %s ya que se recibió una señal SIGUSR1\n", argv[0]);

    return 1;
}