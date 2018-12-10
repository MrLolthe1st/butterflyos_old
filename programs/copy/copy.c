#include "..\includes\executable.c"
#include "..\includes\stdio.h"
#include "..\includes\structs.h"
#include "..\includes\forms.h"
#include "..\includes\windowsEventsCodes.h"
#define buf_size 65536
void _main(int argc, char ** argv)
{	

	if(argc!=2)
		return;
	
	FILE * z = fopen(argv[0],"r");
	FILE * u = fopen(argv[1],"w");
	if(!z)
	{
		printf("Can't find file %s!\n", argv[0]);
		return;
	}
	fseek(z,0,2);
	uint sz = ftell(z);
	rewind(z);
	char * buf = malloc(buf_size);
	int k=0;
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
		
		int kk=k;
		if(i>0)
		{
			for(int oo=0;oo<6;oo++)
				printf("%c", 8);
			while(k>0||k==0)
			{
				printf("%c",8);
				k/=10;
				if(k==0)
					break;
			}
		}
		k=(int)((i+1)*1.0/(sz*1.00/buf_size*1.0)*100.0);
		if(k>100)
			k=100;
		printf("%d done!",k);
	}
	free(buf);
	fclose(z);
	fclose(u);
	
}
