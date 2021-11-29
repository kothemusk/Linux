#include <stdio.h>   
#include <fcntl.h>   
#include <stdlib.h>   
#include <sys/socket.h>   
#include <netinet/in.h>   
#include <sys/time.h>   
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXLINE 80   
#define MAX_SOCK 100  

char *escapechar = "quit\n";   
char *bye = "User leaved"; 

int readline(int fd, char *ptr, int maxlen) {
   int n, rc;
   char c;
      for(n = 1; n < maxlen; n++) {
	  if((rc = read(fd, &c, 1)) == 1) {
	     *ptr++ = c;
	        if (c == '\n') break;
	  }
	   
	  else if (rc == 0) {
	        if(n == 1) return (0);
	        else break;
	 }

     }
   *ptr = 0;

   return (n);

} 

 

int s;  

struct Name {   

    char n[20]; 

    int len;  

} name;   

 

int main(int argc, char *argv[]) {   

    char line[MAXLINE], sendline[MAXLINE+1];  

    int n, pid, size;  

    struct sockaddr_in saddr;  

    int nfds;  

    fd_set read_fds; 
    
    struct hostent *h;
    char *host = argv[1];
    int port = atoi(argv[2]);


 

 

   
   printf("Insert your name : ");
   scanf("%s",name.n);
	

    name.len = strlen(name.n);  

 
        if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {   

          printf("Client : Can't open stream socket.\n");   

 return -1;  

    }  
    	if ((h = gethostbyname(host)) == NULL) {
		printf("invalid hostname %s\n", host); 
		exit(2);
	}



	memset((char *)&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	memcpy((char *)&saddr.sin_addr.s_addr, (char *)h->h_addr, h->h_length);
    	saddr.sin_port = htons(port);  



        if(connect(s,(struct sockaddr *)&saddr, sizeof(saddr)) < 0) {   

  printf("Client : Can't connect to server.\n");   

 return -1;  

    }
 

    nfds = s + 1;  

    FD_ZERO(&read_fds);  



    while(1) {  


 FD_SET(0, &read_fds);  

 FD_SET(s, &read_fds); 

  if(select(nfds, &read_fds, (fd_set *)0, (fd_set *)0, (struct timeval *)0) < 0) {   

      printf("select error\n");  

      return -1;  

 }  

  if (FD_ISSET(s, &read_fds)) {   

      char recvline[MAXLINE];  

      int size;  

          if ((size = recv(s, recvline, MAXLINE, 0)) > 0) {   

    recvline[size] = '\0';   

    printf("%s \n", recvline);   

      }  

 } 
	
	
	
	
      if (FD_ISSET(0, &read_fds)) {   

          if (readline(0, sendline, MAXLINE) > 0) {   

      		 size = strlen(sendline);  

		sprintf(line, "%s:%s", name.n, sendline); 
	
    		if (send(s, line, size + name.len, 0) != (size+name.len))   

            	printf("Error : Written error on socket.\n");   

    		if (size == 5 && strncmp(sendline, escapechar, 5) == 0) {   

       		 return -1;  

  		}  

      	}	  

    }
  }
} 
