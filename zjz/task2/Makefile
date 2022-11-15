ifneq ($(KERNELRELEASE),)
obj-m:=chrdev.o
else
PWD	:=$(shell pwd)
KDIR:=/usr/src/linux-headers-5.15.0-52-generic
all:
	make -C $(KDIR) M=$(PWD) modules	
clean:
	rm -rf *.o *.ko *.mod.c *.symvers *.c~ *~ .*.cmd *.mod *.order
endif