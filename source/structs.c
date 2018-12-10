typedef struct globalVar_
{
	char * name;
	unsigned int ptr;
	struct globalVar_ *next;
}GlobalVariable;
typedef struct ELFH_ {
	unsigned int MAGIC;
} ELFHeader;

typedef struct __attribute__((packed)) _Window {
	char * caption;
	unsigned char type;
	unsigned int wwidth;
	unsigned int wheight;
	unsigned int x;
	unsigned int y;
	unsigned int lastx;
	unsigned int lasty;
	unsigned int lastUpdate;
	unsigned int id;
	short cursorX;
	short cursorY;
	unsigned char cursorState;
	void(*handler)(void * event);
	struct _Window * next;
	unsigned char * video;
	unsigned int updating;
} Window;
typedef struct WindowEvent_ {
	unsigned int code;
	void * data;
} WindowEvent;


#define DIRECTORY_FLAG 0x10
typedef struct __attribute__((packed)) _Dentry {
	unsigned char name[11];
	unsigned char attributes;
	unsigned char _some;
	unsigned char deletedChar;
	unsigned short createdTime;
	unsigned short createdDate;
	unsigned short _some2;
	unsigned short clusterHi;
	unsigned short lastEditedTime;
	unsigned short lastEditedDate;
	unsigned short clusterLo;
	unsigned int size;
}
Dentry;

typedef struct __attribute__((packed)) _D {
	Dentry entries[16];
	struct _D * next;
	unsigned char f;
}
dirEntry;

typedef struct _pralloc
{
	void * addr;
	struct _pralloc * next;
} processAlloc;
typedef struct
{
	void * entry;
	processAlloc *allocs;
} ELF_Process;
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
	Window * w;
	char * buffer;
	int head, tail, length;
	int inted;
} FILE;
typedef struct __attribute__((packed)) _E {
	unsigned int eax;//4
	unsigned int ebx;//8
	unsigned int ecx;//12
	unsigned int edx;//16
	unsigned int ebp;//20
	unsigned int esp;//24
	unsigned int esi;//28
	unsigned int edi;//32
	unsigned int eflags;//36
	unsigned int state;//40
	void * startAddr;//44
	void * currentAddr;//48
	void * stack;//52
	unsigned int sse[4 * 8];//
	unsigned int mmx[2 * 8];//244
	unsigned int priority;//248
	unsigned int priorityL;//252
	void * elf_process;//256
	char ** argv;//260
	unsigned int argc;//264
	unsigned int runnedFrom;//268
	char * workingDir;//272
	FILE * stdout;
	FILE * stdin;
	FILE * stderr;

} Process;


Process * procTable = 0;
int currentRunning = 0, procCount = 0;
char* formatString(char* str, va_list ap);