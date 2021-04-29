
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_PROCESOS 1
/*semáforos*/

int pipefd[2];


struct datos_tipo{
    int dato;
    int p;
};

int *proceso(void * datos)
{
    printf("llego el primer hilo");
    struct datos_tipo *datos_proceso;
    datos_proceso = (struct datos_tipo *) datos;
    int a, i, j, p;
    // sem_wait(semaforo); //decremento MAX_PROCESOS
    a = datos_proceso -> dato;
    p = datos_proceso -> p;

    for(i = 0; i<=p; i++){
        printf("%i ",a);
    }

    fflush(stdout);
    sleep(2);
    for(i=0; i<=p; i++){
        printf("- ");
    }
    fflush(stdout);
    // sem_post(semaforo);
}

int main()
{
    // int error;
    // char *valor_devuelto;
    // //Var para hilos
    // struct datos_tipo hilo1_datos, hilo2_datos;
    // pthread_t idhilo1, idhilo2, idhilo3, idhilo4;

    // hilo1_datos.dato = 1;
    // hilo2_datos.dato = 2;
    // hilo1_datos.p = 10;
    // hilo2_datos.p = 5;

	// int r;
    // r = pipe(pipefd);
    // if(r < 0){
	// 	printf("error pipe()");
	// 	exit(-1);
	// }
    // // char testigo = 'X';
    // // printf("voy a escribir");
    // // fflush(stdout);
    // // close(pipefd[0]);
    // // write(pipefd[1], &testigo, 1);
    // // open(pipefd[0], 0);
    // // close(pipefd[1]);
    // /* se lanzan los hilos */
    // error= pthread_create(&idhilo1, NULL, (void *)proceso, (void *)(&hilo1_datos));
    // if(error != 0){
    //     perror ("No puedo crear hilo");
    //     exit (-1);
    // }

    // error= pthread_create(&idhilo2, NULL, (void *)proceso, (void *)(&hilo2_datos));
    // if(error != 0){
    //     perror ("No puedo crear hilo");
    //     exit (-1);
    // }

    // pthread_join(idhilo2, (void **)&valor_devuelto);
    // pthread_join(idhilo1, (void **)&valor_devuelto);

    // close(pipefd[0]);
    // close(pipefd[1]);
    // return 0;
    int error;
    char *valor_devuelto;
    //Var para hilos
    struct datos_tipo hilo1_datos, hilo2_datos;
    pthread_t idhilo1, idhilo2, idhilo3, idhilo4;

    hilo1_datos.dato = 1;
    hilo2_datos.dato = 2;
    hilo1_datos.p = 10;
    hilo2_datos.p = 5;
    int r;
    r = pipe(pipefd);
    if(r < 0){
		printf("error pipe()");
		exit(-1);
	}
    // char testigo[1] = {'X'};
    printf("voy a escribir\n");
    write(pipefd[1], "X", 1);
    char buffer[1];
    read(pipefd[0], buffer, 1);
    printf("%c\n",&buffer);
    error= pthread_create(&idhilo1, NULL, (void *)proceso, (void *)(&hilo1_datos));
    if(error != 0){
        perror ("No puedo crear hilo");
        exit (-1);
    }

    error= pthread_create(&idhilo2, NULL, (void *)proceso, (void *)(&hilo2_datos));
    if(error != 0){
        perror ("No puedo crear hilo");
        exit (-1);
    }

    pthread_join(idhilo2, (void **)&valor_devuelto);
    pthread_join(idhilo1, (void **)&valor_devuelto);
    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}