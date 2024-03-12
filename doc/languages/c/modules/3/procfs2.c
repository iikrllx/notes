#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>

#define procfs_name "buffer1k"
#define PROCFS_MAX_SIZE 1024

static char procfs_buffer[PROCFS_MAX_SIZE];
static size_t procfs_buffer_size = 0;
struct proc_dir_entry *our_proc_file;

static ssize_t procfile_write(struct file *file, const char *buffer, size_t length, loff_t *offset)
{
	printk(KERN_INFO "procfile_write (/proc/%s) called\n", procfs_name);
	printk(KERN_INFO "%ld:%lld\n", length, *offset);

	/* get buffer size */
	/* buffer пользовательский, пользователь пишет туда echo "hello" > /proc/<f> */
	/* в buffer будет строка "...", а length будет равен 4 */
	procfs_buffer_size = length; /* "..." -> 4 (length = 4) */
	if (procfs_buffer_size > PROCFS_MAX_SIZE)
		procfs_buffer_size = PROCFS_MAX_SIZE;

	/* write data to the buffer */
	if (copy_from_user(procfs_buffer, buffer, procfs_buffer_size))
		return -EFAULT;

	// На всякий случай поднять *offset, но это необязательно, до этого он равен 0
	// и автоматически не изменяется
	*offset += procfs_buffer_size;

	return procfs_buffer_size;
}

static ssize_t procfile_read(struct file *file, char *buffer, size_t length, loff_t *offset)
{
	int ret;

	printk(KERN_INFO "procfile_read (/proc/%s) called\n", procfs_name);
	printk(KERN_INFO "%ld:%lld\n", length, *offset);

	/* Без этой проверки будет бесконечный цикл вывода buffer */
	if (*offset > 0) {
		printk(KERN_INFO "*offset > 0\n");
		ret = 0;
	} else {
		printk(KERN_INFO "In condition\n");
		printk(KERN_INFO "%ld:%ld:%lld\n", length, procfs_buffer_size, *offset);

		if (length < procfs_buffer_size)
			return -EINVAL;

		if (copy_to_user(buffer, procfs_buffer, procfs_buffer_size))
			return -EFAULT;

		*offset = procfs_buffer_size;
		ret = procfs_buffer_size;
	}

	return ret;
}

static struct proc_ops ops = {
    .proc_read = procfile_read,
    .proc_write = procfile_write,
};

static int __init init(void)
{
	our_proc_file = proc_create(procfs_name, 0644, NULL, &ops);

	if (our_proc_file == NULL)
	{
		remove_proc_entry(procfs_name, NULL);
		printk("Error: Could not initialize /proc/%s\n", procfs_name);
		return -ENOMEM;
	}

	printk("/proc/%s created\n", procfs_name);
	return 0;
}

static void __exit clean(void)
{
	remove_proc_entry(procfs_name, NULL);
	printk("/proc/%s removed\n", procfs_name);
}

module_init(init);
module_exit(clean);

MODULE_LICENSE("GPL");
