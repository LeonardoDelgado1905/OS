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

int main(int argc, char *argv[]){
    printf("Bienvenido\n");
    int clientfd, r, hod, option = 0, id;
    char sourceId[35], dtsId[35];
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
    r = recv()

    struct searcher query;
    query.action = true;
    char error[2] = "-1";
    memcpy(query.sourceid, error, 2*sizeof(char));
    memcpy(query.dstid, error, 2*sizeof(char));
    query.hod = -1;
    
    do{
        printf("\n1. Ingresar origen\n2. Ingresar destino\n3. Ingresar hora\n4. Buscar tiempo de viaje medio\n5. Salir\n");
        scanf("%d", &option);   // Menu de opciones para la práctica

        switch (option){
        case 1:
            printf("Ingrese ID del origen: ");
            scanf("%s", sourceId);

            if(atoi(sourceId)>0 && atoi(sourceId)<1161){
                memcpy(query.sourceid, &sourceId, sizeof(sourceId));
                printf("La dirección de ID de origen que ha ingresado es valida.\n");
            }else{
                printf("Por favor ingrese una dirección de ID de origen valido.\n");
            }
            break;
        case 2:
            printf("Ingrese ID del destino: ");
            scanf("%s", dtsId);
            
            if(atoi(dtsId)>0 && atoi(dtsId)<1161){  
                memcpy(query.dstid, &dtsId, sizeof(dtsId));
                printf("La dirección de ID de destino que ha ingresado es valida.\n");
            }else{
                printf("Por favor ingrese una dirección de ID de destino valido.\n");
            }

            break;
        case 3:
            printf("Ingrese hora del día: ");
            scanf("%d", &hod);

            if(hod>=0 && hod<=23){
                query.hod = hod;
                printf("La hora del dia que ha ingresado es valida.\n");
            }else{
                printf("Por favor ingrese una hora del día valida.\n");
            }
            break;
        case 4:
            if(query.hod==-1 || query.sourceid=="-1" || query.dstid=="-1"){
                printf("Ingrese todos los datos antes de realizar la busqueda.\n");
            }else{
                r = send(clientfd, (const void *)&query, sizeof(query), 0);
                val_error(r, -1, "\n-->Error en send(): ");

                r = recv(clientfd, &result, sizeof(float), 0);
                val_error(r, -1, "\n-->Error en recv(): ");

                if(result==-1){
                    printf("Tiempo de viaje medio: NA \n");
                }else{
                    printf("Tiempo de viaje medio: %.2f\n", result);
                }
                fflush(stdout);
            }            
            break;
        case 5:
            query.action = false;
            r = send(clientfd, (const void *)&query, sizeof(query), 0);
            close(clientfd);
            break;
        default:
            printf("Ingrese una opción valida por favor.");
            break;
        }
        getchar();
        printf("Presione una tecla para continuar");
        getchar();
        system("clear");
    }while(option!=5);
}