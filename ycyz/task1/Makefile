obj-m := hello_world.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test_hello:
	sudo dmesg -C # clean dmesg
	sudo insmod hello_world.ko
	sudo rmmod hello_world
	sudo dmesg
