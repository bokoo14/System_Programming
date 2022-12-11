#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main(){
	char msg[100]="";
	int fd1, fd2, nread;
	
	fd1 = open("fifo1", O_RDWR); // 쓰기
	fd2 = open("fifo2", O_RDWR); // 읽기
	
	while(1){
		// 쓰기
		printf("fd in WRITER= %d \n", fd1);
		printf("Enter a string to send : ");
		gets(msg);
		if (!strcmp(msg, "end")){exit(0);}
		write(fd1, msg, sizeof(char)*100+1);
		
		fflush(msg);
		
		// 읽기
		printf("fd2 in READER = %d \n", fd2);
		nread = read(fd2, msg, 100);
		printf("READER : %s \n", msg);
	}

}