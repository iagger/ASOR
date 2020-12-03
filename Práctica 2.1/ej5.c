#include <sys/utsname.h>    // para struct utsname
#include <stdio.h>  // standard input output
#include <errno.h>  // para errno
#include <string.h> // para la función strerror()

int main() {

    struct utsname buf;

    if (uname(&buf) == 0) {
        printf("sysname: %s\nnodename: %s\nrelease: %s\nversion: %s\nmachine: %s\ndomainname: %s\n", buf.sysname, buf.nodename, buf.release, buf.version, buf.machine, buf.__domainname);
    } else {
         printf("Error code : %d ; Error message: %s\n", errno, strerror(errno));
    }
    return 1;
}