#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/ioport.h>
#include<linux/fs.h>
#include<linux/wait.h>
#include<linux/poll.h>
#include<linux/sched.h>
#include <linux/slab.h>

struct platform_driver *pDri;

static int testprobe(struct platform_device *pdev)
{
	printk(KERN_EMERG"match ok \n");
	return 0;
}

static int testremove(struct platform_device *pdev)
{
    printk(KERN_EMERG"driver remove!\n");
    return 0;
}

static int testinit(void)
{
    printk(KERN_EMERG"driver init!\n");
	pDri = kzalloc(sizeof(struct platform_driver),GFP_KERNEL);
	pDri->driver.name = "zjzDev";
	pDri->probe = testprobe;
	pDri->remove = testremove;
    return platform_driver_register(pDri);
}

static void testexit(void)
{
    printk(KERN_EMERG"driver exit!\n");
    platform_driver_unregister(pDri);
    return;
}

MODULE_LICENSE("Dual BSD/GPL");
module_init(testinit);
module_exit(testexit);
