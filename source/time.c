
int hour, minute, sec = 0, *sec100 = 0x09913;

void Wait(unsigned int n)
{
	unsigned int ls = (*sec100);
	while ((*sec100) - ls < n)
	{
		__asm__("int $0x40");//Continue execution
	}
}