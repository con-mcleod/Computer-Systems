# COMP1521 Practice Prac Exam #1
# int lowerfy(char *src, char *dest)

   .text
   .globl lowerfy

# params: src=$a0, dest=$a1
lowerfy:
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
   # if you need to save more $s? registers
   # add the code to save them here

# function body
# locals: s0=src, s1=dest, s2=i, s3=n, s4=ch
   move     $s0,$a0
   move     $s1,$a1
#  s2=i
   li       $s2, 0
#  s3=n
   li       $s3, 0

while:
#  t0 = src+(i)
   move     $t0, $s2
   add      $t0, $t0, $s0
#  t0 = ch = src[i]
   lb       $t0, ($t0)
#  while (src[i] != '\0') {
   beq      $t0, $0, end_while
#  if (ch >= 'A' && ch <= 'Z') {
   blt      $t0, 'A', not_if
   bgt      $t0, 'Z', not_if
#  ch = ch -'A' + 'a';
   sub      $t0, $t0, 'A'
   add      $t0, $t0, 'a'
#  n++
   addi     $s3, $s3, 1

not_if:
#  dest[i] = ch;
   move     $t1, $s2
   add      $t1, $t1, $s1
   sb       $t0, ($t1)
#  i++;
   addi     $s2, $s2, 1
   j        while

end_while:
#  dest[i] = '\0';
   move     $t0, $s2
   add      $t0, $t0, $s1
   sb       $0, ($t0)
#  return n;
   move     $v0, $s3

# epilogue
   # if you saved more than two $s? registers
   # add the code to restore them here
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

