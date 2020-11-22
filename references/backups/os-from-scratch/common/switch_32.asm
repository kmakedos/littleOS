[bits 16]

switch_to_pm:

    cli
    lgdt [gdt_descriptor]

    mov eax, cr0 ; we must set cr0 bit 0 to 1
    or eax, 0x1
    mov cr0, eax

    jmp CODE_SEG:init_pm

[bits 32]

init_pm:
    mov ax, DATA_SEG ; moving our segment registers to use then data selector in new GDT
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    call BEGIN_PM
