#include "..\includes\executable.c"
#include "..\includes\stdio.h"
#include "..\includes\structs.h"
#include "..\includes\forms.h"
#include "..\includes\windowsEventsCodes.h"

typedef struct _tl
{
	struct _tl * left, * down;
	char * buf;
} TextLine;
TextLine * fl;
void KeyHandler(char k);
FILE * curFile;
Window * w;
char kkey = 0;

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
	kkey=k;
	lockTaskSwitch(1);
	if(cstate)
		updateCursor();
	cstate = 0;
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
typedef struct{
	unsigned char b;
	unsigned char g;
	unsigned char r;
} ScreenPoint;
void updateCursor()
{
	int cx = cursorX - pageOffsetX,
		cy = cursorY - pageOffsetY;
	if (cx * 8 >= width)
		pageOffsetX += 2;
	cx = cursorX - pageOffsetX;
	if (cy * 16 >= height)
		pageOffsetY += 2;
	cy = cursorY - pageOffsetY;
	cstate = 1 - cstate;
	for(int i=0;i<16;i++)
	{
		ScreenPoint * p = (uint)w->video + 22*3*width + cx * 8 * 3 + (cy) * 16 * width * 3 + i* width * 3;
		//printTextToWindow(2,w,"\n%x %x",w->video,p);
		p->b^=255;
		p->g^=255;
		p->r^=255;
	}
	
}
void FillWithTextAt(char * ln, TextLine * op, TextLine * lineStart)
{
	TextLine * lsz = lineStart;
	char * ss = op->buf;
	int i=0;
	while(*ln)
	{
		if(*ln == 10)
		{
			lsz->down = malloc(sizeof(TextLine));
			lsz->down->buf=malloc(512);
			lsz->down->left=0;
			op=lsz->down;
			ss=lsz->down->buf;
			lsz=lsz->down;
			i=0;
			continue;
		}
		*ss=*ln;
		i++;
		if(i==256)
		{
			op->left = malloc(sizeof(TextLine));
			op->left->buf=malloc(512);
			ss=op->left->buf;
			op=op->left;
			op->down=0;
			op->left=0;
			i=0;
		}
		++ln;
		++ss;
	}
}
void * strend(char * ln)
{
	while(*ln)
		++ln;
	return ln;
}
void InsertText(char * ln, int pos)
{
	int inslen = (uint)strend(ln)-(uint)ln;
	TextLine * p = fl;
	if(!fl)
	{
		fl = malloc(sizeof(TextLine));
		fl->down=0;
		fl->buf = malloc(512);
		fl->left=0;
		p=fl;
	}
	int cpos = 0,ccpos=0;
	TextLine * pz=p;
	while(cpos<=pos&&p)
	{
		pz = p;
		while(p)
		{
			cpos+=(uint)strend(p->buf)-(uint)p->buf;
			if(cpos>=pos) break;
			p=p->left;
			ccpos=cpos;
		}
		if(cpos>=pos) break;
		p=pz->down;
	}
	if(512-((uint)strend(p->buf)-(uint)p->buf)>=inslen)
	{
		//memccpy((uint)p->buf+ccpos++inslen,(uint)p->buf+pos-ccpos+inslen,
		memcpy((uint)p->buf+pos-ccpos+inslen,(uint)p->buf+pos-ccpos,(uint)strend(p->buf)-(uint)p->buf-(pos-ccpos));
		memcpy((uint)p->buf+pos-ccpos,ln,inslen);
	} else
	if(!p->left)
	{
		TextLine * u = malloc(sizeof(TextLine));
		u->left=0;
		u->down=0;
		u->buf=malloc(512);
		p->left=u;
		FillWithTextAt(ln, u, pz);
	}
	
}

void AddTextToLine(int k, char * ln)
{
	
}

void InsertLineAfter(int k, char * ln)
{
	
}

void LoadFile()
{
	fseek(curFile,0,2);
	int sz = ftell(curFile);
	rewind(curFile);
	
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
	TextLine * z =fl, *pz=fl;
	while(z)
	{
		pz=z;
		while(z)
		{
			printTextToWindow(1,w,z->buf);
			z=z->left;
		}
		z=pz->down;
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
	fl=0;
	redraw();
	InsertText("abcde",0);
	InsertText("aebcde",1);
	outText();
	
	if(curFile)
	{
		
	}
	for(;;)
	{
		
		updateCursor();
		Wait(100);
	};
}