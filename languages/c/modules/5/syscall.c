#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/unistd.h>
#include <linux/sched.h>
#include <asm/uaccess.h>

/*
Данный модуль не компилируется, служит просто примером обращения к sys_call_table
Напрямую обращаться к sys_call_table не рекомендуется и в современных версиях ядра
это может потребовать отключения механизма защиты памяти (CONFIG_KALLSYMS)

К сожалению, замена системных вызовов в Linux является довольно сложной задачей
и может привести к нестабильности системы, если выполнять её неаккуратно.
Сейчас это запрещается политикой и является зловредной практикой.

Начиная с определенных версий ядра Linux, `sys_call_table` не экспортируется,
что означает, что его адреса не могут быть прочитаны напрямую модулями ядра.
В `/proc/kallsyms` значение `D` означает, что символ является глобальным
и инициализированным (data), но он может быть недоступен для модификации
из загружаемых модулей ядра из-за ограничений безопасности.

Вот еще одна причина опасности таких методов.
The init_module function replaces the appropriate location in sys_call_table and
keeps the original pointer in a variable. The cleanup_module function uses that
variable to restore everything back to normal. This approach is dangerous,
because of the possibility of two kernel modules changing the same system call.
*/

/*
 * The system call table (a table of functions). We
 * just define this as external, and the kernel will
 * fill it up for us when we are insmod'ed
 *
 * sys_call_table is no longer exported in 2.6.x kernels.
 * If you really want to try this DANGEROUS module you will
 * have to apply the supplied patch against your current kernel
 * and recompile it.
 */
extern void *sys_call_table[];

/*
 * UID we want to spy on - will be filled from the
 * command line
 */
static int uid;
module_param(uid, int, 0644);

/*
 * A pointer to the original system call. The reason
 * we keep this, rather than call the original function
 * (sys_open), is because somebody else might have
 * replaced the system call before us. Note that this
 * is not 100% safe, because if another module
 * replaced sys_open before us, then when we're inserted
 * we'll call the function in that module - and it
 * might be removed before we are.
 *
 * Another reason for this is that we can't get sys_open.
 * It's a static variable, so it is not exported.
 */
asmlinkage int (*original_call) (const char *, int, int);

/*
 * The function we'll replace sys_open (the function
 * called when you call the open system call) with. To
 * find the exact prototype, with the number and type
 * of arguments, we find the original function first
 * (it's at fs/open.c).
 *
 * In theory, this means that we're tied to the
 * current version of the kernel. In practice, the
 * system calls almost never change (it would wreck havoc
 * and require programs to be recompiled, since the system
 * calls are the interface between the kernel and the
 * processes).
 */
asmlinkage int our_sys_open(const char *filename, int flags, int mode)
{
	int i = 0;
	char ch;

	/*
	 * Check if this is the user we're spying on
	 */
	if (uid == current->uid) {
		/*
		 * Report the file, if relevant
		 */
		printk("Opened file by %d: ", uid);
		do {
			get_user(ch, filename + i);
			i++;
			printk("%c", ch);
		} while (ch != 0);
		printk("\n");
	}

	/*
	 * Call the original sys_open - otherwise, we lose
	 * the ability to open files
	 */
	return original_call(filename, flags, mode);
}

/*
 * Initialize the module - replace the system call
 */
int init_module()
{
	/*
	 * Warning - too late for it now, but maybe for
	 * next time...
	 */
	printk(KERN_ALERT "I'm dangerous. I hope you did a ");
	printk(KERN_ALERT "sync before you insmod'ed me.\n");
	printk(KERN_ALERT "My counterpart, cleanup_module(), is even");
	printk(KERN_ALERT "more dangerous. If\n");
	printk(KERN_ALERT "you value your file system, it will ");
	printk(KERN_ALERT "be \"sync; rmmod\" \n");
	printk(KERN_ALERT "when you remove this module.\n");

	/*
	 * Keep a pointer to the original function in
	 * original_call, and then replace the system call
	 * in the system call table with our_sys_open
	 */
	original_call = sys_call_table[__NR_open];
	sys_call_table[__NR_open] = our_sys_open;

	/*
	 * To get the address of the function for system
	 * call foo, go to sys_call_table[__NR_foo].
	 */

	printk(KERN_INFO "Spying on UID:%d\n", uid);

	return 0;
}

void cleanup_module()
{
	/*
	 * Return the system call back to normal
	 */
	if (sys_call_table[__NR_open] != our_sys_open) {
		printk(KERN_ALERT "Somebody else also played with the ");
		printk(KERN_ALERT "open system call\n");
		printk(KERN_ALERT "The system may be left in ");
		printk(KERN_ALERT "an unstable state.\n");
	}

	sys_call_table[__NR_open] = original_call;
}
