global outb
global inb
global load_gdt
; outb - send a byte to an I/O port
; stack:    [esp + 8] the data byte
;           [esp + 4] the I/O port
;           [esp    ] return address

outb:
    mov al, [esp + 8]   ; move the data to be sent into the al register
    mov dx, [esp + 4]   ; move the address of the I/O port into the dx register
    out dx, al          ; send the data to the I/O port
    ret 

; inb - returns a byte from the given IO port
; stack: [esp + 4] The address of the IO port
;        [esp    ] The return address
inb:
    mov dx, [esp + 4]   ; move the address of the I/O port to the dx register
    in  al, dx          ; read a byte from the port and store it in the al register
    ret                 ; return the read byte


; load_gdt - Load Global Descriptor Table 
load_gdt:
    lgdt [esp + 12]

