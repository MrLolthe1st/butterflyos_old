const double eps = 1e-9;

void initCoProc() {
	__asm__ __volatile__("finit \n\
	fldln2"
		::: "memory");
}

int max(int a, int b) {
	if (a >= b)
		return a;
	else
		return b;
}

int min(int a, int b) {
	if (a <= b)
		return a;
	else
		return b;
}

double fact(double n) {
	double fac = 1;
	for (int i = 1; i <= n; i++)
		fac *= i;
	return fac;
}

double sqrt(double x) {
	double r;
	__asm__ __volatile__("fsqrt": "=t"(r) : "0"(x) : "memory");
	return r;
}

double fabs(double x) {
	double r;
	__asm__ __volatile__("fabs": "=t"(r) : "0"(x) : "memory");
	return r;
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
