
#include "..\includes\stdio.h"
#include "..\includes\structs.h"
#include "..\includes\forms.h"
#include "..\includes\windowsEventsCodes.h"
#define buf_size 165536


int handle(void * a) {

}
unsigned short bswap16(unsigned short q)
{
	return ((q & 0xFF) << 8) + ((q >> 8) & 0xff);
}
unsigned char zigzag_table8[8][8];
	unsigned char quant[16][16][16];
unsigned char scan[16][16][256];
unsigned char huf_codes[4096][16][2];
short huf_len[16][16][2];
short dct[256];
unsigned char zigzagx[64];
unsigned char zigzagy[64];
double sqrt(double x) {
	double r;
	__asm__ __volatile__("fsqrt": "=t"(r) : "0"(x) : "memory");
	return r;
}

double cos(double x) {
	double r;
	__asm__ __volatile__("fcos": "=t"(r) : "0"(x) : "memory");
	return r;
}
double pi = 0.196349540849362;
typedef struct _btree {
	short val, len;
	struct _btree * l;
	struct _btree * r;
	struct _btree * parent;
} btree;

void ptree(btree *p, int indent, btree * el)
{
	if (p != NULL) {
		if (p->r) {
			ptree(p->r, indent + 4, el);
		}
		if (indent) {
			for (int i = 0; i < indent; i++)
				printf(" ");
		}
		if (p->r) {
			printf(" /\n"); for (int i = 0; i < indent; i++)
				printf(" ");
		}
		if (p != el)
			printf("%02x \n", p->val);
		else
			printf("!%02x! \n", p->val);
		if (p->l) {
			for (int i = 0; i < indent; i++)
				printf(" ");
			printf(" \\\n");
			ptree(p->l, indent + 4, el);
		}
	}
}
btree * huffs[16][2] = { 0 };
btree * last_insert;
btree * huf_insert(btree * where, int val, int clen, int nlen)
{
	if (!where)
	{
		where = malloc(sizeof(btree));
		where->l = 0;
		where->r = 0;
		where->parent = 0;
		where->val = val;
		where->len = clen;
		if (clen == nlen) {
			last_insert = where;
			return where;
		}

	}

	if (!where->l)
	{
		where->l = huf_insert(where->l, val, clen + 1, nlen);
		where->l->parent = where;
		return where;
	}
	if (!where->r)
	{
		where->r = huf_insert(where->r, val, clen + 1, nlen);
		where->r->parent = where;
		return where;
	}
	return huf_insert(where->parent, val, clen - 1, nlen);
}
float matrix[16][16][8][8];
int mcnt[16] = { 0 };
float sx[16][16][16][16];
static btree *init_branches(btree *racine)
{
	btree *fils = malloc(sizeof(btree));
	fils->parent = racine;
	fils->r = NULL;
	fils->l = NULL;
	return fils;
}

//int YCbCrToRGB()


#pragma GCC push_options
#pragma GCC optimize ("Ofast")
//#pragma GCC option("arch=native","tune=native","no-zero-upper") //Enable AVX
//#pragma GCC target("avx")  //Enable AVX
float sxx[16][16][8][8];
typedef struct {
	float a[8][8];
} wow;
typedef struct {
	float a[8][8];
} wow1;
float table[64];
float tmp[4]={0};
float tmp2[4]={0};
float tmp3[4]={0.25,0.25,0.25,0.25};
#ifdef Wdw
float compute(int x, int y, wow * matrix1)
{	
	__asm__("\
	push %%esi\n\
	push %%edi\n\
	push %%ecx\n\
	movl %2, %%edi\n\
	movl %1, %%esi\n\
	movups (%3), %%xmm1\n\
	mov $8, %%ecx\n\
	__uu:\n\
		movups (%%esi), %%xmm0\n\
		mulps (%%edi), %%xmm0\n\
		addps %%xmm0, %%xmm1\n\
		movups 16(%%esi), %%xmm0\n\
		mulps 16(%%edi), %%xmm0\n\
		addps %%xmm0, %%xmm1\n\
		add $32, %%esi\n\
		add $32, %%edi\n\
		dec %%ecx\n\
		#test %%ecx, %%ecx\n\
		jnz __uu\n\
	movups %%xmm1, (%0)\n\
	pop %%ecx\n\
	pop %%edi\n\
	pop %%esi\n\
	"::"r"(&tmp),"r"(&sxx[y][x]),"r"(matrix1), "r"(&tmp2));
	
	return (tmp[0]+tmp[1]+tmp[2]+tmp[3]);
}
#endif

