#include <stdio.h>
#include <signal.h>

const int num_capturas = 10;

int num_SIGINT = 0;
int num_SIGTSTP = 0;

void my_handler(int signal) {
    if (signal == SIGINT) num_SIGINT++;
    if (signal == SIGTSTP) num_SIGTSTP++;
}

int main() {

    // man sigaction
    struct sigaction action;

    // Cambiar el handler de SIGINT
    sigaction(SIGINT, NULL, &action);
    action.sa_handler = my_handler;
    sigaction(SIGINT, &action, NULL);

    // Cambiar el handler de SIGTSTP
    sigaction(SIGTSTP, NULL, &action);
    action.sa_handler = my_handler;
    sigaction(SIGTSTP, &action, NULL);

    sigset_t sigset;

    while (num_SIGINT + num_SIGTSTP < num_capturas) sigsuspend(&sigset);

    printf("Capturadas %i señales (SIGINT/SIGTSTP)\n\tSIGINT -> %i\n\tSIGTSTP -> %i\n", num_capturas, num_SIGINT, num_SIGTSTP);

    return 1;

}