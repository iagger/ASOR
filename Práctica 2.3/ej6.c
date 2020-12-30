#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>


void printAttributes() {
    printf("pid: %i\n", getpid());
    printf("ppid: %i\n", getppid());
    printf("pgid: %i\n", getpgid(getpid()));
    printf("sid: %i\n", getsid(getpid()));
    // man getrlimit
    struct rlimit lim;
    if (getrlimit(RLIMIT_NOFILE, &lim) == -1) {
        printf("Error(%i) -> %s\n", errno, strerror(errno));
    }
    printf("Límite de ficheros abiertos: %i\n", lim.rlim_max);
    // man getcwd
    size_t max_path = PATH_MAX + 1;
    char* path = malloc(sizeof(char) * max_path);
    getcwd(path, max_path);
    printf("Directorio de trabajo: %s\n", path);
    free(path);
}

int main() {

    pid_t pid = fork();

    if (pid == -1) {
        printf("ERROR (%i) -> %s", errno, strerror(errno));
    }

    if (pid == 0) { // Proceso hijo
        pid_t child_sid = setsid(); // Nueva sesion proceso hijo
        if (chdir("/tmp") == -1) { // Nuevo directorio de trabajo proceso hijo
            printf("ERROR (%i) -> %s", errno, strerror(errno));
        }

        sleep(5); // Para que acabe antes el padre. El proceso init adopta al hijo al quedar éste huérfano
        printf("\nATRIBUTOS PROCESO HIJO\n");
        printAttributes();

    } else {
        // sleep(5); // Para que acabe antes el hijo. En este caso el proceso hijo queda como defunt
        printf("\nATRIBUTOS PROCESO PADRE\n");
        printAttributes();
    }

    return 0;

}