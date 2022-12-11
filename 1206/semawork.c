#include <stdio.h>
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include<unistd.h>

int main(){
	sem_t *sem;
	int work_t, i;

	srand(time(NULL));
	sem = sem_open("testsem", O_CREAT, 0666, 1); //새로운 세마포어 만들기 -> 마지막 원하는 값으로 초기화

	for (i=0; i<10; i++){
		printf("Trying to get a semaphore \n");
		sem_wait(sem);

		work_t = rand() %6 +1;
		printf("Working for %d sec \n", work_t);
		sleep(work_t);
		printf("          Done\n\n");

		sem_post(sem);
		sleep(1);
	}
}
