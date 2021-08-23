#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <time.h>
#include "../utils.h"
#define SHM_SIZE 1024  /* make it a 1K shared memory segment */


char *attach_memory_block(){
    key_t key = 7877;
    int shmid;
    char *data;
    if ((shmid = shmget(key, sizeof(char) * 3, 0666 | IPC_CREAT)) == -1) {
        perror("shmget");
        return NULL;
    }
    data = shmat(shmid, NULL, 0);
    if (data == (char*)(-1)) {
        return NULL;
    }
    return data;
}
int main(int argc, char *argv[]){
    long int size = atoi(argv[1]);
    int iterations = atoi(argv[2]);
    clock_t begin, end;
    double time_spent = 0.0;
    char *block = attach_memory_block();

    int pid;
    for(int i = 0; i < iterations; ++i){
        begin = clock();            
        pid = fork();
        if(pid == 0){        
            char* mg = createMessage(size);
            strncpy(block, mg, size);
            exit(0);
        }
        else{        
            char *rcv = createMessage(size);
            end = clock();            
            time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
        }
    }
    if(pid != 0){        
        showResult("Memoria compartida", size, time_spent/iterations);
        fflush(stdout);
    }
    
    if (shmdt(block) == -1) {
        perror("shmdt");
        exit(-1);
    }
    return 0;
}