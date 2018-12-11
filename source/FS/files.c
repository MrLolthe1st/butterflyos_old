
#define FILE_RIGHTS_READ 1
#define FILE_RIGHTS_WRITE 2
#define FILE_RIGHTS_APPEND 4

typedef  struct __attribute__((packed)) _feil
{
	uint add1;
	uint add2;
	uint add3;
	uint size;
} FileInfo;
FileInfo * FileSeek(uint diskId, char * f)
{
	//kprintf("[%x %s]", diskId, f);
	if (drives[diskId].type == 0)
	{
		return (FileInfo*)FAT32Seek(diskId, f);
	}
}
int putc(int ch, FILE * f)
{
	if (!f->inted)
	{
		f->head = 0;
		f->tail = -1;
		f->length = 0;
		f->inted = 1;
	}
	if (f->length < 1024) {
		//f->tail = (f->tail + 1) % f->bufSize;
	}
	else return -1;

}
uint FileAppendBytes(FILE * f, void * bytes, uint cnt)
{
	if (drives[f->diskId].type == 0)
	{
		return FAT32Append(f->diskId, f->add2, f->add3, bytes, cnt);
	}
}
uint FileClear(FILE * f)
{
	if (drives[f->diskId].type == 0)
	{
		return FAT32ClearChain(f->diskId, f->add2, f->add3);
	}
}
void FileCreate(uint diskId, void * f)
{
	if (drives[diskId].type == 0)
		FAT32CreateFile(diskId, f);
}
void concatdir(char * dir, const char * cmd)
{
	if (cmd[0] == '\\') {
		for (int i = 3; i < 512; i++)
			dir[i] = 0;
		++cmd;
	}
	const char * cu = cmd;
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

		cu = cmd;
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
		const char * lslash = (char*)((uint)dir + 2), *llslash = (char*)((uint)dir + 2);
		cu = dir;
		uint zz = -1;
		while (*cu)
		{
			//printTextToWindow(2,w,"%c %x %x %d\n",(uint)*cu,(uint)((uint)lslash-(uint)dir),(uint)((uint)llslash-(uint)dir),(uint)zz);
			if (*cu == '.'&&cu[1] == '.')
			{
				z = (char*)((uint)llslash + 1);
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
				cu = dir; lslash = (char*)((uint)dir + 2);
				llslash = (char*)((uint)dir + 2);
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
FILE *fopen(const char *fname, const char *mode)
{

	char * ups = malloc(512);

	if (fname[1] != ':')
	{
		//Working dir

		char * wdir = procTable[currentRunning].workingDir;
		char * z = wdir;
		char * p = ups;
		while (*z)
		{
			*p = *z;
			++z;
			++p;
		}

		concatdir(ups, fname);
		//
	}
	else {
		char * p = ups;
		const char * z = fname;
		while (*z)
		{
			*p = *z;
			++p;
			++z;
		}
	}
	if (!drives[ups[0] - 'A'].avaliable)
		return 0;
	FILE * n = (FILE*)malloc(sizeof(FILE));
	n->name = ups;
	n->rights = 0;
	n->type = 0;
	n->diskId = ups[0] - 'A';
	if (mode[0] == 'r')
		n->rights |= 1;
	else
		if (mode[0] == 'w')
			n->rights |= 2;
		else
			n->rights |= 4;
	if (mode[1] == 'b')
		n->rights |= 8;
	if (mode[2] == 'b')
		n->rights |= 8;

	n->currentByte = 0;


	printTextToWindow(7, mywin, "~Path: %s && %x\n", ups, 0);
	FileInfo * q = FileSeek(ups[0] - 'A', (char*)((uint)ups + 3));
	uint ut = 0;

	printTextToWindow(7, mywin, "Path: %s && %x\n", ups, q);
	if (!q && !(n->rights & 2)) {
		free(n);

		return 0;
	}
	else if ((n->rights & 2) && !q) {
		FileCreate(n->diskId, (char*)((uint)ups + 3));
		printTextToWindow(7, mywin, "!Path: %s && %x\n", ups, q);
		q = FileSeek(ups[0] - 'A', (char*)((uint)ups + 3));
		ut = 1;
	}

	n->add1 = q->add1;
	n->add2 = q->add2;
	n->add3 = q->add3;
	n->size = q->size;
	printTextToWindow(7, mywin, "File opened, size %dBytes, directory cluster=%x, dirIndex = %x\n", n->size, n->add2, n->add3);
	if (n->rights & 2 && !ut)
		FileClear(n);//Clear file if W mode used
	free(q);
	return n;
}
direntry * DirectoryListing(char *fname)
{
	char * ups = malloc(512);

	if (fname[1] != ':')
	{
		//Working dir

		char * wdir = procTable[currentRunning].workingDir;
		char * z = wdir;
		char * p = ups;
		while (*z)
		{
			*p = *z;
			++z;
			++p;
		}

		concatdir(ups, fname);
		//
	}
	else {
		char * p = ups;
		char * z = fname;
		while (*z)
		{
			*p = *z;
			++p;
			++z;
		}
	}
	if (drives[fname[0] - 'A'].type == 0)
		return FAT32GetDir(fname[0] - 'A', (char*)((uint)fname + 3));
}

void attachIoToWindow(Window * w)
{
	procTable[currentRunning].stdin->w = w;
	procTable[currentRunning].stdout->w = w;
	procTable[currentRunning].stderr->w = w;
}

void printf(char * text, ...)
{
	FILE * out = procTable[currentRunning].stdout;
	char buf[1024];
	va_list args;

	va_start(args, text);
	vsnprintf(buf, sizeof(buf), text, args);
	va_end(args);

	if (out->w)
		printTextToWindowFormatted(7, out->w, buf);
}
#define stdin_stream 0
#define stdout_stream 1
#define stderr_stream 2
FILE *  getProcessSTDStream(int id)
{
	if (id == stdin_stream)
		return procTable[currentRunning].stdin;
	if (id == stdout_stream)
		return procTable[currentRunning].stdout;
	if (id == stderr_stream)
		return procTable[currentRunning].stderr;
	return 0;
}
uint fseek(FILE *stream, long offset, int origin) {
	long long z = stream->currentByte;
	if (origin == 0)
		stream->currentByte = 0 + offset;
	else if (origin == 1)
		stream->currentByte += offset;
	else if (origin == 2)
		stream->currentByte = stream->size + offset;
	if (stream->currentByte < 0 || stream->currentByte > stream->size) {
		stream->currentByte = z;
		return 1;
	}
	return 0;
}
long ftell(FILE * f)
{
	if (!f)
		return -1;
	return f->currentByte;
}
int rewind(FILE * f)
{
	if (!f)
		return 0;
	f->currentByte = 0;
	return 1;
}

void FileWrite(FILE * f, void * addr, uint cnt)
{

	if (drives[f->diskId].type == 0)
		FAT32Append(f->diskId, f->add2, f->add3, addr, cnt);

}
uchar fwrite(void *buf, uint size, uint count, FILE *stream)
{
	//kprintf("%x %x!", stream->add2, stream->add3);

	FileWrite(stream, buf, size*count);
	//stream->currentByte += size * count;
}
uchar fgetc(FILE * f)
{

}
void FileRead(FILE * f, void * addr, uint from, uint cnt)
{

	if (drives[f->diskId].type == 0)
		FAT32ReadFileB(f->diskId, f->add1, from, cnt, addr);


}
uchar fread(void * addr, uint size, uint count, FILE *f)
{
	if (!f)
		return 0;
	FileRead(f, addr, f->currentByte, size*count);
	f->currentByte += size * count;
}
int fclose(FILE * f)
{
	if (!f)
		return 0;
	free(f);
	return 1;
}

void mkdir(char *p, uint mode)
{
	if (drives[p[0] - 'A'].type == 0)
		FAT32CreateDirectory(p[0] - 'A', (char*)((uint)p + 3));
}