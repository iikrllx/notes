#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h> /* Для макросов module_init / module_exit */

/* __initdata аналогичен __init, но не для функций, а переменных */
static int hello3_data __initdata = 3;

static int __init hello_3_a(void)
{
	printk("Hello, world! -> %d \n", hello3_data);
	return 0;
}

static void __exit hello_3_b(void)
{
	printk("Goodbye, world! 3 \n");
	/* Освободит hello3_data */
}

module_init(hello_3_a);
module_exit(hello_3_b);

MODULE_LICENSE("GPL");
