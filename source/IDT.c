/*
* Author: Novozhilov Alexandr @mrlolthe1st
*/
//Не трогать до следующего коммента, где это будет разрешено!

#pragma GCC push_options
#pragma GCC optimize ("Ofast")
char codes[] = { 0,0,'1','2','3','4','5','6','7','8','9','0','-','=',8,'\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',0,'a','s','d','f','g','h','j','k','l',';','\'','`',0,'\\','z','x','c','v','b','n','m',',','.','/',0,'*',0,' ',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'-',0,0,0,'+',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
char codes_sh[] = { 0,0,'!','@','#','$','%','^','&','*','(',')','_','+',8,'\t','Q','W','E','R','T','Y','U','I','O','P','{','}','\n',0,'A','S','D','F','G','H','J','K','L',':','"','~',0,'|','Z','X','C','V','B','N','M','<','>','?',0,'*',0,' ',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'-',0,0,0,'+',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
//0x90 - nop
#define IDT_HANDLER(func) unsigned char func = 0x90;\
__asm__(#func ": \npusha \n call __"# func " \n  popa  \n iret \n");\
void _## func()





#define IT 0x09000
# define IR 0x09800
# define SCS 0x8
#define keys_buff 0x9810
//0x90 - nop
uint sugg = 0;
#define IDT_HANDLERM(func) unsigned char func = 0x90;\
__asm__(#func ": \n \
pushl %esp\n\
pushl %eax\n\
pushl %ebx\n\
pushl %ecx\n\
pushl %edx\n\
pushl %esi\n\
pushl %edi\n\
pushl %ebp\n\
movl %esp,_sugg\n\
\n call __"# func " \n\
popl %ebp\n\
popl %edi\n\
popl %esi\n\
popl %edx\n\
popl %ecx\n\
popl %ebx\n\
popl %eax\n\
add $4,%esp\
\n iret \n");\
void _## func()
void multiHandler() {
	int stack = 0x500000, s2 = 0;
	__asm__("movl %%esp,%0\n movl _sugg,%1": "=r" (stack), "=r" (s2) : );
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
		if (procTable[currentRunning].priorityL > 0)
			procTable[currentRunning].priorityL--;

		if (procTable[currentRunning].priorityL == 0) {
			procTable[currentRunning].priorityL = procTable[currentRunning].priority;
			currentRunning = (currentRunning + 1) % procCount;

			while (!procTable[currentRunning].state & 1) currentRunning = (currentRunning + 1) % procCount;
		}
	}
	__asm__("\n\
		mov %0,%%esi\n\
		mov 0(%%esi),%%eax\n\
		mov 4(%%esi),%%ebx\n\
		mov 8(%%esi),%%ecx\n\
		mov 12(%%esi),%%edx\n\
		mov 16(%%esi),%%ebp\n\
		mov 20(%%esi),%%esp\n\
		mov 32(%%esi),%%edi\n\
		pushl %%edi\n\
		mov $0x8,%%edi\n\
		pushl %%edi\n\
		mov 44(%%esi),%%edi\n\
		pushl %%edi\n\
		mov 28(%%esi),%%edi\n\
		mov 24(%%esi),%%esi\n\
		iret\n\
		"::"r" ((unsigned int)procTable + sizeof(Process) * currentRunning));

}

IDT_HANDLERM(multitasking) {
	__asm__("movb $0x20, %al \n\
		outb %al, $0x20\n\
		");
	*((uint*)((uint)g_localApicAddr + 0xb0)) = 0;
	*sec100 = (*sec100) + 1; // % 100;
	__asm__("\
	call _multiHandler");

}
IDT_HANDLERM(multitasking2) {
	__asm__("\
	call _multiHandler");
}

#include "ELF.c"
void processEnd() {
	//for (;;);
	lockTaskSwitch(1);
	free(procTable[currentRunning].startAddr);
	//free(procTable[currentRunning].stack);
	ELF_Process * z = procTable[currentRunning].elf_process;
	processAlloc * p = z->allocs;
	while (p)
	{
		free(p->addr);
		processAlloc * pz = p->next;
		free(p);
		p = pz;
	}
	//kprintf("Emd!");
	for (int i = 0; i < procCount; i++)
		if (procTable[i].runnedFrom == currentRunning)
			procTable[i].runnedFrom = 0;
	if (procTable[currentRunning].runnedFrom)
		procTable[procTable[currentRunning].runnedFrom].state |= 1;
	for (int i = 0; i < procTable[currentRunning].argc; i++)
		free(procTable[currentRunning].argv[i]);
	free(procTable[currentRunning].argv);
	free(procTable[currentRunning].workingDir);
	free(procTable[currentRunning].stdout);
	free(procTable[currentRunning].stdin);
	free(procTable[currentRunning].stderr);
	memcpy((char*)&procTable[currentRunning], (char*)&procTable[procCount - 1], sizeof(Process));
	procTable[procCount - 1].priorityL = 1;
	procCount--;
	//printTextToWindow(6, mywin, "\nEnd!%x\n", currentRunning);
	procTable[procCount].state = 0;
	currentRunning = procCount;
	unlockTaskSwitch();
	for (;;);
}
typedef struct _eqa {
	unsigned int name;
	unsigned int value;
	unsigned int size;
	unsigned char info;
	unsigned char other;
	unsigned short shndx;
}
Elf32_Sym;
typedef struct {
	unsigned int addr;
	unsigned int info;

}
rel;
uint stack_size = 65536 * 2;
void runProcess(char * fileName, uint argc, char **argv, uint suspendIt, char * dir) {
	FILE * fp = fopen(fileName, "r");
	fseek(fp, 0, 2);
	if (!fp)
		return;
	uint z = ftell(fp);
	rewind(fp);
	void(*progq)() = (void*)malloc(z);// FAT32ReadFileATA(0, "OO.O");
	fread((void*)progq, z, 1, fp);
	fclose(fp);
	//kprintf("%x\n", &getKey);
	ELF_Process *  entry = relocELF((void*)progq);
	printTextToWindow(5, mywin, "Elf");
	if (!entry)
	{
		printTextToWindow(5, mywin, "~");
		free((void*)progq);
		return;
	}
	procTable[procCount].state = 0;
	//progq = entry;
	void * stack = malloc(stack_size);
	procTable[procCount].stack = stack;
	addProcessAlloc(entry, stack);
	procTable[procCount].argc = argc;
	procTable[procCount].argv = argv;

	procTable[procCount].workingDir = malloc(512);
	char * zz = dir;
	uint ooo = 0;
	while (*zz)
	{
		procTable[procCount].workingDir[ooo++] = *zz;
		++zz;
	}
	procTable[procCount].elf_process = entry;
	procTable[procCount].esp = (uint)stack + stack_size - 12;
	procTable[procCount].currentAddr = entry->entry;
	//kprintf("!%x %x!",entry, entry->entry);
	procTable[procCount].startAddr = (void*)progq;
	//	procTable[procCount].eax = entry;
	procTable[procCount].priority = 2;
	procTable[procCount].priorityL = 2;
	procTable[procCount].eflags = 0x216;
	procTable[procCount].stdin =(FILE*) malloc(sizeof(FILE));
	procTable[procCount].stdout = (FILE*) malloc(sizeof(FILE));
	procTable[procCount].stderr =(FILE*)malloc(sizeof(FILE));
	procTable[procCount].stdin->w = procTable[currentRunning].stdin->w;
	procTable[procCount].stdout->w = procTable[currentRunning].stdout->w;
	procTable[procCount].stderr->w = procTable[currentRunning].stderr->w;
	procTable[procCount].runnedFrom = currentRunning;
	if (suspendIt)
		procTable[currentRunning].state &= ~1;
	*((unsigned int *)(stack + stack_size - 4)) = (uint)argv;
	*((unsigned int *)(stack + stack_size - 8)) = argc;
	//*((unsigned int *)(stack + 8180)) = 0x08;
	*((unsigned int *)(stack + stack_size - 12)) = (uint)&processEnd;
	//*((unsigned int *)(stack + 8180)) = &processEnd;
	//progq();
	procCount++;
	procTable[procCount-1].state = 1;
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
void int_l() {
	unsigned short * limit = (short*)IR;
	unsigned int * place = (uint*)(IR + 2); *limit = 256 * 8 - 1; *place = IT;
	__asm__("lidt 0(,%0,)"::"a" (IR));
}
IDT_HANDLER(irq_ex) {
	unsigned int o = 0;

	//OutTextXYV(10, 10, "Dividing by zero", 0xFF00FF, 1, 1024, videoMemory);
	for (;;);
}

unsigned char * mouse_cur;
unsigned char updatingW = 0;
unsigned char buttons = 0;
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
char pointIn(int a, int b, int c, int d, int e, int f) {
	if (a >= c && a <= e && b >= d && b <= f)
		return 1;
	else
		return 0;
}
int wox = 0, woy = 0, dragging = 0;
void mouseHandler()
{
	if (mouseX < 2) {
		mouseX = 2;
	}
	if (mouseX >= width - 18) {
		mouseX = width - 18;
	}

	if ((1 << 5) & mouse_byte[0] != 0)
		mouseY += mouse_byte[2];
	else
		mouseY -= mouse_byte[2];
	if (mouseY < 2) {
		mouseY = 2;
	}
	if (mouseY >= height - 18) {
		mouseY = height - 18;
	}
	if (drawed) {
		CopyToVMemoryD(lastX - 1, lastY - 1, 19, 19, under);
		// CopyFromVMemoryD(mouseX,mouseY,17,17,under);
		CopyFromVMemoryD(mouseX - 1, mouseY - 1, 19, 19, under);
		//OutTextXYM(0,0,
		lastX = mouseX;
		lastY = mouseY;
		CopyToVMemoryTransparent(mouseX, mouseY, (unsigned short)16, (unsigned short)16, mouse_cur);
	}
	if ((buttons < lastButtonState)) {
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
					w->handler(&we);
				}

				if ((buttons & 4) < (lastButtonState & 4)) {
					we.code = WINDOWS_MOUSE_MIDDLE_BUTTON_UP;
					w->handler(&we);
				}

				if ((buttons & 2) < (lastButtonState & 2)) {
					we.code = WINDOWS_MOUSE_MIDDLE_BUTTON_UP;
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
			//printTextToWindow(6, mywin, "\nE%x\n", clickedIn -> handler);
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
				clickedIn->handler(&we);
			}

			if ((buttons & 4) > (lastButtonState & 4) && dragging == 0) {
				we.code = WINDOWS_MOUSE_MIDDLE_BUTTON_DOWN;
				clickedIn->handler(&we);
			}

			if ((buttons & 2) > (lastButtonState & 2) && dragging == 0) {
				we.code = WINDOWS_MOUSE_MIDDLE_BUTTON_DOWN;
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

		//if(!(1&mouse_byte[0]))
		//  CopyToVMemoryD(lastX,lastY,17,17,under);
		mouseHandler();
		//CopyFromVMemory(mouseX,mouseY,17,17,under);
		//   CopyToVMemoryTransparentD(mouseX,mouseY,(unsigned short)16,(unsigned short)16,mouse_cur);
		//   CopyToVMemoryTransparent(mouseX,mouseY,(unsigned short)16,(unsigned short)16,mouse_cur);
		break;
	}
	//}
	//for(;;);
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
	kprintf("z");
}

IRQ_HANDLER1(irq_time8) {
	qwx++;
	kprintf("!");
	*sec100 = (*sec100) + 1; // % 100;

}
char shift = 0;

//Инициализвация очереди
void initKeys() {
	unsigned char * keysInQueue = (uchar*)KeysQueue;
	unsigned char * queueFirst = (uchar*)(KeysQueue + 1);
	unsigned char * queueLast = (uchar*)(KeysQueue + 2); *keysInQueue = 0; *queueFirst = 0; *queueLast = 0;
}
//Добавляет символ в очередь
void addKey(char c) {
	if (c == 0) return;
	unsigned char * keysInQueue = (uchar*)KeysQueue;
	unsigned char * queueFirst = (uchar*)(KeysQueue + 1);
	unsigned char * queueLast = (uchar*)(KeysQueue + 2);
	(*keysInQueue)++; *((unsigned char *)KeysQueue + 3 + (*queueLast)) = c; *queueLast = ((*queueLast) + 1) % 256;
}
//Не сам обработчик клавы;)
void keyboard_handle() {

	unsigned char o = inportb(0x60);
	//kprintf("!");
	if (o == 0x36 || o == 0x2A)
		shift = 1; //Shift нажали
	else if (o == 0x36 + 0x80 || o == 0x2A + 0x80)
		shift = 0; //Shift отпустили
	if (o < 0x80) //Если нажали, а не отпустили
	{
		char c = codes[o];
		if (shift == 1)
			c = codes_sh[o];
		addKey(c);
	}
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
u8 *g_ioApicAddr;

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
void iint() {
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
		inst(i, &irq_time81, 0x8F);
	for (int i = 40; i < 48; i++)
		inst(i, &irq_time8, 0x8F);
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
	inst(0x0, &irq_ex, 0x8e);
	inst(0x1, &irq_ex1, 0x8e);
	inst(0x3, &irq_ex3, 0x8e);
	inst(0x4, &irq_ex4, 0x8e);
	inst(0x5, &irq_ex5, 0x8e);
	inst(0x6, &irq_ex6, 0x8e);
	inst(0x30, &kbdService, 0x8e); //Keyboard service
	inst(0x40, &multitasking2, 0x8e); //For sleeps and etc
	//    inst(0x40, &videoService, 0x8e);
	int_l(); //Loading IDT
	unsigned short hz = 119;
	outportb(0x43, 0x34);
	outportb(0x40, (unsigned char)hz & 0xFF); //Low
	outportb(0x40, (unsigned char)(hz >> 8) & 0xFF); //Hight, about 1000 times per second

	LocalApicInit();
	IoApicInit();
	IoApicSetEntry(g_ioApicAddr, AcpiRemapIrq(0), 0x20);
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
