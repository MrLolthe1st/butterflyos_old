#include "..\includes\executable.c"
#include "..\includes\stdio.h"
#include "..\includes\structs.h"
#include "..\includes\forms.h"
#include "..\includes\windowsEventsCodes.h"

void KeyHandler(char k);
FILE * curFile;
typedef struct _line{
	char * text;
	struct _line * next;
	int length;
} line;
line * text = 0;
Window * w;
char kkey = 0;

typedef struct {
	unsigned char b;
	unsigned char g;
	unsigned char r;
} ScreenPoint;
int width,height;
int cursorX = 0, cursorY = 0, pos = 0, cstate = 0,
	pageOffsetY = 0, pageOffsetX = 0, pageSizeX = 0,
	pageSizeY = 0, lastCursorUpdate = 0;
void handle(WindowEvent * z)
{
	if(z->code==WINDOWS_KEY_DOWN)
	{
		KeyHandler (*((char*)z->data));
	}
}
void KeyHandler(char k)
{
	lockTaskSwitch(1);
	kkey=k;
	int cx = cursorX - pageOffsetX,
		cy = cursorY - pageOffsetY;
	if(cstate)
	for(int i=0;i<16;i++)
	{
		ScreenPoint * p = (uint)w->video + cx * 8 * 3 + (cy) * 16 * width * 3 + i* width * 3;
		//printTextToWindow(2,w,"\n%x %x",w->video,p);
		p->b^=255;
		p->g^=255;
		p->r^=255;
	}
	cstate=0;
	updateCursor();
	cursorX++;
	unlockTaskSwitch();
	
}

unsigned char openFile(char * fname)
{
	curFile = fopen(fname,"r");
	if(!curFile)
	{
		printTextToWindow(1,w,"No input file found, press\
		Y to create, whatever else for exit\n");
		while(!kkey) Wait(1);
		if(kkey=='Y'||kkey=='y')
		{
			curFile = fopen(fname,"w");
			fclose(curFile);
			curFile = fopen(fname,"r");
			return 1;
		} else {
			return 0;
		}
	} else return 1;
}
void MoveLeft(int k)
{
	for(int i=0; i<pageSizeY;i++)
	{
		for(int j=0;j<16;j++)
		memcpy((uint)w->video + (i*16 + j)*3*width,(uint)w->video + (i*16 +j)*3*width + k*3*8, (pageSizeX-k)*3*8);
	}
	for(int i=0; i<pageSizeY;i++)
	{
		for(int j=0;j<16;j++)
			memset((uint)w->video + (i*16+j)*3*width + k*3*8, 0, k*3*8);
	}
}
void MoveRight(int k)
{
	for(int i=0; i<pageSizeY;i++)
	{
		for(int j=0;j<16;j++)
			memcpy1((uint)w->video + (i*16 +j)*3*width + k*3*8,(uint)w->video + (i*16 + j)*3*width, (pageSizeX-k)*3*8);
	}
	for(int i=0; i<pageSizeY;i++)
	{
		for(int j=0;j<16;j++)
			memset((uint)w->video + (i*16+j)*3*width, 0, k*3*8);
	}
}
void updateCursor()
{
	int cx = cursorX - pageOffsetX,
		cy = cursorY - pageOffsetY;
	int lpox = pageOffsetX;
	int lpoy = pageOffsetY;
		
	if (cx * 8 >= width - 16){
		pageOffsetX += 6;
		MoveLeft(6);
	}	
	cx = cursorX - pageOffsetX;
	if (cy * 16 >= height - 32)
		pageOffsetY += 6;
	cy = cursorY - pageOffsetY;
	w->cursorX = cx;
	w->cursorY = cy;
	
}
int min(int a, int b)
{
	return a<b?a:b;
}

int strlen(char * s)
{
	int k=0;
	while(s&&*s)
	{
		s++;
		k++;
	}
	return k;
}

void InsertLine(char * linee)
{
	
	if(!text)
	{
		line * l = (line*) malloc(sizeof(line));
		l->next=0;
		l->text = linee;
		l->length = strlen(linee);
		text=l;
	} else
	{
		line * l = text;
		while(l->next) l=l->next;
		line * ll = (line*) malloc(sizeof(line));
		ll->next=0;
		ll->text = linee;
		ll->length = strlen(linee);
		l->next = ll;
	}
}

void LoadFile()
{
	fseek(curFile,0,2);
	int sz = ftell(curFile);
	rewind(curFile);
	int cpos = 0;
	char * cline = 0;
	int curLen = 0, llen = 0;
	while(cpos!=sz)
	{
		char buf[1028];
		int cnt = min(cpos + 1028, sz) - cpos;
		fread(&buf, cnt, 1, curFile);
		cpos+=cnt;
		for(int i = 0;i<cnt;i++)
		{
			
			if(curLen-llen>1023)
			{
				char * f= malloc(curLen + 1028);
				memcpy(f, cline, curLen);
				free(cline);
				llen=curLen;
				cline=f;
			}
			if(!cline)
			{
				cline=malloc(1024);
				curLen=0;llen = 0;
			}
			cline[curLen] = buf[i];
			curLen++;
			if(buf[i]==10)
			{
				InsertLine(cline);
				free(cline);
				cline = 0;
				curLen=0;
				llen = 0;
			}
		}
	}
	InsertLine(cline);
}
void redraw()
{
	BarVideo(0,0,width-1,height-1,0xFFFFFF, 
			width,height,w->video);
	BarVideo(0,20,width-1,22,0x64B5F6,
			width,height,w->video);
	
}
void outText()
{
	int cy = 0;
	line * l = text;
	while(l)
	{
		printf("%.90s",l->text);
		cy++;
		if(cy=pageSizeY)
			break;
	}
}
void _main(int argc, char ** argv)
{	
	w = openWindow(720,480,1,&handle,"Notepad--");
	//printTextToWindow(2,w,"qq");
	width = 720;
	height = 480;
	pageSizeX = width / 8;
	pageSizeY = height / 16;
	if(argc)
		if(!openFile(argv[0]))
		{
			closeWindow(w);
			return;
		};
	//redraw();
	LoadFile();
	outText();
	printTextToWindow(4,w,"123456789\n123456789\n");
	if(curFile)
	{
		
	}
	for(;;)
	{
		
		//updateCursor();
		int cx = cursorX - pageOffsetX,
		cy = cursorY - pageOffsetY;
		lockTaskSwitch(1);
		cstate = 1 - cstate;
		for(int i=0;i<16;i++)
		{
			ScreenPoint * p = (uint)w->video + cx * 8 * 3 + (cy) * 16 * width * 3 + i* width * 3;
			//printTextToWindow(2,w,"\n%x %x",w->video,p);
			p->b^=255;
			p->g^=255;
			p->r^=255;
		}
		unlockTaskSwitch();
		Wait(50);
	};
}