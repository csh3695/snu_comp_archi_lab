.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text


	.align	1
	.globl	gcd
	.type	gcd, @function
gcd:
	#------Your code starts here------
	#LHS: a0, RHS: a1
Loop:	beq a0, a1, Exit
	bge a0, a1, Else
	sub a1, a1, a0
	beq x0, x0, Loop
Else:	sub a0, a0, a1
	beq x0, x0, Loop
Exit:	
	#Load return value to reg a0
	#------Your code ends here------

	#Ret
	jr	ra
	.size	gcd, .-gcd


	.ident	"GCC: (GNU) 9.2.0"