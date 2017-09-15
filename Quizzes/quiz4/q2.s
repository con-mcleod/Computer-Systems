


	.data

	.data
	.align 2
main_ret_save:
	.word 4

	.text
	.globl main


main:

	sw		$ra, main_ret_save

	li		$t1, 0
	li		$t2, 1
	li		$t3, 10

	lw		$ra, main_ret_save
	jr		$ra

loop:
	bgt		$t2, $t3, end_loop
	mul		$t1, $t1, $t2
	addi	$t2, $t2, 1
	j		loop

end_loop:
	sw		$t1, result
	j		$ra




# answer is 0