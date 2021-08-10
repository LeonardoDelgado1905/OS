#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>
#include "find_library.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <strings.h>


#define PORT 3535


int val_error(int returned, int error_value, char *msg){
    if(returned <= error_value){
        perror(msg);
        exit(EXIT_FAILURE);
    }
    return 0;
}

int main (){
    struct timeval start, end;
    double StopWatch;

    struct searcher query;

    int serverfd, clientfd, r, opt = 1;
    struct sockaddr_in server, client;
    socklen_t tamano;

        
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
    
    float result;
    do{
        r = recv(clientfd, (void *)&query, sizeof(query), 0);
        if(r < 0){
            perror("\n-->Error en recv(): ");
            exit(-1);
        }
        
        hash_table = fopen("hash_table.bin", "rb");
        binaryFileR = fopen("linkedlist.bin", "rb");
        int find = read_hash(hash(query.sourceid));
        struct router Guia;
        Guia.next = find;

        while(Guia.next != -1 && (strcmp(Guia.dstid, query.dstid)!=0 || Guia.hod != query.hod)){
            Guia = read_router(Guia.next);   
        }
        
        if(Guia.next == -1 && (strcmp(Guia.dstid, query.dstid)!=0 || Guia.hod != query.hod)){
            result = -1;      
        }else{
            result = Guia.mean_travel_time;
        }
        r = send(clientfd, &result, sizeof(float), 0);
        if(r < 0){
            perror("\n-->Error en send(): ");
            exit(-1);
        } 
        
        fclose(binaryFileR);
        fclose(hash_table);
    }while(query.action!=false);
    close(clientfd);    
}