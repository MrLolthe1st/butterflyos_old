
#include "..\includes\stdio.h"
#include "..\includes\structs.h"
#include "..\includes\forms.h"
#include "..\includes\windowsEventsCodes.h"
#define buf_size 165536
void main(int argc, char ** argv)
{	

	if(argc!=3){
		printf("COPY: Use: copy <filename>|<directory> <filename>|<directory>\n");
		return;
	}
	FILE * z = fopen(argv[1],"rb");
	if(!z)
	{
		printf("Can't find input file %s!\n", argv[1]);
		return;
	}
	FILE * u = fopen(argv[2],"wb");
	if(!u)
	{
		printf("Can't create file to write %s!\n", argv[2]);
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
