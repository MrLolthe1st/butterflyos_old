typedef struct __attribute__((packed)) _Pixel {
	unsigned char b;
	unsigned char g;
	unsigned char r;
}Pixel;

// ------------------------------------------------------------------------------------------------
int width = 1024;
int height = 768;
#define widthf 1024.0
#define heightf 768.0
#define vSizeDw 589824
unsigned int bpp = 3;
unsigned char * videoMemory;
unsigned char * fontPointer = 0;
unsigned char * videoBuffer;
unsigned int STU = 0, ok = 1;

// ------------------------------------------------------------------------------------------------
//Puts pixel to video buffer
void putPixel(int x, int y, unsigned int color) {
	if (x >= 0 && y >= 0 && x < width&&y < height)
		* ((Pixel *)(videoBuffer + x * bpp + y * width * bpp)) = *((Pixel *)& color);
}

int uubpp = 0;
// ------------------------------------------------------------------------------------------------
//Puts pixel on the screen
void putPixelD(int x, int y, unsigned int color) {
	Pixel * p = &color;
	if (x >= 0 && y >= 0 && x < width&&y < height)
	{
		if (uubpp > 2)
			*((Pixel *)(videoMemory + x * bpp + y * width * bpp)) = *p;
		else
			*((unsigned short*)(videoMemory + x * 2 + width * y * 2)) = (p->b / 8) + ((p->g / 8) << 6) + ((p->r / 8) << 11);
	}
}

// ------------------------------------------------------------------------------------------------
//Puts pixel in some image in memory
void putPixelVideo(unsigned int x, unsigned int y, unsigned int color, unsigned int w, unsigned int h, unsigned char * where) {
	if (x >= 0 && y >= 0 && x < w&&y < h)
		*((Pixel *)((int)where + x * 3 + y * w * 3)) = *((Pixel *)& color);
}

// ------------------------------------------------------------------------------------------------
unsigned char fmma(unsigned char a, unsigned char b)
{

}
// ------------------------------------------------------------------------------------------------
void softBox(int x1, int y1, int x2, int y2, int darker, int size)
{
	int zz = darker / size;
	int ff = 0;
	for (int i = x1 - size; i <= x2 + size; i++, ff++)
	{
		int oo = size - 1;
		ff = 1;
		int oz = 0;
		if (i > x2) {
			int u = oo;
			oo = -((x2)-i);
			for (int j = y1; j < y2; j++)
			{
				*((unsigned char *)((unsigned int)videoBuffer + i * 3 + (j)*width * 3)) = (unsigned char)max(0, min(255, ((int)*((unsigned char *)((int)videoBuffer + i * 3 + 0 + (j)*width * 3)) + darker * ff - max(darker, oo*zz + oz * zz))));
				*((unsigned char *)((unsigned int)videoBuffer + i * 3 + 1 + (j)*width * 3)) = (unsigned char)max(0, min(255, ((int)*((unsigned char *)((int)videoBuffer + i * 3 + 1 + (j)*width * 3)) + darker * ff - max(darker, oo*zz + oz * zz))));
				*((unsigned char *)((unsigned int)videoBuffer + i * 3 + 2 + (j)*width * 3)) = (unsigned char)max(0, min(255, ((int)*((unsigned char *)((int)videoBuffer + i * 3 + 2 + (j)*width * 3)) + darker * ff - max(darker, oo*zz + oz * zz))));

			}
			oz = -((x2)-i);
			oo = u;
		}
		if (i < x1)
		{
			int u = oo;
			ff = 0;
			oo = -(i - (x1 - size));
			for (int j = y1; j < y2; j++)
			{
				*((unsigned char *)((unsigned int)videoBuffer + i * 3 + (j)*width * 3)) = (unsigned char)max(0, min(255, ((int)*((unsigned char *)((int)videoBuffer + i * 3 + 0 + (j)*width * 3)) + darker * ff - max(darker, oo*zz + oz * zz))));
				*((unsigned char *)((unsigned int)videoBuffer + i * 3 + 1 + (j)*width * 3)) = (unsigned char)max(0, min(255, ((int)*((unsigned char *)((int)videoBuffer + i * 3 + 1 + (j)*width * 3)) + darker * ff - max(darker, oo*zz + oz * zz))));
				*((unsigned char *)((unsigned int)videoBuffer + i * 3 + 2 + (j)*width * 3)) = (unsigned char)max(0, min(255, ((int)*((unsigned char *)((int)videoBuffer + i * 3 + 2 + (j)*width * 3)) + darker * ff - max(darker, oo*zz + oz * zz))));

			}
			oo = u;
			oz = -(i - (x1 - size));
			ff = 0;
		}
		for (int j = y1 - size; j < y1; j++, oo--)
		{
			*((unsigned char *)((unsigned int)videoBuffer + i * 3 + (j)*width * 3)) = (unsigned char)max(0, min(255, ((int)*((unsigned char *)((int)videoBuffer + i * 3 + 0 + (j)*width * 3)) + darker * ff - max(darker, oo*zz + oz * zz))));
			*((unsigned char *)((unsigned int)videoBuffer + i * 3 + 1 + (j)*width * 3)) = (unsigned char)max(0, min(255, ((int)*((unsigned char *)((int)videoBuffer + i * 3 + 1 + (j)*width * 3)) + darker * ff - max(darker, oo*zz + oz * zz))));
			*((unsigned char *)((unsigned int)videoBuffer + i * 3 + 2 + (j)*width * 3)) = (unsigned char)max(0, min(255, ((int)*((unsigned char *)((int)videoBuffer + i * 3 + 2 + (j)*width * 3)) + darker * ff - max(darker, oo*zz + oz * zz))));
		}
	}
	for (int i = x1 - size; i <= x2 + size; i++, ff++)
	{
		int oo = 0;
		ff = 1;
		int oz = 0;
		if (i > x2)
			oz = -((x2)-i);
		if (i < x1)
		{
			oz = -(i - (x1 - size));
			ff = 0;
		}
		for (int j = y2; j < y2 + size; j++, oo++)
		{
			*((unsigned char *)((unsigned int)videoBuffer + i * 3 + (j)*width * 3)) = (unsigned char)max(0, min(255, ((int)*((unsigned char *)((int)videoBuffer + i * 3 + 0 + (j)*width * 3)) + darker * ff - max(darker, oo*zz + oz * zz))));
			*((unsigned char *)((unsigned int)videoBuffer + i * 3 + 1 + (j)*width * 3)) = (unsigned char)max(0, min(255, ((int)*((unsigned char *)((int)videoBuffer + i * 3 + 1 + (j)*width * 3)) + darker * ff - max(darker, oo*zz + oz * zz))));
			*((unsigned char *)((unsigned int)videoBuffer + i * 3 + 2 + (j)*width * 3)) = (unsigned char)max(0, min(255, ((int)*((unsigned char *)((int)videoBuffer + i * 3 + 2 + (j)*width * 3)) + darker * ff - max(darker, oo*zz + oz * zz))));
		}
	}
}

