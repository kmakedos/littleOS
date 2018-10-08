section .data
    userMsg db  'Please enter a number:'
    lenUserMsg  equ $-userMsg
    dispMsg db 'You have entered: '
    lenDispMsg  equ $-dispMsg

section .bss
    num resb 5


section .text
    global _start
_start:
                            ;   Write Message 
    mov eax,4               ;   sys_write
    mov ebx,1               ;   file descriptor
    mov ecx,userMsg         ;
    mov edx,lenUserMsg
    int 80h

    mov eax,3
    mov ebx,2 
    mov ecx,num
    mov edx,5               ;   5 bytes numeric, 1 for sign
    int 80h


    mov eax,4
    mov ebx,1
    mov ecx,dispMsg
    mov edx,lenDispMsg
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,num
    mov edx,5
    int 80h

    call _end


_end:
    mov eax,1
    mov ebx,0
    int 80h

