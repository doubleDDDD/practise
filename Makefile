obj-m += example2.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	$(CROSS_COMPILE)gcc -o test test.c
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -rf test
