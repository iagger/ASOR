#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>


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

    fd_set set;
    int fd;

    while ((fd = -1) == -1) { // colocamos de nuevo el descriptor a -1 para elegir de nuevo el descriptor adecuado

        while (fd == -1) {
            FD_ZERO(&set);
            FD_SET(sck, &set);  // colocamos el socket 
            FD_SET(0, &set);    // colocamos la entrada estándar
            fd = select(sck+1, &set, NULL, NULL, NULL); // sck es el máximo fd ya que es positivo y por tanto mayor o igual que 0
        }

        time_t t = time(NULL);
        struct tm* tiempo = localtime(&t);

        size_t resp_len = 20;
        char resp[resp_len];

        if (FD_ISSET(sck, &set)){ // si fd es el socket, hacemos lo mismo que en el ejercicio anterior
            size_t s = recvfrom(sck, rec, 2, 0, (struct sockaddr *) &client, &client_len);
            rec[1] = (char)0; // fin de string
            getnameinfo((struct sockaddr *) &client, client_len, host_buf, NI_MAXHOST, serv_buf, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
            printf("SCK -> %i bytes de %s:%s\n", s, host_buf, serv_buf);

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
        } else { // si no es el socket, respondemos por consola
            read(0, rec, 2);    rec[1] = (char)0; // leemos 2 bytes de consola (caracter + '\n')
            switch (rec[0]) { 
                case 't':
                    resp_len = strftime(resp, resp_len, "%I:%M:%S %p", tiempo); resp[resp_len] = (char)0;
                    printf("STDIO -> %s\n", resp);
                break;
                case 'd':
                    resp_len = strftime(resp, resp_len, "%Y-%m-%d", tiempo); resp[resp_len] = (char)0;
                    printf("STDIO -> %s\n", resp);
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
    } 

    return 1;

}