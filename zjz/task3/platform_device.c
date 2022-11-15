#include <linux/init.h>                                                                                                                      
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/ioport.h>
#include<linux/fs.h>
#include<linux/wait.h>
#include<linux/poll.h>
#include<linux/sched.h>
#include <linux/slab.h>

struct platform_device *pDev;

static void testrelease(struct device *dev)
{
    return;
}
 
static int testinit(void)
{
	printk(KERN_EMERG"device init!\n");
	pDev = kzalloc(sizeof(struct platform_device),GFP_KERNEL);
	pDev->name = "zjzDev";
	pDev->id = 3;
	pDev->dev.release = testrelease;
	return platform_device_register(pDev);
}

static void testexit(void)
{
	printk(KERN_EMERG"device exit!\n");
	platform_device_unregister(pDev);
	return;
}

MODULE_LICENSE("Dual BSD/GPL");
module_init(testinit);
module_exit(testexit);
