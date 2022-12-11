#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h> 


//program B2
int main(){
	// B
	int msgqid;
	key_t key;
	char buf[100];

	// A
	int nread2;
	int msgqid2;
	key_t key2;
	char buf2[100];

	key2 = 1234;
	msgqid2 = msgget (key2, IPC_CREAT | 0666);

	key = 1235;
	msgqid = msgget (key, IPC_CREAT | 0666);
	
	
	while(1){
		// program B : key = 1234에서 읽기
		printf("This is Program1\n");

		//printf ("msgqpid2 = %d \n", msgqid2);
		nread2 = msgrcv (msgqid2, buf2, 100, 0, 0);
		printf ("nread = %d, buf =[%s] \n", nread2, buf2);
		strcat(buf2, "bokyung");
		printf ("nread = %d, buf =[%s] \n", nread2, buf2);


		// program B : key = 1235에 쓰기
		printf("This is Program2\n");
		//printf ("msgqpid = %d \n", msgqid);
		msgsnd (msgqid, buf2, strlen(buf2) + 1, 0); //문자열+bokyung보내기

	}

}


