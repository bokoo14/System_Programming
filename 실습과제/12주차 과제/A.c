#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>


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
	
	sem_getvalue (sem2, &svalue);
	printf("svalue2=%d \n", svalue);

	// 공유메모리 
	key_t key=100;
    int shmid;
    char *shmaddr;
    
    shmid = shmget (key, sizeof(char)*100, IPC_CREAT | 0666);
	
    printf("shmid = %d\n", shmid);
	printf("sem_write = %p\n", sem);	
    printf("sem_read = %p\n", sem2);

    shmaddr = shmat(shmid, NULL, 0);

	do {
		// program A
		//sem_wait(sem); //세마포어 0으로 초기화
		printf("This is ProgramA\n");
		printf ("Enter a string to send in program A: ");
		gets (buf);
		
        //공유메모리에 쓰기
		strcpy(shmaddr, buf);
		sem_post(sem);

		if (!strcmp(buf, "end")) return 0;
        
       // program B 
		sem_wait(sem2);
		printf("This is ProgramB\n");
        strcpy(buf, shmaddr);	
		printf("ProgramB string is %s \n", buf);
	} while (strcmp(buf, "end"));

    shmdt(shmaddr);

	return 0;
}