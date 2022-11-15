#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<sys/select.h>
#include<sys/ioctl.h>

int main()
{
	int fd;
	fd = open("/dev/zjzchar", O_RDWR);
	if(fd==-1)
		printf("error\n");
	printf("fd=%d\n",fd);
	int res = ioctl(fd,0,821);
	printf("res = %d\n",res);
	return 0;
}