// ------------------------------------------------------------------------------------------------
unsigned int u;
//Waits CRT back way
void waitRetrace() {
	while (inportb(0x3DA) & 0x8) {};
	while (!(inportb(0x3DA) & 0x8)) {}
}

// ------------------------------------------------------------------------------------------------
//Copies video buffer to video memory
void swapBuffer() {
	//Waits retrace
	while (inportb(0x3DA) & 0x8) {};
	while (!(inportb(0x3DA) & 0x8)) {};
	if(uubpp>2)
	__asm__("\
		.byte 0x60						#Save registers in stack			\n\
		mov %2,%%ecx 					#Repeat count to ecx				\n\
		mov %0,%%edi 					#Video memory start to edi			\n\
		mov %1,%%esi 					#Video buffer start to esi			\n\
		ww1sse2: \
			movups  (%%esi),%%xmm0		#Copy 16 bytes to xmm0 from buffer	\n\
			movups 	%%xmm0,(%%edi)		#Copy from xmm0 to video memory		\n\
			movups  16(%%esi),%%xmm0	#16 again, but + 16 from current	\n\
			movups 	%%xmm0,16(%%edi)	#16 again, but + 16 from current	\n\
			movups  32(%%esi),%%xmm0	#16 again, but + 32 from current	\n\
			movups 	%%xmm0,32(%%edi)	#16 again, but + 32 from current	\n\
			movups  48(%%esi),%%xmm0	#16 again, but + 48 from current	\n\
			movups 	%%xmm0,48(%%edi)	#16 again, but + 48 from current	\n\
			add 	$64,%%edi			#Add 64 bytes to edi				\n\
			add 	$64,%%esi			#Add 64 bytes to esi				\n\
			dec		%%ecx				#Decrement count					\n\
			#test 	%%ecx,%%ecx 		#Compare ecx with zero				\n\
			jnz 	ww1sse2 			#If not zero, repeat again			\n\
		.byte 0x61							#Restore registers from stack		\
		"::"r" (videoMemory), "r" (videoBuffer), "r" (ccnt));
	else
	{
		for (int i = 0; i < width*height; i++)
		{
			Pixel * w = ((unsigned int)videoBuffer + i*3 );
			*((unsigned short*)((unsigned int)videoMemory + i * 2)) = (w->b / 8) + ((w->g / 8) << 6) + ((w->r / 8) << 11);
		}
	}
}

// ------------------------------------------------------------------------------------------------
//Copies image to the screen
void CopyToVMemoryD(int x1, int y1, int w, int h, unsigned char * b) {
	int j;
	int sx1 = x1;
	x1 = max(x1, 0);
	w = w - (x1 - sx1);
	int startY = max(0, y1);
	int endY = min(height, y1 + h);
	int mmw = min(x1 + w, width) - x1;
	
	if (bpp == 3)
		for (j = startY; j < endY; j++)
			__asm__("\
		pusha				#Store registers to stack		\n\
		mov %0,%%edi		#Video memory addr to edi		\n\
		mov %1,%%ecx		#Pixel count to ecx				\n\
		mov %2,%%esi		#Image addr to esi				\n\
		copyToVmemory3: 									\n\
		movsb				#Copy first byte				\n\
		movsw				#Copy 2nd and 3rd bytes			\n\
		dec %%ecx			#Decrement count of pixels		\n\
		#test %%ecx,%%ecx	#Compare ecx with zero			\n\
		jnz copyToVmemory3	#Not end? -> next iteration		\n\
		popa				#Restore registers from stack	\
		"::"r" (videoMemory + j * width * 3 + x1 * 3), "r" (mmw), "r" (b + (j - y1) * w * 3));
	else
		for (j = startY; j < endY; j++)
			__asm__("\
		pusha				#Store registers to stack		\n\
		mov %0,%%edi		#Video memory addr to edi		\n\
		mov %1,%%ecx		#Pixel count to ecx				\n\
		mov %2,%%esi		#Image addr to esi				\n\
		copyToVmemory4: 									\n\
		movsb				#Copy first byte				\n\
		movsw				#Copy 2nd and 3rd bytes			\n\
		inc %%edi			#Skip useless byte				\n\
		dec %%ecx			#Decrement count of pixels		\n\
		#test %%ecx,%%ecx	#Compare ecx with zero			\n\
		jnz copyToVmemory4	#Not end? -> next iteration		\n\
		popa				#Restore registers from stack	\
		"::"r" (videoMemory + j * width * 4 + x1 * 4), "r" (mmw), "r" (b + (j - y1) * w * 3));
}

