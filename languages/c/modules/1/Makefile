# Указывает на объектный файл модуля, который будет .ko
obj-m += hello-1.o
obj-m += hello-2.o
obj-m += hello-3.o
obj-m += hello-4.o
obj-m += hello-5.o
obj-m += startstop.o

# Эти два файла мы объединили в один
startstop-objs := start.o stop.o

# Часто obj-m и obj-y используют хак: obj−$(CONFIG_FOO)
# CONFIG_FOO имеет значение 'y' допустим
#
# obj-y означает, что модули будут встроены в само ядро (компилируется прям в ядро)
# obj-m означает, что они будут загружаться и выгружаться

# Команда `make -C` используется для указания директории,
# в которой должен быть запущен `make`, то есть в /lib/modules/$(uname -r)/build
#
# M=/home/<user>/sources/modules/1 передает путь в котором лежит исходный файл для сборки
#
# modules это цель, которая объявлена в /lib/modules/$(uname -r)/build/Makefile

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
