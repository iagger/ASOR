#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main() {

    // Creamos un conjunto de señales que contenga las especificadas en el enunciado. Lo aplicaremos como máscara para que sean bloqueadas.
        // man sigemptyset
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    sigaddset(&sigset, SIGTSTP);
        // man sigprocmask
    sigset_t old_set;
    sigprocmask(SIG_BLOCK, &sigset, &old_set);

    // Obtenemos la variable de entorno SLEEP_SECS
    //setenv("SLEEP_SECS", "30", 1);
    int sleep_secs = atoi(getenv("SLEEP_SECS"));
    
    // Suspendemos la ejecución durante SLEEP_SECS segundos
    printf("El proceso dormirá durante %i segundos,\n", sleep_secs);
    sleep(sleep_secs);

    // Comprobamos si se han recibido las señales SIGINT o SIGTSTP durante la suspension sleep(SLEEP_SECS)
        // man sigpending
    sigset_t sigset_pending;
    sigpending(&sigset_pending);

    // Los eliminamos de la máscara si se han recibido

    sigset_t sigset_unmask;

    if (sigismember(&sigset_pending, SIGINT)) {
        printf("\nSe recibió una señal SIGINT.");
        sigaddset(&sigset_unmask, SIGINT);
    }
    if (sigismember(&sigset_pending, SIGTSTP)) {
        printf("\nSe recibió una señal SIGTSTP.");
        sigaddset(&sigset_unmask, SIGTSTP);
    }

    sigprocmask(SIG_UNBLOCK, &sigset_unmask, &old_set);

    return 0;

}