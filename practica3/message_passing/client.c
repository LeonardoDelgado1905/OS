#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdbool.h>

#define PORT 3535

int main(int argc, char *argv[]){
    printf("Bienvenido\n");
    int clientfd, r, hod, option = 0, id;
    char package[35];
    struct sockaddr_in client;
    struct hostent *he;
    float result;
    
    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if(clientfd < 0){
        perror("\n-->Error en socket():");
        exit(-1);
    }
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT);

    inet_aton(argv[1], &client.sin_addr);
    
    r = connect(clientfd, (struct sockaddr *)&client, (socklen_t)sizeof(struct sockaddr));
    if(r < 0){
        perror("\n-->Error en connect(): ");
        exit(-1);
    }

    r = send(clientfd, (const void *)&query, sizeof(query), 0);
    close(clientfd);
    system("clear");
}