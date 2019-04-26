# GDB

```bash
# Regular build
mkdir bin
gcc gdb/gdbtest.c -o bin/gdbtest
bin/gdbtest


# Build with debugging symbols (needed for debugging)
gcc -g gdb/gdbtest.c -o bin/gdbtest
readelf --debug-dump=decodedline bin/gdbtest
gdb bin/gdbtest

# In gdb
break 5 # put breakpoint on line 5
run     # run program
quit    # quit
```