#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int cnt=0;

void my_sig_handler (int signum)
{
    cnt++;
	 if(cnt > 3) {
        exit(1);
    }

    time_t ct;
	struct tm tm;

	ct = time (NULL);
	tm = *localtime (&ct);
	printf("%d-%d-%d %d:%d:%d \n", 1900+tm.tm_year, 1+tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf("Bokyung\n");

 
    alarm(5);
}

int main()
{
    signal (SIGALRM, my_sig_handler);
	alarm(5);

    while(1) {
		
    }

	return 0;
}

