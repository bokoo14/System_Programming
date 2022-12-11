#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
struct Node {
	int a;
	float b;
	char name[12];
};

int main ()
{
	int fd;
	struct Node node1;
	struct Node node2;
	struct Node node3;
	struct Node node4;
	struct Node node5;
	
	fd = open ("data3.txt", O_RDWR | O_CREAT);
	read (fd, &node1, sizeof(struct Node));
	read (fd, &node2, sizeof(struct Node));
	read (fd, &node3, sizeof(struct Node));
	read (fd, &node4, sizeof(struct Node));
	read (fd, &node5, sizeof(struct Node));
	
	printf ("node1.a = %d\n", node1.a);
	printf ("node1.b = %f\n", node1.b);
	printf ("node1.name = %s\n", node1.name);
	
	printf ("node2.a = %d\n", node2.a);
	printf ("node2.b = %f\n", node2.b);
	printf ("node2.name = %s\n", node2.name);
	
	printf ("node3.a = %d\n", node3.a);
	printf ("node3.b = %f\n", node3.b);
	printf ("node3.name = %s\n", node3.name);
	
	printf ("node4.a = %d\n", node4.a);
	printf ("node4.b = %f\n", node4.b);
	printf ("node4.name = %s\n", node4.name);
	
	printf ("node5.a = %d\n", node5.a);
	printf ("node5.b = %f\n", node5.b);
	printf ("node5.name = %s\n", node5.name);
	
	close (fd);
}