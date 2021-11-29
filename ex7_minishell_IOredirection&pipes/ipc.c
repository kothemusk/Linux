
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>


void redir_in(const char *cmd){
	int fd0 = open(cmd, O_RDONLY);
	dup2(fd0,STDIN_FILENO);
	close(fd0);
}

void redir_out(const char *cmd){
	int fd1 = open(cmd,O_RDWR|O_CREAT,0644);
	dup2(fd1,STDOUT_FILENO);
	close(fd1);
}

int main(void){


int status;
int endPid;
size_t size;
pid_t pid;
do{
	printf("$ ");
	char *cmd;
	char cmd_2[20];
	
	char *text1 = NULL;
	char *text2 = NULL;
	char *command1[10];
	char *command2[10];
	char *temp;
	
	
	const char *arg[10];
	char path[100];
	int index = 0;
	getline(&cmd,&size,stdin);
	
	char *ptr_out = strchr(cmd,'>');
	char *ptr_in = strchr(cmd,'<');
	char *ptr_pipe = strchr(cmd,'|');
	
		cmd[strlen(cmd)-1] = '\0';
		text1 = strtok(cmd,"|");
		text2 = strtok(NULL, "|");
		
		strcat(text1,"\0");
		strcat(text2, "\0");
		
		
	
		int k = 0;
		
		temp = strtok(text1," ");
		while(temp!=NULL){
			command1[k] = temp;
			temp = strtok(NULL," ");
			k++;
		}
		command1[k] = (char*)0;
		
		
		k = 0;
		
		temp = strtok(text2," ");
		while(temp!=NULL){
			command2[k] = temp;
			temp = strtok(NULL," ");
			k++;
		}
		command2[k] = (char*)0;
	
	//int i=0;
	//char *ptr = strtok(cmd," ");
	
	//while(ptr != NULL){
		//arg[i] = ptr;
		//ptr = strtok(NULL," ");
		//i++;
		
	//}
	
	//arg[i] = NULL;
	if(strcmp(command1[0],"quit")==0){
			return(0);
			}
			
	sprintf(path, "/bin/%s",command1[0]);
	
	pid = fork();
	


	if(pid == 0){

		if(ptr_in != NULL){
			redir_in(command1[3]);
			execl(path,command1[0],command1[1],NULL);
		}
		
		if(ptr_out != NULL){
			redir_out(command1[3]);
			execl(path,command1[0],command1[1],NULL);
		}
		
		if(ptr_pipe != NULL){
		int fd[2];
		pid_t pid1;
		


		
		pipe(fd);
		
		switch(fork()){
			case -1: perror("fork error"); break;
			case 0: if(close(1) == -1) perror("close");
				if(dup(fd[1]) != 0);
				if(close(fd[0]) == -1 || close(fd[1]) == -1){
					perror("close1");
				}
				execvp(command1[0], command1);
				exit(0);
			default: if(close(0) == -1) perror("close2");
				if(dup(fd[0]) == -1 || close(fd[1]) == -1) perror("close4");
				execvp(command2[0],command2);
				exit(0);
		}
		
		if(close(fd[0]) == -1 || close(fd[1]) == -1) perror("close55");
		while(wait(NULL)!= -1);
		}
			
		else{
		execl(path,command1[0],command1[1],NULL);
		}
		
	
	
}
	if(pid>0){
		wait(NULL);
	}
	
}while(1);

}

	





