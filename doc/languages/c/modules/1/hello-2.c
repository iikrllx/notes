#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h> /* Для макросов module_init / module_exit */

static int __init hello_2_a(void)
{
	printk("Hello, world! 2 \n");
	return 0;
}

static void __exit hello_2_b(void)
{
	printk("Goodbye, world! 2 \n");
}

/*
__init эта функция будет вызвана один раз в момент загрузки модуля в ядро.
После вызова такая функция может быть удалена из памяти, освобождая ресурсы,
так как она больше не будет нужна в процессе работы ядра.

__exit освобождает ресурсы, память, устройства.

Для встроенных модулей ядра __exit не используется, потому что они не выгружаются из ядра (не lkm).
Но иногда, все равно используется, для очистки кода.
*/

/* По современным меркам можно использовать такие трюки */
module_init(hello_2_a);
module_exit(hello_2_b);

MODULE_LICENSE("GPL");
