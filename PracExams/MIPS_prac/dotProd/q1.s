# COMP1521 Practice Prac Exam #1
# (int dp, int n) dotProd(int *a1, int n1, int *a2, int n2)

	.text
	.globl dotProd

# params: a1=$a0, n1=$a1, a2=$a2, n2=$a3
dotProd:
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
	addi $sp, $sp, -4
	sw   $s6, ($sp)
	# if you need to save more $s? registers
	# add the code to save them here

# function body
# locals: a1=$s0, n1=$s1, a2=$s2, n2=$s3, i=$s4, sum=$s5, len=$s6

# (int,int) dotProd(int *a1, int n1, int *a2, int n2)
# {

	move		$s0, $a0
	move		$s1, $a1
	move		$s2, $a2
	move		$s3, $a3
#  int i, len, sum = 0;
	li 		$s4, 0
	li 		$s5, 0

#  if (n1 < n2)
	blt		$s1, $s3, if_1
#  else
#  len = n2;
	move		$s6, $s3
	j 			while_loop

if_1:
#  len = n1;
	move		$s6, $s1

while_loop:
#  while (i < len) { 
	# t0 = 4*i
	bge		$s4, $s6, end_loop
	move		$t0, $s4
	mul		$t0, $t0, 4
	# t1 = a1[4*i]
	add		$t1, $t0, $s0
	lw			$t1, ($t1)
	# t2 = a2[4*i]
	add		$t2, $t0, $s2
	lw			$t2, ($t2)
#  t3 = a1[4*i]*a2[4*i];
	mul		$t3, $t1, $t2
#	sum = sum + a1[i]*a2[i];
	add 		$s5, $s5, $t3
#  i++;
	addi		$s4, $s4, 1
	j while_loop

#  return (sum,len);
end_loop:
	move		$v0, $s5
	move		$v1, $s6


# epilogue
	# if you saved more than two $s? registers
	# add the code to restore them here
	lw   $s6, ($sp)
	addi $sp, $sp, 4
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

