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
	struct router *next; //4
};

struct linked_list{
	struct router *header;
	struct router *tail;
	int size;
};

void add(struct linked_list list, struct router *node){
	if(list.header == NULL){
		list.header = node;
		list.tail = node;
	}else{
		list.tail->next = node;
		list.tail = node;
	}
}

void constructor(struct router myrouter, char sourceid[], char dstid[], int hod, float mean_travel_time, float standard_deviation_travel_time){
	memcpy(myrouter.sourceid, sourceid, sizeof(char[35]));
	memcpy(myrouter.dstid, dstid, sizeof(char[35]));
	myrouter.mean_travel_time = mean_travel_time;
	myrouter.standard_deviation_travel_time = standard_deviation_travel_time;
}

int main(){
	FILE *practice;
	practice = fopen("listasenlazadas.dat", "w+");
	struct router myrouter;
	constructor(myrouter, "478", "627" , 0, 1145.57, 523.7);
	struct router myrouter2;
	constructor(myrouter2, "478", "637",	0, 1163.38,	250.21);
	900
	int idx_headers[2] = {1, 30};


	1600, 478
	tail[478] == 900
	// arreglo que guarde los "tails" 
	router tail
	.next = 1600
	fwrite()


	
	fwrite(,    practice + 1600...)
	next = fread(buffer, sizeof(int), 5, practice + sizeof(struct router) );


	struct linked_list list; 
	add(list, &myrouter);
	add(list, &myrouter2);
	fwrite(&list, sizeof(struct linked_list), 4, practice);

	// printf("el size de la estructura es: %d\n", sizeof(struct router));
	// <router> alkdfjlaksdjf
	// // FILE *practice;
	// practice = fopen("practicabinaria.dat", "w+");

	// int val[5] = {1, 2, 3, 5, 9938};
	// fwrite(val, sizeof(int), 4, practice);
	// fclose(practice);
	// FILE *lectura;
	// lectura = fopen("practicabinaria.dat", "r");
	// int buffer[5];
	// fread(buffer, sizeof(int), 5, lectura);
	// //for(int i = 0; i < 5; i++){
	// //	printf("%d\n", buffer[i]);	
	// //}
	// fclose(lectura);
	return 0;
}
// bool matchRouters(struct router *aux, char goal_sourceid[], char goal_dstid[], int goal_hod){
// 	return (aux->dstid == goal_dstid) && (aux->hod == goal_hod);
// }

// struct router findRouter(struct linked_list list, char goal_sourceid[], char goal_dstid[], int goal_hod){
// 	struct router *aux = list.header;	
// 	if(aux == NULL){
// 		return NULL;
// 	}else{
// 		while(aux->next != NULL && !matchRouters(aux, goal_dstid, goal_hod)){
			
// 		}
// 		return true;
// 	}
	
// }
