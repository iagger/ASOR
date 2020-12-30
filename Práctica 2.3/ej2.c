#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sched.h>

int main() {

    pid_t pid = getpid();

    // Planificador actual 
    int sched = sched_getscheduler(pid);
    if (sched== SCHED_OTHER) printf("Planificador: OTHER\n");
    else if (sched == SCHED_FIFO) printf("Planificador: FIFO\n");
    else if (sched == SCHED_RR) printf("Planificador: ROUND-ROBIN\n");
    else printf("Planificador: undetermined\n");

    // Prioridad actual 
    struct sched_param p;
    sched_getparam(pid, &p);
    printf("Prioridad actual: %i\n", p.sched_priority);

    // Prioridades máx y mín
    printf("Máx. prioridad: %i\nMín. prioridad: %i\n", sched_get_priority_max(sched), sched_get_priority_min(sched));

    return 1;
}