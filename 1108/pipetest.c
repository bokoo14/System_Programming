#include <stdio.h>
#include <fcntl.h>

int main ()
{
	int pid, result1, result2, data;
	int fd1[2];
	int fd2[2];
	char buf[100];

	result1 = pipe(fd1);
	result2 = pipe(fd2);
	printf ("result1 = %d, fd1[0] = %d fd1[1] = %d\n", result1, fd1[0], fd1[1]);
	printf ("result2 = %d, fd2[0] = %d fd2[1] = %d\n", result2, fd2[0], fd2[1]);
	
	pid = fork ();
	if (pid == 0) {
		close (fd1[1]);
		read (fd1[0], buf, 100);
		printf ("CHILD1 : %s \n", buf);
		read (fd1[0], &data, sizeof(int));
		printf ("CHILD1 : data = %d\n", data);
		
		close (fd2[0]);
		read (fd2[1], buf, 100);
		printf ("CHILD2 : %s \n", buf);
		read (fd2[1], &data, sizeof(int));
		printf ("CHILD2 : data = %d\n", data);	
	}
	else {
		close (fd1[0]);
		strcpy (buf, "hello this is 1");
		write (fd1[1], buf, strlen(buf) + 1);
		sleep (2);
		data = 20;
		write (fd1[1], &data, sizeof(int));
		wait (pid);
		
		close (fd2[1]);
		strcpy (buf, "hi this is 2");
		write (fd2[0], buf, strlen(buf) + 1);
		sleep (2);
		data = 10;
		write (fd2[0], &data, sizeof(int));
		wait (pid);
	}

	/*
	if (pid == 0) {
		strcpy (buf, "This is a child.\n");
		write (fd, buf, strlen(buf) + 1);
	}
	else {
		strcpy (buf, "This is a parent.\n");
			write (fd, buf, strlen(buf) + 1);
	}
	*/
	close (fd1);
	close (fd2);
}