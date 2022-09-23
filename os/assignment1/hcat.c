#include "types.h"
#include "stat.h"
#include "user.h"

char c;
int num;
void
cat(int fd)
{
  int n;
  int cnt=0;
  while((n = read(fd, &c, 1)) > 0) {
    if (write(1, &c, n) != n) {
      printf(1, "cat: write error\n");
      exit();
    }
	if(c=='\n')
		cnt++;
	if(cnt==num)
		exit();
  }
  if(n < 0){
    printf(1, "cat: read error\n");
    exit();
  }
}

int main(int argc, char *argv[])
{
  int fd, i;

  if(argc <= 1){
    cat(0);
    exit();
  }
  num=atoi(argv[1]);
  for(i = 2; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "cat: cannot open %s\n", argv[i]);
      exit();
    }
    cat(fd);
    close(fd);
  }
  exit();
}
