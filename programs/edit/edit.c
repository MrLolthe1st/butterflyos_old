#include "..\includes\executable.c"
#include "..\includes\stdio.h"
#include "..\includes\structs.h"
#include "..\includes\forms.h"
#include "..\includes\windowsEventsCodes.h"
unsigned int * sec100 = 0x09913;
void KeyHandler(char k);
FILE * curFile;
typedef struct _line {
	char * text;
	struct _line * next;
	int length;
} line;
line * text = 0;
Window * w = 0;
char kkey = 0;

typedef struct {
	unsigned char b;
	unsigned char g;
	unsigned char r;
} ScreenPoint;
int width, height;
int cursorX = 0, cursorY = 0, pos = 0, cstate = 0,
pageOffsetY = 0, pageOffsetX = 0, pageSizeX = 0,
pageSizeY = 0, lastCursorUpdate = 0;
char queue[256];
int head = 0, tail = -1, length = 0;
void insertKey(char c)
{
	tail = (tail + 1) % 256;
	queue[tail] = c;
	length++;
}
char getKey()
{
	if(length<1) return 0;
	char c = queue[head];
	head = (head + 1)%256;
	length--;
	return c;
}
void handle(WindowEvent * z)
{
	if (z->code == WINDOWS_KEY_DOWN)
	{
		insertKey(*((char*)z->data));
	}
}


