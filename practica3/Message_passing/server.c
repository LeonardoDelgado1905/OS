#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <stdbool.h>
#include "../utils.h"
#include <time.h>

#define PORT 3535
#define BACKLOG 1000


int main(){
    int serverfd, clientfd, r, opt = 1, iterations;
    struct sockaddr_in server, client;
    socklen_t tamano;
    clock_t end;
        
    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverfd < 0){
        perror("\n-->Error en socket():");
        exit(-1);
    }
    
    server.sin_family = AF_INET; 
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(server.sin_zero, 8); 
    
    setsockopt(serverfd,SOL_SOCKET,SO_REUSEADDR,(const char *)&opt,sizeof(int));

    r = bind(serverfd, (struct sockaddr *)&server, sizeof(struct sockaddr));
    if(r < 0){
        perror("\n-->Error en bind(): ");
        exit(-1);
    }
    
    r = listen(serverfd, BACKLOG);
    if(r < 0){
        perror("\n-->Error en Listen(): ");
        exit(-1);
    }
    
    clientfd = accept(serverfd, (struct sockaddr *)&client, &tamano);
    if(clientfd < 0)
    {
        perror("\n-->Error en accept: ");
        exit(-1);
    }
    long int size = 0;
        r = recv(clientfd, (void *)&size, sizeof(long int), 0);
        r = recv(clientfd, (void *)&iterations, sizeof(int), 0);
    do{
        
        char* message = (char*)malloc(size);
        r = recv(clientfd, message, size, 0);
        if(r < 0){
            perror("\n-->Error en recv(): ");
            exit(-1);
        }
        r = send(clientfd, "Recibido", 8, 0);
        if(r < 0){
            perror("\n-->Error en send(): ");
            exit(-1);
        } 
        iterations--;
    }while(iterations > 0);  
    
    close(clientfd);   
}