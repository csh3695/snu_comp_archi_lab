ld	x1, 8(x0)
addi	x2, x0, 255
addi	x3, x0, 132
or	x5, x2, x3
and	x4, x1, x2
xori	x6, x0, -444
and	x7, x1, x3
sd	x7, 32(x0)
sd	x6, 24(x0)
sd	x5, 16(x0)
sd	x4, 8(x0)
halt
