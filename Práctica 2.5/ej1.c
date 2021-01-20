#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>

int main(int argc, char** argv) {

    struct addrinfo crit;
    struct addrinfo *res;

    memset(&crit, 0, sizeof(struct addrinfo));

    crit.ai_family = AF_UNSPEC;
    crit.ai_flags = AI_PASSIVE;
    crit.ai_socktype = crit.ai_protocol = 0;
    crit.ai_canonname = NULL;
    crit.ai_addr = NULL;
    crit.ai_next = NULL;

    int ret = getaddrinfo(argv[1], NULL, &crit, &res);

    if (ret != 0) printf("ERROR(%i) en addrinfo -> %s", ret, strerror(ret));
    else {

        printf("# Las familias: AF_INET(2) y AF_INET6(10) (ver socket.h)\n");
        printf("# Los tipos de socket: SOCK_STREAM(1), SOCK_DGRAM(2) y SOCK_RAW(3)\n");

        while (res != NULL){

            if (res->ai_family == AF_INET) {

                char inet[INET_ADDRSTRLEN + 1];
                getnameinfo(res->ai_addr, sizeof(struct sockaddr_in), inet, INET_ADDRSTRLEN + 1, NULL, 0, NI_NUMERICHOST);
                printf("%s\t%i\t%i\n", inet, res->ai_family, res->ai_socktype);
            }
            if (res->ai_family == AF_INET6) {
                char inet6[INET6_ADDRSTRLEN + 1];
                getnameinfo(res->ai_addr, sizeof(struct sockaddr_in6), inet6, INET6_ADDRSTRLEN + 1, NULL, 0, NI_NUMERICHOST);
                printf("%s\t%i\t%i\n", inet6, res->ai_family, res->ai_socktype);
            }

            res = res->ai_next;
        }

    }

    return 0;
}