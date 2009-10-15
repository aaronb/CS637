#include "types.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"
#include "trace.h"


struct st_item * trace;
struct st_item * next_item;

void 
st_init() {
	trace = (struct st_item *) kalloc(TRACE_SIZE);
	if (trace == 0)
		panic("trace cannot alloc");
	next_item = trace;
}


void 
st_add(struct proc * p) {
	if ((next_item - trace) >= (TRACE_SIZE / sizeof(struct st_item))) {
		cprintf("trace log full, discarding all entries\n");
		next_item = trace;
	}
	next_item->pid = p->pid;
	next_item->ticks = ticks;
	next_item++;
}


void 
st_print(){
	struct st_item * cur = trace;
/*	while (cur < next_item) {
		cprintf("%d\t%d\n", cur->pid, cur->ticks);
 		cur++;
	}*/

   int end_tick = ticks;
   int sample_size = 6000;    //length of sample in ticks

   int num_runs[100];

   //zero
   int i;
   for (i=0; i<100; i++) {
      num_runs[i] = 0;
   }

   for (cur = trace; cur < next_item; cur++) {
      if (cur->ticks < (end_tick - sample_size))
         continue;
      num_runs[cur->pid]++;      
   }

   cprintf("In the last %d ticks,\n", sample_size);      
   cprintf("pid, times ran\n");
   for (i=0; i<100; i++) {
      if (num_runs[i] > 0) {
         cprintf("%d %d\n", i, num_runs[i]);
      }
   }

}
