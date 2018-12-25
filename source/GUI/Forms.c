//refactor it

#define COLOR_PURPLE 0x6A1B9A
#define COLOR_RED 0xC62828
#define COLOR_BLUE 0x1565C0
#define COLOR_GREEN 0x81C784
#define COLOR_AQUA 0xB3E5FC
#define COLOR_YELLOW 0xFFEB3B
#define COLOR_WHITE 0xE0E0E0

// ------------------------------------------------------------------------------------------------
const unsigned int colors[] = {
	0,
	COLOR_BLUE,
	COLOR_GREEN,
	COLOR_AQUA,
	COLOR_RED,
	COLOR_PURPLE,
	COLOR_YELLOW,
	COLOR_WHITE
};

int startX = 30;
int startY = 30;		//Window cascade start
int windowsCount = 0; 	//Count, useless
unsigned int cid = 1; 	//Window id's


// ------------------------------------------------------------------------------------------------
IDT_HANDLER(videoService)
{
	unsigned int eax = 0, ebx = 0, ecx = 0, edx = 0, esi = 0, edi = 0;
	__asm__("mov %%eax,%0 \n mov %%ebx,%1 \n mov %%ecx,%2 \n mov %%edx,%3 \n mov %%esi, %4 \n mov %%edi, %5":"=r"(eax), "=r"(ebx), "=r"(ecx), "=r"(edx), "=r"(esi), "=r"(edi) : );
	if (eax == 0)
	{
		//Open window
		//In: eax = 0, ebx - window width, ecx = window height, edx = window type, esi - handler address, edi - window caption(ACIIZ)

	}
}

char * ico = 0;
char * ico_big = 0;
char * menu = 0;
char * ico_path = "A:\\IMG\\std_ico.bmp";
char * menu_path = "A:\\IMG\\menu.bmp";
// ------------------------------------------------------------------------------------------------
void initWindows()
{
	ico_path[0] += bootedFrom;
	menu_path[0] += bootedFrom;
	ico = getBmpAndScaleIt(ico_path, 16, 16);
	menu = getBmpAndScaleIt(menu_path, 30, 30);
	ico_big = getBmpAndScaleIt(ico_path, 30, 30);
}

// ------------------------------------------------------------------------------------------------
//Draws desktop
void drawDesktop()
{
	//Draw background
	//CopyToVMemory(0, 0, width, height - 32, cat);
	Bar(0, 0, width - 1, height - 1, 0xFFFFFF);
	//Task Panel
	Bar(0, height - 34, width - 1, height - 1, 0x01579B);
	//Some text...
	OutTextXY(width - 270, height - 19 - 32, "ButterflyOS stable build 0.1.2.0", 0xDD2C00, 1);
}


// ------------------------------------------------------------------------------------------------
void printChars(unsigned char color, Window * w, char * text)
{
	switch (*text) {
	case 8:
		//Backspace
		w->cursorX--;
		//Cursor out of bounds by X
		if (w->cursorX < 0)
		{
			//Cursor to end of line and...
			w->cursorX = w->wwidth / 8 - 1;
			//Up onto one line
			w->cursorY--;
			//Cursor out of bounds by Y?
			if (w->cursorY < 0)
			{
				//Cursor to start of video memory of the window
				w->cursorX = 0;
				w->cursorY = 0;
			}
		}
		//Draw space where was symbol
		drawcharvf(' ', w->cursorX * 8, w->cursorY * 16, colors[color], 1, w->wwidth, w->wheight, w->video);
		//Goto next character in string
		text++;
		return;

	case 9:
	{
		//Tabulation
		w->cursorX += 4;
		text++;
		return;
	};
	case 10:
	{
		//Enter
		//Goto line start
		w->cursorX = 0;
		//Next line
		w->cursorY++;
		//Next character in string
		text++;
		//Overflow
		if (w->cursorY == w->wheight / 16)
		{
			//Scroll memory up
			memcpy(w->video, w->video + 16 * w->wwidth * 3, (w->wheight - 16)*w->wwidth * 3);
			//Zero last line
			memset(w->video + (w->wheight - 16)*w->wwidth * 3, 0, 16 * w->wwidth * 3);
			//Back to last line
			w->cursorY--;
		}
		return;
	};
	}
	//Draw char from string
	drawcharv(*text, w->cursorX * 8, w->cursorY * 16, colors[color], 1, w->wwidth, w->wheight, w->video);
	//Goto next character
	text++;
	//Next symbol at line
	w->cursorX++;
	//Bound cursor
	w->cursorY = w->cursorY + (w->cursorX / (w->wwidth >> 3));
	w->cursorX = w->cursorX % (w->wwidth >> 3);
	//Overflow
	if (w->cursorY == w->wheight / 16)
	{
		//Scroll memory up
		memcpy(w->video, w->video + 16 * w->wwidth * 3, (w->wheight - 16)*w->wwidth * 3);
		//Zero last line
		memset(w->video + (w->wheight - 16)*w->wwidth * 3, 0, 16 * w->wwidth * 3);
		//Back to last line
		w->cursorY--;
	}
}

