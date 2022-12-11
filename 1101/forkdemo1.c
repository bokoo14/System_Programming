#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int sum;
int main (){
	int result, mypid;
	
	mypid = getpid();
	printf("my pid = %d \n", mypid);
	sum++;
	result = fork();
 
	
	sleep(1);
	if (result ==0){//child process
		sleep(3);
		mypid = getpid();
		printf("After fork: ");
		printf("my pid = %d result = %d \n", mypid, result);
	} 
	else{//parent process
		wait(NULL); //내가 fork한 child가 끝날때까지 기다림
		printf("this is a parent\n");
	} 
	

	
}