This is mostly copied from the excellent Julia Evans: https://github.com/jvns/kernel-module-fun

Kernel modules are used to extend the kernel functionality, e.g. writing device drivers.

First install kernel devel and headers:

```bash
# On centos
sudo yum install kernel-devel kernel-headers
# Seems to work on ubuntu out of the box
```

Then run the Makefile to build the module:
```bash
make
# To clean up afterwards:
make clean
```

Note that this using this particular Makefile is the official way to build kernel modules:
http://stackoverflow.com/questions/9492559/module-compiling-asm-linkage-h-file-not-found

Then play around with it:
```bash
# Show some info
modinfo hello.ko

insmod hello.ko
# insmod is a very simple way to insert module, best to use modprobe -> more advanced

# Show that the module is loaded
lsmod | grep hello

dmesg #  show that the hello world message is showing up

# remove module, normally we use modprobe instead as it's more advanced
rmmod hello


dmesg # show that hello world exit message shows

```
