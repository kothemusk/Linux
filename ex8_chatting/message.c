#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/msg.h>
#include <unistd.h>
#include <time.h> 


struct msg
{
	long msgtype;
	/* implement here */
	char text[256]; 
};


struct msg_ack 
{
	long msgtype;
	/* implement here */ 
	char text[256];
};


int main()
{
	/* 
	 * @ int uid: user id 
	 * @ int receiver_id: receveri's id 
	 * */ 
	int uid; 
	int receiver_id; 
		printf("my id is \n");
	scanf("%d", &uid);
	getchar(); // flush   
		printf("who to send\n");
	scanf("%d", &receiver_id); 
	getchar(); // flush  
		
	/* 
	 * code to get key and QID 
	 *
	 *
	 * */ 
	 
	 key_t k1 = 12345;
	 key_t k2 = 67890;
	 
	 int qid_1 = msgget(k1,IPC_CREAT|600);	 
	 if(qid_1 == -1){
	 	perror("msgget1 error:");
	 	exit(0);
	 }
	 
	 int qid_2 = msgget(k2,IPC_CREAT|600);	 
	 if(qid_2 == -1){
	 	perror("msgget2 error:");
	 	exit(0);
	 }
	 	
	time_t seconds = time(NULL);
	
	if (fork() == 0) 
	{
		while (1)
		{
			/* receive message  */ 
			/* get msg from queue and print out */ 
			
			struct msg msg;
			
			if(msgrcv(qid_1,&msg,sizeof(msg),1,0)==-1){
				perror("msg rcv failed");
				exit(0);
			}
			printf("\nRECEIVED %s\n",msg.text);
			printf("%d read message at:\t %s\n",receiver_id,ctime(&seconds));
			
			struct msg_ack msg_ack;
			
			if(msgrcv(qid_2,&msg_ack,sizeof(msg_ack),1,0)==-1){
				perror("msg rcv failed");
				exit(0);
			}
			printf("\nRECEIVED %s\n",msg_ack.text);
			printf("%d read message at:\t %s\n",uid,ctime(&seconds));
			
			
		}		
	
	}
	else
	{
		while (1) 
		{
			/* send message  */ 
			/* get user input and send to the msg queue*/

			struct msg msg;
			msg.msgtype = 1;
			fgets(msg.text,256,stdin);
			if(msgsnd(qid_1,&msg,sizeof(msg),0)==-1){
				perror("msg send fail");
				exit(0);
			}
			
			struct msg_ack msg_ack;
			msg_ack.msgtype = 1;
			fgets(msg_ack.text,256,stdin);
			if(msgsnd(qid_2,&msg_ack,sizeof(msg_ack),0)==-1){
				perror("msg send fail");
				exit(0);
			}
			

		}
		
	}	


	return 0;
}
