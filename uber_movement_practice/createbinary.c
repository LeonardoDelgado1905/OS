#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "find_library.h"

int *heads;
int *tails;
int main(){

	NUM_ORIGINS = 1160;
	tails = malloc(NUM_ORIGINS*sizeof(int));
	memset(heads, -1, NUM_ORIGINS*sizeof(int));
	memset(tails, -1, NUM_ORIGINS*sizeof(int));
	
	binaryFile = fopen("linkedlist.bin", "wb");
	binaryFileR = fopen("linkedlist.bin", "rb");
	

	cadastral_data = fopen("bogota-cadastral.csv", "r");
	
	struct router myrouter;
	
	char line[1024];
	fgets(line, 1024, cadastral_data);

	int m= 0;
	int cota = 100000;

    while (fgets(line, 1024, cadastral_data))//Lee cada csv de el archivo
    {	
		char* tmp = strdup(line);
		char* sourceid = getfield(tmp, 0);
		memcpy(myrouter.sourceid, sourceid, sizeof(sourceid));
		tmp = strdup(line);
		char* dstid = getfield(tmp, 1);
		memcpy(myrouter.dstid, dstid, sizeof(dstid));
		tmp = strdup(line);
		myrouter.hod = atoi(getfield(tmp, 2));
		tmp = strdup(line);
		myrouter.mean_travel_time = atof(getfield(tmp, 3));
		tmp = strdup(line);
		myrouter.standard_deviation_travel_time = atof(getfield(tmp, 4));
	 	add(heads, tails, m++, myrouter);		
        free(tmp);
    }

	FILE *hash_table;
	hash_table = fopen("hash_table.bin", "wb+");

	fwrite(heads,sizeof(int),n,hash_table);
	free(heads);
	free(tails);
	fclose(binaryFile);
	fclose(binaryFileR);
	fclose(hash_table);
	fclose(cadastral_data);

	return 0;
}