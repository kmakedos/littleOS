LDFLAGS = -T link.ld 

AS = nasm
ASFLAGS = -f elf64 -g
BIN_DIR = bin
all: hello_world registers_stars read_keyboard change_name add_two_nums


hello_world: hello_world.o
	ld $(LDFLAGS) hello_world.o -o $(BIN_DIR)/hello_world

change_name: change_name.o
	ld $(LDFLAGS) change_name.o -o $(BIN_DIR)/change_name

read_keyboard: read_keyboard.o
	ld $(LDFLAGS) read_keyboard.o -o $(BIN_DIR)/read_keyboard


registers_stars: registers_stars.o
	ld $(LDFLAGS) registers_stars.o -o $(BIN_DIR)/registers_stars

add_two_nums: add_two_nums.o
	ld $(LDFLAGS) add_two_nums.o -o $(BIN_DIR)/add_two_nums



%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@ 

clean:
	rm -rf *.o bin/*
