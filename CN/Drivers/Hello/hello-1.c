#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int hello1_data __initdata = 4;

static int hello1_init(void) {
	printk(KERN_INFO "Hello World: %d\n", hello1_data);
	return 0;
}

static void hello1_exit(void) {
	printk(KERN_INFO "GoodBye World!\n");
}

module_init(hello1_init);
module_exit(hello1_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Avinash");
