obj-m := my_string.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	sudo rm -rf rwtest

test_dev:
	sudo dmesg -C
	sudo insmod my_string.ko
	sudo gcc rwtest.c -o rwtest
	sudo ./rwtest
	sudo dmesg
	sudo rmmod my_string
	sudo dmesg
