#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/io.h>
#include <linux/errno.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/slab.h>

#define MAX_SIZE 0x1000
#define DEVICE_NAME "My_Dev"

struct my_dev
{
	dev_t dev_num;		//device number
	struct cdev dev_cdev;	//cdev
	struct class *dev_class;//class
	struct device *dev_device;	//device
	int major;		//major number
	int minor;		//minor number
	unsigned char dev_mem[MAX_SIZE];
};

struct my_dev dev_main;		//main device

//open
static int my_dev_open(struct inode *inode, struct file *file)
{
	printk("my_dev_open succeed.\n");
	return 0;
}

//release
static int my_dev_release(struct inode *inode, struct file *file)
{
	printk("my_dev_release succeed,\n");
	return 0;
}

//read
static ssize_t my_dev_read(struct file *file, char __user *user, size_t t, loff_t *f)
{
	int ret;
	char buffer[50] = "Read test!";

	if(copy_to_user(user,buffer,t)){
		ret = -EFAULT;
	}else{
		ret = t;
	}
	return ret;
}

//write
static ssize_t my_dev_write(struct file *file, const char __user *user, size_t t, loff_t *f)
{
	int ret;
	char buffer[50];

	if(copy_from_user(buffer,user,t)){
		ret = -EFAULT;
	}else{
		ret = t;
		printk("kernal gets:%s\n",buffer);
	}
	return ret;
}

//file operations
static const struct file_operations my_dev_fops =
{
	.owner = THIS_MODULE,
	.open = my_dev_open,
	.release = my_dev_release,
	.read = my_dev_read,
	.write = my_dev_write,
};

// register
static int __init my_dev_init(void)
{
	int ret;
	printk("Register start!\n");
	
	//allocate device number
	if(dev_main.major){
		if(dev_main.minor){
			dev_main.dev_num = MKDEV(dev_main.major,dev_main.minor);
		}else{
			dev_main.dev_num = MKDEV(dev_main.major,0);
		}
		register_chrdev_region(dev_main.dev_num,1,DEVICE_NAME);
	}else{
		ret = alloc_chrdev_region(&dev_main.dev_num,0,1,DEVICE_NAME);
		if(ret < 0){
			printk("My_Dev register failure.\n");
			unregister_chrdev_region(dev_main.dev_num,1);
			return ret;
		}
		dev_main.major = MAJOR(dev_main.dev_num);
		dev_main.minor = MINOR(dev_main.dev_num);
	}
	printk("dev_main.major = %d\ndev_main.minor = %d\n",dev_main.major,dev_main.minor);

	//register char device
	dev_main.dev_cdev.owner = THIS_MODULE;
	cdev_init(&dev_main.dev_cdev,&my_dev_fops);
	if((ret = cdev_add(&dev_main.dev_cdev,dev_main.dev_num,1)) < 0){
		printk(KERN_NOTICE"error %d adding %s device\n",ret,DEVICE_NAME);
		unregister_chrdev_region(dev_main.dev_num,1);
		return ret;
	}

	//create device
	dev_main.dev_class = class_create(THIS_MODULE,DEVICE_NAME);
	if(IS_ERR(dev_main.dev_class)){
		printk("ERROR:cannot create a cdev_class.\n");
		unregister_chrdev_region(dev_main.dev_num,1);
		return -1;
	}
	dev_main.dev_device = device_create(dev_main.dev_class,NULL,dev_main.dev_num,0,DEVICE_NAME);
	if(IS_ERR(dev_main.dev_device)){
		ret = PTR_ERR(dev_main.dev_device);
		unregister_chrdev_region(dev_main.dev_num,1);
                return -1;
	}
	return ret;
}

// exit
static void __exit my_dev_exit(void)
{
	cdev_del(&dev_main.dev_cdev);
	device_destroy(dev_main.dev_class,dev_main.dev_num);
	class_destroy(dev_main.dev_class);
	unregister_chrdev_region(dev_main.dev_num,1);
	printk("exit successful.\n");
	return;
}

module_init(my_dev_init);
module_exit(my_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ycyz");
