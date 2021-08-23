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
    int status, pid, r;
    char *data;
    remove("./File_communication/message.dat");
    pid = fork();
    if(pid == -1){
        perror("the process couldn't be created.");
        exit(-1);
    }
    for(int i = 0; i < iterations; ++i){
        if(pid == 0){
            
            file = fopen("./File_communication/message.dat","w+");
            if(file == NULL){
                perror("The file couldn't be opened.");
                exit(-1);
            }
            //char *mg = createMessage(size);
            begin = clock();
            r = fwrite(createMessage(size),sizeof(char),size,file);
            printf("val: %d\n", r);
            if(r == 0){
                perror("The file couldn't be written.");
                exit(EXIT_FAILURE);
            }
            fclose(file);
            //exit(0);
        }
        else{
            
            long int res = 0;
            do{

                file = fopen("./File_communication/message.dat","r");
                if(file == NULL){
                    //perror("The file couldn't be opened.");
                    continue;
                }
                fseek(file, 0L, SEEK_END);
                res = ftell(file);
                printf("LLEGUE YO: %ld\n", res);
                if(clock() - begin > 200){
                    break;
                }
            }while(res < size);
            
            /*for(long i = 0; i<size; i++){
                
                r = fread(data,sizeof(char),1,file);
                if(r == 0){
                    perror("The file couldn't be read.");
                    exit(EXIT_FAILURE);
                }
            }*/
            fclose(file);
            end = clock();
            
            time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
            
        }
    }

    //fclose(file);
    if(pid != 0){        
        showResult("Archivos", size, time_spent/iterations);
        fflush(stdout);
    }
    
}