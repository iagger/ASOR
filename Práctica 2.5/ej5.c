#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>


const int N_PROC = 2;

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

    int bnd = bind(sck, res->ai_addr, res->ai_addrlen);

    if (bnd == -1) {
        printf("ERROR(%i) en bind -> %s", errno, strerror(errno));
        return -1;
    }

    freeaddrinfo(res);

    char rec[2];

    struct sockaddr_storage client;
    socklen_t client_len = sizeof(client);

    char host_buf[NI_MAXHOST];
    char serv_buf[NI_MAXSERV];

    for (int i = 0; i < N_PROC; ++i) {

        pid_t pid = fork();

        if (pid == 0) {
            while (1 > -1) {
                size_t s = recvfrom(sck, rec, 2, 0, (struct sockaddr *) &client, &client_len);
                rec[1] = (char)0; // fin de string
                getnameinfo((struct sockaddr *) &client, client_len, host_buf, NI_MAXHOST, serv_buf, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
                printf("%i bytes de %s:%s\n", s, host_buf, serv_buf);

                time_t t = time(NULL);
                struct tm* tiempo = localtime(&t);
                size_t resp_len = 20;
                char resp[resp_len];

                switch (rec[0]) {
                    case 't':
                        resp_len = strftime(resp, resp_len, "%I:%M:%S %p", tiempo); resp[resp_len] = (char)0;
                        sendto(sck, resp, resp_len, 0, (struct sockaddr *) &client, client_len);
                    break;
                    case 'd':
                        resp_len = strftime(resp, resp_len, "%Y-%m-%d", tiempo); resp[resp_len] = (char)0;
                        sendto(sck, resp, resp_len, 0, (struct sockaddr *) &client, client_len);
                    break;
                    case 'q':
                        printf("Saliendo...\n");
                        return -1;
                    break;
                    default:
                        printf("Comando no soportado %c...\n", *rec);
                    break;
                } 

            } 
        } else { // espera a los procesos hijos
            int st;
            wait(&st);
        }

    }

    return 1;

}