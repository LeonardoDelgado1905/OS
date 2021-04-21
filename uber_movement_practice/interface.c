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

struct mail{
    int id;
    char data[35];
};

int main(){
    int option = 0;
    int descr, descr2, r, hod;
    char sourceId[35], dtsId[35];
    struct mail msg, msg2; 
    printf("Bienvenido\n");
    do{
        printf("\n1. Ingresar origen\n2. Ingresar destino\n3. Ingresar hora\n4. Buscar tiempo de viaje medio\n5. Salir\n");
        scanf("%d", &option);
        switch (option){
        case 1:
            printf("Ingrese ID del origen: ");
            scanf("%s", sourceId);

            do{		/* intentar la conexion */
                descr = open ("tuberia", O_WRONLY);
                if (descr == -1) sleep (1);
            }while (descr == -1);
            msg.id = 1;
            memcpy(msg.data, &sourceId, sizeof(sourceId));
            r = write (descr, &msg, sizeof(struct mail));

            break;
        case 2:
            printf("Ingrese ID del destino: ");
            scanf("%s", dtsId);

            do{		/* intentar la conexion */
                descr = open ("tuberia", O_WRONLY);
                if (descr == -1) sleep (1);
            }while (descr == -1);
            msg.id = 2;
            memcpy(msg.data, &dtsId, sizeof(sourceId));
            r = write (descr, &msg, sizeof(struct mail));

            break;
        case 3:
            printf("Ingrese hora del día: ");
            scanf("%d", &hod);

            do{		/* intentar la conexion */
                descr = open ("tuberia", O_WRONLY);
                if (descr == -1) sleep (1);
            }while (descr == -1);
            msg.id = 3;
            memcpy(msg.data, &hod, sizeof(sourceId));
            r = write (descr, &msg, sizeof(struct mail));

            break;
        case 4:
            do{		/* intentar la conexion */
                descr = open ("tuberia", O_WRONLY);
                if (descr == -1) sleep (1);
            }while (descr == -1);
            msg.id = 4;
            r = write (descr, &msg, sizeof(struct mail));


            unlink ("tuberia2");
            sleep(1);
            r = mkfifo ("tuberia2", 0);
            val_error(r, -1, "mkfifo error");
            r = chmod("tuberia2", 0777);  //777 en octal
            val_error(r, -1, "chmod error");
            descr = open("tuberia2", O_RDONLY);
            val_error(descr, 0, "open error");
            r = read (descr, &msg2, sizeof(struct mail));
            val_error(r, 0, "read error");
            if(msg2.id==-1){
                printf("Ingrese todos los datos antes de hacer la busqueda.\n");
            }else{
                printf("Tiempo de viaje medio: \n");
            }
            break;
        case 5:
            do{		/* intentar la conexion */
                descr = open ("tuberia", O_WRONLY);
                if (descr == -1) sleep (1);
            }while (descr == -1);
            msg.id = 5;
            r = write (descr, &msg, sizeof(struct mail));
            break;
        default:
            printf("Ingrese una opción valida por favor.");
            break;
        }
    }while(option!=5);
}