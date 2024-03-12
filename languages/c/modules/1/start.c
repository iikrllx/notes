#include <linux/kernel.h>
#include <linux/module.h>

int init_module(void)
{
	printk("Start\n");
	return 0;
}

MODULE_LICENSE("GPL");

/*
Если загрузить данный модуль (./start.ko), мы не сможем сделать rmmod
Он не знает как выйти, нет __exit / cleanup_module
Придется ребутать систему, или если включен CONFIG_MODULE_FORCE_UNLOAD
можно сделать $ rmmod -f <module>

Модуль ядра отработал и будто бы висит и ничего не делает (ждет rmmod -> __exit),
повторный запуск будет когда ядро этого захочет.
*/
