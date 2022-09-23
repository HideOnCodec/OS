#include "param.h"
#include "types.h"
#include "user.h"
#include "stat.h"

int main(int argc, char *argv[])
{
	char *buf[100];
	if(argc<2){
		printf(1,"Wrong input\n");
		exit();
	}
	
	if(trace(atoi(argv[1]))<0){
		printf(1,"trace failed\n");
		exit();
	}
	for(int i=0; i<argc-2; i++)
		buf[i]=argv[i+2];
	
	exec(buf[0],buf);
	exit();
}
