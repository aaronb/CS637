#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
   int pid, tickets;
   if (argc > 1) 
   {
      pid = atoi(argv[1]);
      printf(1, "Current tickets: %d\n", get_tickets(pid));
   }

   if (argc > 2) 
   {
      tickets = atoi(argv[2]);
      int r=set_tickets(pid, tickets);
      if (r >= 0)
         printf(1, "Tickets now: %d\n", get_tickets(pid));
      else 
         printf(1, "Error %d\n", r);
   }

  exit();
}
