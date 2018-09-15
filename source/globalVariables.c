GlobalVariable * globalTableFirst;
void initGlobals()
{
	globalTableFirst = (GlobalVariable*)malloc(12);
	*((unsigned int*)0x09917) = globalTableFirst;
	globalTableFirst->next = 0;
	globalTableFirst->name = "@globalInit";

}
void addGlobalVariable(char * name, void * addr)
{
	GlobalVariable * w = globalTableFirst;
	while (w->next)
		w = w->next;
	w->next = (GlobalVariable*)malloc(12);
	w = w->next;
	w->next = 0;
	w->name = (int)name;
	w->ptr = (int)addr;
}
unsigned int getVariableAddress(char * name)
{

	GlobalVariable * w = globalTableFirst;
	while (w)
	{
		char * c = w->name;
		char * b = name;
		while (*c&&*b&&*c == *b)
		{
			c++; b++;
		}
		if (*c == *b&&*c == 0)
		{
			return w->ptr;
		}
		w = w->next;
	}
}