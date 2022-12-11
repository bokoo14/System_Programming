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
	node1.a = 10;
	node1.b = 3.14;
	strcpy (node1.name, "Kim");
	
	struct Node node2;
	node2.a = 11;
	node2.b = 4.14;
	strcpy (node2.name, "Park");
	
	struct Node node3;
	node3.a = 12;
	node3.b = 5.14;
	strcpy (node3.name, "KK");
	
	struct Node node4;
	node4.a = 13;
	node4.b = 6.14;
	strcpy (node4.name, "CC");
	
	struct Node node5;
	node5.a = 14;
	node5.b = 7.14;
	strcpy (node5.name, "DD");

	
	fd = open ("data3.txt", O_RDWR | O_CREAT | S_IWUSR | S_IRUSR);
	write (fd, &node1, sizeof(struct Node));
	write (fd, &node2, sizeof(struct Node));
	write (fd, &node3, sizeof(struct Node));
	write (fd, &node4, sizeof(struct Node));
	write (fd, &node5, sizeof(struct Node));
	
	close (fd);
}