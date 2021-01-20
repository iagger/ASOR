#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

const int MAX_ECHO_BYTES = 100;
const int N_PROC = 2;

int main(int argc, char** argv) {

    struct addrinfo crit;
    struct addrinfo *res;

    // Criterios de búsqueda
    memset(&crit, 0, sizeof(struct addrinfo));
    crit.ai_family = AF_UNSPEC;
    crit.ai_flags = AI_PASSIVE;
    crit.ai_socktype = SOCK_STREAM;

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

    int bnd = bind(sck, res->ai_addr, res->ai_addrlen);

    if (bnd == -1) {
        printf("ERROR(%i) en bind -> %s", errno, strerror(errno));
        return -1;
    }

    freeaddrinfo(res);

    if (listen(sck, 1) == -1) {
        printf("ERROR(%i) en listen -> %s", errno, strerror(errno));
        return -1;
    }

    size_t rec_len = MAX_ECHO_BYTES;
    char rec[rec_len];

    struct sockaddr_storage client;
    socklen_t client_len = sizeof(client);

    char host_buf[NI_MAXHOST];
    char serv_buf[NI_MAXSERV];


    int client_ac = accept(sck, (struct sockaddr *) &client, &client_len);

    if (client_ac == -1) {
        printf("ERROR en aceptando al cliente");
        return -1;
    }

    getnameinfo((struct sockaddr *) &client, client_len, host_buf, NI_MAXHOST, serv_buf, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
    printf("Conexión desde %s %s\n", host_buf, serv_buf);

    while (rec_len = recv(client_ac, rec, rec_len - 1, 0)) {
        rec[rec_len] = (char)0;
        send(client_ac, rec, rec_len, 0);
        rec_len = MAX_ECHO_BYTES;
    }
    close(client_ac);
    printf("Conexión terminada\n");
    

    return 1;

}