// ------------------------------------------------------------------------------------------------

//Copy 
void CopyToVMemoryTransparentD(unsigned int x1, unsigned int y1, unsigned int w, unsigned int h, unsigned char * b) {
	unsigned int i, j;

	for (j = y1; j < y1 + h; j++)
		for (i = x1; i < x1 + w; i++)
			if ((*((unsigned short *)(b + (j - y1) * w * 3 + (i - x1) * 3))) //Green and Blue не 0
				|| (*((unsigned char *)(b + (j - y1) * w * 3 + (i - x1) * 3 + 2)))) //Red Не 0
				* ((Pixel *)(videoBuffer + j * width * bpp + i * bpp)) = *((Pixel *)(b + (j - y1) * w * 3 + (i - x1) * 3));
}


// ------------------------------------------------------------------------------------------------
void CopyFromVMemoryD(int x1, int y1, int w, int h, unsigned char * b) {
	//return;
	int j; int sx1 = x1;
	x1 = max(x1, 0);
	w = w - (x1 - sx1);
	int startY = max(0, y1);
	int endY = min(height, y1 + h);
	int mmw = min(x1 + w, width) - x1;
	int buf = (unsigned int)videoMemory + startY * width * bpp + x1 * bpp;
	int bb2 = (unsigned int)b;

	if (bpp == 3) {
		for (j = startY; j < endY; j++, buf += width + width + width, bb2 += w * 3) {
			//memcpy( videoBuffer + j*width*3 + x1*3,, w*3);
			__asm__("pusha\n\
		mov %0,%%edi\n\
		mov %1,%%ecx\n\
		mov %2,%%esi\n\
		w2211: \n\
		movsb\n\
		movsw\n\
		dec %%ecx\n\
		#test %%ecx,%%ecx\n\
		jnz w2211\n\
		popa\
		"::"r" (bb2), "r" (mmw), "r" (buf));
		}
	}
	else
		for (j = startY; j < endY; j++, buf += width + width + width + width, bb2 += w * 3)
			__asm__("pusha\n\
		mov %0,%%edi\n\
		mov %1,%%ecx\n\
		mov %2,%%esi\n\
		w221w: \n\
		movsb\n\
		movsw\n\
		inc %%esi\n\
		dec %%ecx\n\
		#test %%ecx,%%ecx\n\
		jnz w221w\n\
		popa\
		"::"r" (bb2), "r" (mmw), "r" (buf));
}


// ------------------------------------------------------------------------------------------------
void CopyToVMemory(int x1, int y1, int w, int h, unsigned char * b) {
	int j;
	int sx1 = x1;
	x1 = max(x1, 0);
	int ww = w + (sx1 - x1);
	int startY = max(0, y1);
	int endY = min(height, y1 + h);
	int mmw = min(x1 + w, width) - x1;
	b -= ((sx1 - x1)) * 3;
	void * bufStart = videoBuffer + startY * width * bpp + (x1)* bpp;
	unsigned int cc = width * bpp;
	int wow = min(x1 + ww, width) - x1;
	void * bbstart = b;
	int ccc = w * 3;
	for (j = startY; j < endY; j++, bufStart += cc, bbstart += ccc) {
		if (bpp == 3)
			__asm__("pusha\n\
		mov %0,%%edi\n\
		mov %1,%%ecx\n\
		mov %2,%%esi\n\
		w22q: \n\
		movsb\n\
		movsw\n\
		dec %%ecx\n\
		#test %%ecx,%%ecx\n\
		jnz w22q\n\
		popa\
		"::"r" (bufStart), "r" (wow), "r" (bbstart));
		else
			__asm__("pusha\n\
		mov %0,%%edi\n\
		mov %1,%%ecx\n\
		mov %2,%%esi\n\
		w22qq: \n\
		movsb\n\
		movsw\n\
		inc %%edi\n\
		dec %%ecx\n\
		#test %%ecx,%%ecx\n\
		jnz w22qq\n\
		popa\
		"::"r" (bufStart), "r" (wow), "r" (bbstart));
		//bufStart += cc;
	}
}


// ------------------------------------------------------------------------------------------------
void CopyToVmemS(int x1, int y1, int w, int h, int c, int l, char * b) {

}


