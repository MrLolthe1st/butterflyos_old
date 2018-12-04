
int screenWidth = 80, screenHeight = 25;
char * videoMem = (char*)0xB8000;
int cursor = 0x0;
char attr = 0x0A;
char table[16] = "0123456789ABCDEF";
void clearScreen()
{
	for (int i = 0; i < screenWidth * screenHeight; i++)
	{
		printChar(' ');
	}
}


void move_cursor(int x, int y)
{
	int cursorLocation = y * 80 + x;
	outportb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
	outportb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
	outportb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
	outportb(0x3D5, cursorLocation);      // Send the low cursor byte.
}
void scroll()
{
	for (int i = 0; i < screenHeight - 1; i++)
	{
		for (int j = 0; j < 160; j++)
		{
			*(videoMem + 160 * (i)+j) = *(videoMem + 160 * i + 160 + j);
		}
	}
	for (int i = 0; i < 160 * 2; i += 2)
	{
		*(videoMem + 24 * 160 + i) = 0;
		*(videoMem + 24 * 160 + i + 1) = attr;
	}
	cursor -= 160;
}
void setCursor(int u)
{
	cursor = u;
	move_cursor((cursor % 160 / 2), cursor / 160);
}
void printChar(char s)
{
	int lc = cursor;
	if (s == 0) return;
	if (s == 8) { cursor -= 2; *(videoMem + cursor) = ' '; move_cursor(((cursor % 160) / 2), cursor / 160); return; }
	if (s == 9) {
		*(videoMem + cursor) = ' '; *(videoMem + cursor + 2) = ' '; *(videoMem + cursor + 4) = ' '; cursor += 8;
		*(videoMem + cursor + 6) = ' '; move_cursor(((cursor % 160) / 2), cursor / 160); return;
	}
	if (s == 13 || s == 10) { cursor = ((cursor / (screenWidth * 2)) + 1) * screenWidth * 2; if (cursor / 160 >= screenHeight) scroll(); move_cursor(((cursor % 160) / 2), cursor / 160); return; }
	if (lc / 160 < (lc + 2) / 160 && (lc + 2) / 160 > 24)scroll();
	//if(lc/160<(lc+2)/160)scroll();

	*(videoMem + cursor++) = s;
	*(videoMem + cursor++) = attr;
	move_cursor(((cursor % 160) / 2) + 1, cursor / 160);
}
void printInt(unsigned int x, char digCount)
{
	int i = 0; int pow = 1;
	for (i = 0; i < digCount - 1; i++)
		pow *= 10;
	for (i = 0; i < digCount; i++)
	{
		char z = (x / pow) % 10;
		printChar(0x30 + z);
		pow /= 10;
	}
}
void printString(char *s)
{
	int i = 0;
	while (s[i] != 0)
	{
		printChar(s[i]);
		if ((s[i] == 13 && s[i + 1] == 10) || (s[i] == 10) && (s[i + 1] == 13))
			i++;
		//if (s[i]==13||s[i]==10) i++;

		i++;
	}
}
void panic(char * s)
{
	attr = 0x4E;
	printString(s);
	for (;;) {};
}
void printHex(unsigned long long a, char bytesCount)
{
	int shr = (bytesCount * 2 - 1) * 4;
	for (int i = 0; i < bytesCount * 2; i++)
	{
		char cur = (a >> shr) & 0x0F;
		printChar(table[cur]);
		shr -= 4;
	}
}
void setAttr(char at)
{
	attr = at;
}
void GotoXY(char x, char y)
{
	cursor = screenWidth * y * 2 + 2 * x;
}




