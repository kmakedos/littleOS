SYS_EXIT equ 1 ; x64 is 60, x86 is 1
SYS_READ equ 3
SYS_WRITE equ 4
STDIN equ 0
STDOUT equ 1

section .data
msg db 'Give me a number:', 0xA
msg_len equ $- msg

sum_msg db 'Sum is:', 0xA
sum_len equ $- sum_msg

section .bss
    num1 resb 4
    num2 resb 4
    res  resb 4

section .text
    global _start
_start:
    mov eax,SYS_WRITE
    mov ebx,STDOUT
    mov ecx,msg
    mov edx,msg_len
    int 80h


    mov rax,SYS_READ
    mov rbx,STDIN
    mov rcx,num1
    add [res],rcx
    mov rdx,4
    int 80h

    mov eax,SYS_WRITE
    mov ebx,STDOUT
    mov ecx,msg
    mov edx,msg_len
    int 80h

    mov eax,SYS_READ
    mov ebx,STDIN
    mov ecx,num2
    add [res],ecx
    mov edx,4
    int 80h


    mov eax,SYS_WRITE
    mov ebx,STDOUT
    mov ecx,sum_msg
    mov edx,sum_len
    int 80h

    mov eax,SYS_WRITE
    mov ebx,STDOUT
    mov ecx,res
    mov edx,4
    int 80h

    call _end
_end:
    mov eax,SYS_EXIT
    xor ebx,ebx
    int 80h

