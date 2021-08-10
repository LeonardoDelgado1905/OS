#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#define SHM_SIZE 1024  /* make it a 1K shared memory segment */


char *attach_memory_block(char *filename, int size){
    key_t key;
    int shmid;
    char *data;
    if ((key = ftok(filename, size) == -1)) {
        perror("ftok");
        return NULL;
    }
    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
        perror("shmget");
        return NULL;
    }
    data = shmat(shmid, NULL, 0);
    if (data == (char *)(-1)) {
        return NULL;
    }
    return data;
}
int main(int argc, char *argv[]){
    
    int pid = fork();
    int size = 10;

    char *block = attach_memory_block("channel.txt", size);
    if(pid == 0){
        printf("Soy el hijo que lee: %s\n", block);
        strncpy(block, "hola mundo", size);
        printf("El hijo escribe: %s\n", block);
    }
    else{
        printf("Padre lee: %s\n", block);
        sleep(1);
        printf("Luego de 1s, el padre lee: %s\n", block);
    }


    if (shmdt(block) == -1) {
        perror("shmdt");
        exit(1);
    }
    return 0;
}