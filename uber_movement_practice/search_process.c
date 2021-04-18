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
FILE *binaryFile;
void write_router(long unsigned int position, struct router myrouter){
	long unsigned int curPos=sizeof(struct router)*position;
	fseek(binaryFile,curPos,SEEK_SET);
	fwrite(&myrouter,sizeof(struct router),1,binaryFile);
	return ;
}
struct router read_router(long unsigned int position){
	struct router value;
	long unsigned int curPos=sizeof(struct router)*position;
	fseek(binaryFile,curPos,SEEK_SET);
	fread(&value,sizeof(struct router),1,binaryFile);
	return value;
}

int hash(char sourceid[]){
	return atoi(sourceid);
}
int n;
void add(int *heads, int *tails, int curPos, struct router myRouter){

	int idx = hash(myRouter.sourceid)*sizeof(int);
	
	if(*(heads + idx) == -1){ //Es el primero que encuentro
		
		*(heads + idx) = *(tails + idx) = curPos;
		// printf("como soy nuevo: %s mi head es: %d\n", myRouter.sourceid, *(heads + idx));
	}else{
		struct router tail_router = read_router(*(tails+idx));
		tail_router.next = curPos;
		write_router(*(tails+idx),tail_router);
		write_router(curPos, myRouter);
		*(tails+idx) = curPos;
	}
}

// Hasta acá

char* getfield(char* line, int num)
{	
	// printf("linea: %s", line);
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


int *heads;
int *tails;
int main(){
 	binaryFile = fopen("linkedlist.bin", "wb+");
	char buffer[35] = "999    ";
	printf("%d", hash(buffer));
	n = 1160;
	//int *heads;		// Inicializa un puntero al valor donde inicia el arreglo de heads
	heads = (int*)malloc(n*sizeof(int)); 	// Libera el espacio para guardar n estucturas router	
	tails = (int*)malloc(n*sizeof(int));

	memset(heads, -1, n*sizeof(int));
	memset(tails, -1, n*sizeof(int));


	
	FILE *cadastral_data;
	cadastral_data = fopen("bogota-cadastral.csv", "r");
	
	struct router myrouter;
	
	char line[1024];	
	fgets(line, 1024, cadastral_data);
	int m= 0;
    while (fgets(line, 1024, cadastral_data))//Lee cada csv de el archivo
    {	
		printf("linea: %s", line);
		// printf("linea1----%s", line);
		char* tmp = strdup(line);
		// printf("%d\n", 1);
		char* sourceid = getfield(tmp, 0);
		memcpy(myrouter.sourceid, sourceid, sizeof(sourceid));
		tmp = strdup(line);
		char* dstid = getfield(tmp, 1);
		memcpy(myrouter.dstid, dstid, sizeof(dstid));
		// printf("sourceid: %s, dstid: %s\n", myrouter.sourceid, myrouter.dstid);
		// printf("%d\n", 3);
		tmp = strdup(line);
		myrouter.hod = atoi(getfield(tmp, 2));
		// printf("%d\n", 4);
		tmp = strdup(line);
		myrouter.mean_travel_time = atof(getfield(tmp, 3));
		// printf("%d\n", 5);
		tmp = strdup(line);
		myrouter.standard_deviation_travel_time = atof(getfield(tmp, 4));
		// printf("%s %d\n", myrouter.sourceid, m);
		
	 	add(heads, tails, m++, myrouter);		
		
        free(tmp);
     }
	free(heads);
	free(tails);
	
	fclose(binaryFile);
	fclose(cadastral_data);

	/**/
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