float compute(int x, int y, wow * matrix1)
{
	float tmp = 0;
	float tmp2 = 0;
	wow1 * sxx1 = &sxx[x][y];
	for (int u = 0; u < 8; u++){
		
		for (int v = 0; v < 8; v++)
		{
			tmp += sxx1->a[u][v]*matrix1->a[v][u];
		}
	}
	return tmp;
}
typedef struct{
	float a[16][16];
} color;
void preo(int j, int curcnt1)
{
	wow * matrix1 = &matrix[curcnt1][j];
	color * c = &sx[curcnt1][j];
	for (unsigned char x = 0; x < 8; x++) {
		for (unsigned char y = 0; y < 8; y++) {
			
			c->a[y][x] = compute(x, y, matrix1);
		}
	}
}Window *w;
int Imgsx = 0, Imgsy = 0;
int ofmx[4] = {0, 8, 0, 8};
int ofmy[4] = {0, 0, 8, 8};

int ofmxx[4] = {0, 4, 0, 4};
int ofmyy[4] = {0, 0, 4, 4};
void draw(int ofx, int ofy)
{
	if(ofx>Imgsx)
		return;
	if(ofy>Imgsy)
		return;
	for (int k=0;k<4;k++){
		color * yy = &sx[k][0];
		color * bb = &sx[0][1];
		color * rr = &sx[0][2];
		for (int i = 0; i < 8; i++) {
			int coy = (ofy + i + ofmy[k]) * 720 * 3 ;
			coy += (ofx + 0 +ofmx[k])*3;
			if (ofy + i < Imgsy)
				for (int j = 0; j < 8; j++, coy+=3)
				{
					if (ofx + j >= 719 || ofx + j >= Imgsx)
						break;
					float valr = yy->a[j][i]*0.25 + rr->a[(j>>1) +ofmxx[k]][(i>>1) +ofmyy[k]] * 0.3505 + 128;
					if (valr > 255)
						valr = 255;
					if (valr < 0)
						valr = 0;
					//imager[i][j] = (int) valr;
					float valg = yy->a[j][i]*0.25 - bb->a[(j>>1)+ofmxx[k]][(i>>1)+ofmyy[k]] * 0.086035 - rr->a[(j>>1)+ofmxx[k]][(i>>1)+ofmyy[k]] * 0.178535 + 128;
					if (valg > 255)
						valg = 255;
					if (valg < 0)
						valg = 0;
					//imageg[i][j] = (int) valg;
					int valb = yy->a[j][i]*0.25 + bb->a[(j>>1)+ofmxx[k]][(i>>1)+ofmyy[k]] * 0.443 + 128;
					if (valb > 255)
						valb = 255;
					if (valb < 0)
						valb = 0;
					//imageb[i][j] = (int) valr;
	#ifndef WIN32

					*((unsigned char*)((unsigned int)w->video + coy + 2)) = valr;
					*((unsigned char*)((unsigned int)w->video + coy + 1)) = valg;
					*((unsigned char*)((unsigned int)w->video + coy + 0)) = valb;
	#endif
				}
		}
	}
}

			int comp[16];
