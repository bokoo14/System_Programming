#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

int main(){
	key_t key;
	int shmid;
	int *shmaddr;

	key=100;
	shmid=shmget(key,sizeof(int), IPC_CREAT | 0666); //공유 메모리에 값을 씀
	shmaddr = shmat(shmid, 0, 0);
	printf("shmaddr = %p \n", shmaddr);
	*shmaddr = 0;
	shmdt(shmaddr);
}