// ------------------------------------------------------------------------------------------------
void CopyToVMemoryTransparent(int x1, int y1, int w, int h, char * b) {
	int i, j;

	for (j = y1; j < min(height - 1, y1 + h); j++)
		for (i = x1; i < x1 + w; i++)
			if ((*((unsigned short *)(b + (j - y1) * w * 3 + (i - x1) * 3))) //Green and Blue не 0
				|| (*((unsigned char *)(b + (j - y1) * w * 3 + (i - x1) * 3 + 2)))) //Red Не 0
			{
				if(uubpp>2)
				*((Pixel *)(videoMemory + j * width * bpp + i * bpp)) = *((Pixel *)(b + (j - y1) * w * 3 + (i - x1) * 3));
				else {
					Pixel * ww = ((Pixel *)(b + (j - y1) * w * 3 + (i - x1) * 3));
					*((unsigned short*)((unsigned int)videoMemory + (i+j*width) * 2)) = (ww->b / 8) + ((ww->g / 8) << 6) + ((ww->r / 8) << 11);
				}
			}
}
void CopyToVMemoryTransparent1(int x1, int y1, int w, int h, char * b) {
	int i, j;

	for (j = y1; j < min(height - 1, y1 + h); j++)
		for (i = x1; i < x1 + w; i++)
			if ((*((unsigned short *)(b + (j - y1) * w * 3 + (i - x1) * 3))!=0xFFFF) //Green and Blue не 0
				|| (!(*((unsigned char *)(b + (j - y1) * w * 3 + (i - x1) * 3 + 2))) == 0xFF)) //Red Не 0
				* ((Pixel *)(videoBuffer + j * width * bpp + i * bpp)) = *((Pixel *)(b + (j - y1) * w * 3 + (i - x1) * 3));
}

// ------------------------------------------------------------------------------------------------
void CopyFromVMemory(int x1, int y1, int w, int h, unsigned char * b) {
	//return;
	int j;
	int sx1 = x1;
	x1 = max(x1, 0);
	w = w - (x1 - sx1);
	int startY = max(0, y1);
	int mmw = min(x1 + w, width) - x1;
	int endY = min(height, y1 + h);
	void * bufStart = videoBuffer + startY * width * bpp + (x1)* bpp;
	unsigned int cc = width * bpp;
	void * bbstart = b;
	int ccc = w * 3;
	for (j = startY; j < endY; j++, bufStart += cc, bbstart += ccc) {
		//memcpy( videoBuffer + j*width*3 + x1*3,, w*3);
		if (bpp == 3) {
			__asm__("pusha\n\
		mov %0,%%edi\n\
		mov %1,%%ecx\n\
		mov %2,%%esi\n\
		w2q1: \n\
		movsb\n\
		movsw\n\
			dec %%ecx\n\
			#test %%ecx,%%ecx\n\
		jnz w2q1\n\
		popa\
		"::"r" (bbstart), "r" (mmw), "r" (bufStart));
		}
		else
			__asm__("pusha\n\
		mov %0,%%edi\n\
		mov %1,%%ecx\n\
		mov %2,%%esi\n\
		w2qq1: \n\
		movsb\n\
		movsw\n\
		inc %%esi\n\
			dec %%ecx\n\
			#test %%ecx,%%ecx\n\
		jnz w2qq1\n\
		popa\
		"::"r" (bbstart), "r" (mmw), "r" (bufStart));
	}
}

// ------------------------------------------------------------------------------------------------
void BarL(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color) {
	__asm__(
		"push %%eax\n\
	push %%ebx\n\
	push %%ecx\n\
	push %%edx\n\
	push %%edi\n\
	push %%esi\n\
	mov %0,%%eax\n\
	mov %0,%%esi\n\
	mov %1,%%edi\n\
	mov %3,%%edx\n\
	mov %4,%%ebx\n\
	VertBarLoop:\
		inc %%ebx\n\
		cmp %%ebx,%%edx\n\
	\
	pop %%esi\n\
	pop %%edi\n\
	pop %%edx\n\
	pop %%ecx\n\
	pop %%ebx\n\
	pop %%eax\n\
	"::"r" (color), "r" (videoBuffer), "r" (width), "r" (x2), "r" (x1));
}


// ------------------------------------------------------------------------------------------------
void Bar(int x1, int y1, int x2, int y2, unsigned int color) {
	if (x1 >= width || y1 >= height)
		return;
	short y;
	x1 = min(max(x1, -1), width - 1);
	y1 = min(max(y1, -1), height - 1);
	x2 = min(max(x2, -1), width - 1);
	y2 = min(max(y2, -1), height - 1);
	void * bufStart = videoBuffer + width * bpp * y1 + x1 * bpp;
	unsigned int cc = width * bpp;
	if (bpp == 3)
		for (y = y1; y <= (short)(y2); y++, bufStart += cc) {
			//	kprintf("");
			__asm__("push %%ecx \n\
		push %%edi \n\
		push %%esi \n\
		mov %0,%%edi\n\
		mov %1,%%ecx\n\
		mov %2,%%esi\n\
		wl: movsb\n\
		movsw\n\
		dec %%esi\n dec %%esi \n dec %%esi\n\
		dec %%ecx\n\
		test %%ecx,%%ecx\n\
		jnz wl\n\
		pop %%esi\n\
		pop %%edi\n\
		pop %%ecx\n\
		"::"r" (bufStart), "r" (x2 - x1 + 1), "r" (&color));
		}
	else
		for (y = y1; y <= (short)(y2); y++, bufStart += cc)
			__asm__("push %%ecx \n\
		push %%edi \n\
		push %%esi \n\
		mov %0,%%edi\n\
		mov %1,%%ecx\n\
		mov %2,%%esi\n\
		wql: movsb\n\
		movsw\n\
		inc %%edi\n\
		dec %%esi\n dec %%esi \n dec %%esi\n\
		dec %%ecx\n\
		test %%ecx,%%ecx\n\
		jnz wql\n\
		pop %%esi\n\
		pop %%edi\n\
		pop %%ecx\n\
		"::"r" (videoBuffer + width * bpp * y + x1 * bpp), "r" (x2 - x1 + 1), "r" (&color));
}

