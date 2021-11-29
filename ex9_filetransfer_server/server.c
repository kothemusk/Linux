#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#define MAXLINE 256


int main (int argc, char *argv[]) {
	int n, listenfd, connfd, caddrlen;
	struct hostent *h;
	struct sockaddr_in saddr, caddr;
	char buf[256];
	int port = atoi(argv[1]);
	
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("socket() failed.\n");
		exit(1);
	}
	
	memset((char *)&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(port);   
	if (bind(listenfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
		printf("bind() failed.\n");
		exit(2);
	}
	
	if (listen(listenfd, 5) < 0) {
		printf("listen() failed.\n");
		exit(3);
	}
	
	while (1) {
	caddrlen = sizeof(caddr);
	if ((connfd = accept(listenfd, (struct sockaddr *)&caddr,(socklen_t *)&caddrlen)) < 0) {
		printf ("accept() failed.\n");
		continue;
	}
	// echo

	int nbyte = 256;
	size_t filesize = 0, bufsize = 0;
	FILE *file = NULL;
	ntohs(filesize);
	recv(connfd,&filesize,sizeof(filesize),0);
	ntohs(filesize);
	printf("got %ld bytes from client. \n",filesize);
	
	char new_name[55];
	
	recv(connfd,new_name,55,0);
	
	file = fopen(new_name,"wb");
	
	bufsize = 256;
	while(nbyte!=0){
		nbyte = recv(connfd, buf, bufsize, 0);
		fwrite(buf,sizeof(char),nbyte,file);
	}
	
	close(connfd);
	}
	
	return 0;
}
