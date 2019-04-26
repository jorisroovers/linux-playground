; From http://www.cirosantilli.com/elf-hello-world/#generate-the-example
; This program basically does:
;  write(1, "Hello 32-bit world!\n", 20); // 20 = string length
;  exit(0) // 0 = normal exit

section .data
    hello_world db "Hello 32-bit world!", 10                    ; 10 = Decimal ASCII newline hard (0x0A)
    hello_world_len  equ $ - hello_world
section .text
    global _start
    _start:
        ; write(1, "Hello world!\n", 13)
        mov eax, 4                   ; write() = x86_32 syscall number 4
        mov ebx, 1                   ; filehandle = 1 = STDOUT
        mov ecx, hello_world         ; Insert "Hello World!\n" string
        mov edx, hello_world_len     ; Insert length of Hello World string
        int 80h                      ; Perform the syscall

        ; exit(0)
        mov eax, 1                  ; exit() = x86_64 syscall number 60
        mov ebx, 0                  ; 0 = normal exit
        int 80h                     ; Perform the syscall