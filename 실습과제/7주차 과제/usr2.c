#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int pid;

void my_sig_handler (int signum)
{
	printf("usr2 signum = %d \n", signum);
	printf("signal is caught.\n");
	printf("usr1 input pid : ");
    scanf("%d: ", &pid); //USR1입력

    kill (pid, 10); //받으면 USR1전송

    exit(0);
}

int main() {
	signal (SIGUSR2, my_sig_handler);
	printf("pid = %d \n", getpid());
    while(1){};
	return 0;
}

