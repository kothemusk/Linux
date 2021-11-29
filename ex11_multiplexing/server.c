#include   <stdio.h> 
#include   <fcntl.h> 
#include   <stdlib.h> 
#include   <signal.h> 
#include   <sys/socket.h> 
#include   <sys/file.h> 
#include   <netinet/in.h> 
#include <string.h>
#define MAXLINE    1024 
#define MAX_SOCK    512 

  

char *escapechar = "quit\n"; 
int readline(int fd, char *ptr, int maxlen) {

   int n, rc;

   char c;

      for(n = 1; n < maxlen; n++) {

  if((rc = read(fd, &c, 1)) == 1) {

     *ptr++ = c;

        if (c == '\n') break;

  } else if (rc == 0) {

        if(n == 1) return (0);

     else break;

 }

   }

   *ptr = 0;

   return (n);

} 
 

int main(int argc, char *argv[])    { 

   char   rline[MAXLINE], my_msg[MAXLINE]; 

   char   *start = "User joined"; 

   int  i, j, n; 

   int  s, client_fd, clilen; 

   int  nfds; 

   fd_set  read_fds; 

   int  num_chat = 0;

   int  client_s[MAX_SOCK]; 
   
   char name[20];

   struct sockaddr_in  client_addr, server_addr; 


   

      if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0){
      	printf("Server: Can't open stream socket.");    
      	return -1; 
	} 

   

   bzero((char *)&server_addr, sizeof(server_addr));   

   server_addr.sin_family = AF_INET;               

   server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 

   server_addr.sin_port = htons(atoi(argv[1]));      

    

      if (bind(s,(struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) { 

      printf("Server: Can't bind local address.\n"); 

      return -1; 

   } 



   listen(s, 5); 

   nfds = s + 1;  

   FD_ZERO(&read_fds); 

    

   while(1) { 


      if ((num_chat-1) >= 0)  nfds = client_s[num_chat-1] + 1; 



      FD_SET(s, &read_fds); 

      for (i=0; i<num_chat; i++)  FD_SET(client_s[i], &read_fds); 

       
 if (select(nfds, &read_fds, NULL, NULL,NULL) < 0) { 

       printf("select() error\n"); 

       return -1; 

      } 


      if (FD_ISSET(s, &read_fds)) { 

       clilen = sizeof(client_addr); 

       client_fd = accept(s, (struct sockaddr *)&client_addr, &clilen); 

 
	
	
       if (client_fd != -1)  { 

        client_s[num_chat] = client_fd;  

        num_chat++; 

        send(client_fd, start, strlen(start), 0); 


       } 

      } 


      for (i = 0; i < num_chat; i++)  { 

      if (FD_ISSET(client_s[i], &read_fds)) { 

         if ((n = recv(client_s[i], rline, MAXLINE,0))  > 0)  { 

           rline[n] = '\0'; 
           printf("got %d byte from user\n",n);
           



           if (exitCheck(rline, escapechar, 5) == 1) { 

         shutdown(client_s[i], 2); 

         if(i != num_chat-1)  client_s[i] = client_s[num_chat-1]; 

         num_chat--; 

         continue; 

           } 

            for (j = 0; j < num_chat; j++)  send(client_s[j], rline, n, 0); 


         } 

      } 

   } 

} 

 }

int exitCheck(rline, escapechar, len) 

  char  *rline;    

  char  *escapechar; 

  int    len; 

  { 

     int  i, max; 

     char  *tmp; 

    

     max = strlen(rline);   

     tmp = rline; 

     for(i = 0; i<max; i++) { 

        if (*tmp == escapechar[0]) { 

          if(strncmp(tmp, escapechar, len) == 0) 

          return 1; 

        } else  

  tmp++; 

     }  

   return -1; 

} 




