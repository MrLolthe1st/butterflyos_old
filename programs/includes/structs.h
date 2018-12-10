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


typedef struct _pralloc
{
	void * addr;
	struct _pralloc * next;
} processAlloc;

typedef struct __attribute__((packed)) _E {
	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;
	unsigned int ebp;
	unsigned int esp;
	unsigned int esi;
	unsigned int edi;
	unsigned int eflags;
	unsigned int state;
	void * startAddr;
	void * currentAddr;
	void * stack;
	unsigned int sse[4 * 8];
	unsigned int mmx[2 * 8];
	unsigned int priority;
	unsigned int priorityL;
	void * elf_process;

} Process;
