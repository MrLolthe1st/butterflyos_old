#define size_t unsigned int

void memcpy(unsigned char * s, unsigned char * d, unsigned int count);
void memset(void * addr, char s, unsigned int count);

int strlen(char * ss)
{
	int k = 0;
	char * s = ss;
	while (s&&*s)
	{
		s++;
		k++;
	}
	return k;
}