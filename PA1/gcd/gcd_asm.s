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
LOOP:	
	beq a0, a1, EXIT	# if LHS == RHS => EXIT with return value LHS
	bge a1, a0, COND1	# if RHS > LHS => goto COND1
	sub a0, a0, a1
	bge x0, x0, LOOP	# LHS -= RHS and LOOP again
COND1:					
	sub a1, a1, a0
	bge x0, x0, LOOP	# COND1 : RHS-=LHS and LOOP again
EXIT:					# a0 is return value itself
	#Load return value to reg a0
	#------Your code ends here------

	#Ret
	jr	ra
	.size	gcd, .-gcd


	.ident	"GCC: (GNU) 9.2.0"
