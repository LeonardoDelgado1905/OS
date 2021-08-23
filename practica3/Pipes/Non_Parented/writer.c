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
    int descr, descr2, longmens, i, r;
    clock_t begin, end;
    double time_spent = 0.0;
    char conf;

    do{
        descr = open ("tuberia", O_WRONLY);
        if (descr == -1) sleep (1);
    }while (descr == -1);

    for (i=0; i<iterations; i++){
        printf("iteration writer: %i\n", i);
        if(size<64000){
            char* msg = createMessage(size);
            begin = clock();
            r = write (descr, msg, size);
            val_error(r, 0, "write error");
            sleep(1);
        }else{
            int auxSize = 50000;
            char* msg = createMessage(auxSize);
            begin = clock();
            for(int k = 0;k < size; k += auxSize){
                printf("Envio del paquete %i\n" , k/auxSize),
                r = write (descr, msg, auxSize);
                val_error(r, 0, "write error");
                sleep(1);
            }
        }
        sleep(1);
        r = mkfifo ("tuberia2", 0);
        val_error(r, -1, "mkfifo error");
        r = chmod("tuberia2", 0777);
        val_error(r, -1, "chmod error");
        descr2 = open("tuberia2", O_RDONLY);
        val_error(descr2, 0, "open error");
        r = read (descr2, &conf, sizeof(char));
        val_error(r, 0, "read error");
        end = clock();
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
        close(descr2);
    }
    showResult("tuberias no emparentadas", size, time_spent/iterations);
    close(descr);
}
