CC = gcc
CXX = g++
target = riscv-assembler

c_sources = 
cxx_sources = main.cpp riscv-assembler.cpp
headers = riscv-assembler.h
objects = $(cxx_sources:.cpp=.o) $(c_sources:.c=.o)

c_flags = -Wall -Werror -I.
ld_flags = 

all: $(target)

$(target):	$(objects)
		$(CXX) $(objects) $(ld_flags) -o $(target)

.cpp.o:
	$(CXX) $(c_flags) -c $< -o $@

.c.o:
	$(CC) $(c_flags) -c $< -o $@

clean:
	rm -f $(objects) $(target) *.dat
