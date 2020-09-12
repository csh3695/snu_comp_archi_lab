cc = riscv64-unknown-elf-gcc
target = gcd

c_srcs = main.c
asm_srcs = gcd_asm.s

c_objs = $(c_srcs:.c=.o)
asm_objs = $(asm_srcs:.s=.o)

c_flags = -Wall -Werror -std=c99
ld_flags = 

all: $(target)

$(target):	$(c_objs) $(asm_objs)
		$(cc) $(c_objs) $(asm_objs) -o $(target)

.c.o:
	$(cc) $(c_flags) -c $< -o $@

.s.o:
	$(cc) -c $< -o $@

clean:
	rm -f $(c_objs) $(asm_objs) $(target)

#Usage:
# $> make
# $> spike $RISCV/bin/pk ./gcd 4 6	#Try different numbers!
