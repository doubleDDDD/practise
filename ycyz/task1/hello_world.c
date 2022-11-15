#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Chengyuze Yang");
MODULE_DESCRIPTION("Hello world module written by ycyz.");

static int init_hello_world_module(void)
{
	printk("Start of hello world module.\n");
	printk("Hello, world!\n");
	return 0;
}

static void exit_hello_world_module(void)
{
	printk("End of hello world module.\n");
	return;
}

module_init(init_hello_world_module);
module_exit(exit_hello_world_module);
