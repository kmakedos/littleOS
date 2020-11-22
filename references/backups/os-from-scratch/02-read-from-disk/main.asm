[org 0x7c00]

mov bp, 0x8000
mov sp, bp


mov bx, 0x9000
mov dh, 2

call disk_load

mov dx, [0x9000]
call print_hex

call print_newline

mov dx, [0x9000 + 512]
call print_hex

jmp $

%include "../common/print_functions.asm"
%include "../common/disk_load.asm"

;BOOT_DRIVE: db 0
times 510-($-$$) db 0
dw 0xAA55

times 256 dw 0xDADA
times 256 dw 0xFACE

