# COMP1521 Practice Prac Exam #1
# int rmOdd(int *src, int n, int*dest)

	.text
	.globl rmOdd

# params: src=$a0, n=$a1, dest=$a2
rmOdd:
# prologue
	addi $sp, $sp, -4
	sw   $fp, ($sp)
	la   $fp, ($sp)
	addi $sp, $sp, -4
	sw   $ra, ($sp)
	addi $sp, $sp, -4
	sw   $s0, ($sp)
	addi $sp, $sp, -4
	sw   $s1, ($sp)
	# if you need to save more $s? registers
	# add the code to save them here

# function body
# locals: src=s1, n=s2, dest=s3, i=s4, j=s5

	# load params into s registers
	move 	$s1, $a0
	move	$s2, $a1
	move 	$s3, $a2
	# int i, j = 0;
	li    $s4, 0
	li    $s5, 0

while:
	# break if i >= n
	bge   $s4, $s2, end_while
	# t0 = i
	move	$t0, $s4
	# t0 = 4*i
	mul	$t0, $t0, 4
	# t0 = src + 4*i
	add 	$t0, $t0, $s1
	# t0 = src[4*i]
	lw 	$t0, ($t0)

	# t1 = src[4*i] % 2
	rem	$t1, $t0, 2
	# jump to next loop if not 0
	bne	$t1, 0, next_loop

	# t2 = j
	move 	$t2, $s5
	# t2 = 4*j
	mul	$t2, $t2, 4
	# t2 = src + 4*j
	add 	$t2, $t2, $s3
	# src[4*j] = src[4*i]
	sw		$t0, ($t2)

	# j++
	addi	$s5, $s5, 1

next_loop:
	# i++
	addi	$s4, $s4, 1
	j		while

end_while:
	# store j in return value
	move	$v0, $s5

# epilogue
	# if you saved more than two $s? registers
	# add the code to restore them here
	lw   $s1, ($sp)
	addi $sp, $sp, 4
	lw   $s0, ($sp)
	addi $sp, $sp, 4
	lw   $ra, ($sp)
	addi $sp, $sp, 4
	lw   $fp, ($sp)
	addi $sp, $sp, 4
	j    $ra