int lcoef[3]={0};
int prep(int j, int *cpos1, int *mask1, unsigned char *fs)
{
	int cpos = *cpos1;
	short mask = *mask1;
		int curcnt1 = mcnt[j];
	//int curcnt = curcnt1;
	int matrixpos = 0;
	wow * matrix1=&matrix[curcnt1][j];
	color * sxc =&sx[curcnt1][j];
	for (; matrixpos < 64;)
	{
		sxc->a[zigzagx[matrixpos]][zigzagy[matrixpos]] = 0;
		matrix1->a[zigzagx[matrixpos]][zigzagy[matrixpos]] = 0;
		matrixpos++;
	}
	matrixpos = 0;
	//printf("!%d %d\n", cpos, cnt);
	int idxd = (comp[j] >> 4) & 0xF;
	int idxa = (comp[j]) & 0xF;
	//printf("DC:%d AC:%d\n", idxd, idxa);
	btree * cur = huffs[idxd][0];
	//	printf("~n", cpos, cnt);
	while (cur->r || cur->l)
	{
		if (mask&fs[cpos])
			cur = cur->r;
		else
			cur = cur->l;
		if (mask == 1) {
			mask = 0x100;
			cpos++;
		}
		if (!cur)
			return 1;
		mask >>= 1;

	}

	int coef = 0;
	int fwer = (fs[cpos] & mask ? 1 : 0);
	for (int i = 0; i < cur->val; i++)
	{
		coef = coef * 2 + (fs[cpos] & mask ? 1 : 0);
		if (mask == 1) {
			mask = 0x100;
			cpos++;
		}
		mask >>= 1;
	}
	if (!fwer&&cur->val > 0)
		coef = coef - (1 << cur->val) + 1;
	coef+=lcoef[j];
	lcoef[j]=coef;
	matrix1->a[zigzagx[matrixpos]][zigzagy[matrixpos]] = coef*quant[zigzagx[matrixpos]][zigzagy[matrixpos]][dct[j] & 0xFF];
	matrixpos++;
	// printf("DC Coef: %d\n", cur->val);
	//cur =huffs[idxa][1];
	while (matrixpos < 64) {

		cur = huffs[idxa][1];

		while (cur->r || cur->l)
		{
			if (mask&fs[cpos])
				cur = cur->r;
			else
				cur = cur->l;
			if (mask == 1) {
				mask = 0x100;
				cpos++;
			}
			mask >>= 1;

		}
		//printf("#%d %d\n", cpos, cnt);
		if (!cur->val)
			break;
		for (int i = 0; i < (cur->val) >> 4; i++) {
			if (matrixpos > 63)
				break;
			matrix1->a[zigzagx[matrixpos]][zigzagy[matrixpos]] = 0;
			matrixpos++;
		}
		int coeflen = cur->val & 0xF;
		int acoef = 0;
		fwer = (fs[cpos] & mask ? 1 : 0);
		for (int i = 0; i < coeflen; i++)
		{
			acoef = acoef * 2 + (fs[cpos] & mask ? 1 : 0);
			if (mask == 1) {
				mask = 0x100;
				cpos++;
			}
			mask >>= 1;
		}

		if (!fwer)
			acoef = acoef - (1 << coeflen) + 1;
		if (matrixpos > 63)
			break;
		matrix1->a[zigzagx[matrixpos]][zigzagy[matrixpos]] = acoef*quant[zigzagx[matrixpos]][zigzagy[matrixpos]][dct[j] & 0xFF];
		matrixpos++;
	}

	//printf("!%d!",  dct[j]&0xFF);

	preo(j, curcnt1);
	mcnt[j]++;
	*mask1 = mask;
	*cpos1 = cpos;
	if (mcnt[j] == ((dct[j] >> 12) & 0xF)*((dct[j] >> 8) & 0xF))
		return 1;	
	return 0;
}
#pragma GCC pop_options

