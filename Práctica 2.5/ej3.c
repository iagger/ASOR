#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char** argv) {

    struct addrinfo crit;
    struct addrinfo *res;

    // Criterios de búsqueda
    memset(&crit, 0, sizeof(struct addrinfo));
    crit.ai_family = AF_UNSPEC;
    crit.ai_flags = AI_PASSIVE;
    crit.ai_socktype = SOCK_DGRAM;

    int ret = getaddrinfo(argv[1], argv[2], &crit, &res);

    if (ret != 0) { 
        printf("ERROR(%i) en addrinfo -> %s", ret, strerror(ret));
        return -1;
    }

    int sck = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if (sck == -1) {
        printf("ERROR(%i) en creación de socket -> %s", errno, strerror(errno));
        return -1;
    }

    freeaddrinfo(res);

    char rec[2];

    struct sockaddr_storage client;
    socklen_t client_len = sizeof(client);

    char host_buf[NI_MAXHOST];
    char serv_buf[NI_MAXSERV];

    sendto(sck, argv[3], 2, 0, res->ai_addr, res->ai_addrlen);

    if (*argv[3] == 't' || *argv[3] == 'd') {
        size_t resp_len = 20;
        char resp[resp_len];
        resp_len = recvfrom(sck, resp, resp_len, 0, (struct sockaddr *) &client, &client_len);  resp[resp_len] = (char)0;
        printf("%c\n%s\n", *argv[3], resp);
    } else printf("Comando no soportado %c...", *argv[3]);

    return 1;
}