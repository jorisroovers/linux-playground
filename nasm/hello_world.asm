; From http://www.cirosantilli.com/elf-hello-world/#generate-the-example
; This program basically does:
;  write(1, "Hello 64-bit World!\n", 20); // 20 = string length
;  exit(0) // 0 = normal exit

section .data
    hello_world db "Hello 64-bit world!", 10                     ; 10 = Decimal ASCII newline hard (0x0A)
    hello_world_len  equ $ - hello_world
section .text
    global _start
    _start:
        ; write(1, "Hello world!\n", 13)
        mov rax, 1                   ; write() = x86_64 syscall number 1
        mov rdi, 1                   ; filehandle = 1 = STDOUT
        mov rsi, hello_world         ; Insert "Hello World!\n" string
        mov rdx, hello_world_len     ; Insert length of Hello World string
        syscall                      ; Perform the syscall

        ; exit(0)
        mov rax, 60                 ; exit() = x86_64 syscall number 60
        mov rdi, 0                  ; 0 = normal exit
        syscall                     ; Perform the syscall 