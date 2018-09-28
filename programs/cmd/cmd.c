#include "includes\stdio.h"

void _main(int argc, char ** argv)
{
	char * dir = malloc(512);
	char * cmd = malloc(512);
	dir[0]='A';
	dir[1]=':';
	dir[2]='\\';
	int dirLen = 3;
	int cmdLen = 0;
	for(;;)
	{
		kprintf("\n%s>", dir);
		char key = 0;
		cmdLen=0;
		for(int i=0;i<512;i++)
			cmd[i]=0;
		while(key!=10)
		{
			while((key=getKey())==0){Wait(1);};
			if(key==10) continue;
			if(key==0x9) continue;
			kprintf("%c",key);
			if(key==0x8) { cmd[cmdLen--]=0; continue;}
			cmd[cmdLen]=key;
			cmdLen++;
		}
		if(strcmp(cmd,"dir"))
		{
			direntry * d = DirectoryListing(dir);
			while(d)
			{
				kprintf("\n%s",&d->name);
				//void *ii = d;
				d=d->next;
				//free(ii);
			}
		}  else
		if(strcmp(cmd,"cd"))
		{
			kprintf("zz");
		} 
		Wait(1);
	}
}
int strcmp(char * a, char *b)
{
	while(*a&&*b)
	{
		if(*a!=*b)
			return 0;
		++a;
		++b;
	}
	return 1;
}