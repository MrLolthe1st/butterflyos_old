
#define size_t unsigned int

#define VMAlloc malloc
#define KeysQueue 0x09810
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
void nope(int a, ...)
{

}
unsigned int nextS;
#include "windowsEventsCodes.c"
#include "structs.c"
int ccnt = 0;
int drawed = 0, lastButtonState = 0, lastInteractWinId = 0;
Window * windows = 0;
int activeWindow = 0, rec = 0;
int cursorSpeed = 700;
Window * mywin = 0;

#pragma GCC push_options
#include "Link.h"
#include "devices/fpu.c"
#include "time.c"
#include "mathf.c"
#include "string.c"
#include "video.c"
#include "Devices/ports.c"
#include "memory.c"
#include "globalVariables.c"
#include "kprin.c"
#include "Devices\PCI.c"
#include "Devices/device.c"
#include "Devices/disk.c"
#include "FS/fat32.c"
#include "FS\files.c"
#include "Devices/cpu.c"
#pragma GCC optimize ("O0")
#include "SVGA/svga.c"
#include "Devices/ps2mouse.c"
#include "idt.c"
#include "GUI\Forms.c"
#pragma GCC pop_options
#include "usb\usbd.c"
#include "usb\ehci.c"
#include "usb\uhci.c"
#include "usb\storage.c"
#include "usb\mouse.c"
#include "usb\keyboard.c"
#include "usb\hub.c"
#include "internet\internet.c"
#include "internet\rtl8139.c"
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

void k_main()
{
	//hubinit=&_usbHubInit;
	initCoProc();
	setCursor(0);
	clearScreen();
	setCursor(0);
	enableFPU();
	printString("Counting memory...\n");

	mm_init(0x400000);
	kprintf("Memory count: 0x%x bytes\n", pheap_end);
	initGlobals();
	initPS2Mouse();
	initKeys();
	void * processTable = malloc(sizeof(Process) * 1024);
	procTable = processTable;
	*((unsigned int*)0x09921) = processTable;
	procTable[0].state = 1;
	procTable[0].priority = 20;
	procTable[0].priorityL = 20;

	currentRunning = 0;
	procCount = 1;
	//nextS = &nnn;
	//initSVGA1(0;
	iint();
	//unsigned char nnn = 0x90;
	rtc();
	//while(getKey()!=0);
	initDevices();
	ATAInit();
	initSVGA();
	kprintf("ButterflyOS started. Build from 8th august 2018.\n");
	char b[512];

	initGlobals();
	addGlobalVariable("malloc", &malloc);
	addGlobalVariable("free", &free);
	addGlobalVariable("printTextToWindow", &printTextToWindow);
	addGlobalVariable("closeWindow", &closeWindow);
	addGlobalVariable("openWindow", &openWindow);
	addGlobalVariable("fopen", &fopen);
	addGlobalVariable("fclose", &fclose);
	addGlobalVariable("fread", &fread);
	addGlobalVariable("ftell", &ftell);
	//addGlobalVariable("fseek", &fseek);
	unsigned char * cur_dir = malloc(512);
	unsigned char * cur_cmd = malloc(512);
	unsigned char key = 0x0;
	*(cur_dir + 0) = '/';
	*(cur_dir + 1) = 0;
	unsigned short pos = 0;
	mywin = openWindow(640, 680, 0, 0, "CPU Info");
	mywin->handler = &Win1Handler;

	//CpuDetect();
	//for(;;);
	//
	updateWindows();
	PciInit();
	kprintf("List of connected disk devices:\n");
	for (int i = 0; i < dcount; i++)
		kprintf(" Device #%d, structNo = %x, type = %x\n", i, diskDevices[i].structNo, diskDevices[i].type);
	makeLogicDrives();
	FILE * f = fopen("A:\\BINARIES\\QQ.O", "r");
	uchar * tq = malloc(1026);
	fread(tq, 1, 512, f);
	fread(tq, 1, 510, f);
	fread(tq, 1, 3, f);
	kprintf("\nResult %x", tq[2]);
	//kprintf("Size: %x, add1 %x, add2 %x", f->size, f->add1, f->add2);
	//FAT32ReadFile(0, "BINARIES\\QQ.O");
	for (;;);
	//for (;;);
	CopyFromVMemory(width / 2, height / 2, 17, 17, under);
	//kprintf("qq");

	char * mo = malloc(12);
	int tttt = 0;
	WindowEvent we;
	we.data = malloc(2);
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
		//UsbPoll();
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
		draw3D(640, 680, tttt, mywin->video);
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
