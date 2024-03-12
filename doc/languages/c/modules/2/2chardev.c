#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>

#define DEVICE_NAME "chardev"
#define BUF_LEN 80

static int major;
static int is_device_open = 0;

static char msg[BUF_LEN];
static char *msg_Ptr;

/*
Функции device_read / device_write / device_open / device_release
Лежат в linux/fs.h, это интерфейс ядра
Параметры должны соответствовать прототипам

Структура struct file предоставляет открытый файл (устройство), содержит
информацию о файле.

Буфер buffer из пространства пользователя (драйвер записывает туда данные)

length максимальное кол-во байт buffer, которое пользователь может прочитать или записать,
драйвер устройства должен учитывать этот размер и не должен читать больше данных,
чем запрошено. Например: while (bytes_read < length). Это: buffer[length]

offset смещение в файле (позиция) если оно равно 0, значит чтение начнется с начала
а если пользователь указал другой offset (из системной программы), тогда
чтение будет с середины (например) "times Hello world!"

Структура struct inode используется для предоставления информации о файловой
системе устройства, которое открывается. В контексте драйвера устройства,
`inode` может содержать важные данные, такие как номер устройства (major и minor numbers),
которые идентифицируют конкретное устройство в системе.
*/

/* Called when a process, which already opened the dev file, attempts to
   read from it. */
static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset)
{
	int bytes_read = 0;

	printk("device_read\n");

	if (*msg_Ptr == 0)
		return 0;

	/* Когда пользовательское приложение хочет получить доступ к данным, которые находятся
	   в пространстве ядра (например, данные от драйвера устройства), оно не может просто
	   обратиться к этим данным напрямую. Вместо этого, ядро предоставляет специальные
	   механизмы для безопасного копирования данных из ядра в пользовательское пространство.
	*/

	/* Используется для копирования данных из пространства
	   ядра в пространство пользователя. Это системный вызов, который
	   позволяет ядру безопасно передавать данные в пользовательскую программу,
	   например, когда необходимо вернуть результаты работы ядра в пользовательское приложение. */

	/* Эта функция копирует один байт данных из пространства ядра (где находится драйвер)
	   в пространство пользователя. msg_Ptr находится в пространстве ядра (наш драйвер устройства)
	   put_user копирует содержимое msg_Ptr в пользовательский buffer (который находится в userspace) */

	/* Благодаря этой функции после события cat /dev/chardev в выводе пользовательского
	   терминала будет запись:
	   I already told you 0 times Hello world!
	   I already told you 1 times Hello world!
	   Функция device_open инкрементирует в пространстве ядра свою переменную */

	while (*msg_Ptr != '\0') {
		put_user(*msg_Ptr++, buffer++);
		bytes_read++;
	}

	// возвращает количество прочитанных байт
	return bytes_read;
}

/* Called when a process writes to dev file: echo "hi" > /dev/hello */
static ssize_t device_write(struct file *filp, const char *buffer, size_t length, loff_t *offset)
{
	printk("device_write\n");

	printk("Sorry, this operation isn't supported.\n");
	return -EINVAL;
}

/* Called when a process tries to open the device file, like "cat /dev/mycharfile" */
static int device_open(struct inode *inode, struct file *file)
{
	static int counter = 0;

	printk("device_open\n");

	if (is_device_open)
		return -EBUSY;

	is_device_open++;
	sprintf(msg, "I already told you %d times Hello world!\n", counter++);
	msg_Ptr = msg;
	try_module_get(THIS_MODULE);

	return 0;
}

/* Called when a process closes the device file. */
static int device_release(struct inode *inode, struct file *file)
{
	printk("device_release\n");

	is_device_open--;
	module_put(THIS_MODULE);

	return 0;
}

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
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
