global loader                           ;   the entry symbol for ELF
MAGIC_NUMBER    equ     0x1BADB002      ;   define the magic number constant
FLAGS           equ     0x0             ;   multiboot flags
CHECKSUM        equ     -MAGIC_NUMBER   ;   calculate the checksum
                                        ;   magic_number + checksum + flags should equal 0
section     .text:                      ;   start of the text (code)
align       4                           ;   code must be 4 byte aligned
    dd  MAGIC_NUMBER                    ;   write the magic number to machine code
    dd  FLAGS                           ;   write flags
    dd  CHECKSUM                        ;   and the checksum

loader:                                 ;   the loader label
    mov eax,0xCAFEBABE                  ;   place the number 0xCAFEBABE to EAX register
.loop:                                  ;   loop forever
    jmp .loop
