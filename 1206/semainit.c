#include <stdio.h>
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>

int main(){
	sem_t *sem;
	int svalue;
	int ival;

	printf("Enter an integer: ");
	scanf("%d: ", &ival);
	sem = sem_open("test", O_CREAT, 0666, ival); //새로운 세마포어 만들기 -> 마지막 원하는 값으로 초기화
	sem_getvalue(sem, &svalue);
	if (svalue < ival) {
		printf("weq");
		for (int i = svalue; i < ival; i++)
			sem_post (sem);
	}
	else {
		printf("aaa");
		for (int i = svalue; i > ival; i--)
			sem_wait (sem);
	}
	sem_getvalue (sem, &svalue);
	printf("svalue=%d \n", svalue);
}
