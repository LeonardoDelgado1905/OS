#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../../utils.h"
#include <time.h>

int main(int argc, char* argv[]){
    long int size = atoi(argv[1]);
    int iterations = atoi(argv[2]);  
    int descr, descr2, i, r;
    char a = '0';
    
    unlink ("tuberia");
    sleep(1);
    r = mkfifo ("tuberia", 0);
    val_error(r, -1, "mkfifo error");
    r = chmod("tuberia", 0777);
    val_error(r, -1, "chmod error");
    descr = open("tuberia", O_RDONLY);
    val_error(descr, 0, "open error");
 
    for (i=0; i<iterations; i++){
        if(size<64000){
            char buf[size];
            r = read (descr, buf, size);
            val_error(r, 0, "read error");
        }else{
            int auxSize = 50000;
            char buf[auxSize];
            for(long int k = 0; k < size; k += auxSize){
                r = read (descr, buf, auxSize);
                //printf("Recibido del paquete %li\n" , k/auxSize);
                val_error(r, 0, "read error");
            }
        }  
        unlink ("tuberia2");
        do{
            descr2 = open ("tuberia2", O_WRONLY);
            if (descr2 == -1) sleep (1);
        }while (descr2 == -1);
        r = write (descr2, &a, sizeof(char));
        val_error(r, 0, "write error");
        close (descr2);
    } 
    close (descr);
}