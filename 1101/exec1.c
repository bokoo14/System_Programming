#include <unistd.h>
#include <stdio.h>

int main(){
	char* arglist[3];
	arglist[0]="./a.out";
	arglist[1]="NULL";
	
	printf("my pid= %d\n ", getpid());
	sleep(1);
	execvp("./a.out", arglist);
	printf("*** ./a.out is done \n");
}

