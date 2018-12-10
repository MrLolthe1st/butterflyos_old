#define uint unsigned int

unsigned char testForGUI();
void memcpy(unsigned char * s, unsigned char * d, unsigned int count);
void memcpy1(unsigned char * d, unsigned char * s, unsigned int count);
void memset(void * addr, char s, unsigned int count);
void clearScreen();
void unlockTaskSwitch();
void lockTaskSwitch(uint id);
int kprintf(const char* str, ...);

//Memory functions

char * malloc(unsigned int size);
void free(void * mem);

//File functions
typedef struct __attribute__((packed)) _FHandler {
	char * name;
	long long currentByte;
	long long currentByteAppend;
	unsigned int add1;
	unsigned int add2;
	unsigned int add3;
	unsigned int diskId;
	unsigned int fsType;
	unsigned int rights;
	unsigned int size;
	unsigned int type;
	void * w;
	char buffer[1024];
	int head, tail, length;
	int inted;
} FILE;
typedef struct dentr_y
{
	char name[255];
	uint modified;
	uint size;
	unsigned char attrs;
	struct dentr_y * next;
} direntry;
void Wait(unsigned int n);
unsigned char fwrite(const void *buf, uint size, uint count, FILE *stream);
unsigned char fread(void * addr, uint size, uint count, FILE *f);
void fclose(FILE * f);
void rewind(FILE * f);
long ftell(FILE * f);
uint fseek(FILE *stream, long offset, int origin);
FILE *fopen(const char *fname, const char *mode);
void mkdir(char *p, uint mode);
void runProcess(char * fileName, uint argc, char **argv, uint suspendIt, char * workingDir);
void printf(char * text, ...);
void attachIoToWindow(void * w);