#include <stdio.h>
#include <fcntl.h>
#include <string.h>

// program B
int main(){
	char msg[100]="";
	int fd1, fd2, nread;
	
	fd1 = open("fifo1", O_RDWR); //읽기
	fd2 = open("fifo2", O_RDWR); //쓰기
	
	
	while(1){
		// 읽기
		printf("fd1 in READER = %d \n", fd1);
		nread = read(fd1, msg, 100);
		printf("READER : %s \n", msg);
		strcat(msg, "bokyung");
		
		fflush(msg);
		//쓰기
		//printf("Enter a string to send fifo2 : ");
		//gets(msg);
		write(fd2, msg, sizeof(char)*100+1);
	}
}