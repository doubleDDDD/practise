#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<sys/select.h>

#define NUM 10

int main()
{
	int fd;
	int WD,RD;
	char buff[NUM] = "0821";
	fd = open("/dev/zjzchar", O_RDWR);
	if(fd==-1)
		printf("error\n");
	printf("fd=%d\n",fd);
	WD = write(fd,buff,NUM);
	RD = read(fd,buff,NUM);
	printf("WD=%d RD=%d\n",WD,RD);
	printf("buff=%s\n",buff);
	return 0;
}
