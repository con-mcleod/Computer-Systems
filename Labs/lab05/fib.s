# MIPS assembler to compute Fibonacci numbers
# Connor McLeod z5058240

	.data
msg1:
	.asciiz "n = "
msg2:
	.asciiz "fib(n) = "
errorMsg:
	.asciiz "n must be > 0\n"

	.text

# int main(void)
# {
#    int n;
#    printf("n = ");
#    scanf("%d", &n);
#    if (n < 1)
#       printf("n must be > 0\n");
#		exit(1);
#    else {
#		printf("fib(n) = %d\n", fib(n));  
#    }
#    return 0;
# }

	.globl main

main:
	# prologue
	addi $sp, $sp, -4		# create space in stack
	sw   $fp, ($sp)			# store fp in stack memory
	move $fp, $sp 			# ???
	addi $sp, $sp, -4		# create space in stack
	sw   $ra, ($sp)			# Store the memory address of SP in $ra

	# function body
	la   $a0, msg1			# load contents of msg1 into $a0
	li   $v0, 4				# invoke syscall no.4 which prints a string
	syscall					# printf("n = ");

	li   $v0, 5				# invoke syscall no.5 which reads in an int
	syscall					# scanf("%d", &n);
	move $a0, $v0			# store v0 in a0 [a0 = n]

	blt $a0, 1, error 		# if n < 1, branch to error message

	jal  fib				# jump to fib
	nop						# do nothing so that main waits for fib to complete
	


	move $s0, $v0			# s0 = fib(n);

	la   $a0, msg2			# load contents of msg2 into $a0
	li   $v0, 4				# invoke syscall no.4 which prints a string
	syscall					# printf((fib(n) = ");

	move $a0, $s0			# store s0 in a0
	li   $v0, 1				# invoke syscall no.1 which prints an integer
	syscall					# printf("%d", $s0);

	li   $a0, '\n'			# load '\n' into $a0
	li   $v0, 11			# invoke syscall no.11 which ???
	syscall					# printf("\n");

	# epilogue
	lw   $ra, ($sp)			# Store the memory address of SP in $ra
	addi $sp, $sp, 4		# Add '4' to the stack pointer
	lw   $fp, ($sp)			# Store the memory address of SP in FP
	addi $sp, $sp, 4		# Add '4' to the stack pointer
	jr   $ra				# Jump to register $ra


# int fib(int n)
# {
#    if (n < 1)
#       return 0;
#    else if (n == 1)
#       return 1;
#    else
#       return fib(n-1) + fib(n-2);
# }

fib:
	# prologue
	addi $sp, $sp, -4		# create space in stack
	sw   $fp, ($sp)			# store fp in stack memory
	move $fp, $sp 			# ???
	addi $sp, $sp, -4		# create space in stack
	sw   $ra, ($sp)			# store ra in stack memory
	addi $sp, $sp, -4		# create space in stack
	sw   $s0, ($sp)			# store s0 in stack memory
	addi $sp, $sp, -4		# create space in stack
	sw   $s1, ($sp) 		# store s1 in stack memory


	# function body
	add $s0, $a0, $0		# s0 = a0 [store curr val of n in s0]

	blt $s0, 1, ret_zero	# branch if n = 0
	beq $s0, 1, ret_one		# branch if n = 1

	addi $a0, $s0, -1		# n - 1
	jal fib 				# call fib(n-1)

	add $s1, $0, $v0		# s1 = fib(n-1)

	addi $a0, $s0, -2		# n - 2
	jal fib 				# call fib(n-2)

	add $v0, $v0, $s1		# v0 = fib(n-2) + fib(n-1)

#epilogue
fib_epi:
	lw   $s1, ($sp)			# return value of s1 from stack
	addi $sp, $sp, 4		# move stack to next word
	lw   $s0, ($sp)			# return value of s0 from stack
	addi $sp, $sp, 4		# move stack to next word
	lw   $ra, ($sp)			# Store ra in stack memory
	addi $sp, $sp, 4		# move stack to next word
	lw   $fp, ($sp)			# store fp in stack memory
	addi $sp, $sp, 4		# move stack to next word
	jr   $ra 				# Jump to register $ra


error:
	la $a0, errorMsg		# load error message into a0
	li $v0, 4				# Syscall to print error message
	syscall
	li $v0, 10				# Syscall for program exit
	syscall

ret_zero:
	li $v0, 0				# load zero into $v0
	j fib_epi				# jump to fib epilogue
ret_one:
	li $v0, 1				# load 1 into $v0
	j fib_epi				# jump to fib epilogue