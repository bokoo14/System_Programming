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

	shmaddr = shmat (shmid, NULL, 0); //변수의 주소
	printf ("shmaddr = %p \n", shmaddr);

	printf ("Enter an integer to write: ");
	scanf ("%d", &data);

	*((int*)shmaddr) = data; //int형으로 쓰려면

	shmdt (shmaddr);
}