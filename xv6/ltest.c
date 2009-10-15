#include "types.h"
#include "user.h"


void 
test(int t1, int t2) {
   int pid = fork();
   if (pid != 0) //parent
   {
      set_tickets(getpid(), t1);
      set_tickets(pid, t2);
   }

   int iter = 100000000;
   int i, j=0;
   for(i=0; i>-1; i++)
   {
      j = i % 1234567;
      //printf(1, "%d\n", i);
   }
   printf(1, "%d\n", j);
}

void
main(int argc, char* argv[]) 
{
   int t1 = atoi(argv[1]);
   int t2 = atoi(argv[2]);

   test(t1, t2);
   exit();
}
