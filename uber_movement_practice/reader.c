#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "find_library.h"

struct searcher{
	char sourceid[35];  // 35
	char dstid[35]; //35
	int hod; //4
};

struct mail{
    int id;
    char data[35];
};

int val_error(int returned, int error_value, char *msg){
    if(returned <= error_value){
        perror(msg);
        exit(EXIT_FAILURE);
    }
    return 0;
}

int main (){
    struct searcher searcher;
    char error[2] = "-1";
    memcpy(searcher.sourceid, error, sizeof(int));
    memcpy(searcher.dstid, error, sizeof(int));
    searcher.hod = -1;
    int descr, i, r;
    struct mail msg, msg2; 
    do{
        unlink ("tuberia");
        sleep(1);
        r = mkfifo ("tuberia", 0);
        val_error(r, -1, "mkfifo error");
        r = chmod("tuberia", 0777);  //777 en octal
        val_error(r, -1, "chmod error");
        descr = open("tuberia", O_RDONLY);
        val_error(descr, 0, "open error");
        r = read (descr, &msg, sizeof(struct mail));
        val_error(r, 0, "read error");

        if(msg.id==1){
            printf("El source Id es: %s \n", msg.data); fflush(stdout);
            memcpy(searcher.sourceid, msg.data, sizeof(msg.data));
        }else if(msg.id==2){
            printf("El dst Id es: %s \n", msg.data); fflush(stdout);
            memcpy(searcher.dstid, msg.data, sizeof(msg.data));
        }else if(msg.id==3){
            printf("La hora es: %d \n", *msg.data); fflush(stdout);
            searcher.hod = *msg.data;
        }else if(msg.id==4){
            printf("4\n");
            do{		/* intentar la conexion */
                descr = open ("tuberia2", O_WRONLY);
                if (descr == -1) sleep (1);
            }while (descr == -1);
            printf("conexion\n");
            if(searcher.hod==-1 || searcher.sourceid=="-1" || searcher.dstid=="-1"){
                printf("error\n");
                msg2.id = -1;
                r = write (descr, &msg2, sizeof(struct mail));
            }else{
                printf("Hasta acá llego 1\n");
                hash_table = fopen("hash_table.bin", "rb");
                printf("Hasta acá llego 2\n");
                binaryFileR = fopen("linkedlist.bin", "rb");
                printf("Hasta acá llego 2\n");
                int find = read_hash(hash(searcher.sourceid));
                
                struct router Guia;
                Guia.next = find;

                while(Guia.next != -1 && (strcmp(Guia.dstid, searcher.dstid)!=0 || Guia.hod != searcher.hod)){
                    Guia = read_router(Guia.next);   
                }
                printf("Encontre algo\n");
                if(Guia.next == -1 && (strcmp(Guia.dstid, searcher.dstid)!=0 || Guia.hod != searcher.hod)){
                    printf("-1");
                }else{
                    printf("Source: %s\n", Guia.sourceid);
                    printf("Destino: %s\n", Guia.dstid);
                    printf("Hora del día: %d\n", Guia.hod);
                    printf("Tiempo promedio de viaje: %.2f\n", Guia.mean_travel_time);
                }
                fclose(binaryFileR);
                fclose(hash_table);
            }

        }
        close (descr);
        printf("%s %s %d\n", searcher.sourceid, searcher.dstid, searcher.hod);
    }while(msg.id!=5);
    
}