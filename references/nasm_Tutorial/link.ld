ENTRY(_start)                   /* name of the entry label */

SECTIONS {  
    . = 0x0000000000400080;             /* code should be loaded at 4MB */

    .text ALIGN (0x1000) :      /* align at 4 KB */
    {
        *(.text)                /* all text sections from all files */
    }

    .rodata ALIGN (0x1000) :    /* align at 4 KB */
    {
        *(.rodata)              /* all read-only data from all files */
    }

    .data ALIGN (0x1000) :      /* align at 4 KB */
    {
        *(.data)                /* all data sections from all files */
    }

    .bss ALIGN (0x1000) :       /* align at 4 KB */
    {
        *(COMMON)               /* all COMMON sections from all files */
        *(.bss)                 /* all bss sections from all files */
    }
}
