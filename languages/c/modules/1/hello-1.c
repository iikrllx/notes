#include <linux/module.h> /* для init_module / cleanup_module и т.д. */
#include <linux/kernel.h> /* для printk */

/* Вызывает при инициализации модуля (при insmod) */
int init_module(void)
{
	printk(KERN_INFO "Hello, world!\n");

	return 0; /* Если не вернуть 0, а -1 модуль не загрузится, init_module failed */
	/* Либо загрузится, (при return 3), но в dmesg будет Call Trace */
}

/* Вызывает при удалении модуля (при rmmod) */
void cleanup_module(void)
{
	printk(KERN_INFO "Goodbye world\n");
}

/* General Public License - этот модуль свободное ПО */
MODULE_LICENSE("GPL"); /* -> module.h описывает остальные лицензии */

/*
Уровни вывода можно посмотреть в kern_levels.h
Если не указали макрос к printk, тогда будет использоваться:
KERN_DEFAULT

Не стоит использовать номера в виде <4> и т.д.
*/
