#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>
#include "../utils.h"

long int findSize(char file_name[]){
    
    FILE* fp = fopen(file_name, "r");
  
    // checking if the file exist or not
    if (fp == NULL) {
        printf("File Not Found!\n");
        return -1;
    }
  
    fseek(fp, 0L, SEEK_END);
  
    // calculating the size of the file
    long int res = ftell(fp);
  
    // closing the file
    fclose(fp);
  
    return res;
}

int main(int argc, char *argv[]){
    long int size = atoi(argv[1]);
    int iterations = atoi(argv[2]);
    clock_t begin, end;
    double time_spent = 0.0;
    FILE *file;
    int pid, r;
    remove("./message.dat");
    for(int i = 0; i < iterations; ++i){        
        begin = clock();
        pid = fork();
        if(pid == -1){
            perror("the process couldn't be created.");
            exit(-1);
        }
        if(pid == 0){            
            file = fopen("./message.dat","w+");
            if(file == NULL){
                perror("The file couldn't be opened.");
                exit(-1);
            }
            r = fwrite(createMessage(size),sizeof(char),size,file);
            if(r == 0){
                perror("The file couldn't be written.");
                exit(-1);
            }
            //fclose(file);
            exit(0);
        }
        else{
            
            long int res = 0;
            do{                
                //FILE *f;
                file = fopen("./message.dat","r");
                if(file == NULL){ //Aún no se ha mandado el mensaje
                    continue;                   
                }         
                fseek(file, 0L, SEEK_END);
                res = ftell(file);
                fclose(file);
            }while(res < size);
            end = clock();                    
            time_spent += (double)(end - begin) / CLOCKS_PER_SEC;            
        }
    }

    if(pid != 0){        
        showResult("Archivos", size, time_spent/iterations);
        fflush(stdout);
    }
    
}