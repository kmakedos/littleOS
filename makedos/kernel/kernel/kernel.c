#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void) {
	terminal_initialize();
    printf("Welcome to MakeDOS !\n");
    printf("A new operating System !\n");
    printf("Written for the new world !\n");
}
