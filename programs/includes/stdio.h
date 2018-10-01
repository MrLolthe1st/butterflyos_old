#define uint unsigned int
extern char getKey();
void memcpy(unsigned char * s, unsigned char * d, unsigned int count);
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

	uint add1;
	uint add2;
	uint add3;
	uint diskId;
	uint fsType;
	uint rights;
	uint size;
} FILE;
typedef struct dentr_y
{
	char name[255];
	uint modified;
	uint size;
	unsigned char attrs;
	struct dentr_y * next;
} direntry;
unsigned char fwrite(const void *buf, uint size, uint count, FILE *stream);
unsigned char fread(void * addr, uint size, uint count, FILE *f);
void fclose(FILE * f);
void rewind(FILE * f);
long ftell(FILE * f);
uint fseek(FILE *stream, long offset, int origin);
FILE *fopen(const char *fname, const char *mode);
void mkdir(char *p, uint mode);
void runProcess(char * fileName, uint argc, char **argv);