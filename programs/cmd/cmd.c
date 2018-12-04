#include "..\includes\executable.c"
#include "..\includes\stdio.h"
#include "..\includes\structs.h"
#include "..\includes\forms.h"
#include "..\includes\windowsEventsCodes.h"


Window * w;
char kkey = 0;
void handle(WindowEvent * z)
{
	if(z->code==WINDOWS_KEY_DOWN)
	{
		kkey = *((char*)z->data);
	}
}
char RecieveKey()
{
	if(kkey){
		char z=kkey;
		kkey=0;
		return z;
	}
}
int min(int a, int b)
{
	return a<b?a:b;
}
void _main(int argc, char ** argv)
{	
	w=openWindow(720,480,0,&handle,"Command Shell");
	attachIoToWindow(w);
	printf("\nCommand line for ButterflyOS\nWritten by @MrLolthe1st 2018(C)\n");
	char * dir = malloc(512);
	char * cmd = malloc(512);
	char * ucmd = malloc(512);
	printf("11");
	dir[0] = 'A';
	dir[1] = ':';
	dir[2] = '\\';
	int dirLen = 3;
	int cmdLen = 0;
	char key = 0;
	for (;;)
	{
		printf("\n%s>", dir);
		cmdLen = 0;
		key = 0;
		for (int i = 0; i < 512; i++)
			cmd[i] = 0;
		while (key != 10)
		{
			while ((key = RecieveKey()) == 0) { Wait(1); };
			if (key == 10) continue;
			if (key == 0x9) continue;
			if ((key==0x8&&cmdLen > 0)||key!=0x8)
				printf("%c", key);
			if (key == 0x8) { if (cmdLen > 0)cmd[--cmdLen] = 0; continue; }
			cmd[cmdLen] = key;
			cmdLen++;
		}
		printf("\n");
		for(int i=0;i<512;i++)
			ucmd[i]=0;
		toUpper(cmd, ucmd);
		if (ucmd[0] == 'D'&&ucmd[1] == 'I'&&ucmd[2] == 'R'&&ucmd[3]==0)
		{
			///////Wait(10000);
			direntry * d = DirectoryListing(dir);
			uint dircnt = 0, filescnt = 0, tsize = 0;
			while (d)
			{
				uint len = 0;
				char * op = &d->name;
				while (*op)
				{
					if (len == 26)
					{
						d->name[len] = '.';
						d->name[len + 1] = '.';
						d->name[len + 2] = '.';
						d->name[len + 3] = 0;
						len = 29;
						break;
					}
					len++;
					++op;
				}

				printf("%s", &d->name);
				void *ii = d;
				uint day = (d->modified & 0b11111);
				uint month = ((d->modified >> 5) & 0b1111);
				uint year = 1980 + ((d->modified >> 9) & 0b1111111);
				uint second = ((d->modified >> 16) & 0b11111) * 2;
				uint minute = ((d->modified >> 21) & 0b111111);
				uint hour = ((d->modified >> 27) & 0b11111);

				while (len < 29) {
					printf(" ");
					len++;
				}

				printf(w," MOD. ");
				if (day < 10)
					printf("0");
				printf("%d.", day);
				if (month < 10)
					printf("0");
				printf("%d.%d ", month, year);
				if (hour < 10)
					printf("0");
				printf("%d:", hour);
				if (minute < 10)
					printf("0");
				printf("%d ", minute);
				if (d->attrs & 0x10) {

					printf("DIR\n");
					dircnt++;
				}
				else {
					printf("FILE %d KBytes\n", d->size >> 10);
					filescnt++;
				}
				tsize += d->size;
				d = d->next;
				free(ii);
			}
			printf("Total %d KBytes in %d files and %d directories\n", tsize >> 10, filescnt, dircnt);
		}
		else
			if (ucmd[0] == 'C'&&ucmd[1] == 'D' &&ucmd[2]==' ')
			{
				
				concatdir(dir, (uint)cmd + 3);
				char * u = dir;
				while (*((char*)((uint)u + 1)))
				{
					++u;
				}
				if (*u != '\\')
				{
					++u;
					*u = '\\';
				}
			}
			else
			if (ucmd[0] == 'C'&&ucmd[1] == 'A' &&ucmd[2]=='T'&&ucmd[3]==' ')
			{
				char * fname = malloc(256);
				char * z = (uint)cmd+4;
				char *ff = fname;
				while (*z&&*z != ' ')
				{
					*ff = *z;
					++ff;
					++z;

				}
				
				memcpy(ucmd,dir , 512);
				concatdir(dir, fname);
				FILE * f = fopen(dir,"r");
				memcpy(dir, ucmd, 512);
				if(!f)
				{
					printf("File %s isn't exists\n",fname);
					continue;
				}
				fseek(f, 0, 2);
				int size=ftell(f);
				rewind(f);
				char * buf = malloc(4096);
				int cb=0;
				while(cb!=size)
				{
					fread(buf,min(size, cb + 4096)-cb,1,f);
					printf("%s",buf);
					cb=min(size, cb + 4096);
					//break;
				}
				fclose(f);
				free(buf);
			}
			else if (ucmd[0] == 'M'&&ucmd[1] == 'D'&&ucmd[2]==' ')
			{
				memcpy(ucmd, dir, 512);
				concatdir(dir, (uint)cmd + 3);
				mkdir(dir, 0);
				memcpy(dir, ucmd, 512);
			}
			else {
				char * fname = malloc(256);
				char * z = cmd;
				char *ff = fname;
				while (*z&&*z != ' ')
				{
					*ff = *z;
					++ff;
					++z;

				}
				
				uint cid = 0;
				char ** args;
				char * fs = z;
				while (*z)
				{
					if (*z == ' ')
						cid++;
					++z;
				}

				args = malloc(sizeof(*args)*cid);
				z = fs;
				int id = -1, zi = 0;
				while (*z)
				{
					if (*z == ' ')
					{
						id++;
						args[id] = malloc(256);
						zi = 0;
					}
					else
					{
						args[id][zi] = *z;
						zi++;
					}
					++z;
				}
				memcpy(ucmd,dir , 512);
				concatdir(dir, fname);
				FILE * fp = fopen(dir,"r");
				if(!fp)
				{
					printf("%s isn't a command or executable file!\n",fname);
					memcpy(dir, ucmd, 512);
					continue;
				}
				runProcess(dir, cid, args, 0, ucmd);
				memcpy(dir, ucmd, 512);
			}
			Wait(1);
	}
}
void concatdir(char * dir, char * cmd)
{
	if(cmd[0]=='\\'){
		for(int i = 3;i<512;i++)
			dir[i]=0;
		++cmd;
	}
	char * cu = (uint)cmd;
	uint chdisk = 0;
	while (*cu)
	{
		if (*cu == ':')
		{
			chdisk = 1;
			--cu;
			dir[0] = *cu;
			cu++;
			dir[3] = 0;
		}
		++cu;
	}
	if (!chdisk) {
		--cu;

		cu = (uint)cmd;
		char * z = dir;
		while (*z)
			++z;
		char * ls = z;
		while (*cu)
		{
			*z = *cu;
			++z;
			++cu;
		}
		char * lslash = (uint)dir + 2, *llslash = (uint)dir + 2;
		cu = dir;
		uint zz = -1;
		while (*cu)
		{
			//printTextToWindow(2,w,"%c %x %x %d\n",(uint)*cu,(uint)((uint)lslash-(uint)dir),(uint)((uint)llslash-(uint)dir),(uint)zz);
			if (*cu == '.'&&cu[1] == '.')
			{
				z = (uint)llslash + 1;
				++cu;
				++cu;
				++cu;
				while (*z)
				{
					if (*cu == 0)
						*z = 0;
					else
						*z = *cu;
					++z;
					if (*cu)
						++cu;
				}
				cu = dir; lslash = (uint)dir + 2;
				llslash = (uint)dir + 2;
				zz = -1;
			}
			if (*cu == '\\') {
				zz++;
				if (zz > 0) {
					llslash = lslash;
					lslash = cu;

				}
			}
			++cu;
		}

	}

}

void toUpper(char * a, char *b)
{
	while (*a)
	{
		if (*a >= 'a'&&*a <= 'z')
			*b = *a + ('A' - 'a');
		else
			*b = *a;
		++a;
		++b;
	}
}
int strcmp(char * a, char *b)
{
	if (*a != *b)
		return 0;
	while (*a&&*b)
	{
		if (*a != *b)
			return 0;
		++a;
		++b;
	}
	if (*a != *b)
		return 0;
	return 1;
}
