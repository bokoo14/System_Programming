#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>


//program B
int main() {
	// A
	sem_t *sem;
	int work_t, i;
	sem = sem_open("Program A", O_CREAT, 0666, 0); 
	char buf[100];
	
	int svalue;
	sem_getvalue (sem, &svalue);
	printf("svalue=%d \n", svalue);
		   
	// B
	sem_t *sem2;
	int work_t2, i2;
	sem2 = sem_open("Program B", O_CREAT, 0666, 0); 
	//sem_wait(sem2); //세마포어 0으로 초기화
	char buf2[100];
	
	sem_getvalue (sem2, &svalue);
	printf("svalue2=%d \n", svalue);
	
	// 공유메모리 
	key_t key=100;
    int shmid;
    char *shmaddr;

    shmid = shmget (key, sizeof(char)*100, IPC_CREAT | 0666);
    printf("shmid = %d \n", shmid);
    printf("sem1 is %p \n", sem);
    printf("sem2 is %p \n", sem2);
	
	shmaddr = shmat(shmid, NULL, 0);
	

	do {
		// program B 
		sem_wait(sem);
		printf("This is ProgramB\n");
		strcpy(buf, shmaddr);

		strcat(buf, "bokyung");
		printf("string + bokyung = %s \n", buf);

		if (!strcmp(buf, "endbokyung")) return 0;

        sleep(2);

        //공유 메모리에 쓰기
		strcpy(shmaddr, buf);
		
		//program A
		sem_post(sem2);

	} while (strcmp(buf, "end"));

    shmdt(shmaddr);

	return 0;
}