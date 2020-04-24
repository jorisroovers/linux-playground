# Hugepages



## Kernel config
Huge pages need to be enabled at kernel compile time, most linux distros do this by default.
See ```cat /boot/config-`uname -r`  | grep -i huge``` for related compile time flags.

However, the feature also needs to be enabled at run-time.

```sh
# By default, no hugepages are allocated
$ sysctl vm.nr_hugepages
0
# Alternatively:
$ cat /proc/sys/vm/nr_hugepages
0
# This will also show in /proc/meminfo
$ cat /proc/meminfo | grep -i huge
AnonHugePages:         0 kB
ShmemHugePages:        0 kB
HugePages_Total:       0
HugePages_Free:        0
HugePages_Rsvd:        0
HugePages_Surp:        0
Hugepagesize:       2048 kB  # Hugepage size: 2MB. Supported sizes is architecture dependent.

# Set the max number of hugepages the kernel should allow (default=0)
$ sudo sysctl vm.nr_hugepages=5

$ cat /proc/meminfo | grep -i huge
AnonHugePages:         0 kB
ShmemHugePages:        0 kB
HugePages_Total:       5
HugePages_Free:        5
HugePages_Rsvd:        0
HugePages_Surp:        0
Hugepagesize:       2048 kB
```

# Huge pages (non-shared)
```sh
# Compile and run program in *background*
cd hugetables
mkdir bin
gcc -std=c99 hugepages.c -o bin/hugepages
bin/hugepages &

# Note how 3 huge pages are Reserved (Rsvd)
$ cat /proc/meminfo | grep -i huge
AnonHugePages:         0 kB
ShmemHugePages:        0 kB
HugePages_Total:       5
HugePages_Free:        5
HugePages_Rsvd:        3
HugePages_Surp:        0
Hugepagesize:       2048 kB

# Note that when you disable hugepages, the program gives an error
$ sudo sysctl vm.nr_hugepages=0

$ bin/hugepages /tmp/myfile
Huge pages
mmap: Cannot allocate memory
FATAL ERROR
```

# Shared Huge pages
```sh
# Compile and run program in *background*
cd hugetables
mkdir bin
gcc -std=c99 shared_hugepages.c -o bin/shared_hugepages
bin/shared_hugepages &

# Shared Huge Pages need to be created on a 'hugetblfs' mount. 
# Many linux distros have one already pre-mounted:
$ mount | grep hugetlbfs
hugetlbfs on /dev/hugepages type hugetlbfs (rw,relatime,pagesize=2M)

# Pass along the a filename on a 'hugetblfs' mount
sudo bin/shared_hugepages /dev/hugepages/myfile
```