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

struct searcher{
	char sourceid[35];  // 35
	char dstid[35]; //35
	int hod; //4
};

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

    struct searcher searcher;
    char error[2] = "-1";
    memcpy(searcher.sourceid, error, 2*sizeof(char));
    memcpy(searcher.dstid, error, 2*sizeof(char));
    searcher.hod = -1;
    int descr, descr2, i, r;
    struct mail msg, msg2; 

    unlink ("tuberia"); 
    sleep(1);
    r = mkfifo ("tuberia", 0);
    val_error(r, -1, "mkfifo error");
    r = chmod("tuberia", 0777);  //777 en octal
    val_error(r, -1, "chmod error");
    descr = open("tuberia", O_RDONLY);
    val_error(descr, 0, "open error");
    

    do{
        unlink ("tuberia2");

        r = read (descr, &msg, sizeof(struct mail));
        val_error(r, 0, "read error");
        if(msg.id==1){
            memcpy(searcher.sourceid, msg.data.data, sizeof(msg.data.data));
        }else if(msg.id==2){
            memcpy(searcher.dstid, msg.data.data, sizeof(msg.data.data));
        }else if(msg.id==3){
            searcher.hod = msg.data.data3;
        }else if(msg.id==4){

            do{		/* intentar la conexion */
                descr2 = open ("tuberia2", O_WRONLY);
                if (descr2 == -1) sleep (1);
            }while (descr2 == -1);

            if(searcher.hod==-1 || searcher.sourceid=="-1" || searcher.dstid=="-1"){
                msg2.id = -1;
                r = write (descr2, &msg2, sizeof(struct mail));
            }else{
                gettimeofday(&start, NULL);
                hash_table = fopen("hash_table.bin", "rb");
                binaryFileR = fopen("linkedlist.bin", "rb");
                int find = read_hash(hash(searcher.sourceid));
                struct router Guia;
                Guia.next = find;

                while(Guia.next != -1 && (strcmp(Guia.dstid, searcher.dstid)!=0 || Guia.hod != searcher.hod)){
                    Guia = read_router(Guia.next);   
                    
                }
                gettimeofday(&end, NULL);
                StopWatch = (double)(end.tv_sec + (double)end.tv_usec/1000000) -
                    (double)(start.tv_sec + (double)start.tv_usec/1000000);
                msg2.data.executionTime = StopWatch*1000.0;
                if(Guia.next == -1 && (strcmp(Guia.dstid, searcher.dstid)!=0 || Guia.hod != searcher.hod)){
                    msg2.id = 0;
                    r = write (descr2, &msg2, sizeof(struct mail));
                }else{
                    msg2.id = 1;
                    msg2.data.data2 = Guia.mean_travel_time;
                    r = write (descr2, &msg2, sizeof(struct mail));
                }
                fclose(binaryFileR);
                fclose(hash_table);
            }

        }
    }while(msg.id!=5);
    close (descr);
    unlink ("tuberia2");
    unlink ("tuberia");   
}