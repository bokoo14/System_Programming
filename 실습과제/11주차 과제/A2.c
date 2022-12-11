#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h> 


//program A2
int main(){
	// A
	int msgqid;
	key_t key;
	char buf[100];

	// B
	int nread2;
	int msgqid2;
	key_t key2;
	char buf2[100];

	key = 1234;
	msgqid = msgget (key, IPC_CREAT | 0666);

	key2 = 1235;
	msgqid2 = msgget (key2, IPC_CREAT | 0666);
	
	while(1){
		// program A : key = 1234에 쓰기
		printf("This is Program1\n");
		//printf ("msgqpid = %d \n", msgqid);
		printf ("Enter a string to send in program A: ");
		gets (buf);
		msgsnd (msgqid, buf, strlen(buf) + 1, 0);
		if (!strcmp(buf, "end")){exit(0);}


		// program B : key = 1235에서 읽기
		printf("This is Program2\n");
		//printf ("msgqpid2 = %d \n", msgqid2);
		nread2 = msgrcv (msgqid2, buf2, 100, 0, 0);
		printf ("nread = %d, buf =[%s] \n", nread2, buf2);

	}

}


