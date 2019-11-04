# umask
Umask = default file mode for newly created files

## touch
```sh
# same for touch, although it's much better at it.
# NOTE: executable bits are never set automatically, always need to be added
umask 0000 # grant all permissions to everyone
rm -f /tmp/foobar.txt && touch /tmp/foobar.txt && ls -l /tmp/foobar.txt
umask 0020 # Remove "write" permissions from group
rm -f /tmp/foobar.txt && touch /tmp/foobar.txt && ls -l /tmp/foobar.txt
```

## open() syscall

```sh
mkdir bin
gcc create_file.c -o bin/create_file

# Notice that open() syscall doesn't really adhere to umask: it seems to only apply the 'other' bits
# Might have something to do with the O_CREAT flag
umask 0000
bin/create_file /tmp/foobar.txt && ls -l /tmp/foobar.txt && rm -f /tmp/foobar.txt
```