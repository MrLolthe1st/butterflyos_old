//#define DEBUG 1 
/*
     ^
	 | comment
	 it
to turn off debbuging messages

*/

#define size_t unsigned int


short mouseX = 4, mouseY = 4, mouse_cycle = 0, lastX = 4, lastY = 4;
#define VMAlloc malloc
#define KeysQueue 0x09810
//PIC#0; port 0x20
#define IRQ_HANDLER(func) char func = 0x90;\
__asm__(#func ": \npusha \n call __"#func " \n movb $0x20, %al \n outb %al, $0x20 \n popa  \n iret \n");\
void _## func()
unsigned int g_pitTicks = 0;
//PIC#1; port 0xA0
#define IRQ_HANDLER1(func) char func = 0x90;\
__asm__(#func ": \n push %esp \n pusha \n call __"# func " \n movb $0x20, %al \n outb %al, $0xA0 \n outb %al, $0x20 \n popa \n pop %esp\n iret \n");\
void _## func()
//Достает символ из очереди
char pcidone = 0;
char getKey()
{

	unsigned char * keysInQueue = KeysQueue;
	unsigned char * queueFirst = KeysQueue + 1;
	unsigned char * queueLast = KeysQueue + 2;

	if ((*keysInQueue) == 0) return 0;
	(*keysInQueue)--;
	char c = *((unsigned char *)KeysQueue + 3 + (*queueFirst));
	*queueFirst = ((*queueFirst) + 1) % 256;

	return c;
}
unsigned int locked = 0;

void nope(int a, ...)
{

}
unsigned int nextS;
#include "windowsEventsCodes.c"
#include "stdarg.h"
#include "structs.c"
int ccnt = 0;
int drawed = 0, lastButtonState = 0, lastInteractWinId = 0;
Window * windows = 0;
int activeWindow = 0, rec = 0;
int cursorSpeed = 700;
Window * mywin = 0;
unsigned int usbPoll = 1;
#include "Link.h"
#include "devices/fpu.c"
#include "usb_key_layout.c"
#include "mathf.c"
#include "string.c"
#include "video.c"
#include "Devices/ports.c"
#include "memory.c"
#include "globalVariables.c"
#include "kprin.c"
#include "time.c"

void lockTaskSwitch(unsigned int id)
{
	locked += id;
}
void unlockTaskSwitch()
{
	locked -= 1;
}
#include "Devices\PCI.c"
#include "Devices/device.c"
#include "Devices/disk.c"
#include "FS/fat32.c"
#include "FS\files.c"
#include "Devices/cpu.c"
#pragma GCC push_options
#pragma GCC optimize ("Ofast")
#include "SVGA/svga.c"
#include "Devices/ps2mouse.c"
#include "acpi\acpi.c"
#include "idt.c"
#pragma GCC pop_options
#include "GUI\Forms.c"
#include "Devices/pci_ide.c"
#include "usb\usbd.c"
#include "usb\ehci.c"
#include "usb\uhci.c"
#include "usb\storage.c"
#include "usb\mouse.c"
#include "usb\keyboard.c"
#include "usb\hub.c"
#include "internet\internet.c"
#include "internet\rtl8139.c"
u8 g_netTrace;
void * hher;
void Win1Handler(void * ev)
{

	WindowEvent * a = (WindowEvent*)ev;
	if (a->code == WINDOWS_FOCUS_EVENT)
	{
		printTextToWindow(6, mywin, "Focused on that Window:)\n");
	}
	if (a->code == WINDOWS_KEY_DOWN)
	{
		printTextToWindow(6, mywin, a->data);
		mywin->lastUpdate = *sec100;
		mywin->cursorState = 1;
	}
	if (a->code == WINDOWS_DEFOCUS_EVENT)
	{
		printTextToWindow(6, mywin, "UnFocused on that Window:)\n");
	}

	if (a->code == WINDOWS_MOUSE_LEFT_BUTTON_DOWN)
	{
		printTextToWindow(6, mywin, "MButton Down Event\n");
	}
	if (a->code == WINDOWS_MOUSE_LEFT_BUTTON_UP)
	{
		printTextToWindow(6, mywin, "MButton UP Event\n");
	}
}
uchar testForGUI()
{
	return (*((uchar*)0x3FF));
}
uint *stacks;

static void HttpOnTcpState(TcpConn *conn, uint oldState, uint newState)
{
	const char *msg = (const char *)conn->ctx;

	if (newState == TCP_ESTABLISHED)
	{
		TcpSend(conn, msg, strlen(msg));
	}

	if (newState == TCP_CLOSE_WAIT)
	{
		TcpClose(conn);
	}
}
static void HttpOnTcpData(TcpConn *conn, const u8 *data, uint len)
{
	uint col = 0;

	for (uint i = 0; i < len; ++i)
	{
		char c = data[i];
		printTextToWindow(3,mywin,"%c",c);
		++col;
		if (c == '\n')
		{
			col = 0;
		}
		else if (col == 80)
		{
			printTextToWindow(3, mywin, "\n");
			col = 0;
		}
	}
}

#include "smp\smp.c"

void k_main()
{
	//hubinit=&_usbHubInit;
	initCoProc();
	memset(&drives, 0, sizeof(LogicDrive) * 26);
	currentRunning = 0;
	setCursor(0);
	clearScreen();
	setCursor(0);
	enableFPU();
	printString("Counting memory...\n");
	g_usbControllerList = 0;
	mm_init(0x400000);
	kprintf("Memory count: 0x%x bytes\n", pheap_end);
	initGlobals();
	initPS2Mouse();
	initKeys();
	void * processTable = malloc(sizeof(Process) * 1024);
	procTable = processTable;
	*((unsigned int*)0x09921) = processTable;
	procTable[0].state = 1;
	procTable[0].priority = 1;
	procTable[0].priorityL = 1;
	procCount = 1;
	stacks = malloc(65536 * 16);
	*((unsigned int*)0x09925) = stacks;
	*((unsigned int*)0x09929) = stacks;
	*((unsigned int*)0x09933) = &smp_core;
	//nextS = &nnn;
	//initSVGA1(0;
	rtc();
	AcpiInit();
	iint();
	//Wait(1000);
	//unsigned char nnn = 0x90;
	//while(getKey()!=0);
	initDevices();
	ATAInit();
	kprintf("ButterflyOS started. Build from 8th august 2018.\n");
	char b[512];
	//Wait(50);
	initGlobals();
	addGlobalVariable("malloc", &malloc);
	addGlobalVariable("free", &free);
	addGlobalVariable("printTextToWindow", &printTextToWindow);
	addGlobalVariable("closeWindow", &closeWindow);
	addGlobalVariable("openWindow", &openWindow);
	addGlobalVariable("fopen", &fopen);
	addGlobalVariable("clearScreen", &clearScreen);
	addGlobalVariable("fclose", &fclose);
	addGlobalVariable("Wait", &Wait);
	addGlobalVariable("fread", &fread);
	addGlobalVariable("ftell", &ftell);
	addGlobalVariable("fwrite", &fwrite);
	addGlobalVariable("fseek", &fseek);
	addGlobalVariable("rewind", &rewind);
	addGlobalVariable("kprintf", &kprintf);
	addGlobalVariable("memcpy", &memcpy);
	addGlobalVariable("getKey", &getKey);
	addGlobalVariable("DirectoryListing", &DirectoryListing);
	addGlobalVariable("lockTaskSwitch", &lockTaskSwitch);
	addGlobalVariable("unlockTaskSwitch", &unlockTaskSwitch);
	addGlobalVariable("mkdir", &mkdir);
	addGlobalVariable("runProcess", &runProcess);
	addGlobalVariable("testForGUI", &testForGUI);
	addGlobalVariable("ReadFromDisk", &ReadFromDisk);
	addGlobalVariable("putPixelVideo", &putPixelVideo);
	addGlobalVariable("LineVideo", &LineVideo); 
	addGlobalVariable("BarVideo", &BarVideo);
	addGlobalVariable("drawcharv", &drawcharv);
	addGlobalVariable("getProcessSTDStream", &getProcessSTDStream);
	addGlobalVariable("attachIoToWindow", &attachIoToWindow);
	addGlobalVariable("printf", &printf);
	unsigned char * cur_dir = malloc(512);
	unsigned char * cur_cmd = malloc(512);
	unsigned char key = 0x0;
	*(cur_dir + 0) = '/';
	*(cur_dir + 1) = 0;
	unsigned short pos = 0;

	//CpuDetect();
	//for(;;);
	//
	PciInit();
	mywin = openWindow(640, 680, 0, 0, "CPU Info");
	mywin->handler = &Win1Handler;
	initSVGA();
	updateWindows();
	//swapBuffer();
	SmpInit();
	//NetInit();

	runProcess("A:\\CMD.O", 2, 0, 0, "A:\\");
	//kprintf("Size: %x, add1 %x, add2 %x", f->size, f->add1, f->add2);
	//FAT32ReadFile(0, "BINARIES\\QQ.O");
	//kprintf("%x!", &videoMemory);
	//smp_core(0);
	if (g_activeCpuCount > 1)
		for (;;) { 
			UsbPoll();
			NetPoll();
			Wait(1);
		}

	WindowEvent we;
	we.data = malloc(2);
	if (!(*((uchar*)0x3FF)))
		for (;;)
		{
			Window * currentActive = windows;

			while (currentActive)
			{
				if (currentActive->id == activeWindow)
					break;
				currentActive = currentActive->next;
			}
			char key = 0;
			while (key = getKey())
			{
				if (currentActive)
				{
					we.code = WINDOWS_KEY_DOWN;
					*((unsigned char*)we.data) = key;
					*((char*)(we.data + 1)) = 0;
					currentActive->handler(&we);
				}
			}
			UsbPoll();
			NetPoll();
			Wait(1);
		}kprintf("qq");
	CopyFromVMemory(width / 2, height / 2, 17, 17, under);
	kprintf("qq");

	char * mo = malloc(12);
	int tttt = 0;
	//Bar(0,0,400,600,50);
	//for(;;);
	int bb = 1;
	//runProcess("OO.O");
	//runProcess("OO.O");	
	//runProcess("OO.O");	
	mywin->type = 1;
	mywin->x = 250;
	swapBuffer();
	for (;;)
	{
		tttt++;
		//printTextToWindow(1, mywin, "!@#$%x&&&",&_UsbMouseInit);
		UsbPoll();
		NetPoll();
		unsigned int x = *sec100;
		char key = 0;
		Window * currentActive = windows;

		while (currentActive)
		{
			if (currentActive->id == activeWindow)
				break;
			currentActive = currentActive->next;
		}
		while (key = getKey())
		{
			if (currentActive)
			{
				we.code = WINDOWS_KEY_DOWN;
				*((unsigned char*)we.data) = key;
				*((char*)(we.data + 1)) = 0;
				currentActive->handler(&we);
			}
		}
		drawed = 0;
		//draw3D(640, 680, tttt, mywin->video);
		updateWindows();
		int a = mouseX, b = mouseY;
		lastX = a; lastY = b;
		CopyFromVMemory(a - 1, b - 1, 19, 19, under);
		CopyFromVMemory(a - 1, b - 1, 19, 19, under2);
		OutTextXY(0, 680, mo, 0xFF0000, 0x2);
		CopyToVMemoryTransparentD(a, b, (unsigned short)16, (unsigned short)16, mouse_cur);
		swapBuffer();
		CopyToVMemoryD(a - 1, b - 1, 19, 19, under2);
		CopyFromVMemoryD(mouseX - 1, mouseY - 1, 19, 19, under);
		CopyToVMemoryTransparent(mouseX, mouseY, (unsigned short)16, (unsigned short)16, mouse_cur);
		drawed = 1;
		unsigned int o = *sec100;
		if (tttt % 10 == 0)
			bb = o - x;
		__itoa((int)(((uint)mywin->caption)), 16, mo);
	}
}
