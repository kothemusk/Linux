#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <time.h> 
#include <pthread.h>
#include <stdbool.h>


pthread_mutex_t mutex;

bool inside(const double x, const double y){
	const double circle_x = 0.5;
	const double circle_y = 0.5;
	const double r = 0.5;
	
	const double f = (x-circle_x)*(x-circle_x) + (y-circle_y)*(y-circle_y) - r*r;
	
	if(f>0.0) return false;
	else return true;
}

void *piCal(void *data){
	pid_t pid;
	pthread_t tid;
	
	pid = getpid();
	tid = pthread_self();
	
	int point = *((int*)data);
	int attempt = 0;
	int incircle = 0;
	double max = 32767;
	
	
	
	while(attempt<=point){
		pthread_mutex_lock(&mutex);
		
		float x = (double)rand()/(RAND_MAX);
		float y = (double)rand()/(RAND_MAX);
		if(inside(x,y) == true){
			incircle++;
			
		}
		attempt++;
		pthread_mutex_unlock(&mutex);
	}
	

	pthread_exit((void*)incircle);
}
	


int main(int argc,char *argv[])
{
	int thread_num = atoi(argv[1]);
	int points = atoi(argv[2]);
	pthread_t p_thread[thread_num];
	int thr_id;
	int status;
	
	void *tret;
	float result[thread_num];
	
	for(long i=0; i<thread_num; i++){
		thr_id = pthread_create(&p_thread[i],NULL,piCal,(void*)&points);
		if(thr_id<0){
			perror("thread create error:");
			exit(0);
		}
	}
	
	float sum_ = 0;
	for(long i = 0; i<thread_num; i++){
		pthread_join(p_thread[i],&tret);
		int d = (int)tret;
		result[i] = (float)4*d/points;
		sum_ = sum_+result[i];
		
	}
	
	
	printf("pi : %f\n",sum_/thread_num);
	return 0;
}