// ------------------------------------------------------------------------------------------------
void BarVideo(int x1, int y1, int x2, int y2, unsigned int color, int ww, int wh, void * vvideoBuffer) {
	if (x1 >= ww || y1 >= wh)
		return;
	short y;
	x1 = min(max(x1, -1), ww - 1);
	y1 = min(max(y1, -1), wh - 1);
	x2 = min(max(x2, -1), ww - 1);
	y2 = min(max(y2, -1), wh - 1);
	void * bufStart = vvideoBuffer + ww * 3 * y1 + x1 * 3;
	unsigned int cc = ww * 3;
	for (y = y1; y <= (short)(y2); y++, bufStart += cc) {
		//	kprintf("");
		__asm__("push %%ecx \n\
			push %%edi \n\
			push %%esi \n\
			mov %0,%%edi\n\
			mov %1,%%ecx\n\
			mov %2,%%esi\n\
			wzl: movsb\n\
			movsw\n\
			dec %%esi\n dec %%esi \n dec %%esi\n\
			dec %%ecx\n\
			test %%ecx,%%ecx\n\
			jnz wzl\n\
			pop %%esi\n\
			pop %%edi\n\
			pop %%ecx\n\
			"::"r" (bufStart), "r" (x2 - x1 + 1), "r" (&color));
	}
}

// ------------------------------------------------------------------------------------------------
void Line(int x1, int y1, int x2, int y2, unsigned int color) {

	const int deltaX = abs(x2 - x1);
	const int deltaY = abs(y2 - y1);
	const int signX = x1 < x2 ? 1 : -1;
	const int signY = y1 < y2 ? 1 : -1;
	//
	int error = deltaX - deltaY;
	//
	putPixel(x2, y2, color);
	while ((x1 != x2 || y1 != y2)) {
		putPixel(x1, y1, color);
		const int error2 = error * 2;
		//
		if (error2 > -deltaY) {
			error -= deltaY;
			x1 += signX;
		}
		if (error2 < deltaX) {
			error += deltaX;
			y1 += signY;
		}
	}

}


// ------------------------------------------------------------------------------------------------
void LineVideo(int x1, int y1, int x2, int y2, unsigned int color, int w, int h, void * ww) {

	const int deltaX = abs(x2 - x1);
	const int deltaY = abs(y2 - y1);
	const int signX = x1 < x2 ? 1 : -1;
	const int signY = y1 < y2 ? 1 : -1;
	//
	int error = deltaX - deltaY;
	//

	putPixelVideo(x2, y2, color, w, h, ww);
	while ((x1 != x2 || y1 != y2)) {
		putPixelVideo(x1, y1, color, w, h, ww);
		const int error2 = error * 2;
		//
		if (error2 > -deltaY) {
			error -= deltaY;
			x1 += signX;
		}
		if (error2 < deltaX) {
			error += deltaX;
			y1 += signY;
		}
	}

}

// ------------------------------------------------------------------------------------------------
void BarV(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color, unsigned int w, unsigned char * where) {
	if (x1 < 0 || y1 < 0 || x1 > width - 1 || y1 > height - 1) return;
	unsigned int y;
	for (y = y1; y <= y2; y++)
		__asm__("push %%ecx \n\
		push %%edi \n\
		push %%esi \n\
		mov %0,%%edi\n\
		mov %1,%%ecx\n\
		mov %2,%%esi\n\
		wqwl: movsb\n\
		movsw\n\
		sub $3,%%esi\n\
		dec %%ecx\n\
		#test %%ecx,%%ecx\n\
		jnz wqwl\n\
		pop %%esi\n\
		pop %%edi\n\
		pop %%ecx\n\
		"::"r" (where + w * 3 * y + x1 * 3), "r" (x2 - x1 + 1), "r" (&color));
}

// ------------------------------------------------------------------------------------------------

void drawcharv(unsigned char c, int x, int y, unsigned int fgcolor, unsigned int scale, unsigned int w, unsigned int h, unsigned char * where) {
	if (x < 0 || y < 0 || x > width - 1 || y > height - 1) return;
	unsigned int cx, cy, o, o1;
	unsigned int mask[8] = {
		1,
		2,
		4,
		8,
		16,
		32,
		64,
		128
	};
	unsigned char * glyph = fontPointer + (unsigned int)c * 16;

	for (cy = 0; cy < 16; cy++)
		for (cx = 0; cx < 8; cx++)
			if (glyph[cy] & mask[7 - cx])
				for (o = 0; o < scale; o++)
					for (o1 = 0; o1 < scale; o1++)
						putPixelVideo(x + cx * scale + o, y + (cy)* scale + o1, fgcolor, w, h, where);
}

