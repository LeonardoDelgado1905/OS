#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../utils.h"
#include <time.h>

#define PORT 3535



int main(int argc, char *argv[])
{
    long int size = atoi(argv[2]);
    int iterations = atoi(argv[3]);
    int clientfd, r;
    struct sockaddr_in client;
    struct hostent *he;

    double total_result = 0.0;
    clock_t begin, end;
    
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
    

    char* received[8];

    r = send(clientfd, (const void *)&size, sizeof(long int), 0);
    if(size<64000){
        r = send(clientfd, (const void *)&iterations, sizeof(int), 0);  
    }else{
        
        int it = (size/10000)*iterations;
        r = send(clientfd, (const void *)&it, sizeof(int), 0);  
    }
    for (int i = 0; i < iterations; i++){
        if(size<64000){
            char* package = createMessage(size);
            begin = clock();
            r = send(clientfd, (const void *)package, size, 0);
            if(r < 0){
                perror("\n-->Error en send(): ");
                exit(-1);
            }  
            r = recv(clientfd, &received, 8, 0);
            end = clock();
            total_result += (double)(end - begin) / CLOCKS_PER_SEC;
        }else{
            char* package = createMessage(10000);
            int it = (size/10000)*iterations;
            begin = clock();
            for(int j=0; j<it; j++){
                r = send(clientfd, (const void *)package, size, 0);
                if(r < 0){
                    perror("\n-->Error en send(): ");
                    exit(-1);
                }  
                r = recv(clientfd, &received, 8, 0);
            }
            end = clock();
            total_result += (double)(end - begin) / CLOCKS_PER_SEC;
        }
    }
    total_result/=iterations;
    showResult("Paso de mensajes", size, total_result);
    
    close(clientfd);


}