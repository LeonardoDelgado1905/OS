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

struct linked_list{
	struct router *header;
	struct router *tail;
	int size;
};

/*

void add(struct linked_list list, struct router *node){
	if(list.header == NULL){
		list.header = node;
		list.tail = node;
	}else{
		list.tail->next = node;
		list.tail = node;
	}
}
*/
void constructor(struct router myrouter, char sourceid[], char dstid[], int hod, float mean_travel_time, float standard_deviation_travel_time){
	memcpy(myrouter.sourceid, sourceid, sizeof(char[35]));
	memcpy(myrouter.dstid, dstid, sizeof(char[35]));
	myrouter.mean_travel_time = mean_travel_time;
	myrouter.standard_deviation_travel_time = standard_deviation_travel_time;
}
/*
int hash(char sourceid[]){
	return 0;
}

void add(int *heads, int *tails, struct router *myRouter){
	int xd = hash(myRouter->sourceid);
	if(heads[xd]==NULL){
		heads[xd] = tails[xd] = myRouter;
	}else{
		// tails[0]->next = myRouter;
	}
}





// Funciones que mandó el monitor
FILE *binaryFile;
void write(long unsigned int position,int value){
	long unsigned int curPos=sizeof(int)*position;
	fseek(binaryFile,curPos,SEEK_SET);
	fwrite(&value,sizeof(int),1,binaryFile);
	return ;
}
int read(long unsigned int position){
	int value;
	long unsigned int curPos=sizeof(int)*position;
	fseek(binaryFile,curPos,SEEK_SET);
	fread(&value,sizeof(int),1,binaryFile);
	return value;
}
*/
// Hasta acá

char* getfield(char* line, int num)
{	
	char* tok;
    tok = strtok(line, ",");
	
	int n=0;
	while (tok != 0) {
		if(n == num){
			return tok;
		}		
		n++;
        tok = strtok(0,",");
    }
    
}
int main(){

	int n = 1160;
	int *heads;		// Inicializa un puntero al valor donde inicia el arreglo de heads
	heads = (int*)malloc(n*sizeof(int)); 	// Libera el espacio para guardar n estucturas router
	int *tails;
	tails = (int*)malloc(n*sizeof(int));
	// *(tails + sourcid)*sizeof(struct router);

	

	// FILE *practice;
	// practice = fopen("listasenlazadas.dat", "w+");
	// struct router myrouter;
	// constructor(myrouter, "478", "627" , 0, 1145.57, 523.7);
	// struct router myrouter2;
	// constructor(myrouter2, "478", "637",	0, 1163.38,	250.21);
	// 900;
	// int idx_headers[2] = {1, 30};

	FILE *cadastral_data;
	cadastral_data = fopen("bogota-cadastral.csv", "r");
	
	struct router *myrouter;
	
	

	
	char line[1024];	
	fgets(line, 1024, cadastral_data);
	fgets(line, 1024, cadastral_data);
    // // while (fgets(line, 1024, cadastral_data))//Lee cada csv de el archivo
    // // {

	
    char* tmp = strdup(line);
	char* sourceid = getfield(tmp, 0);
	memcpy(myrouter->sourceid, sourceid, sizeof(sourceid));
	tmp = strdup(line);
	char* dstid = getfield(tmp, 1);
	memcpy(myrouter->dstid, dstid, sizeof(dstid));
	tmp = strdup(line);
	myrouter->hod = atoi(getfield(tmp, 3));
	tmp = strdup(line);
	myrouter->mean_travel_time = atof(getfield(tmp, 4));
	tmp = strdup(line);
	myrouter->standard_deviation_travel_time = atof(getfield(tmp, 5));
	// 	//add(myrouter);
    //     free(tmp);
    // }

	
	// struct linked_list list; 
	// add(list, &myrouter);
	// add(list, &myrouter2);
	// fwrite(&list, sizeof(struct linked_list), 4, practice);

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
