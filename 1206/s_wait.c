#include <stdio.h>
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>

int main(){
	sem_t *sem;
	int svalue;
	int ival;

	sem = sem_open("testsem", O_CREAT, 0666, 0); //새로운 세마포어 만들기 -> 마지막 원하는 값으로 초기화
	sem_wait(sem);


	printf("wait is done \n");
}