// ------------------------------------------------------------------------------------------------
//Formats string
char* formatString(char* str, va_list ap)
{
	char * t = mmalloc(4096);
	char * l = t;
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
			case 's': {
				s = va_arg(ap, char*);
				while (*s != 0) { *t = *s; t++; s++; };
				i++;
				continue;

			}
					  /** decimal **/
			case 'd': {
				int c = va_arg(ap, int);
				char str[32] = { 0 };
				__itoa_s(c, 10, str);
				char * s = &str;
				while (*s != 0) { *t = *s; t++; s++; };
				i++;

				continue;
			}
			case 'x': {
				int c = va_arg(ap, int);
				char str[32] = { 0 };
				__itoa(c, 16, str);
				char * s = &str;
				while (*s != 0) { *t = *s; t++; s++; };
				i++;
				continue;
			}
					  /** character **/
			case 'c': {
				// char gets promoted to int for va_arg!
				// clean it.
				char c = (char)(va_arg(ap, int) & ~0xFFFFFF00);
				*t++ = c;
				i++;
				continue;

			}
			}
		}
		else {
			*t = str[i];
			t++;
		}
	}
	*t++ = 0;
	return l;
}


// ------------------------------------------------------------------------------------------------
void printTextToWindowFormatted(unsigned char color, Window * w, char * text) {

	kprintf(text);

	//Window != zero
	if (w) {
		while (*text != 0) {
			//Cursor to bounds
			w->cursorY = w->cursorY + (w->cursorX / (w->wwidth >> 3));
			w->cursorX = w->cursorX % (w->wwidth >> 3);
			switch (*text) {
			case 8:
				//Backspace
				w->cursorX--;
				//Cursor out of bounds by X
				if (w->cursorX < 0)
				{
					//Cursor to end of line and...
					w->cursorX = w->wwidth / 8 - 1;
					//Up onto one line
					w->cursorY--;
					//Cursor out of bounds by Y?
					if (w->cursorY < 0)
					{
						//Cursor to start of video memory of the window
						w->cursorX = 0;
						w->cursorY = 0;
					}
				}
				//Draw space where was symbol
				drawcharvf(' ', w->cursorX * 8, w->cursorY * 16, colors[color], 1, w->wwidth, w->wheight, w->video);
				//Goto next character in string
				text++;
				continue;

			case 9:
			{
				//Tabulation
				w->cursorX += 4;
				text++;
				continue;
			};
			case 10:
			{
				//Enter
				//Goto line start
				w->cursorX = 0;
				//Next line
				w->cursorY++;
				//Next character in string
				text++;
				//Overflow
				if (w->cursorY == w->wheight / 16)
				{
					//Scroll memory up
					memcpy(w->video, w->video + 16 * w->wwidth * 3, (w->wheight - 16)*w->wwidth * 3);
					//Zero last line
					memset(w->video + (w->wheight - 16)*w->wwidth * 3, 0, 16 * w->wwidth * 3);
					//Back to last line
					w->cursorY--;
				}

				continue;
			};
			}
			//Draw char from string
			drawcharv(*text, w->cursorX * 8, w->cursorY * 16, colors[color], 1, w->wwidth, w->wheight, w->video);
			//Goto next character
			text++;
			//Next symbol at line
			w->cursorX++;
			//Bound cursor
			w->cursorY = w->cursorY + (w->cursorX / (w->wwidth >> 3));
			w->cursorX = w->cursorX % (w->wwidth >> 3);
			//Overflow
			if (w->cursorY == w->wheight / 16)
			{
				//Scroll memory up
				memcpy(w->video, w->video + 16 * w->wwidth * 3, (w->wheight - 16)*w->wwidth * 3);
				//Zero last line
				memset(w->video + (w->wheight - 16)*w->wwidth * 3, 0, 16 * w->wwidth * 3);
				//Back to last line
				w->cursorY--;
			}
		}
		//ffree(text);
	}

	w->updating = 0;
	w->cursorState = 1;
	w->lastUpdate = *sec100;
}


// ------------------------------------------------------------------------------------------------
//Print text to window
void printTextToWindow(unsigned char color, Window * w, char * text, ...) {

	char buf[1024];
	va_list args;

	va_start(args, text);
	vsnprintf(buf, sizeof(buf), text, args);
	va_end(args);
	printTextToWindowFormatted(color, w, buf);
}

