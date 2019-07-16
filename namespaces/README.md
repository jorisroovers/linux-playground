# Namespaces

```sh
cd namespaces
mkdir bin

gcc -std=c99 pidns_unshare.c -o bin/pidns_unshare


# sudo required for the new pid to work
sudo bin/pidns_unshare
# In different window
sudo lsns

# Notice how child namespaces match that of the parent, except for PID
sudo ls -l /proc/<child pid>/ns
sudo ls -l /proc/<parent pid>/ns

```