section .data
    name        db 'Mike Makedos'
    lenName     equ $-name



section .text
    global _start
_start:
    mov eax,4
    mov ebx,1
    mov ecx,name
    mov edx,lenName
    int 80h
    mov [name],dword "John"
    mov ecx,name
    mov eax,4
    mov ebx,1
 
    int 80h
    call _end

_end:
    mov eax,1
    mov ebx,0
    int 80h

