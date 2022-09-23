#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"

//memsize() 구현
int sys_memsize(void)
{
	uint size;
	struct proc* p = myproc();
	size = p->sz;
		
	return size;
}

