# prog.s ... Game of Life on a NxN grid
#
# Needs to be combined with board.s
# The value of N and the board data
# structures come from board.s
#
# Written by Connor McLeod z5058240, August 2017

.data
	msg1: 			.asciiz "# Iterations: "
	msg2:			.asciiz "=== After iteration "
	msg3:			.asciiz " ===\n"
	board_0:		.asciiz "."
	board_1:		.asciiz "#"
	new_line:		.asciiz "\n"
	.align 2
	main_ret_save:	.space 4
	maxiters:		.space 4
	nn:				.space 4

.text

.globl main
main:
	# $s0 = maxiters
	# $s1 = N
	# $s2 = n
	# $s3 = i
	# $s4 = j
	# $s5 = nn

	sw			$ra, main_ret_save

	# printf, scanf and assign s0 = maxiters
	la			$a0, msg1
	li			$v0, 4
	syscall
	li			$v0, 5
	syscall
	sw			$v0, maxiters
	lw			$s0, maxiters

	# assign s1: N
	lw			$s1, N

	# assign s2: n = 1
	li			$s2, 1

# while (n <= maxiters)
next_iteration:
	# if n > maxiters, branch to end_main
	bgt			$s2, $s0, end_main

	# assign or reset s3: i = 0
	li			$s3, 0

# while (i < N) - navigate across rows
row_Loop:
	# if N <= i, branch to print_iteration
	ble			$s1, $s3, print_iteration

	# assign or reset s4: j = 0
	li			$s4, 0

# while (j < N) - navigate across columns
col_Loop:
	# if N <= j, branch to end_col_Loop
	ble			$s1, $s4, end_col_Loop

	# assign a0: i
	move			$a0, $s3
	# assign a1: j
	move			$a1, $s4
	# call neighbours(i,j)
	jal			neighbours
	# store return (nn) in s5
	move			$s5, $v0

	# assign t2: (N*i)+j
	mul			$t2, $s1, $s3
	add			$t2, $t2, $s4

# setup to write to newBoard
# newBoard_setup:
	# assign $t3 to [0][0] of newBoard
	la			$t3, newBoard
	# assign t4: &newBoard[i][j]
	add			$t4, $t3, $t2
	# assign t4: load value of newBoard[i][j]
	lb			$t4, ($t4)

# setup to check current board
# checkBoard_setup:
	# assign $t0 to [0][0] of board
	la			$t0, board
	# assign t1: &board[i][j]
	add			$t1, $t0, $t2
	# assign t1: load value of board[i][j]
	lb			$t1, ($t1)

	# continue in col_Loop
	# if board[i][j] = 1, branch
	beq			$t1, 1, check_nn
	# otherwise, branch
	j			set_newBoard_to_0

check_nn:
	# if nn < 2, branch
	blt			$s5, 2, set_newBoard_to_0
	# if nn = 2, branch
	beq			$s5, 2, set_newBoard_to_1
	# if nn = 3, branch
	beq			$s5, 3, set_newBoard_to_1

set_newBoard_to_0:
	# if nn = 3, branch
	beq			$s5, 3, set_newBoard_to_1
	# set newBoard[i][j] to 0
	li			$t5, 0
	sb			$t5, newBoard($t2)
	j			end

set_newBoard_to_1:
	# set newBoard[i][j] to 1
	li			$t5, 1
	sb			$t5, newBoard($t2)
	j			end

end:
	# j++
	addi			$s4, $s4, 1
	j			col_Loop

end_col_Loop:
	# i++
	addi			$s3, $s3, 1
	j			row_Loop

# Function to print each newBoard, also increments n
print_iteration:
	# print "=== After iteration n ===\n"
	la			$a0, msg2
	li			$v0, 4
	syscall
	move			$a0, $s2
	li			$v0, 1
	syscall
	la			$a0, msg3
	li			$v0, 4
	syscall

	# call function to print board
	jal			copyBackAndShow

	# increment n
	addi			$s2, $s2, 1
	# jump to next_iteration
	j			next_iteration

end_main:
	lw			$ra, main_ret_save
	jr			$ra


################################################################
################################################################


neighbours:
	# $t0 = nn
	# $t1 = x
	# $t2 = y
	# $t3 = i+x
	# $t4 = j+y
	# $t5 = board
	# $t6 = 1
	# $t7 = (i+x)*N + board
	# $s1 = N-1 (or N)

	#prologue
	addi			$sp, $sp, -12
	sw			$fp, 0($sp)
	move			$fp, $sp
	sw			$ra, 4($sp)
	sw			$s1, 8($sp)

	#function body

	# assign t6 = 1
	li			$t6, 1

	# assign t0: nn = 0
	li			$t0, 0

	# N = N - 1
	sub			$s1, $s1, $t6

	# assign t1: x = -1
	li			$t1, -1

