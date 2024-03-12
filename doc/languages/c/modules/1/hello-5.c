#include <linux/moduleparam.h> /* for module_param() */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static char *mystring = "";
static int myint = 0;

static int __init hello_5_a(void)
{
	printk("%s:%d\n", mystring, myint);
	return 0;
}

static void __exit hello_5_b(void)
{
	printk("Goodbye, world!\n");
}

module_init(hello_5_a);
module_exit(hello_5_b);

module_param(mystring, charp, 0);
MODULE_PARM_DESC(mystring, "A character string");

module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myint, "A int number");

/*
MODULE_PARM_DESC();
Используется для описания параметров модуля. Эта макроинструкция
принимает два аргумента: имя параметра и строку с описанием этого параметра.
Она используется для документирования параметров, которые можно передать
модулю при его загрузке через командную строку или файлы конфигурации.

Например:
module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

Создает файл в sysfs: /sys/module/<mymodule>/parameters/myint
С правами доступа указанные в 3 аргументе.

Изменение параметров модуля через sysfs может быть полезно для настройки
поведения модуля во время его работы без необходимости перезагрузки самого модуля.

Можно еще использовать: module_param_array для массивов.

Таким образом, `MODULE_PARM_DESC` относится к конкретным параметрам модуля,
а `MODULE_DESCRIPTION` к общему описанию модуля.

Поле vermagic в выводе команды modinfo показывает версию ядра Linux,
с которой совместим модуль. Это включает в себя номер версии ядра, архитектуру процессора,
опции компиляции и версию компилятора, использованные при сборке модуля.
Если эта сущность не совпадает с реальной картиной, тогда модуль не загрузится:
$ insmod <module> -> error (несовпадение vermagic)

Это поле используется системой для предотвращения загрузки модулей,
которые несовместимы с текущим ядром.
*/

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kirill Rekhov");
MODULE_DESCRIPTION("A sample driver");
