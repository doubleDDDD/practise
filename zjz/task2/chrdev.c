#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/wait.h>
#include<linux/poll.h>
#include<linux/sched.h>
#include <linux/slab.h>

#define OK 0
#define ERROR -1

struct cdev *gDev;
struct file_operations *gFile;
dev_t devNum;
unsigned int subDevNum = 1;
int reg_major = 121;
int reg_minor = 0;
char* buffer;
int flag = 0;

int testopen(struct inode*p,struct file*f)
{
    printk(KERN_EMERG"test open!\n");
    return 0;
}

ssize_t testwrite(struct file*f,const char __user *u, size_t s,loff_t *l)
{
    printk(KERN_EMERG"test write!\n");
    return 0;
}

ssize_t testread(struct file*f,char __user *u,size_t s,loff_t *l)
{
    printk(KERN_EMERG"test read!\n");
    return 0;
}

static long testioctl(struct file*fd,unsigned int cmd,unsigned long arg)
{
	printk(KERN_EMERG"test ioctl!\n");
	int res = ERROR;
	switch(cmd)
	{
		case 0:printk(KERN_EMERG"cmd = %d   arg = %d\n",cmd,arg);res = OK;break;
		case 1:printk(KERN_EMERG"cmd = %d   arg = %d\n",cmd,arg);res = OK;break;
	}
	return res;
}

int drvInit(void)
{
    devNum = MKDEV(reg_major,reg_minor);
    printk(KERN_EMERG"decive num is %d\n",devNum);
    if(OK==register_chrdev_region(devNum,subDevNum,"zjzchar"))
    {
        printk(KERN_EMERG"register_chrdev_region ok!\n");
    }
    else
    {
        printk(KERN_EMERG"register_chrdev_region error!\n");
        return ERROR;
    }
    gDev = kzalloc(sizeof(struct cdev),GFP_KERNEL);
    gFile = kzalloc(sizeof(struct file_operations),GFP_KERNEL);
    gFile->open = testopen;
    gFile->write = testwrite;
    gFile->read = testread;
    gFile->unlocked_ioctl = testioctl;
    gFile->owner = THIS_MODULE;
    cdev_init(gDev,gFile);
    cdev_add(gDev,devNum,3);
    return 0;
}

void drvExit(void)
{
    cdev_del(gDev);
    unregister_chrdev_region(devNum,subDevNum);
    return;
}

module_init(drvInit);
module_exit(drvExit);
MODULE_LICENSE("Dual BSD/GPL");
