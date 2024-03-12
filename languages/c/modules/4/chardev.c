/*
 *  chardev.c - Create an input/output character device
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#include "chardev.h"
#define BUF_LEN 80

/*
 * Is the device open right now? Used to prevent
 * concurent access into the same device
 */
static int Device_Open = 0;

/*
 * The message the device will give when asked
 */
static char Message[BUF_LEN];

/*
 * How far did the process reading the message get?
 * Useful if the message is larger than the size of the
 * buffer we get to fill in device_read.
 */
static char *Message_Ptr;

/*
 * This is called whenever a process attempts to open the device file
 */
static int device_open(struct inode *inode, struct file *file)
{
	printk("device_open()\n");
	/*
	 * We don't want to talk to two processes at the same time
	 */
	if (Device_Open)
		return -EBUSY;

	Device_Open++;
	/*
	 * Initialize the message
	 */
	Message_Ptr = Message;
	try_module_get(THIS_MODULE);
	return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
	printk("device_release()\n");
	/*
	 * We're now ready for our next caller
	 */
	Device_Open--;

	module_put(THIS_MODULE);
	return 0;
}

/*
 * This function is called whenever a process which has already opened the
 * device file attempts to read from it.
 */
static ssize_t device_read(struct file *file, char __user *buffer, size_t length, loff_t *offset)
{
	/*
	 * Number of bytes actually written to the buffer
	 */
	int bytes_read = 0;

	printk("device_read()\n");

	/*
	 * If we're at the end of the message, return 0
	 * (which signifies end of file)
	 */
	if (*Message_Ptr == 0)
		return 0;

	/*
	 * Actually put the data into the buffer
	 */
	while (length && *Message_Ptr) {

		/*
		 * Because the buffer is in the user data segment,
		 * not the kernel data segment, assignment wouldn't
		 * work. Instead, we have to use put_user which
		 * copies data from the kernel data segment to the
		 * user data segment.
		 */
		put_user(*(Message_Ptr++), buffer++);
		length--;
		bytes_read++;
	}

	/*
	 * Read functions are supposed to return the number
	 * of bytes actually inserted into the buffer
	 */
	return bytes_read;
}

/*
 * This function is called when somebody tries to
 * write into our device file.
 */
static ssize_t device_write(struct file *file, const char __user *buffer, size_t length, loff_t *offset)
{
	int i;

	printk("device_write()\n");

	/* put_user копирует А в Б */
	/* get_user копирует Б в А */

	/* Копирует данные из userspace в kernelspace буфер под названием Message */
	for (i = 0; i < length && i < BUF_LEN; i++)
		get_user(Message[i], buffer + i);

	Message_Ptr = Message;

	/*
	 * Again, return the number of input characters used
	 */
	return i;
}

/*
 * This function is called whenever a process tries to do an ioctl on our
 * device file. We get two extra parameters (additional to the file
 * structure, which all device functions get): the number of the ioctl called
 * and the parameter given to the ioctl function.
 *
 * If the ioctl is write or read/write (meaning output is returned to the
 * calling process), the ioctl call returns the output of this function.
 *
 */

/* ioctl_param это 3 аргумент функции ioctl(file_desc, IOCTL_GET_MSG, message); */
/* ioctl_num ссылается на IOCTL_SET_MSG и подобные макросы */
long int device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param)
{
	int i;
	char *temp;
	char ch;

	/*
	 * Switch according to the ioctl called
	 */
	switch (ioctl_num) {
	case IOCTL_SET_MSG:
		/*
		 * Receive a pointer to a message (in user space) and set that
		 * to be the device's message. Get the parameter given to
		 * ioctl by the process.
		 */
		temp = (char *)ioctl_param;

		/*
		 * Find the length of the message
		 */
		get_user(ch, temp);
		for (i = 0; ch && i < BUF_LEN; i++, temp++)
			get_user(ch, temp);

		device_write(file, (char *)ioctl_param, i, 0);
		break;

	case IOCTL_GET_MSG:
		/*
		 * Give the current message to the calling process -
		 * the parameter we got is a pointer, fill it.
		 */
		i = device_read(file, (char *)ioctl_param, 99, 0);

		/*
		 * Put a zero at the end of the buffer, so it will be
		 * properly terminated
		 */
		put_user('\0', (char *)ioctl_param + i);
		break;

	case IOCTL_GET_NTH_BYTE:
		/*
		 * This ioctl is both input (ioctl_param) and
		 * output (the return value of this function
		 */
		return Message[ioctl_param];
		break;
	}

	return 0;
}

struct file_operations Fops = {
	.read = device_read,
	.write = device_write,
	.compat_ioctl = device_ioctl,
	.unlocked_ioctl = device_ioctl,
	.open = device_open,
	.release = device_release,
};

static int __init iinit(void)
{
	int ret_val;
	ret_val = register_chrdev(MAJOR_NUM, DEVICE_NAME, &Fops);

	if (ret_val < 0) {
		printk(KERN_ALERT "%s failed with %d\n",
		       "Sorry, registering the character device ", ret_val);
		return ret_val;
	}

	printk(KERN_INFO "%s The major device number is %d.\n",
	       "Registeration is a success", MAJOR_NUM);
	printk(KERN_INFO "If you want to talk to the device driver,\n");
	printk(KERN_INFO "you'll have to create a device file. \n");
	printk(KERN_INFO "We suggest you use:\n");
	printk(KERN_INFO "mknod %s c %d 0\n", DEVICE_NAME, MAJOR_NUM);
	printk(KERN_INFO "The device file name is important, because\n");
	printk(KERN_INFO "the ioctl program assumes that's the\n");
	printk(KERN_INFO "file you'll use.\n");

	return 0;
}

static void __exit eexit(void)
{
	unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
}

module_init(iinit);
module_exit(eexit);
MODULE_LICENSE("GPL");
