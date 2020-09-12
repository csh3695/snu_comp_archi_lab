cc = riscv64-unknown-elf-gcc
target = maze

c_srcs = main.c #maze.c
asm_srcs = maze_asm.s
objects = $(c_srcs:.c=.o) $(asm_srcs:.s=.o)

c_flags = -Wall -Werror -std=c99
ld_flags = 

all: $(target)

$(target):	$(objects)
		$(cc) $(objects) -o $(target)

.c.o:
	$(cc) $(c_flags) -c $< -o $@

.s.o:
	$(cc) -c $< -o $@

clean:
	rm -f $(objects) $(target)

#Usage:
# $> make
# $> spike --isa=RV32IMAFDC $RISCV/bin/pk ./maze input.txt
