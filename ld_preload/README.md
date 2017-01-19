# LD_PRELOAD #

Some messing with LD_PRELOAD: a way to override library calls in C.
Inspired by https://jvns.ca/blog/2014/11/27/ld-preload-is-super-fun-and-easy/


```bash
cd preload
mkdir bin

# compile shared library
gcc -c -Wall -Werror -fpic libhello.c
gcc -c -Wall -Werror -fpic libhackzor.c

# turn it into a shared lib
gcc -shared -o libhello.so libhello.o
gcc -shared -o libhackzor.so libhackzor.o

# Compile myprogram, link libhello and let gcc know to search the current directory for libhello.sh (= -L .)
gcc -Wall -L . -o bin/myprogram myprogram.c -lhello

# Set the library path so the linker can find it
LD_LIBRARY_PATH=$(pwd):$LD_LIBRARY_PATH

chmod +x bin/myprogram
bin/myprogram
# This will print "Hello World"
# However, by setting LD_PRELOAD to export libhackzor.so, we can overwrite that function on runtime
export LD_PRELOAD=$(pwd)/libhackzor.so

# Rerunning bin/myprogram will now result in "Haha, hijacked print_hello!"
# You can also do this by adding libhackzor.so to /etc/ld.so.preload
echo "$(pwd)/libhackzor.so" | sudo tee --append /etc/ld.so.preload

# The best way to see that /etc/ld.so.preload is being used is to actually do an strace on bin/myprogram
# You'll notice that /etc/ld.so.preload is read and consequently libhackzor.so is mapped into memory
strace bin/myprogram

# Note that this happens for every program execution, e.g.:
strace cat README.md
```