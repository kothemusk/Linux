#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	unsigned int pid;
	time_t t;
	struct tm *tm;	
	int fd;
	char *argv[3];
	char buf[512];
	int fd0, fd1, fd2;
	
	
	pid = fork();
	if(pid == -1) return -1;
	if(pid != 0)
		exit(0);
	if(setsid() < 0)
		exit(0);
	if(chdir("/") < 0)
		exit(0);
	
	fd = open("./crontab", O_RDWR);
	
	umask(0);

	close(0);
	close(1);
	close(2);
	
	fd0 = open("/dev/null", O_RDWR);
	fd1 = open("/dev/null", O_RDWR);
	fd2 = open("/dev/null", O_RDWR);
	
	
	t = time(NULL);
	tm = localtime(&t);
	while (1)
	{	
		
		buf[0] = '\0';	

		//insert your code
		//##  hints  ##
		fd = open("./crontab", O_RDWR);
		read(fd,buf,512);
		char *pos = buf;
		char *token;
		int i = 0;
		while((token = strtok_r(pos," ",&pos))){
			argv[i] = token;
			i++;
			}
		
		
		pid = fork();
		
		if(pid==0){

		
		if((atoi(argv[0])!=0) && (atoi(argv[1])!=0)){
		//분,시 둘다 값이 있을 때 = 24h 마다 반복
			while(1){
				if((tm->tm_min == atoi(argv[0])) && (tm->tm_hour == atoi(argv[1]))){
					execl("/bin/sh", "/bin/sh", "-c", argv[2], (char*) NULL);}
				
			
			}
		}
		if((atoi(argv[0])!=0) && (atoi(argv[1])==0)){
		//분만 값이 있을 때 = 매시간 반복
			while(1){
				if((tm->tm_min == atoi(argv[0]))){
					execl("/bin/sh", "/bin/sh", "-c", argv[2], (char*) NULL);}
				t = time(NULL);
				tm = localtime(&t);
			
			}

		}
		if((atoi(argv[0])==0) && (atoi(argv[1])!=0)){
		//시간만 값이 있을 때 = 그 시간에 매분
			while(1){
				if((tm->tm_hour == atoi(argv[1]))){
					execl("/bin/sh", "/bin/sh", "-c", argv[2], (char*) NULL);}
				t = time(NULL);
				tm = localtime(&t);

		
			}
		}
		
		if((atoi(argv[0])==0) && (atoi(argv[1])==0)){
		//둘다 값이 없을 때 = 매분 반복
			while(1){
			if(tm->tm_sec == 0){
					execl("/bin/sh", "/bin/sh", "-c", argv[2], (char*) NULL);}
			t = time(NULL);
			tm = localtime(&t);
			}
			
		
		}
		}
		wait(NULL);
		close(fd);
		
		t = time(NULL);
		tm = localtime(&t);
		
		sleep(60 - tm->tm_sec % 60);
	}

	return 0;
}
