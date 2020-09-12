add x1  x0  x0
ld  x2  16(x0)
add x2  x2  x2
addi x2  x2  160
andi x2  x2  15
ld  x3  24(x0)
add x3  x2  x3
xori x3 x3  255
add x3  x3  x2
addi x2  x2  -1
addi x1 x1 8
sd  x3  0(x1)
beq x2  x2  -4
andi x2 x2  0
andi x3 x2  0
halt