# while x <= 1
x_Loop:
	# if x > 1, branch to neighbours epilogue
	blt			$t6, $t1, neighbours_epilogue

	# assign t2: y = -1
	li			$t2, -1

# while y <= 1
y_Loop:
	# if y > 1 branch to end_y_Loop
	blt			$t6, $t2, end_y_Loop

	# assign t3: x+i
	add			$t3, $t1, $s3
	# assign t4: y+j
	add			$t4, $t2, $s4

	# if (i+x < 0 || i+x > N-1) continue;
	blt			$t3, 0, loop_continue
	bgt			$t3, $s1, loop_continue

	# if (j+y < 0 || j+y > N-1) continue;
	blt			$t4, 0, loop_continue
	bgt			$t4, $s1, loop_continue

	# if (x == 0 && y == 0) continue;
	bne			$t1, 0, checkNeighbours
	bne			$t2, 0, checkNeighbours

	j			loop_continue

checkNeighbours:
	#reset N to original value
	add			$s1, $s1, 1

	# assign t5 to [0][0] of board
	la			$t5, board

	# assign t7: (i+x)*N + (j+y) + &board[i][j]
	mul			$t7, $t3, $s1
	add			$t7, $t7, $t4
	add			$t7, $t7, $t5

	# assign t7: load value of board[i][j]
	lb			$t7, ($t7)

	# reset N to value before checkBoard
	sub			$s1, $s1, 1

	# if board[i+x][j+y] != 1
	bne			$t7, $t6, loop_continue

	# nn++
	add			$t0, $t0, 1

loop_continue:
	# y++
	add			$t2, $t2, 1
	j			y_Loop

end_y_Loop:
	# x++
	add			$t1, $t1, 1
	j			x_Loop

#epilogue
neighbours_epilogue:
	move			$v0, $t0
	lw			$s1, 8($sp)
	lw			$ra, 4($sp)
	lw			$fp, 0($sp)
	addi			$sp, $sp, 12
	jr			$ra


################################################################
################################################################


copyBackAndShow:
	# $s3 = i
	# $s4 = j
	# $t0 = (i*N)+j
	# $t1 = board
	# $t2 = newBoard

	#prologue
	addi			$sp, $sp, -16
	sw			$fp, 0($sp)
	move			$fp, $sp
	sw			$ra, 4($sp)
	sw			$s3, 8($sp)
	sw			$s4, 12($sp)

	# function body

	# assign or reset s3: i = 0
	li			$s3, 0

# navigate across row
# while (i < N)
print_row_Loop:
	# if N <= i, exit copyBackAndShow
	ble			$s1, $s3, copyBackAndShow_epilogue

	# assign or reset s4: j = 0
	li			$s4, 0

# navigate across columns
# while (j < N)
print_col_Loop:
	# if N <= j, branch to newline
	ble			$s1, $s4, print_new_line

	# assign t1: board
	la			$t1, board
	# assign t2: newBoard
	la			$t2, newBoard

	# assign t0: (N*i)+j
	mul			$t0, $s1, $s3
	add			$t0, $t0, $s4

	# set t1 to board + (N*i)+j
	add			$t1, $t1, $t0
	# set t2 to newBoard + (N*i)+j
	add			$t2, $t2, $t0

	# assign t3: newBoard[i][j]
	lb			$t0, ($t2)
	# set board[i][j] = newBoard[i][j]
	sb			$t0, ($t1)
	lb			$t1, ($t1)

check_IJ:
	# if [i][j] = 0, branch to set_0
	beq			$t1, 0, set_0
	bne			$t1, 0, set_1

set_0:
	# set element to "."
	la			$a0, board_0
	j			print_element

set_1:
	# set element to "#"
	la			$a0, board_1
	j			print_element

print_element:
	# print the element and continue
	li			$v0, 4
	syscall
	j			incr_col

incr_col:
	# increment j and continue column loop
	addi			$s4, $s4, 1
	j			print_col_Loop

# print a new line in board
print_new_line:
	# print "\n"
	la			$a0, new_line
	li			$v0, 4
	syscall
	j			incr_row

incr_row:
	# increment i and continue row loop
	addi			$s3, $s3, 1
	j			print_row_Loop

#epilogue
copyBackAndShow_epilogue:
	
	lw			$s4, 12($sp)
	lw			$s3, 8($sp)
	lw			$ra, 4($sp)
	lw			$fp, 0($sp)
	addi			$sp, $sp, 16
	jr			$ra
