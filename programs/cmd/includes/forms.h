Window *openWindow(unsigned int wwidth, unsigned int wheight, 
	unsigned int type, void * handler, char * caption);
void printTextToWindow(unsigned char color, Window * w, const char * text, ...);
void closeWindow(Window * w);
void putPixelVideo(unsigned int x, unsigned int y, unsigned int color, unsigned int w, unsigned char * where);
void draw3D(unsigned int wwidth, unsigned int wheight, unsigned int t, unsigned char * where);