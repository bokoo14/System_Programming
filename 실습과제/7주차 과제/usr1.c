#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int pid;

void my_sig_handler (int signum)
{
	printf("usr1 signum = %d \n", signum); //자신의 pid출력
	printf("signal is caught.\n");

    exit(1);
}

int main() {	
	signal (SIGUSR1, my_sig_handler);
	printf("pid = %d \n", getpid());
    printf("scanf usr2 pid : ");
    scanf("%d", &pid); //USR2입력

    kill (pid, 12);
	
	while(1){
	}
	
	return 0;
}

