# tempfs test

Tempfs disks are in memory disks. You can tests that they are a lot faster by doing the following test:

```bash
# create a ramdisk
mkdir myramdisk
sudo mount -t tmpfs tmpfs myramdisk

# create a 50MB file
head -c 50M </dev/urandom >myfile
# time how long it takes to copy the file
time cat myfile > myfile2

# copy it to myramdisk
cp myfile myramdisk/myfile
# compare how much faster it is in the ramdisk

time cat myramdisk/myfile myramdisk/myfile2
```

