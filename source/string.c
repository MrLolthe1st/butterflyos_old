
#define MAX_STRING_LEN 65536
unsigned int pos(char * s, char * d) {
	for (int i = 0; i < MAX_STRING_LEN; i++) {
		if (s[i] == 0)
			return -1;
		char p = 0;
		for (int j = 0; j < MAX_STRING_LEN; j++) {
			if (d[j] == 0) break;
			if (s[i + j] == 0 && d[j] != 0) {
				p = 1;
				break;
			}
			if (s[i + j] != d[j]) {
				p = 1;
				break;
			}
		}
		if (p == 0)
			return i;
	}
}
char m[26] = "abcdefghijklmnopqrstuvwxyz";
char b[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char upCase(char s)
{
	if (s >= 'a'&&s <= 'z')
		return b[s - 'a'];
	else return s;
}
int llastIndexOf(char * s, char * d) {
	int f = -1;
	int ff = -1;
	for (int i = 0; i < MAX_STRING_LEN; i++) {
		if (s[i] == 0) break;
		char p = 0;
		for (int j = 0; j < MAX_STRING_LEN; j++) {
			if (d[j] == 0) break;
			if (s[i + j] == 0 && d[j] != 0) {
				p = 1;
				break;
			}
			if (s[i + j] != d[j]) {
				p = 1;
				break;
			}
		}
		if (p == 0) {
			ff = f;
			f = i;
			//printHex(ff,1);
		}
	}

	return ff;
}
int lastIndexOf(char * s, char * d) {
	int f = -1;
	for (int i = 0; i < MAX_STRING_LEN; i++) {
		if (s[i] == 0) break;
		char p = 0;
		for (int j = 0; j < MAX_STRING_LEN; j++) {
			if (d[j] == 0) break;
			if (s[i + j] == 0 && d[j] != 0) {
				p = 1;
				break;
			}
			if (s[i + j] != d[j]) {
				p = 1;
				break;
			}
		}
		if (p == 0)
			f = i;
	}
	//printHex(f,1);
	return f;
}
unsigned int strlen(char * s) {
	int i = 0;
	while (s[i] != 0) i++;
	return i;
}
void strcat(char * s, char * d) {
	int l = strlen(d);
	int l2 = strlen(s);
	for (int i = l; i <= l + l2; i++)
		d[i] = s[i - l];
	d[l + l2 + 1] = 0;
}
