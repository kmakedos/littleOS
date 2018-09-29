global loader                                   ;   the entry symbol for ELF
extern kmain
MAGIC_NUMBER        equ     0x1BADB002          ;   define the magic number constant
FLAGS               equ     0x0                 ;   multiboot flags
CHECKSUM            equ     -MAGIC_NUMBER       ;   calculate the checksum
                                                ;   magic_number + checksum + flags should equal 0
KERNEL_STACK_SIZE   equ     4096                ;   size of stack in bytes

section     .text:                              ;   start of the text (code)
align   4                                       ;   code must be 4 byte aligned
    dd  MAGIC_NUMBER                            ;   write the magic number to machine code
    dd  FLAGS                                   ;   write flags
    dd  CHECKSUM                                ;   and the checksum


loader:                                         ;   the loader label
    mov esp, kernel_stack + KERNEL_STACK_SIZE   ;   point esp to the start of the 
                                                ;   stack (end of memory area)
    call kmain
.loop:                                          ;   loop forever
    jmp .loop


section     .bss
align   4
kernel_stack:       
    resb    KERNEL_STACK_SIZE               ;   reserve stack for the kernel
 
