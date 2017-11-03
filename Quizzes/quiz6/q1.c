#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>


int main(void)
{
   pid_t id;  int stat;

   // char *x = 0;
   // *x = 'a';

   if ((id = fork()) != 0) {
      printf("A = %d\n", id);
      printf("The PID of parent is %d\n",getpid());
      wait(&stat);
      printf("stat=%d\n",stat);
      return 1;
   }
   else {
      printf("The PID of child is %d\n",getpid());
      printf("B = %d\n", getppid());
      return 0;
   }
}