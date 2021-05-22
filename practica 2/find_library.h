FILE *binaryFile;
FILE *binaryFileR;
FILE *cadastral_data;
FILE *hash_table;
int NUM_ORIGINS;

struct router{
	char sourceid[35];  // 35
	char dstid[35]; //35
	int hod; //4
	float mean_travel_time; //4
	float standard_deviation_travel_time; //4
	int next; //4
};

void write_router(long unsigned int position, struct router myrouter){
	long unsigned int curPos=sizeof(struct router)*position;
	fseek(binaryFile,curPos,SEEK_SET);
	fwrite(&myrouter,sizeof(struct router),1,binaryFile);
	return;
}

struct router read_router(long unsigned int position){
	struct router value;
	long unsigned int curPos=sizeof(struct router)*position;
	fseek(binaryFileR,curPos,SEEK_SET);
	fread(&value,sizeof(struct router),1,binaryFileR);
	return value;
}
int hash(char sourceid[]){
	return atoi(sourceid);
}
void add(int *heads, int *tails, int curPos, struct router myRouter){

	int idx = hash(myRouter.sourceid);

	if(*(heads + idx) == -1){ //Es el primero que encuentro
		*(heads + idx) = *(tails + idx) = curPos;
		write_router(curPos, myRouter);
	}else{
		//memcpy(tail_router.sourceid, myRouter.sourceid, sizeof(sourceid));
		myRouter.next = -1;
		write_router(curPos, myRouter);
		struct router tail_router = read_router(*(tails+idx));
		tail_router.next = curPos;
		write_router(*(tails+idx),tail_router);
		*(tails+idx) = curPos;
	}
}

char* getfield(char* line, int num)
{	
	char* tok;
    tok = strtok(line, ",");
	
	int n=0;
	while (tok != 0) {
		if(n == num){
			return tok;
		}		
		n++;
        tok = strtok(0,",");
    }
}

int read_hash(long unsigned int position){
    int find = 0;
    long unsigned int curPos=sizeof(int)*position;
	fseek(hash_table,curPos,SEEK_SET);
	fread(&find,sizeof(int),1,hash_table);
	return find;
}
