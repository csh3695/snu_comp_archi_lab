	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text

	#------You can declare additional functions here
	.align	1
	.globl	traverse
	.type	your_funct, @function
your_funct:
	#x_pos:a0, y_pos:a1, depth:a2, prev_trav:a3 //save needed
	#g_maze:s1, g_width:s2, g_height:s3 //const
	#t_up:zero, t_left:t1, t_right:t2, t_down:t3, max_depth:t6 //const
	bge a2, t6, RTM1
	blt a0, zero, RTM1
	blt a1, zero, RTM1 
	bge a0, s2, RTM1
	bge a1, s3, RTM1	# condi. of return -1 (RTM1)
	
	mul t4, a1, s2
	add t4, t4, a0
	addi t5, zero, 8 
	mul t4, t4, t5
	add t4, t4, s1
	ld t4, 0(t4)
	bne t4, zero, RTM1	# Dead end condition : return -1(RTM1)

	sub t4, a0, s2
	addi t4, t4, 1
	bne t4, zero, CONTI1
	sub t4, a1, s3
	addi t4, t4, 1
	bne t4, zero, CONTI1	# Success condition : not succeeded => CONTI1(Traverse up)
	
	beq zero, zero, RTD	# Success condition : succeeded => return depth(RTD)
### min = t4, result = t5
CONTI1:	# Traverse up checking
	#min:t4
	addi t4, zero, -1	# min = -1
	beq a3, t3, CONTI2	# if prev_trav = T_DOWN => pass and goto Traverse left
	##################### call traverse(x_pos, y_pos - 1, depth + 1, T_UP)
	addi sp, sp, -56
	sd t4, 48(sp)
	sd t5, 40(sp)
	sd x1, 32(sp)
	sd a0, 24(sp)
	sd a1, 16(sp)
	sd a2, 8(sp)
	sd a3, 0(sp)
	
	addi a1, a1, -1
	addi a2, a2, 1
	addi a3, zero, 0
	
	jal x1, your_funct
	addi t4, a0, 0 # min = traverse(x_pos, y_pos - 1, depth + 1, T_UP)

	ld a3, 0(sp)
	ld a2, 8(sp)
	ld a1, 16(sp)
	ld a0, 24(sp)
	ld x1, 32(sp)
	ld t5, 40(sp)
	ld zero, 48(sp)
	addi sp, sp, 56
	#####################

CONTI2:	# Traverse left checking
	beq a3, t2, CONTI4	# if prev_trav = T_RIGHT => pass and goto Traverse right
	##################### call traverse(x_pos - 1, y_pos, depth + 1, T_LEFT)
	addi sp, sp, -56
	sd t4, 48(sp)
	sd t5, 40(sp)
	sd x1, 32(sp)
	sd a0, 24(sp)
	sd a1, 16(sp)
	sd a2, 8(sp)
	sd a3, 0(sp)
	
	addi a0, a0, -1
	addi a2, a2, 1
	addi a3, t1, 0
	
	jal x1, your_funct
	addi t5, a0, 0	# result = traverse(x_pos - 1, y_pos, depth + 1, T_LEFT);

	ld a3, 0(sp)
	ld a2, 8(sp)
	ld a1, 16(sp)
	ld a0, 24(sp)
	ld x1, 32(sp)
	ld zero, 40(sp)
	ld t4, 48(sp)
	addi sp, sp, 56
	#####################
	blt t5, zero, CONTI4	# if result < 0 => pass and goto Traverse right
	blt t4, zero, CONTI3
	bgt t4, t5, CONTI3		# if min < 0 or min > result => min = result and goto Traverse right

CONTI3:
	add t4, t5, zero

