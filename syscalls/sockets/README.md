# Socket syscalls

## unix_domain_client.c
```sh
# Compilation (from the syscalls directory):
gcc -std=c99 sockets/unix_domain_client.c -o bin/unix_domain_client

#  root:

# Terminal 1 (start UNIX domain socket):
# 'fork' option keeps the connection alive after client disconnect
socat - UNIX-LISTEN:/tmp/mysocket,fork

# Terminal 2 (run unix domain client);
bin/unix_domain_client
```