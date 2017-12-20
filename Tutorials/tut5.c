// q6


long x;   // assume 8 bytes
int  y;   // assume 4 bytes


.data
x: .space 8
y: .space 4

.text

// scanf("%d", &y);

	li $v0, 5
	syscall
	sw $v0, y

// x = (y + 2000) * (y + 3000);

	lw $t0, y
	addi $t0, $t0, 2000
	lw $t1, y
	addi $t1, $t1, 3000

	mult $t0, $t1
	
	mfhi $t0
	sw $t0, x
	mflo $t0
	sw $t0, x+4