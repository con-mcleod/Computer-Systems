//////////// Q1 /////////////

// ((x*x + y*y) - x*y) * z

// t0 = x, t1 = y, t2 = z
lw $t0, x
lw $t1, y
lw $t2, z

// t3 = x*x
mul $t3, $t0, $t0
// t4 = y*y
mul $t4, $t1, $t1
// t5 = x*y
mul $t5, $t0, $t1

// t6 = x*x + y*y
add $t6, $t3, $t4

// t7 = (x*x + y*y) - x*y
sub $t7, $t6, $t5

// t8 = ((x*x + y*y) - x*y) * z
mul $t8, $t7, $t2

// store answer in v0
sw $v0, $t8




//////////// Q2 /////////////
// while (*s != '\0' && *s == ' ') s++;

loop:
	lw $t0, ($s0)
	beq $t0, '\0', end
	bne $t0, ' ', end
	addi $s0, $s0, 1
	j loop

end:
	DIE






//////////// Q3 /////////////
// if ((x != 0 && 100/x > 5) || y < x)
//    s1;
// else
//    s2;

// becomes

// if (x==0) go to else
// if (100/x <= 5) go to else

	beq $s0, 0, orTest
	// t0 = 100/x
	div $t0, 100, $s0
	ble $t0, 5, orTest
	j if

orTest:
	ble $s0, $s1, else
	j if
else:
	// else statement
	j end
if:
	// if statement
end:


//////////// Q4 /////////////

good example of how to break down if/else statements


//////////// Q5 /////////////
// int max(int array[], int size)
// {
//    int big = array[0];
//	  int i = 1;
//    while (i < size) {
//		  if (array[i] > big) {
//			  big = array[i];
//		  }
//		  i++;
//    }
//	  return big;
// }

	la $a0, array
	lw $a1, size
	jal max

max:
	// prologue
	addi $sp, $sp, -4
	sw $fp, ($sp)
	move $fp, $sp
	addi $sp, $sp, -4
	sw $ra, ($sp)

	// s0: big = vec[0]
	lw $s0, ($a0)
	// s1: i = 1
	li $s1, 1

while:
	// t0 = size
	move $t0, $a1
	// if i >= size, break while loop
	bge $s1, $t0, epilogue
	// t0 = array
	move $t0, $a0
	// t1 = i
	move $t1, $s1
	// t1 = 4*i
	mul $t1, $t1, 4
	// t0 = array[4*i]
	addi $t0, $t0, $t1
	// t0 = value at array[4*i]
	lw $t0, ($t0)
	// if big >= $t0, next
	bge $s0, $t0, next
	// else big = array[4*i]
	move $s0, $t0

next:
	// i++
	addi $s1, $s1, 1
	j while




epilogue:
	move $v0, $s0

	lw $ra, ($sp)
	addi $sp, $sp, 4
	lw $fp, ($sp)
	addi $sp, $sp, 4
	jr $ra




// ////// Q6 ////////////////

prod:
	// prologue
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





	// epilogue
	lw $ra, ($sp)
	addi $sp, $sp, 4
	lw $fp, ($sp)
	addi $sp, $sp, 4
	jr $ra