


	.data

	.data
	.align 2
main_ret_save:
	.word 4

	.text
	.globl main


main:

	sw			$ra, main_ret_save

	add		$t1, $0, $0
	lui		$t1, 0x4321
	ori		$t1, $t1, 0x8765

	#li $t1, 0x43218765
	#addi $t1, 0x8765, 0x4321

	lw			$ra, main_ret_save
	jr			$ra


# answer is li $t1, 0x43218765