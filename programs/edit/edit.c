#include "..\includes\executable.c"
#include "..\includes\stdio.h"
#include "..\includes\structs.h"
#include "..\includes\forms.h"
#include "..\includes\windowsEventsCodes.h"

void KeyHandler(char k);
FILE * curFile;
Window * w;
char kkey = 0;
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
}

unsigned char openFile(char * fname)
{
	curFile = fopen(fname,"r");
	if(!curFile)
	{
		printTextToWindow(1,w,"No input file found, press Y to create, whatever else for exit\n");
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
int width,height;
void redraw()
{
	BarVideo(0,0,width-1,height-1,0xFFFFFF,width,height,w->video);
	BarVideo(0,20,width-1,22,0x64B5F6,width,height,w->video);
	
}
int cursorX = 0, cursorY = 0, pos = 0;
void _main(int argc, char ** argv)
{	
	w = openWindow(720,480,1,&handle,"Notepad--");
	width = 720;
	height = 480;
	if(argc)
		if(!openFile(argv[0]))
		{
			closeWindow(w);
			return;
		};
	redraw();
	for(;;)
	{
		Wait(1);
	};
}