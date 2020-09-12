	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	fibonacci
	.type	fibonacci, @function
fibonacci:
	#------Your code starts here------
	#*OPT: a0, COUNT: a1
	addi a2, a0, 0		# a2 = return address
	addi a3, zero, 1	# a3 = 1 	
	sd a3, 0(a0)		# opt[0] = 1
	addi a3, a3, 1		# a3 = 2	
	blt a1, a3, EXIT	# if count < 2 exit
	addi a0, a0, 8		# opt address update
	addi a3, a3, -1		# a3 = 1	
	sd a3, 0(a0)		# opt[1] = 1
	addi a3, a3, 1		# a3 = 2
LOOP:
	bge a3, a1, EXIT	# if i >= count exit
	ld a4, 0(a0)		# a4 = opt[i]
	ld a5, -8(a0)		# a5 = opt[i-1]
	addi a0, a0, 8		# opt address update
	add a6, a4, a5		# a6 = a4 + a5
	sd a6, 0(a0)		# opt[i+1] = a6 :: opt[i+1] = opt[i-1] + opt[i]
	addi a3, a3, 1		# i++
	beq zero, zero, LOOP # Unconditional branch
EXIT:	
	addi a0, a2, 0		# load return value (a2 : opt address) to a0
	#Load return value to reg a0
	#------Your code ends here------

	#Ret
	jr	ra
	.size	fibonacci, .-fibonacci
	.ident	"GCC: (GNU) 9.2.0"
