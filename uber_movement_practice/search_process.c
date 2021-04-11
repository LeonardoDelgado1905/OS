#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main(){
	FILE *practice;
	practice = fopen("practicabinaria.dat", "w+");
	int val[5] = {1, 2, 3, 5, 9938};
	fwrite(val, sizeof(int), 5, practice);
	fclose(practice);
	FILE *lectura;
	lectura = fopen("practicabinaria.dat", "r");
	int buffer[5];
	fread(buffer, sizeof(int), 5, lectura);
	for(int i = 0; i < 5; i++){
		printf("%d\n", buffer[i]);	
	}
	fclose(lectura);
	return 0;
}
