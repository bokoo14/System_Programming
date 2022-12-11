#include <stdio.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h> 

int main ()
{
	int msgqid, nread;
	key_t key;
	char buf[100];

	key = 1234;
	msgqid = msgget (key, IPC_CREAT | 0666);
	printf ("msgqpid = %d \n", msgqid);
	nread = msgrcv (msgqid, buf, 100, 0, 0);
	printf ("nread = %d, buf =[%s] \n", nread, buf);
}