// ------------------------------------------------------------------------------------------------

void drawcharvf(unsigned char c, int x, int y, unsigned int fgcolor, unsigned int scale, unsigned int w, unsigned int h, unsigned char * where) {
	if (x < 0 || y < 0 || x > width - 1 || y > height - 1) return;
	unsigned int cx, cy, o, o1;
	unsigned int mask[8] = {
		1,
		2,
		4,
		8,
		16,
		32,
		64,
		128
	};
	unsigned char * glyph = fontPointer + (unsigned int)c * 16;

	for (cy = 0; cy < 16; cy++)
		for (cx = 0; cx < 8; cx++)
			//if (glyph[cy] & mask[7 - cx])
			for (o = 0; o < scale; o++)
				for (o1 = 0; o1 < scale; o1++)
					putPixelVideo(x + cx * scale + o, y + (cy)* scale + o1, ((glyph[cy] & mask[7 - cx]) != 0)*fgcolor, w, h, where);
}

// ------------------------------------------------------------------------------------------------
void OutTextXYV(unsigned int x, unsigned int y, char * s, unsigned int color, unsigned int scale, unsigned int w, unsigned int h, unsigned char * where) {
	unsigned int i = 0;
	while (s[i] != 0) {
		drawcharv(s[i], x + i * 8 * scale, y, color, scale, w, h, where);
		i++;
	}
}


// ------------------------------------------------------------------------------------------------
void drawchar(unsigned char c, int x, int y, unsigned int fgcolor, unsigned int scale) {
	unsigned int cx, cy, o, o1;
	unsigned int mask[8] = {
		1,
		2,
		4,
		8,
		16,
		32,
		64,
		128
	};
	unsigned char * glyph = fontPointer + (unsigned int)c * 16;

	for (cy = 0; cy < 16; cy++)
		for (cx = 0; cx < 8; cx++)
			if (glyph[cy] & mask[7 - cx])
				for (o = 0; o < scale; o++)
					for (o1 = 0; o1 < scale; o1++)
						putPixel(x + cx * scale + o, y + (cy)* scale + o1, fgcolor);
}


// ------------------------------------------------------------------------------------------------
void OutTextXY(unsigned int x, unsigned int y, char * s, unsigned int color, unsigned int scale) {
	unsigned int i = 0;
	while (s[i] != 0) {
		drawchar(s[i], x + i * 8 * scale, y, color, scale);
		i++;
	}
}

// ------------------------------------------------------------------------------------------------
void Rect(int x1, int y1, int x2, int y2, unsigned int color) {
	Line(x1, y1, x1 + x2, y1, color);
	Line(x1, y1, x1, y1 + y2, color);
	Line(x1, y1 + y2, x1 + x2, y1 + y2, color);
	Line(x1 + x2, y1, x1 + x2, y1 + y2, color);

}

// ------------------------------------------------------------------------------------------------
void OutFixedTextXY(unsigned int x, unsigned int y, char * s, unsigned int color, unsigned int maxWidth, unsigned int scale) {
	unsigned int i = 0;
	while (s[i] != 0) {
		if (i * 8 * scale + 8 * scale > maxWidth) return;
		drawchar(s[i], x + i * 8 * scale, y, color, scale);
		i++;
	}
}

// ------------------------------------------------------------------------------------------------
void * cat;


// ------------------------------------------------------------------------------------------------
char * getBmpAndScaleIt(char * path, int width, int height)
{
	FILE * f = fopen(path, "r");
	kprintf("###%x###", f);
	if (!f)
		return;
	fseek(f, 0, 2);
	uint sz = ftell(f);
	rewind(f);
	char * cat = mmalloc(sz);
	fread(cat, sz, 1, f);
	//printTextToWindow(3,mywin,"(%d %d)%x~()()",width, height videoBuffer);
	//cat = FAT32ReadFileATA(0, "CAT.BMP");
	//cat = 0x400000;
	short w = *((short *)(cat + 0x12));
	short h = *((short *)(cat + 0x16));
	cat = ((void *)(cat + *((unsigned int *)(cat + 0x0A))));
	char * cat2 = mmalloc(sz);
	void * mo = mmalloc(w * 3);
	double pzz = w * 1.0 / width;
	double pzy = h * 1.0 / height;
	double ci = 0;
	for (int cline = 0; cline < height; cline++, ci += pzy) {
		int cx = 0;
		for (double i = 0; cx < width; i += pzz)
		{
			int lpix = (int)i;
			int cpix = max((int)(i + 0.5), lpix);
			int lpiy = (int)ci;
			int cpiy = (int)(ci + 0.5);
			int sumr = 0, sumg = 0, sumb = 0;
			for (int up = lpiy; up <= cpiy; up++)
				for (int j = lpix; j <= cpix; j++)
				{
					sumr += *(unsigned char*)((uint)cat + up * w * 3 + j * 3);
					sumg += *(unsigned char*)((uint)cat + up * w * 3 + j * 3 + 1);
					sumb += *(unsigned char*)((uint)cat + up * w * 3 + j * 3 + 2);
				}

			sumr /= ((-lpix + cpix) + 1)*((cpiy - lpiy) + 1);
			sumg /= ((-lpix + cpix) + 1)*((cpiy - lpiy) + 1);
			sumb /= ((-lpix + cpix) + 1)*((cpiy - lpiy) + 1);
			*(unsigned char*)((uint)cat2 + cx * 3 + cline * 3 * width) = sumr;
			*(unsigned char*)((uint)cat2 + cx * 3 + cline * 3 * width + 1) = sumg;
			*(unsigned char*)((uint)cat2 + cx * 3 + cline * 3 * width + 2) = sumb;
			//putPixelD(cx, cline, (sumr)+(sumg << 8) + (sumb << 16));
			cx++;
		}
	}
	//Wait(1000);
	cat = ((void *)(cat + *((unsigned int *)(cat - 0x0A))));
	ffree(cat);
	cat = cat2; w = width; h = height;
	for (short i = 0; i < h / 2; i++) {
		memcpy(mo, (void *)(cat + i * w * 3), w * 3);
		memcpy((void *)(cat + i * w * 3), (void *)(cat + (h - i - 1) * w * 3), w * 3);
		memcpy((void *)(cat + (h - i - 1) * w * 3), (void *)(mo), w * 3);
	}
	ffree(mo);
	return cat;
}





