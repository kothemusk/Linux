#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>


void *f(void* arg){
	int *data = (int *)arg;
	int start = data[0];
	int k = 0;
	int *a = (int*)malloc(sizeof(int));
	for(int i = 1; i<=start; i++){
		k = k + data[i]*data[i+start];
	}
	*a=k;
	pthread_exit(a);
}

int main(int argc,char *argv[]){
	int row = atoi(argv[1]);
	int col = atoi(argv[2]);
	
	int matrix[row][col];
	int vector[col];
	
	int id = 0;
	int* data = NULL;
	
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			matrix[i][j] = rand()%10;
		}
	}
	
	for(int i=0;i<col;i++){
		vector[i] = rand() % 10;
	}
	
	printf(" *** Matrix ***\n");
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			printf("[ %d ] ",matrix[i][j]);
		}
		printf("\n");
	}
	
	printf(" *** Vector ***\n");
	for(int i=0;i<col;i++){
		printf("[ %d ]\n",vector[i]);
	}
	
	pthread_t *pid;
	pid = (pthread_t*)malloc(row*sizeof(pthread_t));
	
	
	for(int i=0; i<row; i++){
		data = (int*)malloc((100)*sizeof(int));
		data[0] = col;
		
		if(i==0){
			data[i] = col;
		}
		
		for(int k = 0; k<col; k++)
			data[k+1] = matrix[i][k];
			
		for(int k = 0; k<col; k++)
			data[k+col+1] = vector[k];
			
		pthread_create(&pid[id++],NULL,f,(void*)(data));
	}
	
	printf(" *** Result ***\n");
	
	for(int i = 0; i<row; i++){
		void *t;
		pthread_join(pid[i],&t);	
		int *p = (int*)t;	
		printf("[ %d ]\n",*p);
	}
return 0;	
}
	
