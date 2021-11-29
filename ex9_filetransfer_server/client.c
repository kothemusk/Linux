#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char *argv[]) {
	
	while(1){
		char name[50];
		char new_name[55];
		
		char *buffer;
		printf("File name : ");
		scanf("%s",name);
		
		strcpy(new_name,name);
		strcat(new_name,"_copy");
		
		if(strcmp(name,"quit")==0){
			exit(0);
		}
	
	int n, cfd;
	struct hostent *h;
	struct sockaddr_in saddr;
	char buf[256];
	char *host = argv[1];
	int port = atoi(argv[2]);
	
	if ((cfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("socket() failed.\n"); 
		exit(1);
	}
	
	if ((h = gethostbyname(host)) == NULL) {
		printf("invalid hostname %s\n", host); 
		exit(2);
	}
	
	memset((char *)&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	memcpy((char *)&saddr.sin_addr.s_addr, (char *)h->h_addr, h->h_length);
	saddr.sin_port = htons(port);
	
	if (connect(cfd,(struct sockaddr *)&saddr,sizeof(saddr)) < 0) {
		printf("connect() failed.\n");
		exit(3);
	}
	

		
		size_t fsize,rsize = 0;
		size_t fsize_2;
		
		
		
		
		FILE *file = NULL;
		file = fopen(name,"rb");
	
		fseek(file,0,SEEK_END);
		fsize = ftell(file);
		fseek(file,0,SEEK_SET);
		
		fsize_2 = htons(fsize);
		send(cfd,&fsize_2,sizeof(fsize_2),0);
		
		send(cfd,new_name,55,0);
		
		
		while(rsize!=fsize){
			int fpsize = fread(buf,1,256,file);
			rsize += fpsize;
			send(cfd,buf,fpsize,0);
		}
	
	fclose(file);
	close(cfd);
	}
	
	return 0;
}
