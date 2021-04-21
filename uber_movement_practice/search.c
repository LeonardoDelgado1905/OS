#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "find_library.h"

int main(){
    hash_table = fopen("hash_table.bin", "rb");
    binaryFileR = fopen("linkedlist.bin", "rb");
    char sourceid[35] = "1127";
	char dstid[35] = "879";
    int hod = 23;
   
    int find = read_hash(hash(sourceid));

    struct router Guia;
    Guia.next = find;

    while(Guia.next != -1 && (strcmp(Guia.dstid, dstid)!=0 || Guia.hod != hod)){
        Guia = read_router(Guia.next);   
    }
    if(Guia.next == -1 && (strcmp(Guia.dstid, dstid)!=0 || Guia.hod != hod)){
        printf("-1");
    }
    else{
        printf("Source: %s\n", Guia.sourceid);
        printf("Destino: %s\n", Guia.dstid);
        printf("Hora del día: %d\n", Guia.hod);
        printf("Tiempo promedio de viaje: %.2f\n", Guia.mean_travel_time);
    }
    fclose(binaryFileR);
    fclose(hash_table);
	return 0;
}