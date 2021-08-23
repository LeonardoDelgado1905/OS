char* createMessage(long int size){
    char* package = (char*)malloc(size);
    for(int i=0;i<size;i++){
        package[i] = '0';
    }
    return package;
}

void showResult(char* method, long int size, double time){
    switch(size){
        case 1000:
            printf("El tiempo de envio de 1KB por medio de %s es de: %f\n", method, time);
            break;
        case 10000:
            printf("El tiempo de envio de 10KB por medio de %s es de: %f\n", method, time);
            break;
        case 100000:
            printf("El tiempo de envio de 100KB por medio de %s es de: %f\n", method, time);
            break;
        case 1000000:
            printf("El tiempo de envio de 1MB por medio de %s es de: %f\n", method, time);
            break;
        case 10000000:
            printf("El tiempo de envio de 10MB por medio de %s es de: %f\n", method, time);
            break;
        case 100000000:
            printf("El tiempo de envio de 100MB por medio de %s es de: %f\n", method, time);
            break;
        default:
            printf("Algo salió mal");
    }
}

int val_error(int returned, int error_value, char *msg){
    if(returned <= error_value){
        perror(msg);
        exit(EXIT_FAILURE);
    }
    return 0;
}