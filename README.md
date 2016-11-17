# linux-playground

Personal playground for linux related things.

To get going with the syscalls:
```
vagrant up
vagrant ssh
cd syscalls
gcc -std=c99 basics/helloworld.c -o bin/helloworld
gcc -std=c99 cat/mycat.c -o bin/mycat
gcc -std=c99 cat/syscat.c -o bin/syscat
gcc -std=c99 syslog/mylog.c -o bin/mylog.c

```