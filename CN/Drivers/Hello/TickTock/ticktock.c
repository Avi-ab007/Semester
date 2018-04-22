#include <linux/module.h>
#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/time.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <asm/uaccess.h>

static int Tick_init(void);
static void Tock_exit(void);
static int opendev(struct inode*, struct file*);
static int closedev(struct inode*, struct file*);
static ssize_t readme(struct file*, char*, size_t, loff_t*);
static ssize_t writeme(struct file *, const char *, size_t, loff_t *);


static int Major;

#define SUCCESS 0
#define DEVICE_NAME "TickTock"
static struct file_operations fops = {
	.read 		= readme,
	.write 		= writeme,
	.open 		= opendev,
	.release 	= closedev
};

static int Tick_init(void) {
	printk(KERN_ALERT "Inside kernel %s function\n", __FUNCTION__);
	register_chrdev(786, DEVICE_NAME, &fops);

	// if (Major > 0) {
	// 	printk(KERN_INFO "TickTock is ready for request!: %d\n", Major);
	// 	return 0;
	// } else {
	// 	printk(KERN_INFO "Something did not work out!: %d\n", Major);
	// 	return 0;
	// }
}

static void Tock_exit(void) {
	printk(KERN_ALERT "Inside the kernel %s function\n", __FUNCTION__);
	unregister_chrdev(786, DEVICE_NAME);
}

static int opendev(struct inode* a, struct file* b) {
	printk(KERN_INFO "Someone opened me.");
	return SUCCESS;
}

static int closedev(struct inode* a, struct file* b) {
	printk(KERN_INFO "Someone closed me.");
	return SUCCESS;
}

void reverse(char str[], int length)
{
	int start = 0;
	int end = length -1;
	while (start < end)
	{
		swap(*(str+start), *(str+end));
		start++;
		end--;
	}
}
char *b;
int itoa(int num, char* str) {
	int y;
	int i = 0;
	int base = 10;
	
	bool isNegative = false;

	/* Handle 0 explicitely, otherwise empty string is printed for 0 */
	if (num == 0) {
		int x;
		str[i++] = '0';
		str[i] = '\0';
		
		x = strlen(str); 
		strcpy(b,str); 
		return x;
	}

	// In standard itoa(), negative numbers are handled only with 
	// base 10. Otherwise numbers are considered unsigned.
	if (num < 0 && base == 10) {
		isNegative = true;
		num = -num;
	}

	// Process individual digits
	while (num != 0) {
		int rem = num % base;
		str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
		num = num/base;
	}

	// If number is negative, append '-'
	if (isNegative)
		str[i++] = '-';

	str[i] = '\0'; // Append string terminator

	// Reverse the string
	reverse(str, i);

	
	y = strlen(str); 
	strcpy(b,str); 
	return y;
}
int atoi(const char * str) {
	int res = 0,i=0; // Initialize result
	// Iterate through all characters of input string and
	// update result
	for (i = 0; str[i] != '\0'; ++i)
	    res = res*10 + str[i] - '0';

	// return result.
	return res;
}

static ssize_t readme(struct file *filp,char *buffer,size_t length,loff_t *offset)  {
	int len;
	struct timeval time;
	do_gettimeofday(&time);
	
	b = kmalloc(sizeof(char)*40,GFP_KERNEL);
	len = itoa(time.tv_sec, b);
	copy_to_user(buffer,b,len);
	printk("Return val:%s\n",b);
	return 0;
}

static ssize_t writeme(struct file *filp,const char *buff,size_t len, loff_t *off) {
	int i = atoi(buff);
	struct timespec ab;
	ab.tv_sec = i;
	ab.tv_nsec = 0;
	do_settimeofday(&ab);
	return len;
}

module_init(Tick_init);
module_exit(Tock_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Avinash");