CONFIG_MODULE_SIG=n
obj-m += task_info.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

test:
	gcc -o test test.c

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
