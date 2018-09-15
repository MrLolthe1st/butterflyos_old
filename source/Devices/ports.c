#define uint16_t unsigned short
#define uint32_t unsigned int
#define uint8_t unsigned char
#define uint64_t unsigned long long

uint8_t inportb(uint16_t portid)
{
	uint8_t ret;
	__asm__("inb %%dx, %%al":"=a"(ret) : "d"(portid));
	return ret;
}
uint16_t inportw(uint16_t portid)
{
	uint16_t ret;
	__asm__("inw %%dx, %%ax":"=a"(ret) : "d"(portid));
	return ret;
}
uint32_t inportd(uint16_t portid)
{
	uint32_t ret;
	__asm__("inl %%dx, %%eax":"=a"(ret) : "d"(portid));
	return ret;
}
void outportb(uint16_t portid, uint8_t value)
{
	__asm__("outb %%al, %%dx": : "d" (portid), "a" (value));
}
void outportw(uint16_t portid, uint16_t value)
{
	__asm__("outw %%ax, %%dx": : "d" (portid), "a" (value));
}
void outportd(uint16_t portid, uint32_t value)
{
	__asm__("outl %%eax, %%dx": : "d" (portid), "a" (value));
}