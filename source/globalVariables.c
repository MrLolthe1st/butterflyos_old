GlobalVariable * globalTableFirst;
void initGlobals()
{
	globalTableFirst = (GlobalVariable*)malloc(12);
	*((unsigned int*)0x09917) = (size_t)globalTableFirst;
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
	w->name = name;
	w->ptr = (int)addr;
}



int _getcmpstr(char * a, char *b)
{
	while(a&&b&&*a&&*b)
	{
		if(*a!=*b)
			return 0;
	}
	if(a&&b&&((*a)==(*b)))
		return 1;
	return 0;
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
	if(_getcmpstr(name, "stdin"))
		
	return 0;
}