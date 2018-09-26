
#define FILE_RIGHTS_READ 1
#define FILE_RIGHTS_WRITE 2
#define FILE_RIGHTS_APPEND 4
typedef struct __attribute__((packed)) _FHandler {
	char * name;
	long long currentByte;
	long long currentByteAppend;

	uint add1;
	uint add2;
	uint add3;
	uint diskId;
	uint fsType;
	uint rights;
	uint size;
} FILE;
typedef __attribute__((packed)) struct _feil
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
		return FAT32Seek(diskId, f);
	}
}
uint FileAppendBytes(FILE * f, void * bytes, uint cnt)
{
	if (drives[f->diskId].type == 0)
	{
		return FAT32Append(f->diskId, f->add2,f->add3,bytes,cnt);
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
FILE *fopen(const char *fname, const char *mode)
{
	if (!drives[fname[0] - 'A'].avaliable)
		return 0;
	FILE * n = malloc(sizeof(FILE));
	n->name = fname;
	n->rights = 0;
	n->diskId = fname[0] - 'A';
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


	FileInfo * q = FileSeek(fname[0] - 'A', (uint)fname + 3);
	uint ut = 0;
	if (!q&&!(n->rights&2)) {
		free(n);
		return 0;
	}
	else if ((n->rights & 2) && !q) {
		FileCreate(n->diskId, (uint)fname + 3);
		q = FileSeek(fname[0] - 'A', (uint)fname + 3);
		ut = 1;
	}

	n->add1 = q->add1;
	n->add2 = q->add2;
	n->add3 = q->add3;
	n->size = q->size;
	//kprintf("File opened, size %dBytes, directory cluster=%x, dirIndex = %x\n", n->size, n->add2, n->add3);
	if (n->rights & 2&&!ut)
		FileClear(n);//Clear file if W mode used
	free(q);
	return n;
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
void rewind(FILE * f)
{
	if (!f)
		return 0;
	f->currentByte = 0;
}

void FileWrite(FILE * f, void * addr, uint cnt)
{

	if (drives[f->diskId].type == 0)
		FAT32Append(f->diskId, f->add2, f->add3, addr, cnt);

}
uchar fwrite(const void *buf, uint size, uint count, FILE *stream)
{
	kprintf("%x %x", stream->add2, stream->add3);
	FileWrite(stream, buf, size*count);
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
void fclose(FILE * f)
{
	if (!f)
		return 0;
	free(f);
}

void mkdir(char *p, uint mode)
{
	if (drives[p[0] - 'A'].type == 0)
		FAT32CreateDirectory(p[0] - 'A', (uint)p + 3);
}