#include "includes\stdio.h"

void _main(int argc, char ** argv)
{
//	clearScreen();
	kprintf("\nCommand line for ButterflyOS\nWritten by @MrLolthe1st 2018(C)\n");
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
			kprintf("\nDirectory listing for %s\n",dir);
			///////Wait(10000);
			direntry * d = DirectoryListing(dir);
			uint dircnt=0,filescnt=0,tsize=0;
			while(d)
			{
				uint len=0;
				char * op=&d->name;
				while(*op)
				{
					if(len==26)
					{
						d->name[len]='.';
						d->name[len+1]='.';
						d->name[len+2]='.';
						d->name[len+3]=0;
						len=29;
						break;
					}
					len++;
					++op;
				}
				
				kprintf("%s",&d->name);
				void *ii = d;
				uint day = (d->modified&0b11111);
				uint month = ((d->modified>>5)&0b1111);
				uint year = 1980+((d->modified>>9)&0b1111111);
				uint second = ((d->modified>>16)&0b11111)*2;
				uint minute = ((d->modified>>21)&0b111111);
				uint hour = ((d->modified>>27)&0b11111);
				
				while(len<29){
						kprintf(" ");
						len++;
					}
					
					kprintf(" MOD. ");
					if(day<10)
						kprintf("0");
					kprintf("%d.",day);
					if(month<10)
						kprintf("0");
					kprintf("%d.%d ",month,year);
					if(hour<10)
						kprintf("0");
					kprintf("%d:",hour);
					if(minute<10)
						kprintf("0");
					kprintf("%d ",minute);
				if(d->attrs&0x10){
					
					kprintf("DIR\n");
					dircnt++;
				}
				else{
					kprintf("FILE %d KBytes\n",d->size>>10);
					filescnt++;
				}
				tsize+=d->size;
				d=d->next;
				free(ii);
			}
			kprintf("Total %d KBytes in %d files and %d directories\n",tsize>>10,filescnt,dircnt);
		}  else
		if(strcmp(cmd,"cd"))
		{
			
			char * cu=(uint)cmd + 3;
			uint chdisk=0;
			while(*cu)
			{
				if(*cu==':')
				{
					chdisk=1;
					--cu;
					dir[0]=*cu;
					cu++;
					dir[3]=0; 
					kprintf("\n");
				}
				++cu;
			}
			if(!chdisk){
				--cu;
				if(*cu!='\\')
				{
					++cu;
					*cu='\\';
					++cu;
					*cu=0;
				}
				cu=(uint)cmd + 3;
				char * z=dir;
				while(*z)
					++z;
				char * ls=z;
				while(*cu)
				{
					*z=*cu;
					++z;
					++cu;
				}
				char * lslash=(uint)dir+2,*llslash=(uint)dir+2;
				cu=dir;
				uint zz=-1;
				while(*cu)
				{
					//kprintf("%c %x %x %d\n",(uint)*cu,(uint)((uint)lslash-(uint)dir),(uint)((uint)llslash-(uint)dir),(uint)zz);
					if(*cu=='.'&&cu[1]=='.')
					{
						z=(uint)llslash+1;
						++cu;
						++cu;
						++cu;
						while(*z)
						{
							if(*cu==0)
								*z=0;
							else
								*z=*cu;
							++z;
							if(*cu)
							++cu;
						}
						cu=dir;lslash=(uint)dir+2;
						llslash=(uint)dir+2;
						zz=-1;
					}
					if(*cu=='\\'){
						zz++;
						if(zz>0){
							llslash=lslash;
							lslash=cu;
							
						}
					}
					++cu;
				}
				
				kprintf("\n");
			}
		} 
		Wait(1);
	}
}
int strcmp(char * a, char *b)
{
	if(*a!=*b)
			return 0;
	while(*a&&*b)
	{
		if(*a!=*b)
			return 0;
		++a;
		++b;
	}
	return 1;
}