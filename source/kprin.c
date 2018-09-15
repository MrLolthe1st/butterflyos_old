

char tbuf[32];
char bchars[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };

void __itoa(unsigned i, unsigned base, char* buf) {
	int pos = 0;
	int opos = 0;
	int top = 0;

	if (i == 0 || base > 16) {
		buf[0] = '0';
		buf[1] = '\0';
		return;
	}

	while (i != 0) {
		tbuf[pos] = bchars[i % base];
		pos++;
		i /= base;
	}
	top = pos--;
	for (opos = 0; opos < top; pos--, opos++)
		buf[opos] = tbuf[pos];
	buf[opos] = 0;
}

void __itoa_s(int i, unsigned base, char* buf) {
	if (base > 16) return;
	if (i < 0) {
		*buf++ = '-';
		i *= -1;
	}
	__itoa(i, base, buf);
}
int __qkprintf(const char* str, ...) {
	if (!str)
		return 0;
	va_list ap;
	va_start(ap, str);
	__kprintf_va_list((char *)str, ap);
	return 1;
}

int kprintf(const char* str, ...) {
	if (!str)
		return 0;
	va_list ap;
	va_start(ap, str);
	__kprintf_va_list((char *)str, ap);
	return 1;
}
//Gets formatted string length
int formattedLength(char* str, va_list ap)
{
	int a = 0;
	char * s = 0;
	for (size_t i = 0; i < 4096; i++)
	{
		if (str[i] == 0) break;
		if (str[i] == '%')
		{
			switch (str[i + 1])
			{
				/** string **/
			case 's':
				s = va_arg(ap, char*);
				while (*s != 0) { a++; s++; }
				i++;
				continue;
				/** decimal **/
			case 'd': {
				int c = va_arg(ap, int);
				char str[32] = { 0 };
				__itoa_s(c, 10, str);
				char * s = &str;
				while (*s != 0) { a++; s++; };
				i++;
				continue;
			}
			case 'x': {
				int c = va_arg(ap, int);
				char str[32] = { 0 };
				__itoa(c, 16, str);
				char * s = &str;
				while (*s != 0) { a++; s++; };
				i++;
				continue;
			}
					  /** character **/
			case 'c': {
				// char gets promoted to int for va_arg!
				// clean it.
				char c = (char)(va_arg(ap, int) & ~0xFFFFFF00);
				a++;
				i++;
				continue;
			}
			default:
				break;
			}
		}
		else {
			a++;
		}
	}
	return a;
}
void _abc()
{

}

//Format and Print to the text mode screen using video.c
void __kprintf_va_list(char* str, va_list ap)
{
	//mutex_lock(&m_kprintf);
	char* s = 0;
	//cd->putc('c');
	for (size_t i = 0; i < 4096; i++)
	{
		if (str[i] == 0) break;
		if (str[i] == '%')
		{
			switch (str[i + 1])
			{
				/** string **/
			case 's':
				s = va_arg(ap, char*);
				printString(s);
				i++;
				continue;
				/** decimal **/
			case 'd': {
				int c = va_arg(ap, int);
				char str[32] = { 0 };
				__itoa_s(c, 10, str);
				printString(str);
				i++;
				continue;
			}
			case 'x': {
				int c = va_arg(ap, int);
				char str[32] = { 0 };
				__itoa(c, 16, str);
				printString(str);
				i++;
				continue;
			}
					  /** character **/
			case 'c': {
				// char gets promoted to int for va_arg!
				// clean it.
				char c = (char)(va_arg(ap, int) & ~0xFFFFFF00);
				printChar(c);
				i++;
				continue;
			}
			default:
				break;
			}
		}
		else {
			printChar(str[i]);
		}
	}
	va_end(ap);
}