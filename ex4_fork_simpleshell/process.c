
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>



int main(void){


int status;
int endPid;
size_t size;
pid_t pid;
do{
	
	char *cmd;
	const char *arg[10];
	char path[100];
	getline(&cmd,&size,stdin);
	
	cmd[strlen(cmd)-1] = '\0';
	
	int i=0;
	char *ptr = strtok(cmd," ");
	
	while(ptr != NULL){
		arg[i] = ptr;
		ptr = strtok(NULL," ");
		i++;
		
	}
	arg[i] = NULL;
	if(strcmp(arg[0],"quit")==0){
			exit(0);
			}
	
	pid = fork();
	sprintf(path, "/bin/%s",arg[0]);

if(pid == 0){
	execl(path,arg[0],arg[1],NULL);
	
}
if(pid>0){
	wait(NULL);
	}
}while(1);

}

	





