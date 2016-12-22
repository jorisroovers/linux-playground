#!/usr/bin/env bash

# remove the cgroup from any previous run
CGROUP_DIR="/sys/fs/cgroup/memory/mycoolgroup"
echo "(Re)Creating new cgroup $CGROUP_DIR"
cgdelete memory:mycoolgroup
cgcreate -g memory:mycoolgroup #  can also be done using "mkdir $CGROUP_DIR"

echo "Setting memory.limit_in_bytes to 100k bytes"
echo "100000" > $CGROUP_DIR/memory.limit_in_bytes

echo "Compiling the use_memory program..."
gcc -std=c99 use_memory.c -o use_memory
chmod +x use_memory

echo ""

echo "We will now start our program that will progressively eat more memory"
echo "At some point you'll notice that the program gets killed after it uses more than 100Kib"
echo "Note that the memory usage doesn't get updated after every iteration, this is just the cgroup usage reporting lagging behind a bit"
echo ""
echo "Starting program in the background"
./use_memory &
USE_MEMORY_PID=$!

echo ""

echo "Adding test program with PID $USE_MEMORY_PID to our cgroup"
echo $USE_MEMORY_PID > $CGROUP_DIR/tasks
echo ""

while :
do
    echo "Memory in use: $(cat $CGROUP_DIR/memory.usage_in_bytes)"
    sleep 1
done