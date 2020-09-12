add x1, x0, x0
ld  x2, 8(x0)
addi x2, x2, 255
ori  x2, x2, 256
andi x2, x2, 15
beq x2, x0, 24
addi x1, x1, 8
add x5, x2, x2
sd x5, 0(x1)
addi x2, x2, -1
beq x2, x2, -20
add x1, x0, x0
addi x1, x0, 1
add x2, x0, x0
addi x2, x0, 1
add x3, x0, x0
addi x3, x0, 1
halt