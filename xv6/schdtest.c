#include "types.h"
#include "stat.h"
#include "user.h"


int
main(int argc, char *argv[])
{
	int n;

	if (argc != 3) {
		printf(1, "%s", 
"Usage: schdtest p l \n fork and loop to test scheduler \n There will be 2^p processes and each will loop 2^l times\n");
		exit();
	}

  int forks = atoi(argv[1]);
  int limit = 1 << atoi(argv[2]);
  int i;

  for (i=0; i<forks; i++)
	fork();

  for (i=0; i<limit; i++) {
	  n = i / 12345;
  }

  printf(1, "%s %d \n", "done", n);

  exit();
}
