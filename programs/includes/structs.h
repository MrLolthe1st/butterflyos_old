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
	unsigned char * videoOk;
	unsigned int updating;
	unsigned int buffered;
} Window;
void enableBuffering(Window * w);
void BufferWindow(Window * w);
typedef struct WindowEvent_ {
	unsigned int code;
	void * data;
} WindowEvent;

extern int currentRunning;
typedef struct _pralloc
{
	void * addr;
	struct _pralloc * next;
} processAlloc;


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
	char			fpureg[108];

} Process;
extern Process * procTable;