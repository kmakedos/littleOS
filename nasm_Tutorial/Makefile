LDFLAGS = -T link.ld 

AS = nasm
ASFLAGS = -f elf64 -g

all: hello_world registers_stars read_keyboard change_name


hello_world: hello_world.o
	ld $(LDFLAGS) hello_world.o -o hello_world

change_name: change_name.o
	ld $(LDFLAGS) change_name.o -o change_name

read_keyboard: read_keyboard.o
	ld $(LDFLAGS) read_keyboard.o -o read_keyboard


registers_stars: registers_stars.o
	ld $(LDFLAGS) registers_stars.o -o registers_stars

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o hello_world registers_stars read_keyboard change_name
