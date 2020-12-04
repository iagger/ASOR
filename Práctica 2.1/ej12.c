#include <time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {

    time_t tiempo;

    if (time(&tiempo) == -1) {
        printf("ERROR %i -> %s", errno, strerror(errno));
    } else {
        printf("Seconds since EPOCH: %li\n", tiempo);
    }

    return 1;
}