// ------------------------------------------------------------------------------------------------
void loadFontPointer() {
	///Bar(0, 0, 600, 600, 0xFF0000);
	//fontPointer = FAT32ReadFileATA(0, "STANDART.FNT");

	OutTextXY((width - 35 * 8 * 2) / 2, (height - 16 * 2) / 2, "Please wait, desktop is loading...", 0xFFFFFF, 2);
	//
	//return;
	swapBuffer();
	//cat = getBmpAndScaleIt("A:\\IMG\\WP.BMP", width, height);

	//swapBuffer();
	//Bar(0,0,600,600,0x00FF000);

}


// ------------------------------------------------------------------------------------------------
void(*VBE4F07)();
void SetVisualPage(unsigned char page) {
	__asm__(
		" pusha \n xor %%cx,%%cx\n mov %1,%%edx\n xor %%bx,%%bx \ncall %0 \n popa": /* no outputs */

	: "r" (VBE4F07), /* function pointer in any register */
		"r" (page * height) /* bank number in %edx */
		);
}

// ------------------------------------------------------------------------------------------------

void draw3D(unsigned int wwidth, unsigned int wheight, unsigned int t, unsigned char * where) {
	double ceiling, deltaX, d2;
	unsigned int i, j, xx, yy;
	//some 3D game...
	for (i = 0; i < wheight; i++) {
		d2 = (i - wheight / 2.0) / wheight;

		if (d2 < 0) d2 = -d2;

		if (d2 > 0.01)
			ceiling = 8.0 / d2;
		else
			ceiling = 0;
		for (j = 0; j < wwidth; j++) {
			deltaX = (j - wwidth / 2.0) / wheight;
			deltaX *= ceiling;
			xx = (int)(deltaX) & 15;
			yy = (int)(ceiling + t) & 15;
			putPixelVideo(j, i, (xx << 4) | ((yy << 4) << 16), wwidth, wheight, where);
		}
	}
}

