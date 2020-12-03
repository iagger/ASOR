#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {

    uid_t uid = getuid();
    uid_t euid = geteuid();

    printf("UID real -> %d\nUID efectivo -> %d\n", uid, euid);

    if (uid == euid) {
        printf("El bit setuid está activado, porque uid y euid coinciden\n");
    } else {
        printf("El bit setuid está NO activado, porque uid y euid NO coinciden\n");
    }

    return 1;

}