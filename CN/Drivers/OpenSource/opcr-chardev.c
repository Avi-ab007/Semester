#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>

static dev_t first;					//Global variable for first device number
static struct cdev c_dev;			//Global variable for character device structure
static struct class *dev_class;		//Global variable for device class
static char c;

static int my_open(struct inode *i, struct file *fp) {
	printk(KERN_INFO "Driver: open()\n");
	return 0;
}

static int my_close(struct inode *i, struct file *fp) {
	printk(KERN_INFO "Driver: close()\n");
	return 0;
}

static ssize_t my_read(struct file *fp, char __user *buf, size_t len, loff_t *off) {
	printk(KERN_INFO "Driver: read()\n");
	if (copy_to_user(buf, &c, 1) != 0)
		return -EFAULT;
	return 1;
}

static ssize_t my_write(struct file *fp, const char __user *buf, size_t len, loff_t *off) {
	printk(KERN_INFO "Driver: write()\n");
	if (copy_from_user(&c, buf + len - 1, 1) != 0)
		return -EFAULT;
	return len;
}

static struct file_operations myOps = {
	.owner 		= THIS_MODULE,
	.read 		= my_read,
	.write 		= my_write,
	.open 		= my_open,
	.release 	= my_close
};

static int __init ofcd_init(void) /* Constructor */ {
	printk(KERN_INFO "Hello: charDev registered");
	if (alloc_chrdev_region(&first, 0, 1, "Avinash") < 0) {
		return -1;
	}
	if ((dev_class = class_create(THIS_MODULE, "chardrv")) == NULL) {
		unregister_chrdev_region(first, 1);
		return -1;
	}
	if (device_create(dev_class, NULL, first, NULL, "mynull") == NULL) {
		class_destroy(dev_class);
		unregister_chrdev_region(first, 1);
		return -1;
	}
	cdev_init(&c_dev, &myOps);
	if (cdev_add(&c_dev, first, 1) == -1) {
		device_destroy(dev_class, first);
		class_destroy(dev_class);
		unregister_chrdev_region(first, 1);
		return -1;
	}
	return 0;
}

static void __exit ofcd_exit(void) {
	cdev_del(&c_dev);
	device_destroy(dev_class, first);
	class_destroy(dev_class);
	unregister_chrdev_region(first, 1);
	printk(KERN_INFO "Goodbye, ofcd unregistered!");
}

module_init(ofcd_init);
module_exit(ofcd_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("AVINASH");
MODULE_DESCRIPTION("First character driver");