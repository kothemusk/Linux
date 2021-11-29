#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <assert.h>
#include <sys/select.h>
#include <stdbool.h>
  
typedef struct _query {
    int user;
    int action;
    int data;
} query;

typedef struct _info {
    int id;
    int pw;
    int seat;
    bool status;
} info;

info info_ur[1024];
int seat[257] = {[0 ... 256] = -1};
bool login;

void *thread_func(void *arg){
	query *q;
	int n;
	int buf[15];
	int passcode = 0;
	int connfd = *((int*)arg);
	
	int success = 1;
	int fail = -1;
	
	pthread_detach(pthread_self());
	free(arg);
	while((n = recv(connfd, buf, sizeof(buf), 0)) > 0 ){
		q = (query *)buf;
		//info *info_ur = malloc(sizeof(info));
		printf("%d %d %d\n", q->user, q->action, q->data);
		int user = q->user;
		int action = q->action;
		int data = q->data;
		if(q->action == 1){
			printf("----------Log in-----------\n");
			
			if(info_ur[user].id == 0){//register
				info_ur[user].id = user;
				info_ur[user].pw = data;
				info_ur[user].status = true;
				send(connfd,(char*)&success,sizeof(int),0);
				printf("register completed!\n");
			}
			else if(info_ur[user].pw != data){//wrong pw
				send(connfd,(char*)&fail,sizeof(int),0);
				printf("worng pw..\n");
			}
			else if(info_ur[user].status == 1){
				send(connfd,(char*)&fail,sizeof(int),0);
				printf("User already used in different client..\n");
			}
			else{
				send(connfd,(char*)&success,sizeof(int),0);
				info_ur[user].status = true;
				printf("login success!\n");
			}
		}
		else if(q->action == 2){
			printf("----------Reserve----------\n");
			int location = q->data;
			if(info_ur[user].status == false){
				send(connfd,(char*)&fail,sizeof(int),0);
				printf("register first..\n");
			}
			else if(info_ur[user].status == true){	
				if((q->data < 0) || (q->data > 255)){
					send(connfd,(char*)&fail,sizeof(int),0);
					printf("location out of range..\n");
				}
				else if(seat[location] != -1){
					send(connfd,(char*)&fail,sizeof(int),0);
					printf("location already occupied..\n");
				}
				else{
					seat[location] = user;
					info_ur[q->user].seat = location;
					send(connfd,(char*)&info_ur[user].seat,sizeof(int),0);
					printf("location success!\n");
				}
			}

		}
		else if(q->action == 3){
			printf("---------Check reservation---------\n");
			if(info_ur[user].status == false){
				send(connfd,(char*)&fail,sizeof(int),0);
				printf("login first..\n");
			}
			else if(info_ur[user].status == true){
				if(info_ur[user].seat == 0){
					send(connfd,(char*)&fail,sizeof(int),0);
					printf("No reserved seat..\n");
				}
				else if(info_ur[user].seat != 0){
					send(connfd,(char*)&info_ur[user].seat,sizeof(int),0);
				}
			}
		}
		else if(q->action == 4){
			printf("----------Cancel reservation----------\n");
			if(info_ur[user].status == false){//info_ur[user].pw == 0
				send(connfd,(char*)&fail,sizeof(int),0);
				printf("login first..\n");
			}
			else if(info_ur[user].status == true){
				if(info_ur[user].seat == 0){
					send(connfd,(char*)&fail,sizeof(int),0);
					printf("No reserved seat..\n");
				}
				else{
					seat[data] = -1;			
					send(connfd,(char*)&info_ur[user].seat,sizeof(int),0);
					info_ur[q->user].seat = 0;
					printf("cancel completed.!\n");
				}
			}
			
		}
		else if(q->action == 5){
			printf("-----------Log out-----------\n");
			if(info_ur[user].status == false){
				send(connfd,(char*)&fail,sizeof(int),0);
				printf("login first..\n");
			}
			else{
				send(connfd,(char*)&success,sizeof(int),0);
				info_ur[user].status = false;
			}		
		}
		
		else if (!(q->user | q->action | q->data)){
			send(connfd, seat, sizeof(seat), 0);
			int i;
			for(i=1;i<=256;i++) printf("%d ", seat[i]);
			printf("\n");
			printf("connection terminated\n");
			close(connfd);
			pthread_exit(info_ur);
			return NULL;
		}
		
		else{
			send(connfd,(char*)&fail,sizeof(int),0);
		}
	for(int i=0; i<1024; i++){
		if(info_ur[i].id != 0){
			printf("id(max=1024) : %d , pw : %d , seat : %d , status : %d\n",info_ur[i].id,info_ur[i].pw,info_ur[i].seat,info_ur[i].status);
		}
	}
	printf("---------------------------------\n");
	}
}

int main (int argc, char *argv[]) {

	int n, listenfd, caddrlen;
	struct hostent *h;
	struct sockaddr_in saddr, caddr;
	
	int port = atoi(argv[2]);
	
	
	
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("socket() failed.\n");
		exit(1);
	}

	memset((char *)&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = inet_addr(argv[1]);   
	if (bind(listenfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
		printf("bind() failed.\n");
		exit(2);
	}
	
	if (listen(listenfd, 1024) < 0) {
		printf("listen() failed.\n");
		exit(3);
	}
	
	
	int success = 1;
	int fail = -1;
	
	int *accepted_fd;
	pthread_t tid;
	
	int fdmax = listenfd,fdnum;
	int seat[257] = {0};
	int passcode = 0;
	while (1) {
		accepted_fd = (int*)malloc(sizeof(int));
		if((*accepted_fd = accept(listenfd, (struct sockaddr *)&caddr,(socklen_t *)&caddrlen)) < 0){
			printf("accept failed\n");
			free(accepted_fd);
			continue;
		}
		pthread_create(&tid,NULL, thread_func,accepted_fd);
		
		
		//void *result;
		//pthread_join(tid,&result);	
		//info *info_ur = result;
		//printf("user id : %d , pw : %d\n",info_ur->id, info_ur->pw);
		
		//free(info_ur);
		
	}
	
	
	
	
	return 0;
}

