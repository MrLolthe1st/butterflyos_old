#include "includes\executable.c"
#include "includes\structs.c"
#include "includes\forms.h"
#include "includes\stdio.h"
Window *w;char * q=0, ii=0;
void qq(WindowEvent * a)
{
	printTextToWindow(6, w, "Event!");
}
void _main()
{
	q = malloc(10);
	q[0]=' ';
	q[1]='%';
	q[2]='x';
	q[3]='\n';
	q[4]=0;
	w = openWindow(300,100,0,&qq,"abcde");
	printTextToWindow(6, w, q,&qq);
	int i=0, o;
	//for(;;);
}