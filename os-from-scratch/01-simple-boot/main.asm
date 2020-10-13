[org 0x7c00]

mov bx, HELLO
call print_string

call print_newline

mov bx, GOODBYE

call print_string
call print_newline

mov dx, 0x12fe
call print_hex
call print_newline

jmp $


%include "../common/print_functions.asm"

HELLO:
    db 'Hello World',0

GOODBYE:
    db 'Goodbye',0


times 510-($-$$) db 0
dw 0xaa55
