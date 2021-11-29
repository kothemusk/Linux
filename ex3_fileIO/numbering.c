
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



int main(void){

char filename[] = "Aladdin.txt";
int fd,fd_num;
char buffer[15];
char buffer_check[1];

fd = open(filename, O_RDWR);
if(fd == -1){
	perror("ERROR1");
	return 1;
}

fd_num = open("Aladdin_num.txt", O_WRONLY | O_CREAT | O_TRUNC,S_IRWXU);
if(fd_num == -1){
	perror("ERROR2");
	return 1;
}



int count = 0;
int line = 1;

write(fd_num,"1 | ",4);

while(read(fd,buffer_check,1==1)){
write(fd_num,buffer_check,1);
if(buffer_check[0]=='\n'){

	int index = 0;
	line++;
	int newline = line;
	
	for(int a = line; a!=0;a/=10){
	index++;}
	
	char line_buffer[index];
	int realIndex = index -1 ;
	while(newline > 0 ){
	line_buffer[realIndex] = newline%10 + '0';
	realIndex--;
	newline /= 10;}
	
	write(fd_num,line_buffer,sizeof(line_buffer));
	write(fd_num," |  ",4);
	lseek(fd_num,-1,SEEK_CUR);
}

}

close(fd);
close(fd_num);
}

	





