#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>

int read_test(void)
{
	int file, i, ret;
	char read_buf[50] = {'\0'};
	file = open("/dev/My_Dev",O_RDWR,S_IRUSR|S_IWUSR);
	if(file != -1)
	{
		ret = read(file,read_buf,sizeof(read_buf));
		if(ret < 0){
			printf("read error!\n");
			return -1;
		}
		printf("read_buf is %s\n",read_buf);
		close(file);
	}
	else
	{
		printf("Device open failed when reading!\n");
	}
	return 0;
}

int write_test(void)
{
	int file;
	char msg[50] = "Everything Sucks";
        file = open("/dev/My_Dev",O_RDWR,S_IRUSR|S_IWUSR);
        if(file != -1)
        {
		//printf("Input string to write:(\"quit\" to exit)");
		//scanf("%s",msg);
		write(file,msg,sizeof(msg));
		close(file);
        }
        else
        {
                printf("Device open failed when writing!\n");
        }
        return 0;
}

int main(void)
{
	read_test();
	write_test();
	read_test();
	return 0;
}
