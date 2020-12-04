#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

const int LOOPS = 1000000;

int main() {

    struct timeval tiempoA;
    struct timezone zonaA;
    struct timeval tiempoB;
    struct timezone zonaB;

    if (gettimeofday(&tiempoA, &zonaA) == -1) {

        printf("ERROR %i -> %s", errno, strerror(errno));
    
    } else {

        for (int i = 0; i < LOOPS; ++i);

        if (gettimeofday(&tiempoB, &zonaB) == -1) {
    
            printf("ERROR %i -> %s", errno, strerror(errno));
    
        } else {
            
            printf("Microsecs to loop times %i -> %li us\n", LOOPS, tiempoB.tv_usec-tiempoA.tv_usec);        

        }
    }

    return 1;
}