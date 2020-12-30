#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv) {

    pid_t pid = fork();

    if (pid == -1) {
        printf("ERROR (%i) -> %s", errno, strerror(errno));
    }

    if (pid == 0) { // Proceso hijo
        pid_t child_sid = setsid(); // Nueva sesion proceso hijo
        if (chdir("/tmp") == -1) { // Nuevo directorio de trabajo proceso hijo
            printf("ERROR (%i) -> %s", errno, strerror(errno));
        }

        printf("\nPROCESO HIJO: pid = %i; ppid = %i\n", getpid(), getppid());

        int daemon_std = open("/dev/null", O_CREAT | O_RDWR, 0777);
        int daemon_err = open("daemon.err", O_CREAT | O_RDWR, 0777);
        int daemon_file = open("daemon.out", O_CREAT | O_RDWR, 0777);        

        int fd2 = dup2(daemon_file, 2);
        int fd1 = dup2(daemon_err, 1);
        int fd0 = dup2(daemon_std, 0);

        if (execvp(argv[1], argv + 1) == -1) {
            printf("Error(%i) -> %s\n", errno, strerror(errno));
        }

    } else {
        
        printf("\nPROCESO PADRE: pid = %i; ppid = %i\n", getpid(), getppid());

    }

    return 0;

}