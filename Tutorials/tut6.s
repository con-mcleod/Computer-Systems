######## tutorial q3
# C logic:

if (x==0) goto ORcase;
if (100/x > 5) goto ELSEcase;
ORcase:
	if (y<x) goto IFcase;
	else goto ELSEcase;
IFcase:
	s1;
	goto endif
ELSEcase:
	s2;
endif:
#assembler
if:
	beqz $s0, ORcase
	li $t0, 100
	divu $t0, $t0, $s0
	li $t1, 5
	bgt $t0, $t1, ELSEcase
ORcase:
	bge $s1, $s0, ELSEcase
IFcase:
	#s1
	j endif
ELSEcase:
	#s2
endif:





############ Q4
#C logic

if (x==1) {
	y=5;
} else if (x==2||x==3) {
	y=x+1;
} else if (x==4) {
	y=x*x
} else if (x==5|x==6) {
	if (x==5) y=99;
	y = y+1;
} else {
	y=0;
}
#assembler
case1:
	li $t0, 1
	bne $s0, $t0, case23
	li $s1, 5
	j end
case23:
	li $t0, 2
	beq $s0, $t0, do23
	li $t0, 3
	bne $s0, $t0, case4
do23:
	addi $s1, $s0, 1
case4:
	li $t0, 4
	bne $s0, $t0, case56
	mul $s1, $s0, $s0
	j end
case56:
	li $t0, 5
	bne $s0, $t0, case6
	li $s1, 99
case6:
	li $t0, 6
	bne $s0, $t0, casedefault
	addi $s1, $s1, 1
	j end
casedefault:
	li $s1, 0
end:





######### Q5
max:
	#prologue
	addi $sp, $sp, -4
	sw $fp, ($sp)
	move $fp, $sp
	addi $sp, $sp, -4
	sw $ra, ($sp)
	#main
	lw $s0, ($a0)		#store vec in $s0
	li $s1, 1			#initialise variable i to 1

for:
	move $t0, $a1		
	bge $s1, $t0, end_for
	move $t0, $a0
	move $t1, $s1
	mul $t1, $t1, 4			#4*i
	add $t0, $t0, $t1		#base + 4*i  ---- this means move through each item in the array
											# by moving by the sizeof(int) = 4 through the array
	lw $t0, ($t0)
	ble $t0, $s0, next
	move $s0, $t0

next:
	addi $s1, $s1, 1
	j for

end_for:
	#epilogue
	lw $ra, ($sp)
	addi $sp, $sp, 4
	lw $fp, ($sp)
	addi $sp, $sp, 4
	jr $ra




####### Q6
main:
	li $s0, 2
	li $a0, 3
	li $a1, 5
	move $a2, $s0
	mul $a3, $s0, $s0
	li $t0, 99
	addi $sp, $sp, -4
	sw $t0, ($sp)
	jal prod
	addi $sp, $sp, 4
	move $s0, $v0

prod:
	#pro
	addi $sp, $sp, -4
	sw $fp, ($sp)
	move $fp, $sp
	addi $sp, $sp, -4
	sw $ra, ($sp)
	
	move $t0, $a0
	mul $t0, $t0, $a1
	mul $t0, $t0, $a2
	mul $t0, $t0, $a3
	lw $t1, 4($fp)
	mul $v0, $t0, $t1
	
	#epi
	lw $ra, ($sp)
	addi $sp, $sp, 4
	lw $fp, ($sp)
	addi $sp, $sp, 4
	jr $ra