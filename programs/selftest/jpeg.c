#ifdef WIN32
#include <stdio.h>
#include <stdlib.h>
#endif // WIN32
#ifndef WIN32
#include "..\includes\stdio.h"
#include "..\includes\structs.h"
#include "..\includes\forms.h"
#include "..\includes\windowsEventsCodes.h"
#define buf_size 165536
#endif // WIN32

int handle(void * a) {

}
unsigned short bswap16(unsigned short q)
{
	return ((q & 0xFF) << 8) + ((q >> 8) & 0xff);
}
int zigzag_table8[8][8];	int quant[16][16][16];
int scan[16][16][256];
int huf_codes[4096][16][2];
int huf_len[16][16][2];
int dct[256];
int zigzagx[64];
int zigzagy[64];
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
		if (clen == nlen){
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
		where->r=huf_insert(where->r, val, clen + 1, nlen);
		where->r->parent = where;
		return where;
	}
	return huf_insert(where->parent, val, clen - 1, nlen);
}
int matrix[8][8][16][16]={0};
int mcnt[16] = {0};
float sx[16][16][16][16] = {0};
int RChannel[16][16];
int GChannel[16][16];
int BChannel[16][16];
static btree *init_branches(btree *racine)
{
    btree *fils=malloc(sizeof(btree));
    fils->parent = racine;
    fils->r = NULL;
    fils->l = NULL;
    return fils;
}

			int imager[16][16];
			int imageg[16][16];
			int imageb[16][16];
