#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <grp.h>
#include <pwd.h>

int ls(char *dir_path, char *option);
int head(char *file_path, char *line);
int tail(char *file_path, char *line);
int mv(char *file_path1, char *file_path2);
int cp(char *file_path1, char *file_path2);
int pwd();

int main(){
	while(1){
		int i, cmdrlt;
		char *cmd;
		char *argument[10];
	        size_t size;	
		
		getline(&cmd, &size, stdin);
		cmd[strlen(cmd) - 1] = '\0';

		if (strlen(cmd) == 0){
			printf("ERROR: invalid command\n");
			continue;
		}
		i = 0;
		char *ptr = strtok(cmd, " ");

		while(ptr != NULL){
			argument[i++] = ptr;
			ptr = strtok(NULL, " ");
		}
		argument[i++] = NULL;
		argument[i++] = NULL;
		argument[i] = NULL;
		

		if (strcmp("ls", argument[0]) == 0){
			cmdrlt = ls(argument[1], argument[2]);		
		}
		else if (strcmp("head", argument[0]) == 0){
			cmdrlt = head(argument[3], argument[2]);
		}
		else if (strcmp("tail", argument[0]) == 0){
			cmdrlt = tail(argument[3], argument[2]);
		}
		else if (strcmp("mv", argument[0]) == 0){
			cmdrlt = mv(argument[1], argument[2]);
		}
		else if (strcmp("cp", argument[0]) == 0){
			cmdrlt = cp(argument[1], argument[2]);
		}
		else if (strcmp("pwd", argument[0]) == 0){
			cmdrlt = pwd();
		}
		else if (strcmp("quit", argument[0]) == 0){
			break;
		}
		else{
			printf("ERROR: invalid command\n");
		}

		if (cmdrlt == -1){
			printf("ERROR: The command is executed abnormally\n");
		}
		printf("\n");
	}
	return 0;
}

int ls(char *dir_path, char *option){
	DIR *dp = NULL;
	struct dirent* entry = NULL;

	if(option == NULL){
	
		if((dp=opendir(dir_path))==NULL)
			return(-1);
	
	
		while((entry=readdir(dp))!=NULL){
			printf("%s ",entry->d_name);
		}
		printf("\n");
	}
	
	else{
		if((dp=opendir(dir_path))==NULL)
			return(-1);
	
	
		while((entry=readdir(dp))!=NULL){
			struct stat file_info;
			struct passwd *passwd;
			struct group *group;
			lstat(entry->d_name,&file_info);
			
			printf((file_info.st_mode & S_IRUSR) ? "r" : "-");
			printf((file_info.st_mode & S_IWUSR) ? "w" : "-");
			printf((file_info.st_mode & S_IXUSR) ? "x" : "-");
			printf((file_info.st_mode & S_IRGRP) ? "r" : "-");
			printf((file_info.st_mode & S_IWGRP) ? "w" : "-");
			printf((file_info.st_mode & S_IXGRP) ? "x" : "-");
			printf((file_info.st_mode & S_IROTH) ? "r" : "-");
			printf((file_info.st_mode & S_IWOTH) ? "w" : "-");
			printf((file_info.st_mode & S_IXOTH) ? "x " : "- ");
			
			printf("%2ld ",file_info.st_nlink);
			
			passwd = getpwuid(file_info.st_uid);
			printf("%6s ",passwd->pw_name);
			
			group = getgrgid(file_info.st_gid);
			printf("%6s ",group->gr_name);
			printf("%6ld ",file_info.st_size);
			printf("%s\n",entry->d_name);
			
		}
	}
	
	
return(0);
}

int head(char *file_path, char *line){
	if(file_path[0] == '/'){
		printf("ERROR: invalid path\n");
		return(-1);
	}
	int fd;
	int linecount = 0;
	char buf[1];
	fd = open(file_path, O_RDONLY);
	if(fd == -1){
		perror("ERROR1");
		return 1;
	}
	while(read(fd,buf,sizeof(buf))==1 && linecount!=atoi(line)){
		if(buf[0] == '\n'){
			printf("\n");
			linecount++;
				
				
		}
		else{
			printf("%s",buf);
		}
			
	}
	
	close(fd);
return(0);
	
}

int tail(char *file_path, char *line){
	if(file_path[0] == '/'){
		printf("ERROR: invalid path\n");
		return(-1);
	}
	int fd_1;
	int linecount = 0;
	char buf[1];
	fd_1 = open(file_path, O_RDONLY);	
	if(fd_1 == -1){
		return -1;
	}

	while(read(fd_1,buf,sizeof(buf))==1){
		if(buf[0] == '\n'){
		linecount++;
		}
		
	}	
	close(fd_1);
	
	
	int fd_2;
	fd_2 = open(file_path, O_RDONLY);
	int linecount_2 = 0;
	int lineFrom = linecount - atoi(line);
	
	while(linecount_2 <lineFrom){
		read(fd_2,buf,sizeof(buf));
		if(buf[0] == '\n'){
			linecount_2++;		
		}
	
	}
	while(read(fd_2,buf,sizeof(buf))==1){
			if(buf[0] == '\n'){
				printf("\n");
				linecount++;
				
			}
			else{
				printf("%s",buf);
			}
			
		}
	
	close(fd_2);
return(0);
}


int mv(char *file_path1, char *file_path2){
	if(file_path1[0] == '/' && file_path2[0] == '/'){
		printf("ERROR: invalid path\n");
		return(-1);
	}
	int before, after;
	char buf[1];
	before = open(file_path1, O_RDONLY);
	
	if(before == -1){
		printf("ERROR: file open failed\n");
		return -1;
	}
	after = open(file_path2, O_WRONLY|O_CREAT, S_IRUSR | S_IWUSR);
	
	if(after == -1){
		return -1;
	}
	
	while(read(before,buf,sizeof(buf))==1){
		write(after,buf,sizeof(buf));
	}
	
	unlink(file_path1);
	
return(0);
	

}

int cp(char *file_path1, char *file_path2){
	if(file_path1[0] == '/' && file_path2[0] == '/'){
		printf("ERROR: invalid path\n");
		return(-1);
	}
	int before, after;
	char buf[1];
	before = open(file_path1, O_RDONLY);
	
	if(before == -1){
		printf("ERROR: file open failed\n");
		return -1;
	}
	after = open(file_path2, O_WRONLY|O_CREAT,S_IRUSR | S_IWUSR);
	
	if(after == -1){
		return -1;
	}
	
	while(read(before,buf,sizeof(buf))==1){
		write(after,buf,sizeof(buf));
	}
return(0);
	
}

int pwd(){
	char dir[50];
	printf("%s\n",getcwd(dir,sizeof(dir)));
	
return(0);
}
