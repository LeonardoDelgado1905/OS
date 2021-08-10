#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define CHARLEN 4

int main(){
    pid_t pid;
    int r;
    int pipefd[2];
    char* data;
    char buf[11];
    
    r = pipe(pipefd);
    if(pipefd < 0){ 
        perror("Error pipe() "); 
        exit(-1);
    }
    pid = fork();
    if (pid == -1){
        perror("fork"); 
        exit(EXIT_FAILURE); 
    }
    
    if(pid == 0){
        close(pipefd[0]);
        char* data = "hola mundo";
        r = write(pipefd[1], data, sizeof(data));
        if(r != sizeof(data)){
            perror("error writting pipe"); 
        }
        close(pipefd[1]);
        exit(0);    
    }
    else{ 
        close(pipefd[1]);
        r = read(pipefd[0], buf, sizeof(data));
        if(r != sizeof(data)){
            perror("error reading pipe");
        }
        close(pipefd[0]); 
        buf[r] = 0;
        printf("\nMensaje del hijo: %s \n", buf);
    }
}