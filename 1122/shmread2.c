#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int main ()
{
	int shmid;
	int data;
	char *shmaddr;
	key_t key = 1235;

	shmid = shmget (key, sizeof(int), IPC_CREAT | 0666);
	printf ("shmid = %d \n", shmid);

	shmaddr = shmat (shmid, NULL, 0);
	printf ("shmaddr = %p \n", shmaddr);

	data = *((int*)shmaddr);
	printf ("data = %d \n", data);

	shmdt (shmaddr);
}
