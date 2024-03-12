#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>

#define DEVICE_NAME "chardev" /* Dev name as it appears in /proc/devices */
#define BUF_LEN 80            /* Max length of the message from the device */


/* Globals */
static int major;             /* Major number assigned to our device driver */
static int is_device_open = 0;

static char msg[BUF_LEN];
static char *msg_Ptr;


/* Called when a process, which already opened the dev file, attempts to
   read from it. */
static ssize_t device_read(struct file *filp,   /* see include/linux/fs.h */
				char *buffer,   /* buffer to fill with data */
				size_t length,  /* length of the buffer */
				loff_t *offset)
{
	/* Number of bytes actually written to the buffer */
	int bytes_read = 0;

	printk("device_read\n");

	/*
	 * If we're at the end of the message,
	 * return 0 signifying end of file
	 */
	if (*msg_Ptr == 0)
		return 0;

	/* Actually put the data into the buffer */
	/* Аналогично: length != 0 && *msg_Ptr != '\0' */
	while (length && *msg_Ptr) {
		/*
		 * The buffer is in the user data segment, not the kernel
		 * segment so "*" assignment won't work. We have to use
		 * put_user which copies data from the kernel data segment to
		 * the user data segment. */
		put_user(*(msg_Ptr++), buffer++);
		length--;
		bytes_read++;
	}

	/* Most read functions return the number of bytes put into the buffer */
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

/*
Эти функции используются в ядре Linux для управления счетчиком ссылок на модуль ядра.
Каждый модуль имеет счетчик ссылок, который отслеживает, сколько раз модуль был "захвачен" или "освобожден".
Это предотвращает удаление модуля из памяти, пока он все еще используется другим кодом.

- `try_module_get(THIS_MODULE)` - это функция, которая увеличивает счетчик ссылок на модуль,
если это возможно. Это делается перед использованием модуля, чтобы убедиться, что он не будет
выгружен, пока вы его используете. Если модуль уже в процессе выгрузки, функция вернет 0 (неудачу),
и модуль не должен использоваться.

- `module_put(THIS_MODULE)` - это функция, которая уменьшает счетчик ссылок на модуль,
указывая, что модуль больше не используется. Когда счетчик достигает нуля,
модуль может быть безопасно выгружен из памяти.

`THIS_MODULE` - это макрос, который представляет указатель на структуру модуля текущего модуля.
Это позволяет передать информацию о модуле в эти функции.

try_module_get увеличивает 3 колонку файла /proc/modules
Если эта колонка не равна 0, тогда rmmod будет failed.
а module_put уменьшает эту колонку.

Это механизм предотвращает выгрузку модуля, пока он активно используется.
Если счетчик достигает нуля, это означает, что модуль больше не используется
и может быть безопасно выгружен из ядра.
*/

/* Стуктура которая хранит указатели на функции (системные вызовы)
   Будут использоваться драйвером устройства /dev/chardev
   Будут вызваны для различных операций над файлом устройства
   Эти функции необходимо реализовать самостоятельно (их нет в ядре или в заголовках)

   Файл устройства это абстрактный интерфейс, не FILE как в userspace
   Точки означают инициализация поля под конкретное значение
   Полный набор полей: ./linux-headers-6.1.0-13-common/include/linux/fs.h */
static struct file_operations fops = {
	.read = device_read,       // read
	.write = device_write,     // write
	.open = device_open,       // open
	.release = device_release  // close
};
/* Раньше писали: read: device_read, а теперь .read = device_read */

/*
`register_chrdev` и `unregister_chrdev` - это функции в ядре Linux,
используемые для регистрации и удаления символьного устройства соответственно.
cat /proc/kallsyms | grep 'register_chrdev' */

/* This function is called when the module is loaded */
int init_module(void)
{
	/* Регистрирует новое символьное устройство в системе. Принимает три аргумента:
	   номер устройства, имя устройства и указатель на структуру `file_operations`,
	   которая содержит указатели на функции, реализующие операции чтения, записи,
	   открытия и закрытия устройства. Если функция успешно зарегистрировала устройство,
	   она возвращает 0 или положительное значение.
	   В случае ошибки возвращается отрицательное значение. */

	// Note that we didn't pass the minor number to register_chrdev.
	// That's because the kernel doesn't care about the minor number; only our driver uses it
	//
	// If you pass a major number of 0 to register_chrdev, the return value will be the
	// dynamically allocated major number.
	major = register_chrdev(0, DEVICE_NAME, &fops);

	if (major < 0)
	{
		printk("Registering char device failed with %d\n", major);
		return major;
	}

	/* Устройство зарегестрировано в /proc/devices
	   Темерь можно создать mknod /dev/chardev c <major> 0 */

	printk("Success! You can 'mknod': /dev/%s (major:%d)\n", DEVICE_NAME, major);

	return 0;
}

/* This function is called when the module is unloaded */
void cleanup_module(void)
{
	/* Удаляет символьное устройство из системы. Принимает два аргумента:
	   номер устройства и имя устройства. После вызова этой функции устройство
	   больше не доступно для операций ввода-вывода. */
	unregister_chrdev(major, DEVICE_NAME);
}

MODULE_LICENSE("GPL");
