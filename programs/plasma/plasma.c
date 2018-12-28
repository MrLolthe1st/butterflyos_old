
#include "..\includes\stdio.h"
#include "..\includes\structs.h"
#include "..\includes\forms.h"
#include "..\includes\windowsEventsCodes.h"
#define buf_size 165536

int key = 0;
int handle(WindowEvent * a) {
	if(a->code==WINDOWS_KEY_DOWN)
		key=*((unsigned short*)a->data);
}
void main(int argc, char ** argv)
{
	omain(argc, argv);
}
#pragma GCC push_options
#pragma GCC optimize ("O3")

double sqrt(double x) {
	double r;
	__asm__ __volatile__("fsqrt": "=t"(r) : "0"(x) : "memory");
	return r;
}


double dist(double a, double b, double c, double d){
	double q = (a-c);
	double qq = (b-d);
	return sqrt(q*q + qq*qq);
}
double fabs(double x) {
	double r;
	__asm__ __volatile__("fabs": "=t"(r) : "0"(x) : "memory");
	return r;
}
int rgb(int r, int g, int b)
{
	return r + (g<<8)+(b<<16);
}
double floor(double num) {
   
    long long n = (long long)num;
    double d = (double)n;
    if (d == num || num >= 0)
        return d;
    else
        return d - 1;
}
float fmod(float a, float b)
{
    return (a - b * floor(a / b));
}
unsigned int hsv_to_rgb(int h, float s, float v) {
	float c  = v * s;
	float hp = (float)h / 42.6666666f;
	float x = c * (1.0 - fabs(fmod(hp, 2) - 1.0));
	float m = v - c;
	float rp, gp, bp;
	if (hp < 1.0)      { rp = c; gp = x; bp = 0; }
	else if (hp < 2.0) { rp = x; gp = c; bp = 0; }
	else if (hp < 3.0) { rp = 0; gp = c; bp = x; }
	else if (hp < 4.0) { rp = 0; gp = x; bp = c; }
	else if (hp < 5.0) { rp = x; gp = 0; bp = c; }
	else if (hp < 6.0) { rp = c; gp = 0; bp = x; }
	else               { rp = 0; gp = 0; bp = 0; }
	return rgb((rp + m) * 255, (gp + m) * 255, (bp + m) * 255);
}
typedef struct{
	char r,g,b;
}Point;

float CONST_1 = 4 / 3.1415927;
float CONST_2 = 4 / (3.1415927*3.1415927);
float sins(float x) {
	char u1=0;
	if (x < -3.1415927) {
		x += 6.2831854; u1=1;
	}else if(x > 3.1415927) {
		x -= 6.2831854;
	}

	return (x < 0) ? (CONST_1 * x + CONST_2 * x * x)
			: (CONST_1 * x - CONST_2 * x * x);
}

double sin(double x) {
	double r;
	__asm__ __volatile__("fsin": "=t"(r) : "0"(x) : "memory");
	return r;
}
double cos(double x) {
	double r;
	__asm__ __volatile__("fcos": "=t"(r) : "0"(x) : "memory");

	return r;
}
float t[500*500]={0};
int bswap24(int a)
{
	return (a>>16)&0xFF + (((a>>8)&0xFF) <<8) + ((a&0xff)<<16);
}
void omain(int argc, char ** argv)
{
	Window * w = openWindow(500, 500, 1, &handle, "Graphics Test");
	if(argc==2&&argv[1][0]=='p'){
		double time;

		unsigned int palette[256];
		for (int x = 0; x < 256; ++x) {
			palette[x] = hsv_to_rgb(x,1.0,1.0);
		}
		for (int x = 0; x < 500; ++x) {
			for (int y = 0; y < 500; ++y)
			{
				t[x*500 + y] = sin(dist(x, y, 64.0, 64.0) / 8.0)+sin(dist(x, y, 192.0, 100.0) / 8.0);
			}
		}
		while(key!='q'&&key!='Q')
		{
			time += 1.0;
			Point * s = w->video; int j=0;
			for (int x = 0; x < 500; ++x) {
				for (int y = 0; y < 500; ++y) {
					float value = sin(dist(x + time, y, 128.0, 128.0) / 8.0)
						+ t[j]
						+ sin(dist(x, y + time / 7, 192.0, 64) / 7.0);
					*s++ = *((Point*)&palette[(int)((value + 4) *32)]);j++;
				}
			}
			//BufferWindow(w);
		}
	} else if (argc==2&&argv[1][0]=='3')
	{
		double t =100;
		while(key!='q'&&key!='Q')
		{
			double ceiling, deltaX, d2;
			unsigned int i, j, xx, yy;
			t += 0.1;
			Point * s = w->video;
			double sine=sin(t/10.0);
			double cosine=cos(t/10.0);
			for (i = 0; i < 500; i++) {
				d2 = (i - 250.0) / 500.0;

				if (d2 < 0) d2 = -d2;

				if (d2 > 0.01)
					ceiling = 8.0 / d2;
				else
					ceiling = 100;
				if(ceiling<100)
				for (j = 0; j < 500; j++) {
					deltaX = (j - 250.0) / 500.0;
					deltaX *= ceiling;
					xx = (int)(deltaX * cosine + ceiling * sine) & 15;
					yy = (int)(ceiling* cosine - deltaX * sine) & 15;
					int pp= ((xx << 4) | ((yy << 4) << 8));
					
					*((Point*)((uint)w->video + i*500*3 + j*3))=*((Point*)&pp);
				}
			}
		}
	} else if (argc==2&&argv[1][0]=='c')
	{

	}
	closeWindow(w);
}
#pragma GCC pop_options