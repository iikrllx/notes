obj-m += procfs1.o
obj-m += procfs2.o
obj-m += procfs3.o
obj-m += procfs4.o
obj-m += procfs5-timer.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
