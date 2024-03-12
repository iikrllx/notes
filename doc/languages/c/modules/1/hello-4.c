#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init hello_4_a(void)
{
	printk("Hello, world!\n");
	return 0;
}

static void __exit hello_4_b(void)
{
	printk("Goodbye, world!\n");
}

module_init(hello_4_a);
module_exit(hello_4_b);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kirill Rekhov");
MODULE_DESCRIPTION("A sample driver");

/* Данный модуль поддерживает /dev/testdevice
 * Это помогает системе определить какой модуль загрузить для работы с устройством. */
//MODULE_SUPPORTED_DEVICE("testdevice");
