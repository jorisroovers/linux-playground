# NASM

Simple assembler examples.

Note for 32-bit assembly, you need to have i386 support installed on the machine (see Vagrantfile for installation details).

Linux syscalls are also numbered differently between 64 and 32 bit x86 ISAs.

To invoke syscalls on x86_64, you use the ```syscall``` instruction, while on regular (32bit) x64, you use the ```int 0x80``` instruction.

## 64 bit
```sh
# Assemble
nasm -w+all -f elf64 -o bin/hello_world.o nasm/hello_world.asm
# Link
ld -o bin/hello_world.out bin/hello_world.o

# Execute
bin/hello_world.out

# Inspect
readelf -a bin/hello_world.out

# Disassemble
# Note that nasm optimizes registers to 32 bit:
# https://stackoverflow.com/questions/26504930/recieving-32-bit-registers-from-64-bit-nasm-code
objdump -d bin/hello_world.out

# Note that this is the same as what has been stored in the .text section of the binary
readelf -x .text bin/hello_world.out
```

## 32 bit

```sh
# Assemble
nasm -w+all -f elf32 -o bin/hello_world_32bit.o nasm/hello_world_32bit.asm
# Link
ld -m elf_i386 -o bin/hello_world_32bit.out bin/hello_world_32bit.o

# Execute
bin/hello_world_32bit.out

# Inspect
readelf -a bin/hello_world_32bit.out
```