// ------------------------------------------------------------------------------------------------
void updateWindows()
{
	//Redraws screen
	drawDesktop();
	char time[9];
	//Current time calculation
	int sec = (*sec100 / ticksPerSecond) % 60, min = (*sec100 / (60 * ticksPerSecond)) % 60, hour = (*sec100 / (3600 * ticksPerSecond)) % 24;
	time[0] = (hour / 10 % 10) + 48;
	time[3] = (min / 10 % 10) + 48;
	time[6] = (sec / 10 % 10) + 48;
	time[1] = (hour % 10) + 48;
	time[4] = (min % 10) + 48;
	time[7] = (sec % 10) + 48;
	time[2] = ':';
	time[5] = ':';
	time[8] = 0;
	OutTextXY(width - 74, height - 22, &time, 0xFFFFFF, 1);
	//__itoa(*sec100 % 1000, 10, &time);
	//OutTextXY(900, 746, &time, 0xFFFFFF, 1);
	Window * w = windows;
	//Active window is on top of windows list
	int cx = 0;
	if(menu)
		CopyToVMemoryTransparent1(10, height - 32, 30, 30, menu);
	while (w) {
		if (w->lastUpdate) {
			//Draw(w);
			//CopyToVMemory()
			if(ico_big)
				CopyToVMemory(60 + (cx * 34), height - 32, 30, 30, ico_big);
			cx++;
		}
		w = w->next;
	}
	w = windows;
	while (w) {
		if (w->lastUpdate) {
			Draw(w);
		}
		w = w->next;
	}

}


// ------------------------------------------------------------------------------------------------
//Close window by id
void closeWindowID(unsigned int id) {
	Window * w = windows;
	Window * prev = 0;
	//Iterate through all windows
	while (w) {
		if (w->id == id) {
			if (activeWindow == w->id) {
				if (prev)
					activeWindow = prev->id;
			}
			if (prev)
				prev->next = w->next;
			else
				windows = w->next;
			ffree(w->video);
			ffree(w);
			break;
		}
		prev = w;
		w = w->next;
	}
}


// ------------------------------------------------------------------------------------------------
//Close window 
void closeWindow(Window * ws) {
	if (!ws)
		return;
	Window * w = windows;
	Window * prev = 0;
	//Iterate through all windows
	while (w) {
		if (w->id == ws->id) {
			if (activeWindow == w->id) {
				if (prev)
					activeWindow = prev->id;
			}
			if (prev)
				prev->next = w->next;
			else
				windows = w->next;
			ffree(w->video);
			ffree(w);
			break;
		}
		prev = w;
		w = w->next;
	}
}

// ------------------------------------------------------------------------------------------------
void enableBuffering(Window * w)
{
	w->buffered = 1;
}


// ------------------------------------------------------------------------------------------------
void BufferWindow(Window * w)
{
	lockTaskSwitch(1);
	memcpy(w->videoOk, w->video, (w->wwidth) * (w->wheight) * 3);
	unlockTaskSwitch();
}

// ------------------------------------------------------------------------------------------------
//Opens a window
Window * openWindow(unsigned int wwidth, unsigned int wheight, unsigned int type, void * handler, char * caption) {
	//Allocate new window structure

	Window * win = (Window*)mmalloc(sizeof(Window));
	Window * node = windows;
	//Get active window pointer
	while (node != 0 && node->next != 0) node = node->next;
	win->lastUpdate = 0;
	if (node == 0) {
		//There aren't any windows!
		node = win;
		windows = node;
	}
	else node->next = win;

	win->next = 0;									//Next from us is zero!
	win->caption = caption;							//Caption pointer
	win->handler = (void*)handler;					//Event handler
	win->wwidth = wwidth;							//Window width
	win->wheight = wheight;							//Window height
	win->video = mmalloc(wwidth * (wheight) * 3);	//Video memory
	win->videoOk = mmalloc(wwidth * (wheight) * 3);	//Video memory
	win->type = (unsigned char)type & 0xFF;			//Type
	win->lastx = startX;							//Starting X
	win->lasty = startY;							//Starting Y
	win->id = cid++;								//Window Id
	win->buffered = 0;
	activeWindow = win->id;							//Activate current window
	win->cursorX = 0;								//Cursor X
	win->cursorY = 0;								//Cursor Y
	win->cursorState = 0;							//State
	win->x = startX;								//Starting X
	win->y = startY;								//Starting Y
	startX += 20;									//add 20 for 'cascade'
	startY += 20;
	if (currentRunning && procTable[currentRunning].stdin->w == procTable[procTable[currentRunning].runnedFrom].stdin->w)
	{
		attachIoToWindow(win);
	}
	win->updating = 0;
	win->lastUpdate = *sec100;						//Last time window updated
	if (startX > 200) startX = 30;
	if (startY > 200) startY = 30;
	windowsCount++;
	return win;										//Return window to user
}


