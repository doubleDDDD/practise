obj-m := hello_world.o my_string.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test_hello:
	sudo dmesg -C # clean dmesg
	sudo insmod hello_world.ko
	sudo rmmod hello_world
	sudo dmesg

test_dev:
	sudo dmesg -C
	sudo insmod my_string.ko
	sudo dmesg
	sudo rmmod my_string
	sudo dmesg
