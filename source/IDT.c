/*
* Author: Novozhilov Alexandr @mrlolthe1st
*/
//Не трогать до следующего коммента, где это будет разрешено!

#pragma GCC push_options
#pragma GCC optimize ("Ofast")
char codes[] = { 0,0,'1','2','3','4','5','6','7','8','9','0','-','=',8,'\t','q','w','e','r','t','y','u','i','o','p','[',']',13,0,'a','s','d','f','g','h','j','k','l',';','\'','`',0,'\\','z','x','c','v','b','n','m',',','.','/',0,'*',0,' ',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'-',0,0,0,'+',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
char codes_sh[] = { 0,0,'!','@','#','$','%','^','&','*','(',')','_','+',8,'\t','Q','W','E','R','T','Y','U','I','O','P','{','}',13,0,'A','S','D','F','G','H','J','K','L',':','"','~',0,'|','Z','X','C','V','B','N','M','<','>','?',0,'*',0,' ',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'-',0,0,0,'+',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
//0x90 - nop
#define IDT_HANDLER(func) unsigned char func = 0x90;\
__asm__(#func ": \npusha \n call __"# func " \n  popa  \n iret \n");\
void _## func()

char vk_keys[] =
{
	0x01,//VK_LBUTTON
	0x02,//VK_RBUTTON
	0x03,//VK_CANCEL
	0x04,//VK_MBUTTON
	0x05,//VK_XBUTTON1
	0x06,//VK_XBUTTON2
	0x08,//VK_BACK
	0x09,//VK_TAB
	0x0C,//VK_CLEAR
	0x0D,//VK_RETURN
	0x10,//VK_SHIFT
	0x11,//VK_CONTROL
	0x12,//VK_MENU
	0x13,//VK_PAUSE
	0x14,//VK_CAPITAL
	0x15,//VK_KANA
	0x15,//VK_HANGUEL
	0x15,//VK_HANGUL
	0x17,//VK_JUNJA
	0x18,//VK_FINAL
	0x19,//VK_HANJA
	0x19,//VK_KANJI
	0x1B,//VK_ESCAPE
	0x1C,//VK_CONVERT
	0x1D,//VK_NONCONVERT
	0x1E,//VK_ACCEPT
	0x1F,//VK_MODECHANGE
	0x20,//VK_SPACE
	0x21,//VK_PRIOR
	0x22,//VK_NEXT
	0x23,//VK_END
	0x24,//VK_HOME
	0x25,//VK_LEFT
	0x26,//VK_UP
	0x27,//VK_RIGHT
	0x28,//VK_DOWN
	0x29,//VK_SELECT
	0x2A,//VK_PRINT
	0x2B,//VK_EXECUTE
	0x2C,//VK_SNAPSHOT
	0x2D,//VK_INSERT
	0x2E,//VK_DELETE
	0x2F,//VK_HELP
	0x5B,//VK_LWIN
	0x5C,//VK_RWIN
	0x5D,//VK_APPS
	0x5F,//VK_SLEEP
	0x60,//VK_NUMPAD0
	0x61,//VK_NUMPAD1
	0x62,//VK_NUMPAD2
	0x63,//VK_NUMPAD3
	0x64,//VK_NUMPAD4
	0x65,//VK_NUMPAD5
	0x66,//VK_NUMPAD6
	0x67,//VK_NUMPAD7
	0x68,//VK_NUMPAD8
	0x69,//VK_NUMPAD9
	0x6A,//VK_MULTIPLY
	0x6B,//VK_ADD
	0x6C,//VK_SEPARATOR
	0x6D,//VK_SUBTRACT
	0x6E,//VK_DECIMAL
	0x6F,//VK_DIVIDE
	0x70,//VK_F1
	0x71,//VK_F2
	0x72,//VK_F3
	0x73,//VK_F4
	0x74,//VK_F5
	0x75,//VK_F6
	0x76,//VK_F7
	0x77,//VK_F8
	0x78,//VK_F9
	0x79,//VK_F10
	0x7A,//VK_F11
	0x7B,//VK_F12
	0x7C,//VK_F13
	0x7D,//VK_F14
	0x7E,//VK_F15
	0x7F,//VK_F16
	0x80,//VK_F17
	0x81,//VK_F18
	0x82,//VK_F19
	0x83,//VK_F20
	0x84,//VK_F21
	0x85,//VK_F22
	0x86,//VK_F23
	0x87,//VK_F24
	0x90,//VK_NUMLOCK
	0x91,//VK_SCROLL
	0xA0,//VK_LSHIFT
	0xA1,//VK_RSHIFT
	0xA2,//VK_LCONTROL
	0xA3,//VK_RCONTROL
	0xA4,//VK_LMENU
	0xA5,//VK_RMENU
	0xA6,//VK_BROWSER_BACK
	0xA7,//VK_BROWSER_FORWARD
	0xA8,//VK_BROWSER_REFRESH
	0xA9,//VK_BROWSER_STOP
	0xAA,//VK_BROWSER_SEARCH
	0xAB,//VK_BROWSER_FAVORITES
	0xAC,//VK_BROWSER_HOME
	0xAD,//VK_VOLUME_MUTE
	0xAE,//VK_VOLUME_DOWN
	0xAF,//VK_VOLUME_UP
	0xB0,//VK_MEDIA_NEXT_TRACK
	0xB1,//VK_MEDIA_PREV_TRACK
	0xB2,//VK_MEDIA_STOP
	0xB3,//VK_MEDIA_PLAY_PAUSE
	0xB4,//VK_LAUNCH_MAIL
	0xB5,//VK_LAUNCH_MEDIA_SELECT
	0xB6,//VK_LAUNCH_APP1
	0xB7,//VK_LAUNCH_APP2
	0xBA,//VK_OEM_1
	0xBB,//VK_OEM_PLUS
	0xBC,//VK_OEM_COMMA
	0xBD,//VK_OEM_MINUS
	0xBE,//VK_OEM_PERIOD
	0xBF,//VK_OEM_2
	0xC0,//VK_OEM_3
	0xDB,//VK_OEM_4
	0xDC,//VK_OEM_5
	0xDD,//VK_OEM_6
	0xDE,//VK_OEM_7
	0xDF,//VK_OEM_8
	0xE2,//VK_OEM_102
	0xE5,//VK_PROCESSKEY
	0xE7,//VK_PACKET
	0xF6,//VK_ATTN
	0xF7,//VK_CRSEL
	0xF8,//VK_EXSEL
	0xF9,//VK_EREOF
	0xFA,//VK_PLAY
	0xFB,//VK_ZOOM
	0xFC,//VK_NONAME
	0xFD,//VK_PA1
	0xFE//VK_OEM_CLEAR
};
unsigned char vk_keys_scancodes[256] =
{
	[0x01] = VK_ESCAPE,
	[0x0E] = VK_BACK,
	[0x0F] = VK_TAB,
	[0x1C] = VK_RETURN,
	[0x1D] = VK_CONTROL,
	[0x36] = VK_SHIFT,
	[0x2A] = VK_SHIFT,
	[0x37] = VK_SNAPSHOT,
	[0x38] = VK_MENU,
	[0x39] = VK_SPACE,
	[0x3a] = VK_CAPITAL,
	[0x3B] = VK_F1,
	[0x3C] = VK_F2,
	[0x3D] = VK_F3,
	[0x3E] = VK_F4,
	[0x3F] = VK_F5,
	[0x40] = VK_F6,
	[0x41] = VK_F7,
	[0x42] = VK_F8,
	[0x43] = VK_F9,
	[0x44] = VK_F10,
	[0x45] = VK_NUMLOCK,
	[0x46] = VK_SCROLL,
	[0x47] = VK_HOME,
	[0x48] = VK_UP,
	[0x49] = VK_PRIOR,
	[0x4A] = VK_OEM_MINUS,
	[0x4B] = VK_LEFT,
	[0x4D] = VK_RIGHT,
	[0x4F] = VK_END,
	[0x50] = VK_DOWN,
	[0x51] = VK_NEXT,
	[0x52] = VK_INSERT,
	[0x53] = VK_DELETE,
	[0x57] = VK_F11,
	[0x58] = VK_F12
};
void keyb_init()
{


}

#define IT 0x09000
# define IR 0x09800
# define SCS 0x8
#define keys_buff 0x9810
//0x90 - nop
uint sugg = 0;

// ------------------------------------------------------------------------------------------------
#define IDT_HANDLERM(func) unsigned char func = 0x90;\
__asm__(#func ": \n \
		pushl	%esp			\n\
		pushl	%eax			\n\
		pushl	%ebx			\n\
		pushl	%ecx			\n\
		pushl	%edx			\n\
		pushl	%esi			\n\
		pushl	%edi			\n\
		pushl	%ebp			\n\
		movl	%esp,	_sugg	#Save pointer to stack\n\
		\n call __"# func "		\n\
		popl	%ebp			\n\
		popl	%edi			\n\
		popl	%esi			\n\
		popl	%edx			\n\
		popl	%ecx			\n\
		popl	%ebx			\n\
		popl	%eax			\n\
		add		$4,		%esp	\n\
		iret");\
void _## func()

// ------------------------------------------------------------------------------------------------
void multiHandler() {
	int stack = 0x500000, s2 = 0;
	//Firstly, get stack pointer from sugg
	__asm__("movl %%esp,%0\n movl _sugg,%1": "=r" (stack), "=r" (s2) : );
	//Save SSE registers
	__asm__("\
		push	%%edi					\n\
		mov		%0,		%%edi			\n\
		movups	%%xmm0,	(%%edi)			\n\
		add		$16,	%%edi			\n\
		movups	%%xmm1,	(%%edi)			\n\
		add		$16,	%%edi			\n\
		movups	%%xmm2,	(%%edi)			\n\
		add		$16,	%%edi			\n\
		movups	%%xmm3,	(%%edi)			\n\
		add		$16,	%%edi			\n\
		movups	%%xmm4,	(%%edi)			\n\
		add		$16,	%%edi			\n\
		movups	%%xmm5,	(%%edi)			\n\
		add		$16,	%%edi			\n\
		movups	%%xmm6,	(%%edi)			\n\
		add		$16,	%%edi			\n\
		movups	%%xmm7,	(%%edi)			\n\
		add		$16,	%%edi			\n\
		pop		%%esi					\n\
		"::"r" (&procTable[currentRunning].sse));
	//Save registers
	stack = s2;
	procTable[currentRunning].ebp = *((int *)(stack));
	procTable[currentRunning].edi = *((int *)(stack + 4));
	procTable[currentRunning].esi = *((int *)(stack + 8));
	procTable[currentRunning].edx = *((int *)(stack + 12));
	procTable[currentRunning].ecx = *((int *)(stack + 16));
	procTable[currentRunning].ebx = *((int *)(stack + 20));
	procTable[currentRunning].eax = *((int *)(stack + 24));
	procTable[currentRunning].esp = stack + 44;
	procTable[currentRunning].currentAddr = (void*)*((unsigned int *)(stack + 32));
	procTable[currentRunning].eflags = *((unsigned int *)(stack + 40));
	if (!locked) {
		//Switch process
		if (procTable[currentRunning].priorityL > 0)
			procTable[currentRunning].priorityL--;

		if (procTable[currentRunning].priorityL == 0) {
			procTable[currentRunning].priorityL = procTable[currentRunning].priority;
			currentRunning = (currentRunning + 1) % procCount;

			while (!procTable[currentRunning].state & 1) currentRunning = (currentRunning + 1) % procCount;
		}
	}
	//Just load current values from current process
	__asm__("								\n\
		mov		%1,			%%esi			\n\
		movups	(%%esi),	%%xmm0			\n\
		add		$16,		%%esi			\n\
		movups	(%%esi),	%%xmm1			\n\
		add		$16,		%%esi			\n\
		movups	(%%esi),	%%xmm2			\n\
		add		$16,		%%esi			\n\
		movups	(%%esi),	%%xmm3			\n\
		add		$16,		%%esi			\n\
		movups	(%%esi),	%%xmm4			\n\
		add		$16,		%%esi			\n\
		movups	(%%esi),	%%xmm5			\n\
		add		$16,		%%esi			\n\
		movups	(%%esi),	%%xmm6			\n\
		add		$16,		%%esi			\n\
		movups	(%%esi),	%%xmm7			\n\
		add		$16,		%%esi			\n\
		mov		%0,			%%esi			\n\
		mov		0(%%esi),	%%eax			\n\
		mov		4(%%esi),	%%ebx			\n\
		mov		8(%%esi),	%%ecx			\n\
		mov		12(%%esi),	%%edx			\n\
		mov		16(%%esi),	%%ebp			\n\
		mov		20(%%esi),	%%esp			\n\
		mov		32(%%esi),	%%edi			\n\
		pushl	%%edi						\n\
		mov		$0x8,		%%edi			\n\
		pushl	%%edi						\n\
		mov		44(%%esi),	%%edi			\n\
		pushl	%%edi						\n\
		mov		28(%%esi),	%%edi			\n\
		mov		24(%%esi),	%%esi			\n\
		iret								\n\
		"::"r" ((unsigned int)procTable + sizeof(Process) * currentRunning), "r" (&procTable[currentRunning].sse));

}

// ------------------------------------------------------------------------------------------------
IDT_HANDLERM(multitasking) {
	//Fastest way to decrease error percentage
	__asm__("movb	$0x20,	%al		\n\
			outb	%al,	$0x20	\n\
			");

	// *((uint*)((uint)g_localApicAddr + 0xb0)) = 0;
	//kprintf("1");
	*sec100 = (*sec100) + 1;

	__asm__("call _multiHandler");

}

// ------------------------------------------------------------------------------------------------
IDT_HANDLERM(multitasking2) {
	__asm__("call _multiHandler");
}

#include "ELF.c"

// ------------------------------------------------------------------------------------------------
void processEnd() {
	lockTaskSwitch(1);
	//Free all allocations from process
	ELF_Process * z = procTable[currentRunning].elf_process;
	struct rb_iter *iter = rb_iter_create();
	if (iter) {
		for (void *v = rb_iter_last(iter, z->tree); v; v = rb_iter_prev(iter)) {
			ffree(v);
		}
		rb_iter_dealloc(iter);
	}
	rb_tree_dealloc(z->tree, NULL);
	//What is it, i'm don't know
	for (int i = 0; i < procCount; i++)
		if (procTable[i].runnedFrom == currentRunning)
			procTable[i].runnedFrom = 0;
	//Resume process
	if (procTable[currentRunning].runnedFrom&&!(procTable[procTable[currentRunning].runnedFrom].state&1))
		procTable[procTable[currentRunning].runnedFrom].state ^= 1;

	memcpy((char*)&procTable[currentRunning], (char*)&procTable[procCount - 1], sizeof(Process));
	procTable[procCount - 1].priorityL = 1;
	procCount--;

	procTable[procCount].state = 0;
	currentRunning = procCount;
	//mm_print_out();
	unlockTaskSwitch();

	for (;;);
}


uint stack_size = 65536 * 4;

// ------------------------------------------------------------------------------------------------
void runProcess(char * fileName, uint argc, char **argv, uint suspendIt, char * dir) {

	//Try to open file
	kprintf("1");
	FILE * fp = fopen(fileName, "r");
	fseek(fp, 0, 2);
	if (!fp)
		return;

	//Got a size
	uint z = ftell(fp);
	rewind(fp);
	//mm_print_out();
	kprintf("1");
	void(*progq)() = (void*)mmalloc(z);
	fread((void*)progq, z, 1, fp);
	fclose(fp);
	kprintf("1");
	//Reserve a process
	int _procCount = procCount;
	procTable[_procCount].state = 0;
	procCount++;
	ELF_Process *  entry = relocELF((void*)progq);

	if (!entry)
	{
		//Put last process to reserved, if there isn't any process after us, just
		// copy us to us
		memcpy(&procTable[_procCount], &procTable[procCount - 1], sizeof(Process));
		ffree((void*)progq);
		return;
	}
	addProcessAlloc(entry, progq);
	//Allocate stack
	void * stack = mmalloc(stack_size);
	procTable[_procCount].stack = stack;
	addProcessAlloc(entry, stack);
	//Copy args, they won't be freeed, because that
	// work assigned to caller
	procTable[_procCount].argc = argc;
	procTable[_procCount].argv = argv;
	//Copy working directory path
	procTable[_procCount].workingDir = mmalloc(512);
	char * zz = dir;
	uint ooo = 0;
	while (*zz)
	{
		procTable[_procCount].workingDir[ooo++] = *zz;
		++zz;
	}
	addProcessAlloc(entry, procTable[_procCount].workingDir);
	//Save our elf entry table
	procTable[_procCount].elf_process = entry;
	//Stack to -12, because we have 2 args and adress at top of stack
	// before process have runned
	procTable[_procCount].esp = (uint)stack + stack_size - 12;
	//Current address is a .text entry in ELF File
	procTable[_procCount].currentAddr = entry->entry;
	//Save pointer to buffer, that allocated to read file
	procTable[_procCount].startAddr = (void*)progq;
	procTable[_procCount].priority = 2;
	procTable[_procCount].priorityL = 2;
	//Flags is [------I------PR-]
	procTable[_procCount].eflags = 0x216;
	//Allocate STD IO
	procTable[_procCount].stdin = (FILE*)mmalloc(sizeof(FILE));
	addProcessAlloc(entry, procTable[_procCount].stdin);
	procTable[_procCount].stdout = (FILE*)mmalloc(sizeof(FILE));
	addProcessAlloc(entry, procTable[_procCount].stdout);
	procTable[_procCount].stderr = (FILE*)mmalloc(sizeof(FILE));
	addProcessAlloc(entry, procTable[_procCount].stderr);
	//Preserve caller's std IO to that process
	procTable[_procCount].stdin->w = procTable[currentRunning].stdin->w;
	procTable[_procCount].stdout->w = procTable[currentRunning].stdout->w;
	procTable[_procCount].stderr->w = procTable[currentRunning].stderr->w;
	//Set 'runnedFrom' value
	procTable[_procCount].runnedFrom = currentRunning;
	//Push arguments and return address to stack
	*((unsigned int *)(stack + stack_size - 4)) = (uint)argv;
	*((unsigned int *)(stack + stack_size - 8)) = argc;
	*((unsigned int *)(stack + stack_size - 12)) = (uint)&processEnd;
	procTable[_procCount].state = 1;
	//Suspend process, be runned from
	if (suspendIt)
		procTable[currentRunning].state &= ~1;
}
//Можно трогать : - )
//Утсановка прерывания
//interruptID - Номер прерывания(0-255)
//address - адрес обработчика
void inst(unsigned char interruptID, void * address, unsigned char flags) {
	char * it = (char*)IT;
	unsigned char i;
	unsigned char a[8];
	a[0] = (unsigned int)address & 0x000000FF;
	a[1] = ((unsigned int)address & 0x0000FF00) >> 8;
	a[2] = SCS;
	a[3] = 0;
	a[4] = 0;
	a[5] = flags;
	a[6] = ((unsigned int)address & 0x00FF0000) >> 16;
	a[7] = ((unsigned int)address & 0xFF000000) >> 24;
	for (int k = 0; k < 8; k++)
		* (it + interruptID * 8 + k) = a[k];
}

// ------------------------------------------------------------------------------------------------
void int_l() {
	unsigned short * limit = (short*)IR;
	unsigned int * place = (uint*)(IR + 2); *limit = 256 * 8 - 1; *place = IT;
	__asm__("lidt 0(,%0,)"::"a" (IR));
}

// ------------------------------------------------------------------------------------------------
IDT_HANDLER(irq_ex) {
	unsigned int o = 0;
	kprintf("div zero");
	//OutTextXYV(10, 10, "Dividing by zero", 0xFF00FF, 1, 1024, videoMemory);
	for (;;);
}

unsigned char * mouse_cur;
unsigned char updatingW = 0;
unsigned char buttons = 0;

// ------------------------------------------------------------------------------------------------
//Top window
void windowToTop(int id) {
	Window * prev = windows;
	char fnd = 0;
	if (prev)
		if (prev->id == id && prev->next) {
			Window * last = windows;
			while (last->next) {
				last = last->next;
			}
			windows = prev->next;
			last->next = prev;
			prev->next = 0;
			return;
		}
	while (prev->next) {
		if (prev->next->id == id) {
			fnd = 1;
			break;
		}
		prev = prev->next;
	}
	//If we have prev. window and that window not top window
	if (fnd && prev->next->next) {
		Window * last = windows;
		while (last->next) {
			last = last->next;
		}
		last->next = prev->next; //Last points to us
		prev->next = prev->next->next; //Point to window next our, what needs to be top
		last->next->next = 0; //It is last window

		//ok. ready
	}
}

//Checks, is whether point in some bar
char pointIn(int a, int b, int c, int d, int e, int f) {
	if (a >= c && a <= e && b >= d && b <= f)
		return 1;
	else
		return 0;
}

int wox = 0, woy = 0, dragging = 0;
//Calls hookEvent
void makeMouseHook(uint event, uint ev2)
{
	return;
	HookEvent he;
	//Allocate data, 3 * int
	he.data = (void*)malloc(12);
	uint * w = (uint *)he.data;
	w[0] = ev2;
	w[1] = mouseX;
	w[2] = mouseY;
	hookEvent(event, &he);
	free(he.data);
}
Window * sysConfig = 0;
int cpos = 0, cmode = 0;
char table1[256] = {
	['0'] = 0,['1'] = 1,['2'] = 2,['3'] = 3,['4'] = 4,
	['5'] = 5,['6'] = 6,['7'] = 7,['8'] = 8,['9'] = 9,
	['A'] = 10,['B'] = 11,['C'] = 12,['D'] = 13,['E'] = 14,['F'] = 15
};
void shandler(WindowEvent * e)
{
	if (e->code == WINDOWS_KEY_DOWN)
	{
		unsigned short key = *(unsigned short*)e->data;
		if (key < 0xff) {
			if (key == 0x8 && cpos > 0) {
				cpos--; printTextToWindow(3, sysConfig, "%c", 8);
				cmode /= 16;
			}
			if (key == 13) {
				if (cmode == 0)
					cmode = prevmode;
				if (cmode < 0x100)
					return;
				setVMode(cmode);
				memset(sysConfig->video, 0, 3 * sysConfig->wwidth*sysConfig->wheight);
				//BarVideo(0, 0, sysConfig->wwidth, sysConfig->wheight, 0, sysConfig->wwidth, sysConfig->wheight, sysConfig->video);
				sysConfig->cursorX = 0;
				sysConfig->cursorY = 0;
				printTextToWindow(3, sysConfig, "Current video mode is %dx%dx%d\n", width, height, bpp * 8);
				print_Avail_modes(sysConfig);
				cmode = 0;
				cpos = 0;
			}
			if (key >= 'a'&&key <= 'f')
				key -= 32;
			if ((key >= '0'&&key <= '9') || (key >= 'A'&&key <= 'F'))
			{
				cmode *= 16;
				cmode += table1[key];
				printTextToWindow(3, sysConfig, "%c", key);
				cpos++;
			}
		}
	}
}
void mouseHandler(int fr)
{
	if (mouseX < 0)
		mouseX = 0;

	if (mouseX >= width - 2)
		mouseX = width - 2;
	if (fr) {
		if ((1 << 5) & mouse_byte[0] != 0)
			mouseY += mouse_byte[2];
		else
			mouseY -= mouse_byte[2];
	}
	if (mouseY < 1)
		mouseY = 1;

	if (mouseY >= height - 3)
		mouseY = height - 3;

	if (drawed) {
		CopyToVMemoryD(lastX - 1, lastY - 1, 19, 19, under);
		CopyFromVMemoryD(mouseX - 1, mouseY - 1, 19, 19, under);
		lastX = mouseX;
		lastY = mouseY;
		CopyToVMemoryTransparent(mouseX, mouseY, (unsigned short)16, (unsigned short)16, mouse_cur);
	}
	if ((buttons < lastButtonState)) {
		if (lastButtonState & 1 && !(buttons & 1))
		{
			if (pointIn(mouseX, mouseY, 10, height - 32, 40, height) && !sysConfig) {
				sysConfig = openWindow(648, 400, 0, shandler, "System configuration");
				printTextToWindow(3, sysConfig, "Current video mode is %dx%dx%d\n", width, height, bpp * 8);
				print_Avail_modes(sysConfig);
			}
		}
		if (dragging == 1) {
			dragging = 0;
		}
		else {
			Window * w = windows;
			while (w) {
				if (w->id == lastInteractWinId)
					break;
				w = w->next;
			}
			if (w) {
				WindowEvent we;
				// we.data = w;
				if ((buttons & 1) < (lastButtonState & 1)) {
					we.code = WINDOWS_MOUSE_LEFT_BUTTON_UP;
					we.data = ((mouseX - w->x) << 16) + (mouseY - w->y);
					makeMouseHook(HOOK_MOUSE_CLICK, WINDOWS_MOUSE_LEFT_BUTTON_UP);
					w->handler(&we);
				}

				if ((buttons & 4) < (lastButtonState & 4)) {
					we.code = WINDOWS_MOUSE_MIDDLE_BUTTON_UP;
					we.data = ((mouseX - w->x) << 16) + (mouseY - w->y);
					makeMouseHook(HOOK_MOUSE_CLICK, WINDOWS_MOUSE_MIDDLE_BUTTON_UP);
					w->handler(&we);
				}

				if ((buttons & 2) < (lastButtonState & 2)) {
					we.code = WINDOWS_MOUSE_RIGHT_BUTTON_UP;
					we.data = ((mouseX - w->x) << 16) + (mouseY - w->y);
					makeMouseHook(HOOK_MOUSE_CLICK, WINDOWS_MOUSE_RIGHT_BUTTON_UP);
					w->handler(&we);
				}
			}
		}
	}
	if (dragging == 1) {
		Window * w = windows;
		while (w) {
			if (w->id == lastInteractWinId)
				break;
			w = w->next;
		}
		if (w) {
			w->x = mouseX + wox;
			w->y = mouseY + woy;
		}

	}
	if (buttons != 0 && ((buttons & 1) > (lastButtonState & 1) || (buttons & 2) > (lastButtonState & 2) || (buttons & 4 > lastButtonState & 4))) {
		Window * w = windows;
		Window * clickedIn = 0;
		Window * clickedIn1 = 0;

		while (w) {
			if (pointIn(mouseX, mouseY, w->x, w->y - 20, w->x + w->wwidth, w->y)) {
				clickedIn1 = w;
				if (w->id == activeWindow) break;
			}
			if (pointIn(mouseX, mouseY, w->x, w->y, w->x + w->wwidth, w->y + w->wheight)) {
				clickedIn = w;
				if (w->id == activeWindow) break;
			}
			w = w->next;
		}
		if (clickedIn1) {
			wox = clickedIn1->x - mouseX;
			woy = clickedIn1->y - mouseY;
			clickedIn = clickedIn1;
			lastInteractWinId = clickedIn1->id;
			dragging = (buttons == 1);
		}

		if (clickedIn) {
			char focused = 0;
			int lastActiveId = activeWindow;
			windowToTop(clickedIn->id);
			if (activeWindow != clickedIn->id)
				focused = 1;
			activeWindow = clickedIn->id;
			lastInteractWinId = clickedIn->id;

			WindowEvent we;

			Window * lastActive = windows;
			while (lastActive) {
				if (lastActive->id == lastActiveId)
					break;
				lastActive = lastActive->next;
			}
			if (focused == 0)
				lastActive = 0;
			if (focused == 1) {
				we.code = WINDOWS_FOCUS_EVENT;
				clickedIn->handler(&we);
			}
			if (lastActive) {
				we.code = WINDOWS_DEFOCUS_EVENT;
				lastActive->handler(&we);
			}
			if ((buttons & 1) > (lastButtonState & 1) && dragging == 0) {
				we.code = WINDOWS_MOUSE_LEFT_BUTTON_DOWN;
				we.data = ((mouseX - w->x) << 16) + (mouseY - w->y);
				makeMouseHook(HOOK_MOUSE_CLICK, WINDOWS_MOUSE_LEFT_BUTTON_DOWN);
				clickedIn->handler(&we);
			}

			if ((buttons & 4) > (lastButtonState & 4) && dragging == 0) {
				we.code = WINDOWS_MOUSE_MIDDLE_BUTTON_DOWN;
				we.data = ((mouseX - w->x) << 16) + (mouseY - w->y);
				makeMouseHook(HOOK_MOUSE_CLICK, WINDOWS_MOUSE_MIDDLE_BUTTON_DOWN);
				clickedIn->handler(&we);
			}

			if ((buttons & 2) > (lastButtonState & 2) && dragging == 0) {
				we.code = WINDOWS_MOUSE_RIGHT_BUTTON_DOWN;
				makeMouseHook(HOOK_MOUSE_CLICK, WINDOWS_MOUSE_RIGHT_BUTTON_DOWN);
				clickedIn->handler(&we);
			}
		}
		else {
			Window * lastActive = windows;
			WindowEvent we;
			while (lastActive) {
				if (lastActive->id == activeWindow)
					break;
				lastActive = lastActive->next;
			}
			if (lastActive) {
				we.code = WINDOWS_DEFOCUS_EVENT;
				lastActive->handler(&we);
			}
			activeWindow = -1;
		}
	}
	if (buttons == 0)
		lastInteractWinId = 0;
	if (drawed)
		CopyFromVMemory(mouseX - 1, mouseY - 1, 19, 19, under);
}

IRQ_HANDLER1(irq_mouse) {
	unsigned char status = inportb(0x64);
	if (updatingW) return;
	//while(status&1){
	switch (mouse_cycle) {
	case 0:
		lastButtonState = buttons;
		mouse_byte[0] = inportb(0x60);
		buttons = mouse_byte[0] & 0b0111;
		mouse_cycle++;
		//Wait(10);

		break;
	case 1:
		mouse_byte[1] = inportb(0x60);
		mouse_cycle++;
		break;
	case 2:

		mouse_byte[2] = inportb(0x60);
		if (mouse_byte[0] & 0x80 || mouse_byte[0] & 0x40) {
			mouse_cycle = 0;
			/* x/y overflow? bad packet! */
			break;
		}
		buttons = mouse_byte[0] & 0b0111;
		mouse_cycle = 0;
		if ((1 << 4) & mouse_byte[0] != 0)
			mouseX -= mouse_byte[1];
		else
			mouseX += mouse_byte[1];
		mouseHandler(1);
		break;
	}
}

IDT_HANDLER(irq_ex1) {
	unsigned int o = 0;

	//OutTextXYV(10, 10, "Single-step interrupt", 0xFF00FF, 1, 1024, videoMemory);
	for (;;);
}

IDT_HANDLER(irq_ex3) {
	unsigned int o = 0;

	//OutTextXYV(10, 10, "Breakpoint", 0xFF00FF, 1, 1024, videoMemory);
	for (;;);
}

IDT_HANDLER(irq_ex4) {
	unsigned int o = 0;

	//OutTextXYV(10, 10, "Overflow", 0xFF00FF, 1, 1024, videoMemory);
	for (;;);
}

IDT_HANDLER(irq_ex5) {
	unsigned int o = 0;

	//OutTextXYV(10, 10, "Bounds", 0xFF00FF, 1, 1024, videoMemory);
	for (;;);
}

IDT_HANDLER(irq_ex6) {
	unsigned int o = 0;

	//OutTextXYV(10, 10, "Invalid Opcode", 0xFF00FF, 1, 1024, videoMemory);
	for (;;);
}

IDT_HANDLER(irq_ex7) {
	unsigned int o = 0;

	//OutTextXYV(10, 10, "Coprocessor not available", 0xFF00FF, 1, 1024, videoMemory);
	for (;;);
}

char initS = 0;
IRQ_HANDLER(irq_time) {
	*sec100 = (*sec100) + 1;
	//outportb(0x20,0x20);
	//	OutTextXY(1,1,"aaa",0x1,1);
}
unsigned int qwx = 0;
IRQ_HANDLER(irq_time81) {

	qwx++;
	*sec100 = (*sec100) + 1; // % 100;
	//printTextToWindow(3, mywin, "~~~~!");

}

IRQ_HANDLER1(irq_time8) {
	qwx++;
	kprintf("!");
	*sec100 = (*sec100) + 1; // % 100;
	//printTextToWindow(3, mywin, "~~~~~~~*");

}
char shift = 0;

//Инициализвация очереди
void initKeys() {
	unsigned char * keysInQueue = (uchar*)KeysQueue;
	unsigned char * queueFirst = (uchar*)(KeysQueue + 1);
	unsigned char * queueLast = (uchar*)(KeysQueue + 2); *keysInQueue = 0; *queueFirst = 0; *queueLast = 0;
}
//Добавляет символ в очередь
void addKey(int release, char c, char cc) {
	//if (!c)c = cc;
	//printTextToWindow(3, mywin, "%c %x\n", c, cc);
	//if (c == 0) return;

	unsigned char * keysInQueue = (uchar*)KeysQueue;
	unsigned char * queueFirst = (uchar*)(KeysQueue + 1);
	unsigned char * queueLast = (uchar*)(KeysQueue + 2);
	if (!release) {
		(*keysInQueue)++; *((unsigned short *)KeysQueue + 3 + 2 * (*queueLast)) = (c)+(cc << 8); *queueLast = ((*queueLast) + 1) % 256;
	}
}
//Не сам обработчик клавы;)
void keyboard_handle() {

	unsigned char o = inportb(0x60);
	//kprintf("!");
	if (o == 0x36 || o == 0x2A)
		shift = 1; //Shift нажали
	else if (o == 0x36 + 0x80 || o == 0x2A + 0x80)
		shift = 0; //Shift отпустили
	int release = 0;
	if (o >= 0x80) //Если нажали, а не отпустили
	{
		release = 1;
	}
	char c = codes[o & 0x7F];
	if (shift)
		c = codes_sh[o & 0x7F];
	if (!c&&vk_keys_scancodes[o & 0x7F])
	{
		addKey(release, 0, vk_keys_scancodes[o & 0x7F]);
	}
	addKey(release, c, 0);
	o = inportb(0x61); //отправим контроллеру клавы сигнал о том, что мы завершили работу с клавой
	o |= 1;
	outportb(0x61, o);
}
int abs(int a) {
	if (a < 0) return -a;
	return a;
}

//Real Time Clock
void rtc() {
	unsigned char u[128];
	unsigned char tvalue, index;

	outportb(0x70, 0);
	u[0] = inportb(0x71);
	outportb(0x70, 2);
	u[2] = inportb(0x71);
	outportb(0x70, 4);
	u[4] = inportb(0x71);

	//*sec100 = 0;
	//BDC режим, а-ля 0x23: 0x56: 0x43 ;)
	* sec100 = ((((u[0] / 16) * 10) + (u[0] & 0xf) % 60) * ticksPerSecond) +
		(((u[2] / 16) * 10) + (u[2] & 0xf) % 60) * ticksPerSecond * 60 +
		(((u[4] / 16) * 10) + (u[4] & 0xf) % 24) * ticksPerSecond * 60 * 60;
}

IRQ_HANDLER(irq_keyboard) {
	keyboard_handle();
}
IRQ_HANDLER1(ATA1) {

}
IRQ_HANDLER1(ATA2) {

}
//Non-Mask-able-Interrupts
IDT_HANDLER(NMI) {
	//OutTextXYV(10, 10, "NMI", 0xFFFFFF, 1, 1024, videoMemory);
}
IDT_HANDLER(kbdService) {

}
IRQ_HANDLER(nirq0) {

}
unsigned int ppport = 0;
IRQ_HANDLER1(nirq1) {
	kprintf("nirq1");
}
IDT_HANDLER(idt_std)
{

}

// Разрешаем прерывания
void int_e() {
	__asm__("sti");
}

// Запрещаем прерывания
void int_d() {
	__asm__("cli");
}

// ------------------------------------------------------------------------------------------------
// Globals


// ------------------------------------------------------------------------------------------------
// Memory mapped registers for IO APIC register access
#define IOREGSEL                        0x00
#define IOWIN                           0x10

// ------------------------------------------------------------------------------------------------
// IO APIC Registers
#define IOAPICID                        0x00
#define IOAPICVER                       0x01
#define IOAPICARB                       0x02
#define IOREDTBL                        0x10

// ------------------------------------------------------------------------------------------------
static void IoApicOut(u8 *base, u8 reg, u32 val)
{
	MmioWrite32(base + IOREGSEL, reg);
	MmioWrite32(base + IOWIN, val);
}

// ------------------------------------------------------------------------------------------------
static u32 IoApicIn(u8 *base, u8 reg)
{
	MmioWrite32(base + IOREGSEL, reg);
	return MmioRead32(base + IOWIN);
}

// ------------------------------------------------------------------------------------------------
void IoApicSetEntry(u8 *base, u8 index, u64 data)
{
	IoApicOut(base, IOREDTBL + index * 2, (u32)data);
	IoApicOut(base, IOREDTBL + index * 2 + 1, (u32)(data >> 32));
}
char GPF = 0x90;
__asm__("push %esp; call _GPFF; iret");
void GPFF(char * sp) {
	for (;;);
}
// ------------------------------------------------------------------------------------------------
void IoApicInit()
{
	// Get number of entries supported by the IO APIC
	u32 x = IoApicIn(g_ioApicAddr, IOAPICVER);
	uint count = ((x >> 16) & 0xff) + 1;    // maximum redirection entry

	kprintf("I/O APIC pins = %d\n", count);

	// Disable all entries
	for (uint i = 0; i < count; ++i)
	{
		IoApicSetEntry(g_ioApicAddr, i, 1 << 16);
	}
}

// ------------------------------------------------------------------------------------------------
void iint() {
	keyb_init();
	mouse_cur = malloc(16 * 16 * 4 + 16);
	for (int i = 0; i < 16 * 16 * 4; i++)
		* ((unsigned char *)(mouse_cur + i)) = 0;
	for (int i = 0; i < 11; i++)
		mouse_cur[i * (48 + 3)] = 0x01;
	for (int i = 0; i < 16; i++)
		mouse_cur[i * (48)] = 0x01;
	mouse_cur[48 * 12 + 12] = 0x01;
	mouse_cur[48 * 14 + 6] = 0x01;
	mouse_cur[48 * 15 + 3] = 0x01;
	mouse_cur[48 * 11 + 15] = 0x01;
	for (int i = 0; i < 6; i++) mouse_cur[48 * 11 + 15 + 3 * i] = 0x01;
	mouse_cur[48 * 13 + 9] = 0x01;
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j < i + 1; j++) {
			mouse_cur[48 * (i + 1) + 3 * j] = 0xFF;
			mouse_cur[48 * (i + 1) + 3 * j + 1] = 0xFF;
			mouse_cur[48 * (i + 1) + 3 * j + 2] = 0xFF;
		}
	}
	for (int i = 4; i > 0; i--) {
		for (int j = 1; j < 1 + i; j++) {
			mouse_cur[48 * (4 - i + 11) + 3 * j] = 0xFF;
			mouse_cur[48 * (4 - i + 11) + 3 * j + 1] = 0xFF;
			mouse_cur[48 * (4 - i + 11) + 3 * j + 2] = 0xFF;
		}
	}
	//PIC remap
	outportb(0x20, 0x11);
	outportb(0xa0, 0x11);
	outportb(0x21, 0x20);
	outportb(0xa1, 0x28);
	outportb(0x21, 0x04);
	outportb(0xa1, 0x02);
	outportb(0x21, 0x01);
	outportb(0xa1, 0x01);
	outportb(0x21, 0x00);
	outportb(0xa1, 0x00);
	//All interrupts are allowed
	for (int i = 0; i < 32; i++)
		inst(i, &irq_ex, 0x8E);
	for (int i = 32; i < 40; i++)
		inst(i, &irq_time81, 0x8e);
	for (int i = 40; i < 48; i++)
		inst(i, &irq_time8, 0x8e);
	for (int i = 48; i < 256; i++)
		inst(i, &idt_std, 0x8E);
	for (int i = 0; i < 0x20; i++)
		inst(i, &irq_ex, 0x8e); //Установим обработчики исключенй

	inst(0x20, &multitasking, 0x8e); //PIT - Programmable Interval Timer
	inst(0x28, &irq_time8, 0x8e); //RTC - Real Time Clock
	inst(0x21, &irq_keyboard, 0x8e); //Keyboard
	inst(0x20 + 12, &irq_mouse, 0x8e); //PS/2 Mouse

	//inst(0x20 + 14, & ATA1, 0x8e); //ATA Primary IRQ
	//inst(0x20 + 15, & ATA2, 0x8e); //ATA Secondary IRQ
	for (int i = 0; i < 32; i++) inst(i, &irq_ex, 0x8e);
	inst(0x30, &kbdService, 0x8e); //Keyboard service
	inst(0x41, &multitasking2, 0x8e); //For sleeps and etc
	//    inst(0x40, &videoService, 0x8e);
	int_l(); //Loading IDT
	unsigned short hz = 119;
	outportb(0x43, 0x34);
	outportb(0x40, (unsigned char)hz & 0xFF); //Low
	outportb(0x40, (unsigned char)(hz >> 8) & 0xFF); //Hight, about 1000 times per second

	LocalApicInit();
	IoApicInit();
	IoApicSetEntry(g_ioApicAddr, AcpiRemapIrq(0), 0x20);
	IoApicSetEntry(g_ioApicAddr, AcpiRemapIrq(2), 0x22);
	inst(13, &GPF, 0x8e); //PS/2 Mouse
	int_e(); //Enabling interrupts
	//	unsigned short hz = 65536	;

	int_d();
	outportb(0x70, 0x8A); // select Status Register A, and disable NMI (by setting the 0x80 bit)
	outportb(0x71, 0x20);
	int_e();
	int_d();
	outportb(0x70, 0x8B); // select register B, and disable NMI
	char prev = inportb(0x71); // read the current value of register B
	outportb(0x70, 0x8B); // set the index again (a read will reset the index to register D)
	outportb(0x71, prev | 0x40); // write the previous value ORed with 0x40. This turns on bit 6 of register B
	int_e();

}
//int qwye[8192];


#pragma GCC pop_options