int main(int argc, char ** argv)
{

	//if(argc!=1)
	//	return;
	_zzk(argc, argv);
}
#pragma GCC push_options
#pragma GCC optimize ("Ofast")
void _zzk(int argc, char ** argv) {
	//printf("Can't find file 22!\n");
	FILE * z = fopen(argv[1], "rb");
	if (!z)
	{
		printf("Can't find file %s!\n", argv[1]);
		return;
	}

	fseek(z, 0, 2);
	int sz = ftell(z);
	rewind(z);
	unsigned short current = 0;
	fread(&current, 1, 2, z);

	if (current != 0xD8FF)
		return 0;
#ifndef WIN32
	w = openWindow(720, 780, 1, &handle, "Jpeg");
#endif // WIN32
	int cursz = 8; int q = 0;
	for (int i = 0; i <= cursz * 2 - 1; i++)
	{
		if ((i % 2))
		{
			int x = -1, y = i;
			for (int t = 0; t < i; t++)
			{
				x++;
				y--;
				if ((x >= 0) && (x < cursz) && (y >= 0) && (y < cursz))
				{
					q++; zigzag_table8[x][y] = q;
				}
			}
		}
		else
		{
			int y = -1, x = i;
			for (int t = 0; t < i; t++)
			{
				y++; x--;
				if ((x >= 0) && (x < cursz) && (y >= 0) && (y < cursz))
				{
					q++; zigzag_table8[x][y] = q;
				}
			}
		}
	}
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			zigzagx[zigzag_table8[j][i] - 1] = j;
			zigzagy[zigzag_table8[j][i] - 1] = i;

		}
	float sqrt2 = sqrt(2) / 2;
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			for (int u = 0; u < 8; u++)
				for (int v = 0; v < 8; v++)
				{
					float v1 = 1;
					if (u == 0)
						v1 = sqrt2;
					float v2 = 1;
					if (v == 0)
						v2 = sqrt2;
					sxx[x][y][u][v] = cos(((x + x) + 1)*u*pi)*cos(((y + y) + 1)*v*pi)*v1*v2;
				}
		}
	}

	conread:
		if (ftell(z) >= sz)
			goto endread;
		fread(&current, 2, 1, z);
		current = bswap16(current);
		if (current == 0xFFFE)
		{
			fread(&current, 2, 1, z);
			current = bswap16(current);
			current -= 2;
			//char * s = malloc(current + 1);
			//s[current] = 0;
			fseek(z, current, 1);
			//fread(s, current, 1, z);
			//printf("Comment: %x bytes, %s\n", (unsigned int)current, s);
			//free(s);
			goto conread;
		}
		if (current == 0xFFDB)
		{
			fread(&current, 2, 1, z);
			current = bswap16(current);
			current -= 3;
			int mask = 0;
			fread(&mask, 1, 1, z);
			int len = 1 + ((mask >> 4) & 0xF);
			int idx = mask & 0xF;
			int sx = (current);
			unsigned char * data = malloc(sx);
			fread(data, sx, 1, z);

			//printf("Len: %d\n", sx);
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					quant[j][i][idx] = (int)data[zigzag_table8[j][i] - 1];
					//printf(" %02x", quant[j][i][idx]);
				}
				//printf("\n");
			}
			free(data);
			goto conread;
		}
		if (current == 0xffc0)
		{
			fread(&current, 2, 1, z);
			current = bswap16(current);
			int precis = 0;
			fread(&precis, 1, 1, z);
			fread(&Imgsy, 2, 1, z);
			Imgsy = bswap16(Imgsy);
			fread(&Imgsx, 2, 1, z);
			Imgsx = bswap16(Imgsx);
			int cnt = 0;
			fread(&cnt, 1, 1, z);
			for (int i = 0; i < cnt; i++)
			{
				int wz;
				fread(&wz, 1, 3, z);
				dct[i] = bswap16(wz >> 8);
				////printf("%06x, ", dct[wz&0xFF]);
			}
			goto conread;
		}
		if (current == 0xFFC4)
		{
			//printf("Huff: ",(unsigned int)ftell(z), current);
			fread(&current, 2, 1, z);
			current = bswap16(current);
			int q = 0;
			fread(&q, 1, 1, z);
			int cnt = 0;
			int dest[16] = { 0 };
			for (int i = 0; i < 16; i++)
			{
				unsigned char coef = 0;
				fread(&coef, 1, 1, z);
				dest[i] = coef;
				huf_len[i][q & 0xF][q >> 4] = coef;
				cnt += coef;
				////printf("%02d ", coef);
			}
			btree * huffman_table = init_branches(0);
			huffs[q & 0xF][q >> 4] = huffman_table;
			huffs[q & 0xF][q >> 4]->l = 0;
			huffs[q & 0xF][q >> 4]->r = 0;
			huffs[q & 0xF][q >> 4]->parent = 0;
			huffs[q & 0xF][q >> 4]->val = 0;
			huffs[q & 0xF][q >> 4]->len = 0;
			int *symbole = malloc(4 * cnt + 20);
			for (int i = 0; i < cnt; i++) {
				unsigned char wsz;
				fread(&wsz, 1, 1, z);
				symbole[i] = wsz;
			}
			unsigned char k = 0;
			unsigned char descendu = 0;
			for (unsigned char i = 0; i < 16; i++) {
				unsigned int nombre_symboles = dest[i];
				unsigned char a_descendre = i + 1 - descendu;
				for (unsigned char j = 0; j < nombre_symboles; j++) {
					while (a_descendre > 0) {
						if (huffman_table->l == NULL) {
							btree *huffman_tablefg = init_branches(huffman_table);
							huffman_table->l = huffman_tablefg;
							huffman_table = huffman_table->l;
							a_descendre = a_descendre - 1;
							descendu += 1;
						}
						else if (huffman_table->r == NULL) {
							btree *huffman_tablefd = init_branches(huffman_table);
							huffman_table->r = huffman_tablefd;
							huffman_table = huffman_table->r;
							a_descendre = a_descendre - 1;
							descendu += 1;
						}
						else {
							huffman_table = huffman_table->parent;
							a_descendre = a_descendre + 1;
							descendu -= 1;
						}
					}
					//huffman_table->feuille = true;
					huffman_table->val = symbole[k];
					k = k + 1;
					huffman_table = huffman_table->parent;
					a_descendre = a_descendre + 1;
					descendu -= 1;
				}
			}
			//printf("\n");
			goto conread;
		}
		if (current == 0xFFDA)
		{
			int hlen = 0;
			fread(&hlen, 2, 1, z);
			hlen = bswap16(hlen);
			int scanC = 0;
			fread(&scanC, 1, 1, z);
			char * s = malloc(9);
			for (int i = 0; i < scanC; i++)
			{
				int q;
				fread(&q, 2, 1, z);
				comp[i] = q >> 8;
			}
			int pos[10];

			fread(&pos, hlen - (scanC * 2) - 2 - 1, 1, z);
			//            pos = 0;
			int spos = ftell(z);
			int cnt = 0;
			int juye = 1;
			int lsval = 0;
			unsigned char * nuf = malloc(262144);
			unsigned char * fss=0;;
			int wok = 0;
			while (juye) {
				fread(nuf, 262144, 1, z);
				wok+=262144;
				unsigned char * lp = malloc(wok);
				memcpy(lp, fss, wok - 262144);
				if(fss) free(fss);
				fss=lp;
				memcpy((uint)fss+wok-262144, nuf, 262144);
				for (int i = 0; i < 262144; i++)
				{
					if (lsval == 0xFF && nuf[i] == 0xD9)
					{
						juye = 0;
						break;
					}
					lsval = nuf[i];
					cnt++;
				}
				// //printf("%02x ", ew);
			}
			//free(nuf);
			cnt--;
			//
			//fseek(z, spos, 0);
			//fread(fss, cnt, 1, z);
			unsigned char * fs = malloc(2 + cnt);
			int c2 = 0;
			int clenn = 0, cntw = 0;
			for (clenn = 0; c2 < cnt; clenn++)
			{
				fs[clenn] = fss[c2];
				if (fss[c2] == 0xFF) {
					if (fss[c2 + 1] == 0 && c2 < cnt)c2++;
					//clenn--;
					cntw++;
				}
				c2++;
			}
			//printf("!%d~!~", cntw);
			//Wait(1000);
			free(fss);
			cnt = clenn;

			int mask = 0x80;
			int cpos = 0; 
			int ofx = 0; int ofy = 0; cpos = 0;
				
		treutr:
			//mask<<=1;
			for (int i = 0; i < 16; i++) {
				mcnt[i] = 0;
			}
			while (!prep(0, &cpos, &mask, fs));
			while (!prep(1, &cpos, &mask, fs));
			while (!prep(2, &cpos, &mask, fs));
			draw(ofx, ofy);
			ofx += 16;
			if (ofx >= Imgsx)
			{
				ofx = 0;
				ofy += 16;
			}
			if (cpos < cnt)
				goto treutr;

		}
		
		goto conread;
	endread:
	//printf("\n");

	return 0;
}
