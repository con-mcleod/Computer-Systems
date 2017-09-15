# COMP1521 Lab 04 ... Simple MIPS assembler
# Modified by Callum Bennett-z5101670 and Connor McLeod-z5058240.
#
# Implements something like the C code:
#
#   int fac(int);
# 
#   int main(void) {
#      int n;
#      printf("n: ");
#      scanf("%d", &n);
#      printf("n! = %d\n", fac(n));
#      return 0;
#   }
# 
#   int fac(int k) {
#      if ((k == 0) || (k == 1)) {
#         return k;
#      }
#      int j = (k - 1);
#      int i = (k * j);
#      j--;
#      while (j >= 1) {
#         i = (i * j);
#         j--;
#      }
#      return i;
#   }


### Global data

   .data
msg1:
   .asciiz "n: "
msg2:
   .asciiz "n! = "
eol:
   .asciiz "\n"
n:
   .space 4
x:
   .space 4
y:
   .space 4         

### main() function

   .data
   .align 2
main_ret_save:
   .word 4

   .text
   .globl main

main:
   sw   $ra, main_ret_save
   la   $a0, msg1           # load contents of msg1 into $a0.
   li   $v0, 4              # invoke syscall no.4 which prints the prompt "n: ".
   syscall                  # printf("n: ");

   li   $v0, 5              # syscall no.5 scans user input, stores it in $v0.
   syscall                  # scanf("%d", &n)

   sw   $v0, n              # integer value returned from syscall no.5 stored in n. 
   la   $a0, msg2           # load contents of msg2 into $a0. 
   li   $v0, 4              # invoke syscall no.4 which prints the prompt ("n! = ");
   syscall                  # printf("n! = ").

   lw   $t0, n              # the value of n is passed into $t0.
   addi $t1, $t0, -1        # the value of (n-1) is passed into $t1.
   sw   $t1, x              # integer value in $t1 is passed into x.
   mul  $t2, $t0, $t1       # the value of the product of $t0 and $t1 is stored in $t2.
   sw   $t2, y              # integer value in $t2 is passed into y.
   lw   $a0, x              # (n-1) is passed into $a0.
   lw   $a1, y              # the product (t1 * t2) is passed into $a1.  
   jal  fac                 # fac(n)

   lw   $ra, main_ret_save
   jr   $ra                 # return

### fac() function

   .data
   .align 2
fac_ret_save:
   .space 4
z:
   .space 4   

   .text

fac:
   sw   $ra, fac_ret_save   # return address back to this function is saved.
   beq  $a0, 0, n_equals_1  # if the contents of $a0 is 0, it means n = 1 => branch to n_equals_1
   beq  $a0, -1, n_equals_0 # if the contents of $a0 is -1, it means that n = 0 => branch to n_equals_0

   beq  $a0, 1, return      # if $a0 = 1, branch to return.
   
   addi $a0, $a0, -1        # subtract 1 from $a0 and store the result in $a0.
   mul  $a1, $a1, $a0       # multiply the contents of $a1 and $a0, store in $a1.
   jal fac

n_equals_1:
   li   $a0, 1              # Integer value 1 (because n! = 1) is loaded into $a0
   li   $v0, 1              # Invoke syscall no.1 which prints the value (1) contained within $a0.
   syscall
   j    end                 # jump to end
   
n_equals_0:
   li   $a0, 0              # Integer value 0 (because n! = 0) is loaded into $a0
   li   $v0, 1              # Invoke syscall no.1 which prints the value (0) contained within $a0.
   syscall
   j    end                 # jump to end 

return:
   sw   $a1, z              # Integer value in $a1 (n!) is passed into z.
   lw   $a0, z              # load the integer contained in z into $a0.
   li   $v0, 1              # invoke syscall no.1 which prints the value of n!
   syscall
   
end:                        # end executes the print new line statement before returning to main.
   la   $a0, eol
   li   $v0, 4              # printf("\n");
   syscall
   lw   $ra, main_ret_save
   jr   $ra                 # return ($v0) 