and x1 x1 x0
and x2 x1 x0
and x3 x1 x0
ori x1 x1 255
or x2 x2 x1
or x3 x1 x2
andi x1 x1 15
and x2 x3 x1
and x3 x2 x3
beq x1 x2 8
xor x1 x2 x2
xori x1 x1 16
add x2 x1 x1
addi x2 x2 -17
beq x1 x2 -20
ld x1 0(x0)
ld x2 8(x0)
ld x3 16(x0)
beq x3 x0 8
sd x3 24(x0)
beq x2 x2 8
sd x2 16(x0)
beq x1 x1 8
sd x1 8(x0)
halt