
#define FILE_RIGHTS_READ 1
#define FILE_RIGHTS_WRITE 2
#define FILE_RIGHTS_APPEND 4
typedef struct __attribute__((packed)) _FHandler {
	char * name;
	ulon currentByte;
	uint add1;
	uint add2;
	uint fsType;
	uint rights;
	uint size;
} FILE;
typedef __attribute__((packed)) struct _feil
{
	uint add1;
	uint size;
	uint add2;
} FileInfo;
FileInfo * FileSeek(uint diskId, char * f)
{
	//kprintf("[%x %s]", diskId, f);
	if (drives[diskId].type == 0)
	{
		return FAT32Seek(diskId, f);
	}
}
FILE *fopen(const char *fname, const char *mode)
{
	if (!drives[fname[0] - 'A'].avaliable)
		return 0;
	FILE * n = malloc(sizeof(FILE));
	n->name = fname;
	n->rights = 0;
	if (mode[0] == 'r')
		n->rights |= 1;
	else
		if (mode[0] == 'w')
			n->rights |= 2;
		else
			n->rights |= 4;
	if (mode[1] == 'b')
		n->rights |= 8;
	else if (mode[1] == '+')
		n->rights |= 3;
	if (mode[2] == 'b')
		n->rights |= 8;
	n->currentByte = 0;
	FileInfo * q = FileSeek(fname[0] - 'A', (uint)fname + 3);
	if (!q) {
		free(n);
		return 0;
	}
	n->add1 = q->add1;
	n->add2 = q->add2;
	n->size = q->size;
	free(q);
	return n;
}
uint ftell(FILE * f)
{
	if (!f)
		return 0;
	return f->currentByte;
}
void rewind(FILE * f)
{
	if (!f)
		return 0;
	f->currentByte = 0;
}
void FileRead(FILE * f, void * addr, uint from, uint cnt)
{
	if (drives[f->name[0] - 'A'].type == 0)
		FAT32ReadFileB(f->name[0] - 'A', f->add1, from, cnt, addr);

}
uint fread(void * addr, uint size, uint count, FILE *f)
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