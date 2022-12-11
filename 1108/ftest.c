#include <stdio.h>

int main(){
	pid = fork();
	
	if (pid ==0){
		strcpy(buf, “This is a child \n”);
		write(fd, buf, strlen(buf)+1);
	}
	else{
		sleep(2);
		read(fd, buf, 100);
		printf(“buf = %s \n”, buf);
	}
	
}