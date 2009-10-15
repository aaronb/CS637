#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void 
print(int fd, uint offset)
{
  printf(1, "%d %d \n", offset, check(fd, offset));
}

void
cat(int fd)
{
  int n;

  int offset = 0;

  print(fd, offset);
  print(fd, offset);

   read(fd, buf, sizeof(buf));
   print(fd, offset);
   print(fd, offset+512);

  while((n = read(fd, buf, sizeof(buf))) > 0) {
     offset += n;
    //write(1, buf, n);
  }
  print(fd, offset);
  print(fd, 0);
  if(n < 0){
    printf(1, "cat: read error\n");
    exit();
  }
}

int
main(int argc, char *argv[])
{
  int fd, i;

  if(argc <= 1){
    cat(0);
    exit();
  }

  for(i = 1; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "cat: cannot open %s\n", argv[i]);
      exit();
    }
    cat(fd);
    close(fd);
  }
  exit();
}
