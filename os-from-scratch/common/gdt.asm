gdt_start:
    ; NULL Sector
    dd 0x0 ; 4 byte
    dd 0x0 ; 4 byte

gdt_code:
    dw 0xFFFF       ; BASE 0-15
    dw 0x0          ; LIMIT 0-15
    db 0x0          ; BASE 16-23

    ; 1st flags: present 1, privilege 00, descriptor type 1 -> 1001b,
    ; type flags: code 1, conforming 0, readable 1, accessed 0 -> 1010b
    db 10011010b ; 1st flags, type flags
    ; 2nd flags : granularity 1, 32bit 1, 64bit 0, AVL 0 -> 1100b
    db 11001111b; 2nd flags, LIMIT 6-19
    db 0x0 ; BASE 24-31

gdt_data:
    dw 0xFFFF
    dw 0x0
    db 0x0

    ; type flags: code 0, expand down 0, writeable 1, accessed 0 -> 0010b

    db 10010010b
    db 11001111b

    db 0x0


gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1

    dd gdt_start

CODE_SEG equ gdt_code - gdt_start

DATA_SEG equ gdt_data - gdt_start