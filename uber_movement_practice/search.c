#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct router{
	char sourceid[35];  // 35
	char dstid[35]; //35
	int hod; //4
	float mean_travel_time; //4
	float standard_deviation_travel_time; //4
	int next; //4
};

int hash(char sourceid[]){
	return atoi(sourceid);
}

FILE *binaryFileR;
struct router read_router(long unsigned int position){
	// binaryFile = fopen("linkedlist.bin", "rb");
	struct router value;
	long unsigned int curPos=sizeof(struct router)*position;
	fseek(binaryFileR,curPos,SEEK_SET);
	fread(&value,sizeof(struct router),1,binaryFileR);
	// printf("*******%s\n", value.sourceid);
	return value;
}
FILE *hash_table;
int read_hash(long unsigned int position){
    int find = 0;
    
    long unsigned int curPos=sizeof(int)*position;
    printf("CurPos %d", curPos);
	fseek(hash_table,curPos,SEEK_SET);
	fread(&find,sizeof(int),1,hash_table);
	return find;
}
int main(){
    hash_table = fopen("hash_table.bin", "rb");
    binaryFileR = fopen("linkedlist.bin", "rb");
    char sourceid[35] = "1114";
	char dstid[35] = "694";
    int hod = 19;
   
    int find = read_hash(hash(sourceid));
    printf("el primero aparece en: %d\n", find);
    struct router Guia = read_router(find);
    printf("source: %d\n", Guia.sourceid);
 	/*
     while(Guia.next != -1 || (Guia.dstid!=dstid || Guia.hod != hod)){
        Guia = read_router(Guia.next);    
    }
    if(Guia.next == -1){
        printf("-1");
    }
    else{
        printf("Tiempo promedio de viaje: %10.2f", Guia.mean_travel_time);
    }*/
	return 0;
}