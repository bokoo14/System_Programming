#include <stdio.h>
#include <signal.h>

int main(){
	for(int i =0; i<3; i++){
		printf("Hello\n");
		sleep(1);
	}
}