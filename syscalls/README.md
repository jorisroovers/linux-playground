To get started:

```sh
cd syscalls
mkdir bin

gcc -std=c99 basics/helloworld.c -o bin/helloworld
gcc -std=c99 basics/write.c -o bin/write
gcc -std=c99 cat/mycat.c -o bin/mycat
gcc -std=c99 cat/syscat.c -o bin/syscat
gcc -std=c99 syslog/mylog.c -o bin/mylog.c
gcc -std=c99 execve/become_ls.c -o bin/become_ls.c
gcc -std=c99 session/session_leader.c -o bin/session_leader
gcc -std=c99 seccomp/seccomp.c -o bin/seccomp

gcc -std=c99 sockets/unix_domain_client.c -o bin/client
```