#include "includes\stdio.h"
void _main(int argc, char ** argv)
{
	lockTaskSwitch(1);
	kprintf("%x %x Program runned!\n",argc, argv);
	
	for(int i=0;i<argc;i++)
	{
		kprintf("%s\n",argv[i]);
	}
	unlockTaskSwitch();
	//for(;;);
}