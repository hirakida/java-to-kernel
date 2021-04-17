CFILES = hirakida.c
KDIR = /lib/modules/$(shell uname -r)/build

obj-m := $(CFILES:.c=.o)

default:
	make -C $(KDIR) M=$(PWD) V=1 modules
clean:
	make -C $(KDIR) M=$(PWD) V=1 clean
