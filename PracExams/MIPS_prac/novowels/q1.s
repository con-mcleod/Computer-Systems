# COMP1521 Practice Prac Exam #1
# int novowels(char *src, char *dest)

   .text
   .globl novowels

# params: src=$a0, dest=$a1
novowels:
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
# locals: s0=src, s1=dest, s2=i, s3=j, s4=n, s5=ch

   move  $s0, $a0
   move  $s1, $a1
# int i, j = 0, n = 0;  char ch;
   li    $s2, 0
   li    $s3, 0
   li    $s4, 0

while:
   move  $t0, $s2
   add   $t0, $t0, $s0
   lb    $s5, ($t0)
   beq   $t0, $0, end_while

   move  $a0, $s5
   jal   isvowel
   beq   $v0, 0, not_if
   addi  $s4, $s4, 1
   j next_loop

# while (src[i] != '\0') {
#    ch = src[i];
#    if (isvowel(ch))
#       n++;
#    else {
#       dest[j] = ch;
#       j++;
#    }
#    i++
# }
# dest[j] = '\0';
# return n;

not_if:
   move  $t1, $s3
   add   $t1, $t1, $s1
   sb    $s5, ($t1)
   addi  $s3, $s3, 1

next_loop:
   addi  $s2, $s2, 1
   j     while

end_while:
   move  $t2, $s3
   add   $t2, $t2, $s1
   sb    $0, ($t2)




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

#####

# auxiliary function
# int isvowel(char ch)
isvowel:
# prologue
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   la   $fp, ($sp)
   addi $sp, $sp, -4
   sw   $ra, ($sp)

# function body
   li   $t0, 'a'
   beq  $a0, $t0, match
   li   $t0, 'A'
   beq  $a0, $t0, match
   li   $t0, 'e'
   beq  $a0, $t0, match
   li   $t0, 'E'
   beq  $a0, $t0, match
   li   $t0, 'i'
   beq  $a0, $t0, match
   li   $t0, 'I'
   beq  $a0, $t0, match
   li   $t0, 'o'
   beq  $a0, $t0, match
   li   $t0, 'O'
   beq  $a0, $t0, match
   li   $t0, 'u'
   beq  $a0, $t0, match
   li   $t0, 'U'
   beq  $a0, $t0, match

   li   $v0, 0
   j    end_isvowel
match:
   li   $v0, 1
end_isvowel:

# epilogue
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   j    $ra
