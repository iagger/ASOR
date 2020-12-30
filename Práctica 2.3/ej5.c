#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

int main() {

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

    return 1;
}