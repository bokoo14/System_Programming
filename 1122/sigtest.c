#include <stdio.h>
#include <signal.h>

int cnt =0;
int pnum;
int pids[10]; 


void my_sig_handler(int signum){
	//printf(“signum = %d \n”, signum);
	cnt ++;
	//printf(“cnt = %d \n”, cnt);
}

void barrier(){
	int i;
	for (i=0; i<pnum -1; i++){
		kill(pids[i], SIGUSR1);
	}

	//  n개의 프로세스가 barrier를 호출
	while (cnt<pnum-1){
		pause();
	}
	cnt=0;
}

void work(int sec){
	int i, j, k;
	int sum = 0;
	for (i =0; i<sec; i++){
		for (j =0; j<500; j++){
			for (k=0; k<1000000; k++){
				sum++;
			}
		}
	}
}

int main(){
	int i, work_t;
	printf("pid = %d \n", getpid());
	signal (SIGUSR, my_sig_handler);
	printf("Enter the numbe of processes : ");
	scanf("%d", &pnum);
	srand(time(NULL));
	for (i =0; i<pnum-1 ;i++){
		printf("Enter %d process id : ", i);
		scanf("%d", &pids[i]);

	}

	while(1){
		work_t = srand() % 10 +1;
		printf("Working for %d secs ... \n", work_t);
		work(work_t);
		printf("             Done\n");
		printf("");
		barrier();
	}


}