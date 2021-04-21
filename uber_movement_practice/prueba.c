#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(){
    char caracter[2] = "a";
    int comoEntero = *caracter;
    printf("%d\n", comoEntero);
}