//int YCbCrToRGB()
float sxx[16][16][8][8];
int main(int argc, char ** argv)
{

	//if(argc!=1)
	//	return;

	FILE * z = fopen("as.jpg", "rb");
	if (!z)
	{
		//printf("Can't find file %s!\n", argv[0]);
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
	Window *w = openWindow(720, 780, 1, &handle, "Jpeg");
	#endif // WIN32
	int cursz = 8; int q = 0;
	int Imgsx = 0, Imgsy = 0;
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
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            zigzagx[zigzag_table8[j][i]-1] = j;
            zigzagy[zigzag_table8[j][i]-1] = i;

        }
	float sqrt2 = sqrt(2)/2;
	for(int x=0;x<8;x++){
		for(int y=0;y<8;y++){
			for(int u=0;u<8;u++)
				for(int v=0;v<8;v++)
				{
					float v1 = 1;
					if(u==0)
						v1= sqrt2;
					float v2 = 1;
					if(v==0)
						v2= sqrt2;
					
					//val*=cos(((x+x)+1)*u*pi)*cos(((y+y)+1)*v*pi);
					sxx[x][y][u][v]=cos(((x+x)+1)*u*pi)*cos(((y+y)+1)*v*pi)*v1*v2;
				}
			//sx[y][x][mcnt[j]][j]=sx[y][x][mcnt[j]][j]/4;
		}
	}
	while (1) {
        if(ftell(z)>=sz)
            break;
		fread(&current, 2, 1, z);
		current = bswap16(current);
		if (current == 0xFFFE)
		{
			fread(&current, 2, 1, z);
			current = bswap16(current);
			current -= 2;
			char * s = malloc(current + 1);
			s[current] = 0;
			fread(s, current, 1, z);
			//printf("Comment: %x bytes, %s\n", (unsigned int)current, s);
			free(s);
			continue;
		}
		if (current == 0xFFDB)
		{
			fread(&current, 2, 1, z);
			current = bswap16(current);
			current -= 3;
			int mask = 0;
			fread(&mask, 1, 1, z);
			int len = 1 + (mask >> 4) & 0xF;
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
			continue;
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
			for(int i=0;i<cnt;i++)
            {
                int wz;
                fread(&wz, 1, 3, z);
                dct[i] = bswap16(wz>>8);
                ////printf("%06x, ", dct[wz&0xFF]);
            }
			continue;
		}
		if (current == 0xFFC4)
		{
			//printf("Huff: ",(unsigned int)ftell(z), current);
			fread(&current, 2, 1, z);
			current = bswap16(current);
			int q = 0;
			fread(&q, 1, 1, z);
			int cnt = 0;
            int dest[16] = {0};
			for (int i = 0; i < 16; i++)
			{
				int coef = 0;
				fread(&coef, 1, 1, z);
                dest[i]=coef;
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
			int *symbole =malloc(4*cnt);
            for(int i=0;i<cnt;i++)
                fread(&symbole[i], 1, 1, z);
			unsigned char k = 0;
            unsigned char descendu=0;
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
                            descendu +=1;
                        } else if(huffman_table->r == NULL) {
                            btree *huffman_tablefd = init_branches(huffman_table);
                            huffman_table->r = huffman_tablefd;
                            huffman_table = huffman_table->r;
                            a_descendre = a_descendre - 1;
                            descendu +=1;
                        } else {
                            huffman_table = huffman_table->parent;
                            a_descendre = a_descendre + 1;
                            descendu -=1;
                        }
                    }
                    //huffman_table->feuille = true;
                    huffman_table->val = symbole[k];
                    k = k + 1;
                    huffman_table = huffman_table->parent;
                    a_descendre = a_descendre + 1;
                    descendu -=1;
                }
            }
			//printf("\n");
			continue;
		}
		if(current==0xFFDA)
		{
            int hlen = 0;
            fread(&hlen, 2, 1, z);
            hlen = bswap16(hlen);
            int scanC = 0;
            fread(&scanC, 1, 1, z);
            char * s = malloc(9);
            int comp[16];
            for(int i=0;i<scanC;i++)
            {
                int q;
                fread(&q, 2, 1, z);
                comp[i]=q>>8;
            }
            int pos[10];

            fread(&pos,hlen-(scanC*2)-2-1,1, z);
//            pos = 0;
            int spos=ftell(z);
            int cnt = 0;
			int juye = 1;
			int lsval = 0;
			#pragma GCC push_options
			#pragma GCC Optimize ("fast")
            while(juye){
                unsigned char * nuf = malloc(4096);
                fread(nuf, 4096, 1, z);
				for(int i=0;i<4096;i++)
				{
					if(lsval==0xFF&&nuf[i]==0xD9)
					{
						juye = 0;
						break;
					}
					lsval = nuf[i];
					cnt++;
				}
				free(nuf);
               // //printf("%02x ", ew);
            }
            cnt--;
			//printf("!%d~!~", cnt);
            unsigned char * fs = malloc(1 + cnt);
            fseek(z, spos, 0);
            fread(fs, cnt, 1, z);
            int i1 = 0;
            for(int i=0;i<cnt;i++)
			{
				if(fs[i]==0xFF&&fs[i+1]==0x0)
				{
					for(int j=i+1;j<cnt-1;j++){
						fs[j]=fs[j+1];
					}
					cnt--;
					i++;
				}
			}
            int mask = 0x80;
            int cpos = 0; int lcoef=0;
			int lcoef1 = 0;
			int lcoef2 = 0;
			int ofx=0;int ofy=0;
			while(cpos<cnt){
				//mask<<=1;
                for(int i=0;i<16;i++){
                    mcnt[i]=0;

                    
                }
            for(int j=0;j<scanC;j++){
                //lcoef = 0;
                while(1){
                    int matrixpos = 0;
					for(; matrixpos<64;)
					{
						sx[zigzagx[matrixpos]][zigzagy[matrixpos]][mcnt[j]][j] = 0;
						matrix[zigzagx[matrixpos]][zigzagy[matrixpos]][mcnt[j]][j] = 0;
                        matrixpos++;
					}
					matrixpos=0;
			//printf("!%d %d\n", cpos, cnt);
                    int idxd = (comp[j]>>4)&0xF;
                    int idxa = (comp[j])&0xF;
                    //printf("DC:%d AC:%d\n", idxd, idxa);
                    btree * cur =huffs[idxd][0];
		//	printf("~n", cpos, cnt);
                    while(cur->l||cur->r)
                    {
                        if(mask&fs[cpos])
                            cur=cur->r;
                        else
                            cur=cur->l;
                        if(mask==1){
                            mask=0x100;
                            cpos++;
                        }
                        mask>>=1;

                    }

                    int coef = 0;
                    int fwer =(fs[cpos]&mask?1:0);
                    for(int i=0;i<cur->val;i++)
                    {
                        coef= coef*2 + (fs[cpos]&mask?1:0);
                        if(mask==1){
                            mask=0x100;
                            cpos++;
                        }
                        mask>>=1;
                    }
                    if(!fwer&&cur->val>0)
                        coef = coef - (1<<cur->val)+1;
					if(j==0){
						coef+=lcoef;
						lcoef=coef;
					}
					if(j==1){
						coef+=lcoef1;
						lcoef1=coef;
					}
					if(j==2){
						coef+=lcoef2;
						lcoef2=coef;
					}

                    matrix[zigzagx[matrixpos]][zigzagy[matrixpos]][mcnt[j]][j] = coef;
                    matrixpos++;
                    //printf("DC Coef: %d\n", cur->val);
                    //cur =huffs[idxa][1];
                    while(matrixpos<64){
                        //printf("!%d %d\n", cpos, cnt);
                        cur =huffs[idxa][1];
                        while(cur->l||cur->r)
                        {
                            if(mask&fs[cpos])
                                cur=cur->r;
                            else
                                cur=cur->l;
                            if(mask==1){
                                mask=0x100;
                                cpos++;
                            }
                            mask>>=1;

                        }
                        //printf("#%d %d\n", cpos, cnt);
                        if(!cur->val)
                            break;
                        for(int i=0;i<(cur->val)>>4;i++){
                            //if(matrixpos<64)
                            matrix[zigzagx[matrixpos]][zigzagy[matrixpos]][mcnt[j]][j] = 0;
                            matrixpos++;
                        }
						int coeflen = cur->val&0xF;
                        int acoef = 0;
                        fwer =(fs[cpos]&mask?1:0);
                        for(int i=0;i<coeflen;i++)
                        {
                            acoef= acoef*2 + (fs[cpos]&mask?1:0);
                            if(mask==1){
                                mask=0x100;
                                cpos++;
                            }
                            mask>>=1;
                        }

                        if(!fwer)
                            acoef = acoef - (1<<coeflen)+1;//if(matrixpos>63) break;
                       // if(matrixpos<64)
                        matrix[zigzagx[matrixpos]][zigzagy[matrixpos]][mcnt[j]][j] = acoef;
                      //  //printf("Coef: %d,", acoef,matrixpos);
                     //   //printf("%d %d\n", zigzagx[matrixpos], zigzagy[matrixpos]);
                        matrixpos++;
                        //printf("$%d %d\n", cpos, cnt);
                    }
					while(matrixpos<64)
					{
						matrix[zigzagx[matrixpos]][zigzagy[matrixpos]][mcnt[j]][j] = 0;
                        matrixpos++;
					}
                    //printf("\n");
                    for(int i=0;i<8;i++){
                        for(int ou=0;ou<8;ou++){
                            matrix[ou][i][mcnt[j]][j]*=quant[ou][i][dct[j]&0xFF];

							////printf("%03d ", matrix[ou][i][mcnt[j]][j]);
                        }
                       // //printf("\n");
                    }
                    //printf("!%d!",  dct[j]&0xFF);
                    for(int x=0;x<8;x++){
                        for(int y=0;y<8;y++){
                            for(int u=0;u<8;u++)
                                for(int v=0;v<8;v++)
                                {
                                    sx[y][x][mcnt[j]][j]+=sxx[x][y][u][v]*matrix[v][u][mcnt[j]][j];
                                }
                            sx[y][x][mcnt[j]][j]=sx[y][x][mcnt[j]][j]/4;
                        }
                    }
                    mcnt[j]++;
			//printf("~%d %d\n", cpos, cnt);
                    if(mcnt[j]==((dct[j]>>12)&0xF)*((dct[j]>>8)&0xF))
                            break;

						//Wait(1000);


                }
            }
			//printf("%d %d\n", cpos, cnt);
			for(int i=0;i<16;i++){
				for(int j=0;j<16;j++)
				{
					float valr = sx[j&7][i&7][(i>>3)*2+(j>>3)][0]+sx[j>>1][i>>1][0][2]*1.402 + 128;
					if(valr>255)
						valr=255;
					if(valr<0)
						valr=0;
					//imager[i][j] = (int) valr;
					float valg = sx[j&7][i&7][(i>>3)*2+(j>>3)][0]-sx[j>>1][i>>1][0][1]*0.34414-sx[j>>1][i>>1][0][2]*0.71414 + 128;
					if(valg>255)
						valg=255;
					if(valg<0)
						valg=0;
					//imageg[i][j] = (int) valg;
					int valb = sx[j&7][i&7][(i>>3)*2+(j>>3)][0]+sx[j>>1][i>>1][0][1]*1.772 + 128;
					if(valb>255)
						valb=255;
					if(valb<0)
						valb=0;
					//imageb[i][j] = (int) valr;
					#ifndef WIN32
					
					*((unsigned char*)((unsigned int)w->video + (ofy+i)*720*3 + (ofx+j)*3 + 2))=valr;
					*((unsigned char*)((unsigned int)w->video + (ofy+i)*720*3 + (ofx+j)*3 + 1))=valg;
					*((unsigned char*)((unsigned int)w->video + (ofy+i)*720*3 + (ofx+j)*3 + 0))=valb;
					#endif
				}
			}
				ofx+=16;
				if(ofx>Imgsx)
				{
					ofx=0;
					ofy+=16;
					//lcoef = 0;
					//lcoef1 = 0;
					//lcoef2 = 0;
				}
				//break;
			}
		}

	}
    //printf("\n");

return 0;
}
