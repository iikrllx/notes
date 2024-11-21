#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/seq_file.h>

#define DEVICE_NAME "iter"
#define BUF_LEN 80

/*
`struct proc_ops` и `struct seq_operations` используются для разных
целей и обычно не используются вместе.

`proc_ops` используется при создании простых файлов в /proc файловой системе и
определяет операции, такие как чтение и запись, которые можно выполнить с файлом.

`seq_operations`, с другой стороны, определяет набор операций, используемых при
создании последовательных файлов с помощью интерфейса `seq_file`. Этот интерфейс упрощает вывод данных,
которые можно итерировать, и обеспечивает автоматическую обработку пагинации.
Удобно для последовательного вывода данных.

Если нужно использовать интерфейс `seq_file` для создания файла в /proc, обычно вызываете `proc_create_seq`
или `proc_create_seq_private` для регистрации файла и связываете его с `seq_operations`.
Это позволит вам использовать удобные функции `seq_file`, такие как `seq_printf`, для вывода данных.

Вот пример связывания:

Тут функции последовательности ...

static struct seq_operations my_seq_ops = {
   // callback функции
   .start = my_seq_start,
   .next  = my_seq_next,
   .stop  = my_seq_stop,
   .show  = my_seq_show
};

static int my_proc_open(struct inode *inode, struct file *file)
{
   return seq_open(file, &my_seq_ops);
}

static struct proc_ops my_proc_ops = {
   .proc_open    = my_proc_open,
   .proc_read    = seq_read,
   .proc_lseek   = seq_lseek,
   .proc_release = seq_release
};
*/

static int major;

/* This function is called for each "step" of a sequence */
static int my_seq_show(struct seq_file *s, void *v)
{
	loff_t *spos = (loff_t *) v;
	printk("my_seq_show\n");
	seq_printf(s, "%Ld\n", *spos);
	return 0;
}


/* This function is called at the end of a sequence */
static void my_seq_stop(struct seq_file *s, void *v)
{
	printk("my_seq_stop\n");
	/* nothing to do, we use a static value in start() */
}

/*
This function is called after the beginning of a sequence.
It's called untill the return is NULL (this ends the sequence). */
static void *my_seq_next(struct seq_file *s, void *v, loff_t *pos)
{
	unsigned long *tmp_v = (unsigned long *)v;
	printk("my_seq_next\n");
	(*tmp_v)++;
	(*pos)++;
	return NULL;
}

static void *my_seq_start(struct seq_file *s, loff_t *pos)
{
	static unsigned long counter = 0;

	printk("my_seq_start\n");

	/* beginning a new sequence? */
	if (*pos == 0)
	{
		/* yes => return a non null value to begin the sequence */
		return &counter;
	} else {
		/* no => it's the end of the sequence, return end to stop reading */
		*pos = 0;
		return NULL;
	}
}

static struct seq_operations my_seq_ops = {
	.start = my_seq_start,
	.next  = my_seq_next,
	.stop  = my_seq_stop,
	.show  = my_seq_show,
};

static int my_open(struct inode *inode, struct file *file)
{
	return seq_open(file, &my_seq_ops);
}

/*
.owner = THIS_MODULE
это аналог инструкциям:
try_module_get(THIS_MODULE);
module_put(THIS_MODULE);
*/

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = my_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = seq_release,
};

int init_module(void)
{
	major = register_chrdev(0, DEVICE_NAME, &fops);

	if (major < 0)
	{
		printk("Registering char device failed with %d\n", major);
		return major;
	}

	printk("Success! You can 'mknod': /dev/%s (major:%d)\n", DEVICE_NAME, major);

	return 0;
}

void cleanup_module(void)
{
	unregister_chrdev(major, DEVICE_NAME);
}

MODULE_LICENSE("GPL");
