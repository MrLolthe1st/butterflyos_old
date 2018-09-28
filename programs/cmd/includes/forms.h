Window *openWindow(unsigned int wwidth, unsigned int wheight, 
	unsigned int type, void * handler, char * caption);
void printTextToWindow(unsigned char color, Window * w, const char * text, ...);
void closeWindow(Window * w);