CONTI4: # Traverse right checking
	beq a3, t1, CONTI5	# if prev_trav = T_LEFT => pass and goto Traverse down
	##################### call traverse(x_pos + 1, y_pos, depth + 1, T_RIGHT);
	addi sp, sp, -56
	sd t4, 48(sp)
	sd t5, 40(sp)
	sd x1, 32(sp)
	sd a0, 24(sp)
	sd a1, 16(sp)
	sd a2, 8(sp)
	sd a3, 0(sp)
	
	addi a0, a0, 1
	addi a2, a2, 1
	addi a3, t2, 0
	
	jal x1, your_funct
	addi t5, a0, 0	# result = traverse(x_pos + 1, y_pos, depth + 1, T_RIGHT)

	ld a3, 0(sp)
	ld a2, 8(sp)
	ld a1, 16(sp)
	ld a0, 24(sp)
	ld x1, 32(sp)
	ld zero, 40(sp)
	ld t4, 48(sp)
	addi sp, sp, 56
	#####################	 
	blt t5, zero, CONTI6	# if result < 0 => pass and goto Traverse down
	blt t4, zero, CONTI5
	bgt t4, t5, CONTI5		# if min < 0 or min > result => min = result and goto Traverse down

CONTI5:
	add t4, t5, zero

CONTI6:
	beq a3, zero, RTMIN	# if prev_trav = T_UP => pass and return min
	##################### call traverse(x_pos, y_pos + 1, depth + 1, T_DOWN);
	addi sp, sp, -56
	sd t4, 48(sp)
	sd t5, 40(sp)
	sd x1, 32(sp)
	sd a0, 24(sp)
	sd a1, 16(sp)
	sd a2, 8(sp)
	sd a3, 0(sp)
	
	addi a1, a1, 1
	addi a2, a2, 1
	addi a3, t3, 0
	
	jal x1, your_funct
	addi t5, a0, 0	# result = traverse(x_pos, y_pos + 1, depth + 1, T_DOWN)

	ld a3, 0(sp)
	ld a2, 8(sp)
	ld a1, 16(sp)
	ld a0, 24(sp)
	ld x1, 32(sp)
	ld zero, 40(sp)
	ld t4, 48(sp)
	addi sp, sp, 56
	#####################	
	blt t5, zero, RTMIN		# if result < 0 => pass and return min
	blt t4, zero, CONTI7
	bgt t4, t5, CONTI7		# if min < 0 or min > result => min = result and return min
	
CONTI7:
	add t4, t5, zero
	beq zero, zero, RTMIN

RTM1:	# return -1
	addi a0, zero, -1
	beq zero, zero, EXIT
RTD:	# return depth
	addi a0, a2, 0
	beq zero, zero, EXIT
RTMIN:	# return min
	addi a0, t4, 0
	beq zero, zero, EXIT

EXIT:	
	jr	ra
	.size	your_funct, .-your_funct

	#------Your code ends here
	.align	1
	.globl	solve_maze
	.type	solve_maze, @function
solve_maze:
	#------Your code starts here------
	#maze: a0, width: a1, height: a2
	addi sp, sp, -32
	sd x1, 24(sp)
	sd s1, 16(sp)		#g_maze
	sd s2, 8(sp)		#g_width
	sd s3, 0(sp)		#g_height
	addi t1, zero, 1	#T_LEFT 
	addi t2, zero, 2	#T_RIGHT
	addi t3, zero, 3	#T_DOWN
	addi t6, zero, 20	# MAX_DEPTH
	addi s1, a0, 0		#g_maze
	addi s2, a1, 0		#g_width
	addi s3, a2, 0		#g_height
	and a0, a0, zero
	and a1, a1, zero
	and a2, a2, zero
	addi a3, t2, 0
	jal x1, your_funct	#call solving function


################################
	ld s3, 0(sp)
	ld s2, 8(sp)
	ld s1, 16(sp)
	ld x1, 24(sp)
	addi sp, sp, 32
	# At this point a0 is return value itself.
	#------Your code ends here------

	#Ret
	jr	ra
	.size	solve_maze, .-solve_maze


	.ident	"GCC: (GNU) 9.2.0"