#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>

#define procfs_name "helloworld"

struct proc_dir_entry *our_proc_file;

// Функцию можно найти в: ./linux-headers-6.1.0-13-common/include/linux/proc_fs.h
static ssize_t procfile_read(struct file *file, char *buffer, size_t length, loff_t *offset)
{
	int ret;
	const char *hello_str = "Hello, world!\n";
	size_t hello_len = strlen(hello_str);

	printk("procfile_read (/proc/%s) called\n", procfs_name);

	/*
	Были ли уже прочитаны данные из файла ? Эта проверка нужна, ибо procfile_read вызывается ядром дважды
	Если `*offset` больше нуля, это означает, что все данные уже были прочитаны
	при предыдущем вызове функции чтения, и функция должна вернуть 0, чтобы указать конец файла. */
	if (*offset > 0) {
		/* we have finished to read, return 0 */
		ret = 0;
	} else {
		/* fill the buffer, return the buffer size */
		if (length < hello_len)
			return -EINVAL;

		/* аналогична snprintf, только здесь копирование из пространства ядра в user space  */
		/* при записи бы копировалось из пространство пользователя в ядро (copy_from_user or get_user) */
		/* get_user и put_user обрабатывают только 1 символ, а copy_to_user и copy_from_user полностью */
		if (copy_to_user(buffer, hello_str, hello_len))
			return -EFAULT;

		*offset = hello_len;
		ret = hello_len;
	}

	return ret;
}

// Структура в ./linux-headers-6.1.0-13-common/include/linux/proc_fs.h
static struct proc_ops ops = {
    .proc_read = procfile_read,
};

int init_module(void)
{
	// NULL -> create entry in root directory
	// if not NULL -> create entry in child /proc directory
	// создает /proc/helloworld
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

void cleanup_module()
{
	remove_proc_entry(procfs_name, NULL);
	printk("/proc/%s removed\n", procfs_name);
}

MODULE_LICENSE("GPL");
