
.data

	displayArray:
	.space 0x4000
	
	auxiliarArray:
	.space 0x4000

############################################################
#							   #
#	Populate Auxiliar Array 			   #
#							   #
############################################################
	
.text

	main:
	j	populate
	
	random_number:
	#sw	$a0,	0($s0)
	li	$a1,	2
	li 	$v0,	42
	syscall
	jr	$ra
	
	populate:
	li	$t0,	0x4000
	addi	$t1,	$zero, 	0
	la	$t2,	auxiliarArray
	addi	$t3,	$zero, 	-1
	
	populate_loop:
	bgt	$t1,	$t0,	display
	jal	random_number
	mul	$a0, 	$a0, 	$t3
	add	$t4,	$t2, 	$t1
	sw	$a0,	0($t4)
	addiu	$t1, 	$t1, 	4
	j	populate_loop	
	
############################################################
#							   #
#	Populate Display Array 				   #
#							   #
############################################################

	display:
	li	$t0,	0x4000
	addi	$t1,	$zero, 	0
	la	$t2,	displayArray
	la	$t3,	auxiliarArray
	
	display_loop:
	bgt	$t1, 	$t0, 	update
	add	$t4,	$t3, 	$t1
	lw	$t5,	0($t4)
	add	$t4,	$t2, 	$t1
	sw	$t5,	0($t4)
	addiu	$t1,	$t1, 	4
	j	display_loop
	
############################################################
#							   #
#	Update Auxiliar Array				   #
#							   #
############################################################
#							   #
#	- Any live cell with fewer than 		   #
#	  two live neighbours dies, as 			   #
#	  if caused by under-population.		   #
#							   #
#	- Any live cell with two or three 		   #
#	  live neighbours lives on to the 		   #
#	  next generation.			  	   #
#							   #
#	- Any live cell with more than three 		   #
#	  live neighbours dies, as if by 		   #
#	  overcrowding.					   #
#							   #
#	- Any dead cell with exactly three 		   #
#	  live neighbours becomes a live 		   #
#	  cell, as if by reproduction.			   #
#							   #
############################################################

	verify:
	lw	$a1,	0($a0)
	addi	$a2,	$zero, 	0
	la	$s4,	displayArray
	la	$s5,	auxiliarArray
	addi	$s5,	$s5,	-0x4
	
	verify_1:
	li	$s2,	0xffffffff
	addi	$a3,	$a0,	-0x104
	blt	$a3,	$s4,	verify_2
	lw	$s1,	0($a3)
	seq	$s2,	$s1,	$s2
	add	$a2,	$a2,	$s2
	
	verify_2:
	li	$s2,	0xffffffff
	addi	$a3,	$a0,	-0xd8
	blt	$a3,	$s4,	verify_3
	lw	$s1,	0($a3)
	seq	$s2,	$s1,	$s2
	add	$a2,	$a2,	$s2
	
	verify_3:
	li	$s2,	0xffffffff
	addi	$a3,	$a0,	-0xfc
	blt	$a3,	$s4,	verify_4
	lw	$s1,	0($a3)
	seq	$s2,	$s1,	$s2
	add	$a2,	$a2,	$s2
	
	verify_4:
	li	$s2,	0xffffffff
	addi	$a3,	$a0,	-0x4
	blt	$a3,	$s4,	verify_5
	lw	$s1,	0($a3)
	seq	$s2,	$s1,	$s2
	add	$a2,	$a2,	$s2
	
	verify_5:
	li	$s2,	0xffffffff
	addi	$a3,	$a0,	0x4
	bgt	$a3,	$s5,	verify_6
	lw	$s1,	0($a3)
	seq	$s2,	$s1,	$s2
	add	$a2,	$a2,	$s2
	
	verify_6:
	li	$s2,	0xffffffff
	addi	$a3,	$a0,	0xfc
	bgt	$a3,	$s5,	verify_7
	lw	$s1,	0($a3)
	seq	$s2,	$s1,	$s2
	add	$a2,	$a2,	$s2
	
	verify_7:
	li	$s2,	0xffffffff
	addi	$a3,	$a0,	0xd8
	bgt	$a3,	$s5,	verify_8
	lw	$s1,	0($a3)
	seq	$s2,	$s1,	$s2
	add	$a2,	$a2,	$s2
	
	verify_8:
	li	$s2,	0xffffffff
	addi	$a3,	$a0,	0x104
	bgt	$a3,	$s5,	verify_condition
	lw	$s1,	0($a3)
	seq	$s2,	$s1,	$s2
	add	$a2,	$a2,	$s2
	
	verify_condition:	
	beq	$a1,	$zero,	verify_false
	j	verify_true
	
	verify_true:
	blt	$a2,	2,	verify_dies
	blt	$a2,	4,	verify_lives
	j	verify_dies
	
	verify_false:
	beq	$a2,	3,	verify_lives
	j	verify_dies
	
	verify_lives:
	addi	$s1,	$a0,	0x4000
	li	$s2,	0xffffffff
	sw	$s2,	0($s1)
	j	verify_end
	
	verify_dies:
	addi	$s1,	$a0,	0x4000
	li	$s2,	0x0
	sw	$s2,	0($s1)
	j	verify_end
	
	verify_end:
	jr	$ra

	update:
	li	$t0,	0x4000
	addi	$t1,	$zero, 	0
	la	$t2,	displayArray
	la	$t3,	auxiliarArray
	li	$t4,	0
	
	update_loop:
	bgt	$t1, 	$t0, 	display
	add	$a0, 	$t2,	$t1
	jal	verify
	addiu	$t1,	$t1, 	4
	j	update_loop