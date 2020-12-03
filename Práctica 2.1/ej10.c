#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <stdio.h>

int main() {

    uid_t uid = getuid();
    uid_t euid = geteuid();

    printf("UID real -> %d\nUID efectivo -> %d\n", uid, euid);
    
    struct passwd infoUsuario = *getpwuid(uid);

    printf("Nombre de usuario -> %s\nDirectorio \"home\" -> %s\nDescripción del usuario -> %s\n", infoUsuario.pw_name, infoUsuario.pw_dir, infoUsuario.pw_gecos);
    
    return 1;
}