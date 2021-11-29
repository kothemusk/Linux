#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

void handler(int sig){
	for(int i=0 ; i<5; i++){
		printf("Beep\n");
		sleep(1);	
	}
	printf("I'm Alive\n");
}

void main(){
	signal(SIGINT,handler);
	while(1);
	
	
}
