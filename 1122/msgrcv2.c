#include <stdio.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h> 

int main(){
	key_t key = 1234;
	int msgqid;
	int nread;
	char buf[100];
	int data;

	msgqid = msgget(key, IPC_CREAT | 0666);
	printf("msgqid = %d \n", msgqid);
	nread = msgrcv(msgqid, buf, 100, 0, 0);
	nread = msgrcv(msgqid, &data, sizeof(int), 0, 0);
	printf("nread %d buf = [%s] data = [%d] \n", nread, buf, data);
}