// ------------------------------------------------------------------------------------------------
//NC
void Draw(Window * toDraw) {
	Bar(toDraw->x - 1, toDraw->y - 20, toDraw->x + toDraw->wwidth, toDraw->y, 0x1976D2);
	//BarV(0,0, 7,15, COLOR_BLUE, 1024, videoBuffer);
	if (toDraw->buffered == 1)
		CopyToVMemory(toDraw->x, toDraw->y, toDraw->wwidth, toDraw->wheight, toDraw->videoOk);
	else if (toDraw->buffered == 0)
		CopyToVMemory(toDraw->x, toDraw->y, toDraw->wwidth, toDraw->wheight, toDraw->video);
	Rect(toDraw->x - 1, toDraw->y - 1, toDraw->wwidth + 1, toDraw->wheight + 1, 0x1976D2);
	if (*sec100 - (toDraw->lastUpdate) > 10000 - cursorSpeed * 10) {
		toDraw->lastUpdate = *sec100;
		toDraw->cursorState = 1 - toDraw->cursorState;
	}
	if (toDraw->type == 0)
		if (toDraw->cursorState == 1)
			Bar(toDraw->x + toDraw->cursorX * 8, toDraw->y + toDraw->cursorY * 16, toDraw->x + toDraw->cursorX * 8 + 7, toDraw->y + toDraw->cursorY * 16 + 15, COLOR_BLUE);
		else
			Bar(toDraw->x + toDraw->cursorX * 8, toDraw->y + toDraw->cursorY * 16, toDraw->x + toDraw->cursorX * 8 + 7, toDraw->y + toDraw->cursorY * 16 + 15, 0);
	if(ico)
	CopyToVMemory(toDraw->x + 3, toDraw->y - 17, 16, 16, ico);
	OutFixedTextXY(toDraw->x + 3 + 18, toDraw->y - 17, toDraw->caption, 0xFFFFFF, toDraw->wwidth - 90, 1);
	Bar(toDraw->x + toDraw->wwidth - 26, toDraw->y - 20, toDraw->x + toDraw->wwidth - 1, toDraw->y - 5, 0xFF0000);
	Bar(toDraw->x + toDraw->wwidth - 50, toDraw->y - 20, toDraw->x + toDraw->wwidth - 28, toDraw->y - 5, 0x90CAF9);
	Bar(toDraw->x + toDraw->wwidth - 75, toDraw->y - 20, toDraw->x + toDraw->wwidth - 52, toDraw->y - 5, 0x90CAF9);
	Line(toDraw->x + toDraw->wwidth - 25 + 8, toDraw->y - 20 + 3, toDraw->x + toDraw->wwidth - 8, toDraw->y - 8, 0x0);
	Line(toDraw->x + toDraw->wwidth - 25 + 8 + 1, toDraw->y - 20 + 3, toDraw->x + 1 + toDraw->wwidth - 8, toDraw->y - 8, 0x0);

	Line(toDraw->x + toDraw->wwidth - 25 + 8 - 1, toDraw->y - 20 + 3, toDraw->x - 1 + toDraw->wwidth - 8, toDraw->y - 8, 0x0);

	Line(toDraw->x + toDraw->wwidth - 25 + 8, toDraw->y - 8, toDraw->x + toDraw->wwidth - 8, toDraw->y - 20 + 3, 0x0);
	Line(toDraw->x + toDraw->wwidth - 25 + 8 + 1, toDraw->y - 8, toDraw->x + toDraw->wwidth - 8 + 1, toDraw->y - 20 + 3, 0x0);
	Line(toDraw->x + toDraw->wwidth - 25 + 8 - 1, toDraw->y - 8, toDraw->x + toDraw->wwidth - 8 - 1, toDraw->y - 20 + 3, 0x0);

	Rect(toDraw->x + toDraw->wwidth - 45, toDraw->y - 20 + 3, 13, 9, 0x0);
	Rect(toDraw->x + toDraw->wwidth - 44, toDraw->y - 20 + 4, 11, 7, 0x0);
	Line(toDraw->x + toDraw->wwidth - 58, toDraw->y - 8, toDraw->x + toDraw->wwidth - 58 - 10, toDraw->y - 8, 0x0);
	Line(toDraw->x + toDraw->wwidth - 58, toDraw->y - 8 - 1, toDraw->x + toDraw->wwidth - 58 - 10, toDraw->y - 8 - 1, 0x0);
	//softBox(toDraw->x - 1, toDraw->y - 20, toDraw->x + toDraw->wwidth, toDraw->y +1 + toDraw->wheight, -80,5);
	toDraw->lastx = toDraw->x;
	toDraw->lasty = toDraw->y;

}
