print_string:
    pusha ; push registers

start:
    mov al, [bx] ; bx contains string address
    cmp al, 0 ; 0 terminated string
    je done

    mov ah, 0x0e ; ah contains print fucntion 
    int 0x10 ; print interrupt
    add bx, 1 ; next char
    jmp start

done:
    popa 
    ret


print_newline:
    pusha

    mov ah, 0x0e 
    mov al, 0x0a ; newline
    int 0x10
    mov al, 0x0d ; cr
    int 0x10

    popa
    ret

print_hex:
    pusha
    mov cx, 0 ; index reg

hex_loop:
    cmp cx, 4 ; 4 chars
    je end

    mov ax, dx ; ax working reg, dx is input reg
    and ax, 0x000f ; mask first three
    add al, 0x30 ; convert to ascii
    cmp al, 0x39 ; if > 9; add extra 8 to represent 'A' to 'F'
    jle step2
    add al, 7 ; 'A' is ASCII 65 instead of 58, so 65-58=7
    
step2:
    mov bx, HEX_OUT+5 ; base + length
    sub bx, cx ; index
    mov [bx], al ; copy ascii char on al to position by [bx]
    ror dx, 4 ; 0x1234 -> 0x4123 -> 0x3412 -> 0x2341 -> 0x1234

    add cx, 1
    jmp hex_loop

end:
    mov bx, HEX_OUT
    call print_string

    popa
    ret

HEX_OUT:
    db '0x0000',0




