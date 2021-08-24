#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include "../../utils.h"

int main(int argc, char* argv[]){
    long int size = atoi(argv[1]);
    int iterations = atoi(argv[2]);
    pid_t pid;
    int r;
    int pipefd[2];
    double time_spent = 0.0;
    clock_t begin, end;

    for(int i=0;i<iterations;i++){
        if(size<64000){
            char* msg = createMessage(size);
            char buf[size+1];

            r = pipe(pipefd);
            if(pipefd < 0){ 
                perror("Error pipe() "); 
                exit(EXIT_FAILURE);
            }
            pid = fork();
            if (pid == -1){
                perror("Error fork() "); 
                exit(EXIT_FAILURE); 
            }
            if(pid == 0){
                close(pipefd[0]);
                begin = clock();
                r = write(pipefd[1], msg, size);
                if(r != size){ 
                    perror("error writting pipe"); 
                }
                close(pipefd[1]);
                exit(0);    
            }else{ 
                close(pipefd[1]);
                r = read(pipefd[0], buf, size);
                end = clock();
                if(r != size){  
                    //perror("error reading pipe");
                }
                buf[r] = 0;
                time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
                close(pipefd[0]); 
            }
        }else{
            int auxSize = 10000;
            char* msg = createMessage(auxSize);
            char buf[auxSize+1];
            
            r = pipe(pipefd);
            if(pipefd < 0){ 
                perror("Error pipe() "); 
                exit(EXIT_FAILURE);
            }
            pid = fork();
            if (pid == -1){
                perror("Error fork() "); 
                exit(EXIT_FAILURE); 
            }
            if(pid == 0){
                close(pipefd[0]);
                begin = clock();
                for(int k = 0;k < size; k += auxSize){
                    r = write(pipefd[1], msg, auxSize);
                    if(r != auxSize){ 
                        perror("error writting pipe"); 
                    }
                }
                close(pipefd[1]);
                exit(0);    
            }else{ 
                close(pipefd[1]);
                for(int k = 0; k < size; k += auxSize){
                    r = read(pipefd[0], buf, auxSize);
                    if(r != auxSize){  
                        //perror("error reading pipe");
                    }
                    buf[r] = 0;
                }
                end = clock();
                time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
                close(pipefd[0]); 
            }
        }
    }
    showResult("tuberias emparentadas", size, time_spent/iterations);
    return 0;
}