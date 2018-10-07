#include "..\includes\executable.c"
#include "..\includes\stdio.h"
#include "..\includes\structs.h"
#include "..\includes\forms.h"
#include "..\includes\windowsEventsCodes.h"
#define buf_size 16384
void handle(int a)
{
	
}
void _main(int argc, char ** argv)
{	

	if(argc!=2)
		return;
	Window * w = openWindow(200,100,0,&handle,"Copying files");
	FILE * z = fopen(argv[0],"r");
	FILE * u = fopen(argv[1],"w");
	fseek(z,0,2);
	uint sz = ftell(z);
	rewind(z);
	char * buf = malloc(buf_size);
	
	for(uint i=0;i<=sz/buf_size;i++)
	{
		if((sz-i*buf_size)<buf_size)
		{
			fread(buf,sz-i*buf_size,1,z);
		
			fwrite(buf,sz-i*buf_size,1,u);
		} else{
			fread(buf,buf_size,1,z);
			fwrite(buf,buf_size,1,u);
		}
		printTextToWindow(2,w,"%d done!\n",(int)(i*1.0/(sz*1.00/buf_size*1.0)*100.0));
	}
	closeWindow(w);
	free(buf);
	fclose(z);
	fclose(u);
	
}
