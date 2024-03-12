#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>

#define procfs_name "buffer2k"
#define PROCFS_MAX_SIZE 2048

static char procfs_buffer[PROCFS_MAX_SIZE];
static size_t procfs_buffer_size = 0;
struct proc_dir_entry *our_proc_file;

static int procfile_release(struct inode *i, struct file *file)
{
	printk("procfile_release (/proc/%s) called\n", procfs_name);
	module_put(THIS_MODULE);
	return 0;
}

static int procfile_open(struct inode *i, struct file *file)
{
	printk("procfile_open (/proc/%s) called\n", procfs_name);
	printk("Current UID: %u\n", current_user()->uid.val);
	try_module_get(THIS_MODULE);
	return 0;
}

static ssize_t procfile_write(struct file *file, const char *buffer, size_t length, loff_t *offset)
{
	/*
	Если эта функция имеет такой код, то она будет бесконечно писать в dmesg
	Нужно обновить *offset, тогда проблем не будет:

	printk("procfile_write (/proc/%s) called\n", procfs_name);
	*offset += length;
	return length;
	*/

	printk("procfile_write (/proc/%s) called\n", procfs_name);

	if (length > PROCFS_MAX_SIZE)
		procfs_buffer_size = PROCFS_MAX_SIZE;
	else
		procfs_buffer_size = length;

	if (copy_from_user(procfs_buffer, buffer, procfs_buffer_size))
		return -EFAULT;

	printk("procfile_write: write %lu bytes\n", procfs_buffer_size);
	return procfs_buffer_size;
}

static ssize_t procfile_read(struct file *file, char *buffer, size_t length, loff_t *offset)
{
	printk("procfile_read (/proc/%s) called\n", procfs_name);

	/*
	Почему функция procfile_read вызывается дважды ?
	На самом деле она будет вызываться бесконечное кол-во раз пока не получит offset -> EOF
	EOF это 0 (нужно вернуть return 0), тогда вызов прекратится (сигнализирует о конце файла).
	Вернуть 0 нужно, если offset больше 0 (то есть чтение уже было)

	Если offset равен 0, тогда чтение не производилось еще и нужно что-то прочитать,
	чтобы затем вернуть 0 (EOF)

	Если `offset` равен 0, значит, чтение выполняется в первый раз, и данные копируются
	в пользовательский буфер. После копирования данных, `offset` устанавливается в размер
	буфера, чтобы указать, что чтение было выполнено.

	Функция `procfile_read` может быть вызвана дважды: первый раз для чтения данных и
	второй раз для возврата EOF. Это стандартное поведение для файловой системы `/proc`,
	где файлы часто представляют динамически генерируемую информацию, а не статические данные на диске. */

	/* fix infinite loop */
	if (*offset > 0)
	{
		printk("Done\n");
		return 0;
	}

	/* check current uid value */
	/* cat read only root */
	if (current_user()->uid.val == 0)
	{
		if (copy_to_user(buffer, procfs_buffer, procfs_buffer_size))
			return -EFAULT;
		*offset = procfs_buffer_size; /* fix infinite loop */
	} else
			return -EACCES;

	printk("procfs_read: read %lu bytes\n", procfs_buffer_size);
	return procfs_buffer_size; /* Return the number of bytes "read" */
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