int min(int a, int b)
{
	return a < b ? a : b;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

void KeyHandler(char k)
{
	kkey = k;
	int cx = cursorX - pageOffsetX,
		cy = cursorY - pageOffsetY;
	if (cstate)
		for (int i = 0; i < 16; i++)
		{
			ScreenPoint * p = (uint)w->video + cx * 8 * 3 + (cy) * 16 * width * 3 + i * width * 3;
			//printTextToWindow(2,w,"\n%x %x",w->video,p);
			p->b ^= 255;
			p->g ^= 255;
			p->r ^= 255;
		}
	cstate = 0;
	updateCursor();
	if(k==0x27)
		cursorX++;
	if(k==0x25){
		cursorX = max(0, cursorX - 1);
		updateCursor();
	}

}

unsigned char openFile(char * fname)
{
	curFile = fopen(fname, "r");
	if (!curFile)
	{
		printTextToWindow(1, w, "No input file found, press\
		Y to create, whatever else for exit\n");
		while (!kkey) Wait(1);
		if (kkey == 'Y' || kkey == 'y')
		{
			curFile = fopen(fname, "w");
			fclose(curFile);
			curFile = fopen(fname, "r");
			return 1;
		}
		else {
			return 0;
		}
	}
	else return 1;
}
void MoveLeft(int k)
{
	for (int i = 0; i < pageSizeY; i++)
	{
		for (int j = 0; j < 16; j++)
			memcpy((uint)w->video + (i * 16 + j) * 3 * width, (uint)w->video + (i * 16 + j) * 3 * width + k * 3 * 8, (pageSizeX - k) * 3 * 8);
	}
	for (int i = 0; i < pageSizeY; i++)
	{
		for (int j = 0; j < 16; j++)
			memset((uint)w->video + (i * 16 + j) * 3 * width + (pageSizeX - k) * 3 * 8, 0, k * 3 * 8);
	}
	int cy = 0;
	line * l = text;
	int ccx = w->cursorX;
	int ccy = w->cursorY;
	w->cursorY= 0;
	while(l&&cy<pageOffsetY)
		l=l->next;
	while (l)
	{
		w->cursorX = (pageSizeX - k);
		w->cursorY = cy - pageOffsetY;
		printTextToWindow(7,w,"%.6s", l->text+ min(l->length, pageOffsetX + pageSizeX - k));
		
		cy++;
		l=l->next;
		if (cy == pageOffsetY + pageSizeY)
			break;
	}
	w->cursorX = ccx;
	w->cursorY = ccy;
}
void MoveRight(int k)
{
	for (int i = 0; i < pageSizeY; i++)
	{
		for (int j = 0; j < 16; j++)
			memcpy1((uint)w->video + (i * 16 + j) * 3 * width + k * 3 * 8, (uint)w->video + (i * 16 + j) * 3 * width, (pageSizeX - k) * 3 * 8);
	}
	for (int i = 0; i < pageSizeY; i++)
	{
		for (int j = 0; j < 16; j++)
			memset((uint)w->video + (i * 16 + j) * 3 * width, 0, k * 3 * 8);
	}
	
	int cy = 0;
	line * l = text;
	int ccx = w->cursorX;
	int ccy = w->cursorY;
	w->cursorY= 0;
	while(l&&cy<pageOffsetY)
		l=l->next;
	while (l)
	{
		w->cursorX = 0;
		w->cursorY = cy - pageOffsetY;
		printTextToWindow(7,w,"%.6s", l->text+ min(l->length, pageOffsetX-k));
		
		cy++;
		l=l->next;
		if (cy == pageOffsetY + pageSizeY)
			break;
	}
	w->cursorX = ccx;
	w->cursorY = ccy;
	
}
void updateCursor()
{
	int cx = cursorX - pageOffsetX,
		cy = cursorY - pageOffsetY;
	int lpox = pageOffsetX;
	int lpoy = pageOffsetY;

	if (cx * 8 >= width - 16) {
		pageOffsetX += 6;
		MoveLeft(6);
	}
	if(cx<0)
	{
		MoveRight(min(6,pageOffsetX));
		pageOffsetX-=min(6,pageOffsetX);
		cx=0;
	}
	cx = cursorX - pageOffsetX;
	if (cy * 16 >= height - 32)
		pageOffsetY += 6;
	cy = cursorY - pageOffsetY;
	//w->cursorX = cx;
	//w->cursorY = cy;

}

int strlen(char * ss)
{
	int k = 0;
	char * s=ss;
	while (s&&*s)
	{
		s++;
		k++;
	}
	return k;
}

void InsertLine(char * linee)
{
	if (!text)
	{
		line * l = (line*)malloc(sizeof(line));
		l->next = 0;
		l->length = strlen(linee);
		l->text = malloc(l->length+1);
		memcpy(l->text, linee, l->length);
		text = l;
	}
	else
	{
		line * l = text;
		while (l->next) l = l->next;
		line * ll = (line*)malloc(sizeof(line));
		ll->next = 0;
		ll->length = strlen(linee);
		ll->text = malloc(ll->length+1);
		memcpy(ll->text, linee, ll->length);
	
		l->next = ll;
	}
}

void LoadFile()
{
	fseek(curFile, 0, 2);
	int sz = ftell(curFile);
	rewind(curFile);
	int cpos = 0;
	char * cline = 0;
	int curLen = 0, llen = 0;
	while (cpos != sz)
	{
		char buf[1028];
		int cnt = min(cpos + 1028, sz) - cpos;
		fread(&buf, cnt, 1, curFile);
		cpos += cnt;
		for (int i = 0; i < cnt; i++)
		{

			if (curLen - llen > 1023)
			{
				char * f = malloc(curLen + 1028);
				memcpy(f, cline, curLen+1);
				free(cline);
				llen = curLen;
				cline = f;
			}
			if (!cline)
			{
				cline = malloc(1028);
				curLen = 0; llen = 0;
			}
			if (buf[i] == 10)
			{
				InsertLine(cline);
				free(cline);
				cline = 0;
				curLen = 0;
				llen = 0;
			} else
			{
				
			cline[curLen] = buf[i];
			curLen++;
			}
		}
		
	}
	InsertLine(cline);
	if(cline)
	free(cline);
}
void redraw()
{
	BarVideo(0, 0, width - 1, height - 1, 0xFFFFFF,
		width, height, w->video);
	BarVideo(0, 20, width - 1, 22, 0x64B5F6,
		width, height, w->video);

}
void outText()
{
	w->cursorX = 0;
	w->cursorY = 0;
	int cy = 0;
	line * l = text;
	while(l&&cy<pageOffsetY)
		l=l->next;
	while (l)
	{
		printf("%.90s", l->text + pageOffsetX);
		cy++;
		l=l->next;
		if (cy == pageOffsetY + pageSizeY)
			break;
	}
}
void _main(int argc, char ** argv)
{
	w = openWindow(720, 480, 1, &handle, "Notepad--");
	//printTextToWindow(2,w,"qq");
	width = 720;
	height = 480;
	pageSizeX = width / 8;
	pageSizeY = (height / 16) - 1;
	pageOffsetX = 0;
	cursorX=0;
	pageOffsetY = 0;
	if (argc)
		if (!openFile(argv[0]))
		{
			closeWindow(w);
			return;
		};
	//redraw();
	LoadFile();
	outText();
	if (curFile)
	{

	}
	int lastUpdate = 0;
	for (;;)
	{

		//updateCursor();
		w->updating = 1;
		char c = getKey();
		if(c)
			KeyHandler(c);
		int cx = cursorX - pageOffsetX,
			cy = cursorY - pageOffsetY;
		if(lastUpdate - (*sec100)>500){
			lockTaskSwith(1);
			cstate = 1 - cstate;
			for (int i = 0; i < 16; i++)
			{
				ScreenPoint * p = (uint)w->video + cx * 8 * 3 + (cy) * 16 * width * 3 + i * width * 3;
				//printTextToWindow(2,w,"\n%x %x",w->video,p);
				p->b ^= 255;
				p->g ^= 255;
				p->r ^= 255;
			}
			lastUpdate = *sec100;
			BarVideo(width - 8 * 20, height - 16, width, height, 0, width, height, w->video);
			int lx = w->cursorX;
			int ly = w->cursorY;
			w->cursorX = pageSizeX - 20;
			w->cursorY = pageSizeY;
			printTextToWindow(3, w, "Pos: %04d:%04d", cursorX, cursorY);
			w->cursorX = lx;
			w->cursorY = ly;
			unlockTaskSwith();
		}
		w->updating = 0;
		Wait(1);
	};
}