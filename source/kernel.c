//#define DEBUG 1 
/*
	 ^
	 | comment
	 it
to turn off debbuging messages

*/

#define size_t unsigned int


short mouseX = 4, mouseY = 4, mouse_cycle = 0, lastX = 4, lastY = 4;
int cday, cmonth, cyear;
#define VMAlloc malloc
#define KeysQueue (int)0x08510
//PIC#0; port 0x20
#define IRQ_HANDLER(func) unsigned char func = 0x90;\
__asm__(#func ": \npusha \n call __"#func " \n movb $0x20, %al \n outb %al, $0x20 \n popa  \n iret \n");\
void _## func()
unsigned int g_pitTicks = 0;
//PIC#1; port 0xA0
#define IRQ_HANDLER1(func) unsigned char func = 0x90;\
__asm__(#func ": \n push %esp \n pusha \n call __"# func " \n movb $0x20, %al \n outb %al, $0xA0 \n outb %al, $0x20 \n popa \n pop %esp\n iret \n");\
void _## func()
void printChar(char s);
void outportb(unsigned short portid, unsigned char value);
void inst(unsigned char interruptID, void * address, unsigned char flags);
//Достает символ из очереди

unsigned int locked = 0;

void nope(int a, ...)
{

}
unsigned int nextS;

#include "windowsEventsCodes.c"
#include "stdarg.h"
int kprintf(const char* str, ...);
void __kprintf_va_list(char* str, va_list ap);
#include "structs.c"
#include "mathf.c"
void printTextToWindowFormatted(unsigned char color, Window * w, char * text);
void printTextToWindow(unsigned char color, Window * w, char * text, ...);
int ccnt = 0;
int drawed = 0, lastButtonState = 0, lastInteractWinId = 0;
Window * windows = 0;
int activeWindow = 0, rec = 0;
int cursorSpeed = 700;
Window * mywin = 0;
char pcidone = 0;
short getKey()
{

	unsigned char * keysInQueue = (unsigned char *)KeysQueue;
	unsigned char * queueFirst = (unsigned char *)(KeysQueue + 1);
	unsigned char * queueLast = (unsigned char *)(KeysQueue + 2);

	if ((*keysInQueue) == 0) return 0;
	(*keysInQueue)--;
	short c = *((unsigned short *)KeysQueue + 3 + 2 * (*queueFirst));
	*queueFirst = ((*queueFirst) + 1) % 256;
	//printTextToWindow(3, mywin, "%x", c);
	return c;
}
unsigned int usbPoll = 1;
#include "Link.h"
#include "devices/fpu.c"
#include "usb_key_layout.c"
#include "string.c"
#include "video.c"
#include "Devices/ports.c"
#include "rb_tree\rb_tree.c"
#include "memory.c"
#include "hooks\hooks.c"
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


#include "smp\smp.c"

void HttpOnTcpData(TcpConn *conn, const u8 *data, uint len)
{
	uint col = 0;

	for (uint i = 0; i < len; ++i)
	{
		char c = data[i];
		printTextToWindow(4, mywin, "%c", c);
		++col;
		if (c == '\n')
		{
			col = 0;
		}
		else if (col == 80)
		{
			printTextToWindow(4, mywin, "\n");
			col = 0;
		}
	}
}
void CmdHttp(char * a1, char *a2)
{
	printTextToWindow(4, mywin, "Usage: http <dest ipv4 address> <path>\n");

	Ipv4Addr dstAddr;
	if (!StrToIpv4Addr(&dstAddr, a1))
	{

		printTextToWindow(4, mywin, "Failed to parse destination address\n");
		return;
	}

	u16 port = 80;
	static char buf[256];

	snprintf(buf, sizeof(buf), "GET %s HTTP/1.0\r\n\r\n", a2);

	TcpConn *conn = TcpCreate();
	conn->ctx = buf;
	conn->onState = HttpOnTcpState;
	conn->onData = HttpOnTcpData;

	TcpConnect(conn, &dstAddr, port);
}
void k_main()
{
	//hubinit=&_usbHubInit;
	fontPointer = (unsigned char*)(0x50000 + 256);
	initCoProc();
	memset(&drives, 0, sizeof(LogicDrive) * 26);
	for (int i = 0; i < 64; i++)
	{
		diskDevices[i].sectorsCount = 0;
	}
	currentRunning = 0;
	setCursor(0);
	clearScreen();
	setCursor(0);
	enableFPU();
	printString("Counting memory...\n");
	g_usbControllerList = 0;
	mm_init(0x400000);
	procTable[0].elf_process = mmalloc(sizeof(ELF_Process));
	procTable[0].elf_process->allocs = 0;
	
	kprintf("Memory count: 0x%x bytes\n", pheap_end);
	initGlobals();
	initPS2Mouse();
	initKeys();
	void * processTable = malloc(sizeof(Process) * 1024);
	procTable = processTable;
	*((unsigned int*)0x09921) = (size_t)processTable;
	procTable[0].state = 1;
	procTable[0].priority = 1;
	procTable[0].priorityL = 1;
	procCount = 1;
	stacks = (size_t*)malloc(65536 * 16);
	*((unsigned int*)0x09925) = (size_t)stacks;
	*((unsigned int*)0x09929) = (size_t)stacks;
	*((unsigned int*)0x09933) = (size_t)&smp_core;
	//nextS = &nnn;
	//initSVGA1(0;
	rtc();
	mywin = openWindow(640, 680, 0, 0, "System Info");
	AcpiInit();
	iint();
	//Wait(1000);
	//unsigned char nnn = 0x90;
	//while(getKey()!=0);
	initDevices();
	ATAInit();
	kprintf("ButterflyOS started. Build from 11th December 2018.\n");
	char b[512];
	//Wait(50);
	initGlobals();
	addGlobalVariable("malloc", (void*)&malloc);
	addGlobalVariable("free", (void*)&free);
	addGlobalVariable("printTextToWindow", (void*)&printTextToWindow);
	addGlobalVariable("closeWindow", (void*)&closeWindow);
	addGlobalVariable("openWindow", (void*)&openWindow);
	addGlobalVariable("fopen", (void*)&fopen);
	addGlobalVariable("clearScreen", (void*)&clearScreen);
	addGlobalVariable("fclose", (void*)&fclose);
	addGlobalVariable("Wait", (void*)&Wait);
	addGlobalVariable("BufferWindow", (void*)&BufferWindow);
	addGlobalVariable("enableBuffering", (void*)&enableBuffering);
	addGlobalVariable("fread", (void*)&fread);
	addGlobalVariable("ftell", (void*)&ftell);
	addGlobalVariable("fwrite", (void*)&fwrite);
	addGlobalVariable("fseek", (void*)&fseek);
	addGlobalVariable("rewind", (void*)&rewind);
	addGlobalVariable("kprintf", (void*)&kprintf);
	addGlobalVariable("memcpy", (void*)&memcpy);
	addGlobalVariable("getKey", (void*)&getKey);
	addGlobalVariable("DirectoryListing", (void*)&DirectoryListing);
	addGlobalVariable("lockTaskSwitch", (void*)&lockTaskSwitch);
	addGlobalVariable("unlockTaskSwitch", (void*)&unlockTaskSwitch);
	addGlobalVariable("mkdir", (void*)&mkdir);
	addGlobalVariable("runProcess", (void*)&runProcess);
	addGlobalVariable("testForGUI", (void*)&testForGUI);
	addGlobalVariable("ReadFromDisk", (void*)&ReadFromDisk);
	addGlobalVariable("putPixelVideo", (void*)&putPixelVideo);
	addGlobalVariable("LineVideo", (void*)&LineVideo);
	addGlobalVariable("BarVideo", (void*)&BarVideo);
	addGlobalVariable("drawcharv", (void*)&drawcharv);
	addGlobalVariable("getProcessSTDStream", (void*)&getProcessSTDStream);
	addGlobalVariable("attachIoToWindow", (void*)&attachIoToWindow);
	addGlobalVariable("currentRunning", &currentRunning);
	addGlobalVariable("memcpy1", (void*)&memcpy1);
	addGlobalVariable("printf", &printf);
	addGlobalVariable("memset", &memset);
	addGlobalVariable("fflush", &fflush);
	addGlobalVariable("strlen", &strlen);
	addGlobalVariable("fprintf", &fprintf);
	addGlobalVariable("strerr", 1);
	addGlobalVariable("procTable", &procTable);
	unsigned char * cur_dir = malloc(512);
	unsigned char * cur_cmd = malloc(512);
	unsigned char key = 0x0;
	*(cur_dir + 0) = '/';
	*(cur_dir + 1) = 0;
	unsigned short pos = 0;

	//CpuDetect();
	//for(;;);
	//
	mywin->handler = &Win1Handler;
	PciInit();
	initSVGA();
	updateWindows();
	//swapBuffer();
	SmpInit();
	NetInit();
	NetPrintRouteTable();
	CmdHttp("127.0.0.1", "/");
	printTextToWindow(4, mywin, "\n%xListing of connected devices:\n", (uint)'а');
	{
		printTextToWindow(4, mywin, "USB Devices:\n");

		for (UsbDevice *dev = g_usbDeviceList; dev; dev = dev->next)
		{
			printTextToWindow(3, mywin, "Product='%s' Vendor='%s' Serial=%s\n", &dev->productStr, &dev->vendorStr, &dev->serialStr);
		}
		printTextToWindow(4, mywin, "Disk Devices:\n");
		for (int i = 0; i < 64; i++)
		{
			if (diskDevices[i].sectorsCount > 0)
			{
				((identify_data*)&diskDevices[i].data)->model[39] = 0;
				if (diskDevices[i].type == DISK_TYPE_SATA_AHCI)
					printTextToWindow(3, mywin, "SATA AHCI Drive Model: %s\n", &((identify_data*)&diskDevices[i].data)->model);

				if (diskDevices[i].type == DISK_TYPE_SATA)
					printTextToWindow(3, mywin, "ATA Drive Model: %s\n", &((identify_data*)&diskDevices[i].data)->model);
			}
		}
	}
	char * cmd_path = "A:\\SYSTEM32\\CMD.O";
	char * cmd_work_dir = "A:\\SYSTEM32\\";
	cmd_path[0] = bootedFrom + 'A';
	cmd_work_dir[0] = bootedFrom + 'A';
	runProcess(cmd_path, 2, 0, 0, cmd_work_dir);
	DateTime dtt;
	RtcGetTime(&dtt);
	printTextToWindow(7, mywin, "ButterflyOS started! Booted from %c, current time and date: %02d.%02d.%04d %02d:%02d\n", bootedFrom + 'A', dtt.day, dtt.month, dtt.year, dtt.hour, dtt.min);
	if (*g_activeCpuCount > 1)
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
			short key = 0;
			while (key = getKey())
			{
				if (currentActive)
				{
					we.code = WINDOWS_KEY_DOWN;
					*((unsigned short*)we.data) = key;
					currentActive->handler(&we);
				}
			}
			UsbPoll();
			NetPoll();
			Wait(1);
		}
	CopyFromVMemory(width / 2, height / 2, 17, 17, under);


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
				*((unsigned short*)we.data) = key;
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