typedef struct  __attribute__((packed)) {
	uint16_t attributes;
	uint8_t winA, winB;
	uint16_t granularity;
	uint16_t winsize;
	uint16_t segmentA, segmentB;
	uint realFctPtr;
	uint16_t pitch; // bytes per scanline

	uint16_t Xres, Yres;
	uint8_t Wchar, Ychar, planes, bpp, banks;
	uint8_t memory_model, bank_size, image_pages;
	uint8_t reserved0;

	uint8_t red_mask, red_position;
	uint8_t green_mask, green_position;
	uint8_t blue_mask, blue_position;
	uint8_t rsv_mask, rsv_position;
	uint8_t directcolor_attributes;

	uint32_t physbase;  // your LFB (Linear Framebuffer) address ;)
	uint32_t reserved1;
	uint16_t reserved2;
} BlockInfo;
void do_v86()
{

}
void entering_v86(uint32_t ss) {
	__asm__
	("  pusha\n\
		mov $_lo, %eax\n\
		mov 8(%ebp), %ebx\n\
		mov $0x8400, %edx\n\
		jmp %edx\n\
		_lo:		\n\
		popa\n\
		\n\
		");
}
void entering_v861(uint32_t ss) {
	return;
	__asm__
	("  pusha\n\
		mov $_lo1, %eax\n\
		push %eax\n\
		pushf\n\
		orl  $131072, (%esp)\n\
		movl	$0x0, %eax	\n\
		pushl	%eax		\n\
		mov		$0x8400, %eax\n\
		pushl	%eax		\n\
		mov 24(%esp), %eax\n\
		iret				\n\
		_lo1:				\n\
		popa\n\
		");
}
void setVMode(unsigned short mode)
{
	entering_v86(mode);// iint(); Wait(1);
	outportb(0x20, 0x11);
	outportb(0xa0, 0x11);
	outportb(0x21, 0x20);
	outportb(0xa1, 0x28);
	outportb(0x21, 0x04);
	outportb(0xa1, 0x02);
	outportb(0x21, 0x01);
	outportb(0xa1, 0x01);
	outportb(0x21, 0x00);
	outportb(0xa1, 0x00);
	int_l(); 
	int_e();
	unsigned short * modes = *((unsigned short*)0x4500E) + *((unsigned short*)0x45010) * 16;
	int i = 0;
	BlockInfo * bl = 0x45200;
	while (modes[i] != 0xFFFF) {
		
		if (modes[i] == mode )
		{
			width = bl->Xres;
			height = bl->Yres;
			bpp = bl->bpp/8;
			
			videoMemory = bl->physbase;

			if (videoBuffer)
				ffree(videoBuffer);
			videoBuffer = mmalloc(width * height * 4 + 32 + 4096 * 4);
			uubpp = bpp;
			if (bpp < 3)
				bpp = 3;
			//kprintf("!!%x %x!!!", width, height);
			//	Wait(10000);
			mouseX = width / 2, mouseY = height / 2, mouse_cycle = 0, lastX = width / 2, lastY = height / 2;
			ccnt = (width*height / 64) * 3;
			if (bpp == 4) {
				ccnt = (width * height) / 16;
				ok = 0;
			}
			svga_inited = 1;
		}
		bl = (uint)bl + 256;
		i++;
	}
	//entering_v86(0, 0, 0x8, &do_v86);
}
void print_Avail_modes(Window * mywin)
{
	printTextToWindow(4, mywin, "Note: press enter for first mode\n");
	printTextToWindow(3, mywin, "Available video modes:\n", *((unsigned short*)0x45004));
	unsigned short * modes = *((unsigned short*)0x4500E) + *((unsigned short*)0x45010) * 16;
	int i = 0;
	BlockInfo * bl = 0x45200;
	while (modes[i] != 0xFFFF) {
		if (bl->bpp >= 24) {
			printTextToWindow(3, mywin, "Mode ");
			printTextToWindow(1, mywin, "%03x %dx%dx%02d      ", modes[i], bl->Xres, bl->Yres, bl->bpp);
			if (bl->Xres < 1000)
				printTextToWindow(4, mywin, " ");
			if (bl->Yres < 1000)
				printTextToWindow(4, mywin, " ");
		}
		bl = (uint)bl + 256;
		i++;
	}
	printTextToWindow(3, mywin, "\nEnter new mode: ");
}
// ------------------------------------------------------------------------------------------------
void initSVGA() {
	//__asm__("movl $70999993,%eax\njmp %eax");
	videoBuffer = 0;
	/*
	bpp = (unsigned int) * (((unsigned char *)(0x50000 + 0x19))) / 8;
	width = (unsigned int) * (((unsigned short *)(0x50000 + 18)));
	height = (unsigned int) * (((unsigned short *)(0x50000 + 20)));
	printTextToWindow(3, mywin, "(%dx%dx%d)\n", width, height, bpp);

	uubpp = bpp;
	if (bpp < 3)
		bpp = 3;
	//kprintf("!!%x %x!!!", width, height);
	//	Wait(10000);
	mouseX = width / 2, mouseY = height / 2, mouse_cycle = 0, lastX = width / 2, lastY = height / 2;
	ccnt = (width*height / 64) * 3;
	if (bpp == 4) {
		ccnt = (width * height) / 16;
		ok = 0;
	}
	videoBuffer = mmalloc(width * height * 4 + 32 + 4096*4);
	//videoBuffer = (unsigned char*)((((unsigned int)videoBuffer) / 16) * 16 + 16);
	videoMemory = (unsigned char*)(*((unsigned char *)0x50000 + 40) +
		(*((unsigned char *)0x50000 + 41) << 8) + (*((unsigned char *)0x50000 + 42) << 16) + (*((unsigned char *)0x50000 + 43) << 24));*/
	unsigned short * modes = *((unsigned short*)0x4500E) + *((unsigned short*)0x45010) * 16;
	int i = 0;
	BlockInfo * bl = 0x45200;
	prevmode = 0;
	while (modes[i] != 0xFFFF) {
		if (bl->bpp >= 24) {
			if (bl->Xres == 1024 && bl->Yres == 768)
			{
				prevmode = modes[i];
				setVMode(modes[i]);
				break;
			}
		}
		bl = (uint)bl + 256;
		i++;
	}
	if (!prevmode) {
		int i = 0;
		BlockInfo * bl = 0x45200;
		prevmode = 0;
		while (modes[i] != 0xFFFF) {
			if (bl->bpp >= 24) {
				if (bl->Xres == 800 && bl->Yres == 600)
				{
					prevmode = modes[i];
					setVMode(modes[i]);
					break;
				}
			}
			bl = (uint)bl + 256;
			i++;
		}
	}
	//VBE4F07 = *((unsigned int *)(0x50000 + 256 * 17));
	loadFontPointer();

	//swapBuffer();
	/*
	double ceiling, deltaX, d2;
	unsigned int i,j,xx,yy,t;
	//some 3D game...
	for(t=0;t<1000;t++)
		for(i=0;i<height/2;i++)
		{
			d2 = (i - heightf/4)/heightf*2;

			if(d2<0) d2=-d2;

			if(d2>0.01)
				ceiling = 8.0 / d2;
			else
				ceiling =0;
			for(j=0;j<width/2;j++)
			{
				deltaX = (j-widthf/4)/heightf*2;
				deltaX*=ceiling;
				xx = (int) (deltaX) & 15;
				yy = (int) (ceiling +t) & 15;
				putPixelm(j,i,(xx<<4)|((yy<<4)<<8));
			}
		}
	for(;;);*/
}