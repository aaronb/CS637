#include "types.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  int pid;
  struct proc *np;

  if((np = copyproc(cp)) == 0)
    return -1;
  pid = np->pid;
#ifdef LOTTERY
  np->tickets = NEW_PROC_TICKETS;
#endif
  setstate(np, RUNNABLE);
  return pid;
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return cp->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  if((addr = growproc(n)) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n, ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(cp->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

 extern struct proc proc[NPROC];

int
sys_get_tickets() 
{
#ifdef LOTTERY
   int pid;
   if (argint(0, &pid) < 0)
      return -1;
   struct proc* p = get_proc(pid);
   if (p == 0) return -1;
   return p->tickets;
#else
   return -1;
#endif
}

int
sys_set_tickets()
{
#ifdef LOTTERY
   int pid, newt;
   if (argint(0, &pid) < 0 || argint(1, &newt))
      return -1;
   return set_tickets(pid, newt);
#else
   return -1;
#endif
}
