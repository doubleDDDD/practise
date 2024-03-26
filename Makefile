modname ?= helloworld
KERNELDIR := /lib/modules/$(shell uname -r)/build/
PWD := $(shell pwd)
all:
	make -C $(KERNELDIR) M=$(PWD) modules
clean:
	make -C $(KERNELDIR) M=$(PWD) clean
install:
	cp ./$(modname).ko ./Bin
obj-m:= $(modname).o