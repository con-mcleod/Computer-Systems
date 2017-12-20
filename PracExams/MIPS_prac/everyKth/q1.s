# COMP1521 Practice Prac Exam #1
# int everyKth(int *src, int n, int k, int*dest)

	.text
	.globl everyKth

# params: src=$a0, n=$a1, k=$a2, dest=$a3
everyKth:
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
	addi $sp, $sp, -4
	sw   $s2, ($sp)
	addi $sp, $sp, -4
	sw   $s3, ($sp)
	addi $sp, $sp, -4
	sw   $s4, ($sp)
	addi $sp, $sp, -4
	sw   $s5, ($sp)
	# if you need to save more $s? registers
	# add the code to save them here

# function body
# locals: s0=src, s1=n, s2=k, s3=dest, s4=i, s5=j

	move		$s0, $a0
	move		$s1, $a1
	move		$s2, $a2
	move		$s3, $a3
#  int i, j = 0;
	li			$s4, 0
	li			$s5, 0

#  while (i < n) {

while:
	bge		$s4, $s1, end_while
#	t0 = i
	move		$t0, $s4
#  t1 = j
	move		$t1, $s5
#	t2 = i%k
	rem		$t2, $t0, $s2
#  if (i%k == 0) {
	bne		$t2, 0, incr_i
#  t3 = src(4*i)
	mul		$t3, $t0, 4
	add 		$t3, $t3, $s0
	lw			$t3, ($t3)
#	t4 = dest(4*j)
	mul		$t4, $t1, 4
	add 		$t4, $t4, $s3
#  dest[j] = src[i];
	sw			$t3, ($t4)
#  j++;
	addi		$s5, $s5, 1

incr_i:
#  i++;
	addi		$s4, $s4, 1
	j 			while

end_while:
	move		$v0, $s5

# epilogue
	# if you saved more than two $s? registers
	# add the code to restore them here
	lw   $s5, ($sp)
	addi $sp, $sp, 4
	lw   $s4, ($sp)
	addi $sp, $sp, 4
	lw   $s3, ($sp)
	addi $sp, $sp, 4
	lw   $s2, ($sp)
	addi $sp, $sp, 4
	lw   $s1, ($sp)
	addi $sp, $sp, 4
	lw   $s0, ($sp)
	addi $sp, $sp, 4
	lw   $ra, ($sp)
	addi $sp, $sp, 4
	lw   $fp, ($sp)
	addi $sp, $sp, 4
	j    $ra

