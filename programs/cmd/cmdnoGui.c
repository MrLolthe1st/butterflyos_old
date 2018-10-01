#include "includes\stdio.h"
#pragma GCC push_options
void _main(int argc, char ** argv)
{
	clearScreen();
	kprintf("\nCommand line for ButterflyOS\nWritten by @MrLolthe1st 2018(C)\n");
	char * dir = malloc(512);
	char * cmd = malloc(512);
	char * ucmd = malloc(512);
	dir[0] = 'A';
	dir[1] = ':';
	dir[2] = '\\';
	int dirLen = 3;
	int cmdLen = 0;
	char key = 0;
	for (;;)
	{
		kprintf("\n%s>", dir);
		cmdLen = 0;
		key = 0;
		for (int i = 0; i < 512; i++)
			cmd[i] = 0;
		while (key != 10)
		{
			while ((key = getKey()) == 0) { Wait(1); };
			if (key == 10) continue;
			if (key == 0x9) continue;
			kprintf("%c", key);
			if (key == 0x8) { if (cmdLen > 0)cmd[--cmdLen] = 0; continue; }
			cmd[cmdLen] = key;
			cmdLen++;
		}
		toUpper(cmd, ucmd);
		if (ucmd[0] == 'D'&&ucmd[1] == 'I'&&ucmd[2] == 'R')
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

				kprintf("%s", &d->name);
				//void *ii = d;
				uint day = (d->modified & 0b11111);
				uint month = ((d->modified >> 5) & 0b1111);
				uint year = 1980 + ((d->modified >> 9) & 0b1111111);
				uint second = ((d->modified >> 16) & 0b11111) * 2;
				uint minute = ((d->modified >> 21) & 0b111111);
				uint hour = ((d->modified >> 27) & 0b11111);

				while (len < 29) {
					kprintf(" ");
					len++;
				}

				kprintf(" MOD. ");
				if (day < 10)
					kprintf("0");
				kprintf("%d.", day);
				if (month < 10)
					kprintf("0");
				kprintf("%d.%d ", month, year);
				if (hour < 10)
					kprintf("0");
				kprintf("%d:", hour);
				if (minute < 10)
					kprintf("0");
				kprintf("%d ", minute);
				if (d->attrs & 0x10) {

					kprintf("DIR\n");
					dircnt++;
				}
				else {
					kprintf("FILE %d KBytes\n", d->size >> 10);
					filescnt++;
				}
				tsize += d->size;
				d = d->next;
				//free(ii);
			}
			kprintf("Total %d KBytes in %d files and %d directories\n", tsize >> 10, filescnt, dircnt);
		}
		else
			if (ucmd[0] == 'C'&&ucmd[1] == 'D')
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
			else if (ucmd[0] == 'M'&&ucmd[1] == 'D')
			{
				memcpy(dir, ucmd, 512);
				concatdir(dir, (uint)cmd + 3);
				mkdir(dir, 0);
				memcpy(ucmd, dir, 512);
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
				//kprintf("%x\n",args);
			//	kprintf("\n%x args:\n",args);
				lockTaskSwitch(1);
				memcpy(dir, ucmd, 512);
				concatdir(dir, fname);
				runProcess(dir, cid, args);
				memcpy(ucmd, dir, 512);
				unlockTaskSwitch();
				for (int i = 0; i < cid; i++)
				{
					//	kprintf("!%s\n",args[i]);
						//free(args[i]);
				}
				//free(args);
				//free(fname);
			}
			Wait(1);
	}
}
void concatdir(char * dir, char * cmd)
{
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
			kprintf("\n");
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
			//kprintf("%c %x %x %d\n",(uint)*cu,(uint)((uint)lslash-(uint)dir),(uint)((uint)llslash-(uint)dir),(uint)zz);
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