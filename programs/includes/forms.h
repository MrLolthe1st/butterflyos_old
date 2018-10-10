Window *openWindow(unsigned int wwidth, unsigned int wheight, 
	unsigned int type, void * handler, char * caption);
void printTextToWindow(unsigned char color, Window * w, const char * text, ...);
void closeWindow(Window * w);
void putPixelVideo(unsigned int x, unsigned int y, unsigned int color, unsigned int w, unsigned int h, unsigned char * where);
void draw3D(unsigned int wwidth, unsigned int wheight, unsigned int t, unsigned char * where);
void BarVideo(int x1, int y1, int x2, int y2, unsigned int color, int ww, int wh, void * videoBuffer);
void LineVideo(int x1, int y1, int x2, int y2, unsigned int color, int w, int h, void * ww);
void drawcharv(unsigned char c, int x, int y, unsigned int fgcolor, unsigned int scale, unsigned int w, unsigned int h, unsigned char * where)ж