#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int val_error(int returned, int error_value, char *msg){
    if(returned <= error_value){
        perror(msg);
        exit(EXIT_FAILURE);
    }
    return 0;
}

struct data{
    char data[35];
    float data2;
    int data3;
    double executionTime;
};

struct mail{
    int id;
    struct data data;
};

int main(){
    int option = 0;
    int descr, descr2, r, hod;
    char sourceId[35], dtsId[35];
    struct mail msg, msg2; 

    printf("Bienvenido\n");
    do{		/* intentar la conexion */
        descr = open ("tuberia", O_WRONLY);
        if (descr == -1) sleep (1);
    }while (descr == -1);
    
    do{
        printf("\n1. Ingresar origen\n2. Ingresar destino\n3. Ingresar hora\n4. Buscar tiempo de viaje medio\n5. Salir\n");
        scanf("%d", &option);

        switch (option){
        case 1:
            printf("Ingrese ID del origen: ");
            scanf("%s", sourceId);

            msg.id = 1;     
            memcpy(msg.data.data, &sourceId, sizeof(sourceId));
            r = write (descr, &msg, sizeof(struct mail));

            break;
        case 2:
            printf("Ingrese ID del destino: ");
            scanf("%s", dtsId);
            
            msg.id = 2;
            memcpy(msg.data.data, &dtsId, sizeof(sourceId));
            r = write (descr, &msg, sizeof(struct mail));

            break;
        case 3:
            printf("Ingrese hora del día: ");
            scanf("%d", &hod);

            msg.id = 3;
            msg.data.data3 = hod;
            r = write (descr, &msg, sizeof(struct mail));

            break;
        case 4:

            msg.id = 4;
            r = write (descr, &msg, sizeof(struct mail));

            
            //unlink ("tuberia2");
            sleep(1);
            r = mkfifo ("tuberia2", 0);
            val_error(r, -1, "mkfifo error");
            r = chmod("tuberia2", 0777);  //777 en octal
            val_error(r, -1, "chmod error");
            descr2 = open("tuberia2", O_RDONLY);
            val_error(descr2, 0, "open error");
            r = read (descr2, &msg2, sizeof(struct mail));
            val_error(r, 0, "read error");
            if(msg2.id==-1){
                printf("Ingrese todos los datos antes de hacer la busqueda.\n");
            }else if(msg2.id==0){
                printf("Tiempo de viaje medio: NAN\n");
                printf("La ejecución del programa tomó: %.16g \n", msg2.data.executionTime);
            }else{
                printf("Tiempo de viaje medio: %f\n", msg2.data.data2);
                printf("La ejecución del programa tomó: %.16g \n", msg2.data.executionTime);
            }
            break;
        case 5:

            msg.id = 5;
            r = write (descr, &msg, sizeof(struct mail));
            break;
        default:
            printf("Ingrese una opción valida por favor.");
            break;
        }
        printf("mi opcion es %d", option);
    }while(option!=5);
}