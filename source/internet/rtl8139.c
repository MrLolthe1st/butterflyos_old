
#define ROK                 (1<<0)
#define RER                 (1<<1)
#define TOK     (1<<2)
#define TER     (1<<3)
#define TX_TOK  (1<<15)
#define RX_BUF_SIZE 8192
#define RX_READ_POINTER_MASK (~3)
uint rtl39ioaddr, rx_buffer, current_packet_ptr;
void receive_packet() {
	u16 * t = (u16*)(rx_buffer + current_packet_ptr);
	// Skip packet header, get packet length
	u16 packet_length = *(t + 1);

	// Skip, packet header and packet length, now t points to the packet data
	t = t + 2;
	//qemu_printf("Printing packet at addr 0x%x\n", (uint32_t)t);
	//xxd(t, packet_length);

	// Now, ethernet layer starts to handle the packet(be sure to make a copy of the packet, insteading of using the buffer)
	// and probabbly this should be done in a separate thread...
	void * packet = malloc(packet_length);
	memcpy(packet, t, packet_length);
	//ethernet_handle_packet(packet, packet_length);

	current_packet_ptr = (current_packet_ptr + packet_length + 4 + 3) & RX_READ_POINTER_MASK;

	if (current_packet_ptr > RX_BUF_SIZE)
		current_packet_ptr -= RX_BUF_SIZE;

	outportw(rtl39ioaddr + 0x38, current_packet_ptr - 0x10);
}
IRQ_HANDLER1(_rtl8139)
{
	kprintf("ISR!");
	u16 status = inportw(rtl39ioaddr + 0x3e);
	if (status & TOK) {
		kprintf("Packet sent\n");
	}
	if (status & ROK) {
		//qemu_printf("Received packet\n");
		receive_packet();
	}
	outportw(rtl39ioaddr + 0x3E, 0x5);
}
IRQ_HANDLER1(rtl81391)
{
	//outportw(rtl39ioaddr + 0x3E, 0x1);
	//kprintf)""
}
u8 TSAD_array[4] = { 0x20, 0x24, 0x28, 0x2C };
u8 TSD_array[4] = { 0x10, 0x14, 0x18, 0x1C };
u8 tx_cur;
void sendPacket(void * data, uint len)
{
	outportd(rtl39ioaddr + TSAD_array[tx_cur], data);
	outportd(rtl39ioaddr + TSD_array[tx_cur++], len);
	if (tx_cur > 3)
		tx_cur = 0;
}

void _rtl39_init(uint id, PciDeviceInfo *info)
{
	if (!(info->vendorId == 0x10EC && info->deviceId == 0x8139))
	{
		return;
	}
	PciBar bar;
	PciGetBar(&bar, id, 0);
	rtl39ioaddr = (uintptr_t)bar.u.address;
	uint ioaddr = rtl39ioaddr;
	kprintf("Init RTL8193...\n");
	outportb(ioaddr + 0x52, 0x0);
	kprintf("RTL8193 turned on\n");
	outportb(ioaddr + 0x37, 0x10);
	while ((inportb(ioaddr + 0x37) & 0x10) != 0);
	kprintf("RTL reseted!\n");
	rx_buffer = (uint)malloc(8192 + 16);
	tx_cur = 0;
	outportd(ioaddr + 0x30, (uintptr_t)rx_buffer);
	outportw(ioaddr + 0x3C, 0x0005);
	outportd(ioaddr + 0x44, 0xf | (1 << 7));
	outportb(ioaddr + 0x37, 0x0C);
	uint irqNum = PciRead32(id, PCI_CONFIG_INTERRUPT_LINE);
	inst(0x20 + irqNum, &_rtl8139, 0x8e);
	kprintf("try to send packet\n");

}