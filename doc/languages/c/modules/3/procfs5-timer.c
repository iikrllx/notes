#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/delay.h>

#define procfs_name "buffer2k"
#define PROCFS_MAX_SIZE 2048

static char procfs_buffer[PROCFS_MAX_SIZE];
static size_t procfs_buffer_size = 0;
struct proc_dir_entry *our_proc_file;

long time_remaining = 1 * HZ;

static int procfile_release(struct inode *i, struct file *file)
{
	pr_info("procfile_release (/proc/%s) called\n", procfs_name);
	module_put(THIS_MODULE);
	return 0;
}

static int procfile_open(struct inode *i, struct file *file)
{
	pr_info("procfile_open (/proc/%s) called\n", procfs_name);
	pr_info("Current UID: %u\n", current_user()->uid.val);
	try_module_get(THIS_MODULE);
	return 0;
}

static ssize_t procfile_write(struct file *file, const char *buffer, size_t length, loff_t *offset)
{
	pr_info("procfile_write (/proc/%s) called\n", procfs_name);

	if (length > PROCFS_MAX_SIZE)
		procfs_buffer_size = PROCFS_MAX_SIZE;
	else
		procfs_buffer_size = length;

	if (copy_from_user(procfs_buffer, buffer, procfs_buffer_size))
		return -EFAULT;

	pr_info("procfile_write: write %lu bytes\n", procfs_buffer_size);
	return procfs_buffer_size;
}

static ssize_t procfile_read(struct file *file, char *buffer, size_t length, loff_t *offset)
{
	/* pr_info автоматически добавляет KERN_INFO */
	pr_info("procfile_read (/proc/%s) called\n", procfs_name);
	pr_info("%ld\n", time_remaining);

	/* fix infinite loop */
	/*
	if (*offset > 0)
	{
		printk("Done\n");
		return 0;
	}
	*/

	if (time_remaining <= 0) {
		pr_info("Timeout occurred, exiting loop\n");
		return 0;
	}

	// Уменьшаем оставшееся время
	time_remaining = schedule_timeout(time_remaining);
	pr_info("%ld\n", time_remaining);

	/*
		Можно еще использовать:
		unsigned long timeout = jiffies + 1 * HZ;
		if (time_after(jiffies, timeout)) {
			pr_info("Break infinite loop, timeout occurred\n");
			break;
		}
	*/

	if (current_user()->uid.val == 0)
	{
		if (copy_to_user(buffer, procfs_buffer, procfs_buffer_size))
			return -EFAULT;
		*offset = procfs_buffer_size;
	} else
			return -EACCES;

	pr_info("procfs_read: read %lu bytes\n", procfs_buffer_size);
	return procfs_buffer_size;
}

static struct proc_ops ops = {
    .proc_read = procfile_read,
    .proc_write = procfile_write,
    .proc_open = procfile_open,
    .proc_release = procfile_release,
};

static int __init init(void)
{
	our_proc_file = proc_create(procfs_name, 0644, NULL, &ops);

	if (our_proc_file == NULL)
	{
		remove_proc_entry(procfs_name, NULL);
		pr_info("Error: Could not initialize /proc/%s\n", procfs_name);
		return -ENOMEM;
	}

	pr_info("/proc/%s created\n", procfs_name);
	return 0;
}

static void __exit clean(void)
{
	remove_proc_entry(procfs_name, NULL);
	pr_info("/proc/%s removed\n", procfs_name);
}

module_init(init);
module_exit(clean);

MODULE_LICENSE("GPL");
