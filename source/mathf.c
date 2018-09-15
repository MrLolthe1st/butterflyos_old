double eps=1e-9;
void initCoProc()
{
	__asm__("finit\n\
	fldln2");
}
int max(int a, int b)
{
	if(a>b) return a;
	else return b;
}
int min(int a, int b)
{
	if(a<b) return a;
	else return b;
}
double sqrt(double z)
{
	double l = 0,r = (1 / eps)* 100;
	double m = 0;
	while(r-l>eps)
	{
		m = (l + r) / 2.0;
		if(m * m > z) r = m;
		else l = m;
	}
	return m;
}
double fabs(double x)
{
	if(x>0) return x;
	return -x;
}
double fact(double n)
{
	double fac=1;
	for (int i=1;i<=n;i++)
		fac*=i;
	return fac;
}

double sin(double x)
{
	double res;
	__asm__("mov %0,%%eax \n fld (%%eax) \n fsin \n mov %0,%%eax \n fst (%%eax)"::"r"(&x));
	return x;
}
double cos(double x){
	return x;
}
