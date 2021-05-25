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
#define BACKLOG 32

struct searcher{
	char sourceid[35];  // 35
	char dstid[35]; //35
	int hod; //4
    bool action; // 1
};

int val_error(int returned, int error_value, char *msg){
    if(returned <= error_value){
        perror(msg);
        exit(EXIT_FAILURE);
    }
    return 0;
}

int search(struct searcher query){
    hash_table = fopen("hash_table.bin", "rb");
    binaryFileR = fopen("linkedlist.bin", "rb");
    int find = read_hash(hash(query.sourceid));
    struct router Guia;
    Guia.next = find;

    while(Guia.next != -1 && (strcmp(Guia.dstid, query.dstid)!=0 || Guia.hod != query.hod)){
        Guia = read_router(Guia.next);   
    }
    fclose(binaryFileR);
    fclose(hash_table);
    
    if(Guia.next == -1 && (strcmp(Guia.dstid, query.dstid)!=0 || Guia.hod != query.hod)){
        return -1;      
    }else{
        return Guia.mean_travel_time;
    }
}

int main (){
    struct timeval start, end;
    double StopWatch;

    struct searcher query;

    int serverfd, clientfd, r, opt = 1;
    float result;
    struct sockaddr_in server, client;
    socklen_t tamano;

        
    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    val_error(serverfd, -1, "\n-->Error en socket():");
    
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(server.sin_zero, 8); 
    
    setsockopt(serverfd,SOL_SOCKET,SO_REUSEADDR,(const char *)&opt,sizeof(int));

    r = bind(serverfd, (struct sockaddr *)&server, sizeof(struct sockaddr));
    val_error(r, -1, "\n-->Error en bind(): ");
    
    r = listen(serverfd, BACKLOG);
    val_error(r, -1, "\n-->Error en Listen(): ");
    
    clientfd = accept(serverfd, (struct sockaddr *)&client, &tamano);
    val_error(r, -1, "\n-->Error en accept: ");
    
    while(true){
        r = recv(clientfd, (void *)&query, sizeof(query), 0);
        val_error(r, -1, "\n-->Error en recv(): ");

        result = search(query);     
        
        r = send(clientfd, &result, sizeof(float), 0);
        val_error(r, -1, "\n-->Error en send(): ");
    }
    close(clientfd);    
}