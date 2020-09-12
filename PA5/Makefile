cc = gcc
target = conv_test

c_srcs = main.c conv.c conv_ref.c
objects = $(c_srcs:.c=.o)

c_flags = -Wall -Werror -std=c99 -O0
#ld_flags = -Wl,-z,relro
ld_flags = 

all: $(target)

$(target):      $(objects)
	        $(cc) $(ld_flags) $(objects) -o $(target) ./conv_TA.so

.c.o:
	        $(cc) $(c_flags) -c $< -o $@

clean:
	        rm -f $(objects) $(target)

