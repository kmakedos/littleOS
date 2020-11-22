CC=i686-elf-gcc

boot: 
	nasm -f elf32 boot.asm -o boot.o

kernel:
	$(CC) -c kernel.c -o kernel.o  -std=gnu99 -ffreestanding -O2 -Wall -Wextra

bin:
	$(CC) -T linker.ld -o makedos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

all: $(boot) $(kernel) $(bin)

clean:
	rm -vf *.o
