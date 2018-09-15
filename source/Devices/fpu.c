
void fpu_load_control_word(const unsigned short control)
{
	__asm__("fldcw %0;"::"m"(control));
}

void enableFPU()
{
	size_t cr4;
	__asm__("mov %%cr4, %0" : "=r"(cr4));
	cr4 |= 0x200;
	__asm__("mov %0, %%cr4" :: "r"(cr4));
	fpu_load_control_word(0x27F);
}