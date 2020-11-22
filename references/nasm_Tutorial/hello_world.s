
section .text               ; code
global _start
_start:
    mov edx,len
    mov ecx,msg
    mov ebx,1
    mov eax,4
    int 0x80

    mov eax,1
    int 0x80


section .data               ; data or constants
msg db 'Hello world!', 0xa
len equ $ - msg

section .bss                ; variables

