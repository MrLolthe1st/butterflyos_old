

typedef struct {
	unsigned char data[16];
} CB;

typedef struct {
	u32 signature;
	u32 tag;
	u32 dataLength;
	u8 flags;
	u8 lun;
	u8 cmdLength;
	CB commandBlock;
} CBW;

typedef struct {
	u32 sign;
	u32 tag;
	u32 dt;
	u8 status;
} CSW;
typedef struct {
	u32 signature;
	u32 tag;
	u32 dataLength;
	u8 flags;
	u8 lun ;
	u8 cmdLength;
	u8 opcode;
	u8 sm;
	uint LBA ;
	u8 smm;
	u16 cnt;
	u8 ctrl;
	u8 qz[6];
}Read10;
void _storageInit(UsbDevice * dev)
{
	return;
	printTextToWindow(1, mywin, "Initializing mass storage device....\n");
	//UsbDevRequest(dev, 0b00100001, 0xFF, 0, 0, 0, 0);//Reset mouse
	UsbDevRequest(dev, RT_HOST_TO_DEV | RT_CLASS | RT_INTF, 0xff, 0, dev->intfDesc->intfIndex, 0, 0);
	u8 lunCnt = 0;
	UsbDevRequest(dev, 0b10100001, 0xfe, 0, dev->intfDesc->intfIndex, 1, &lunCnt);
	UsbEndpoint * endpointIn = malloc(sizeof(UsbEndpoint));
	endpointIn->toggle = 1;
	if(dev->intfDesc->endpoints->addr & 0x80)
		endpointIn->desc = dev->intfDesc->endpoints;
	else
		endpointIn->desc = dev->intfDesc->endpoints->next;
	UsbEndpoint * endpointOut = malloc(sizeof(UsbEndpoint));
	endpointOut->toggle = 0;
	if (dev->intfDesc->endpoints->addr & 0x80)
		endpointOut->desc = dev->intfDesc->endpoints->next;
	else
		endpointOut->desc = dev->intfDesc->endpoints;
	// Prepare transfer
	UsbTransfer *t = malloc(sizeof(UsbTransfer));
	
	Read10 ro;
	memset(&ro, 0, sizeof(Read10));
	ro.signature = 0x43425355;
	ro.tag =0x21;
	ro.dataLength = 0x200;
	ro.flags = 0x80;
	ro.lun = 0;
	ro.cmdLength = 10;
	ro.opcode = 0x28;
	ro.LBA = 0;
	ro.cnt =1<<8;


	t->endp = endpointOut;
	t->req = 0;
	t->data = &ro;
	t->len = 0x1F;
	t->complete = false;
	t->success = false;

	dev->hcIntr(dev, t);
	u8 * z = &ro;
	unsigned char * buf = (unsigned char*)malloc(0x800);
	kprintf("\n%x\n", buf);
	while (!t->complete);
	if (!t->success)
		kprintf("SCSI Reques fail!\n");
	else
		kprintf("SCSI Request performed!");
	t->endp = endpointIn;
	t->req = 0;
	t->data = buf;
	t->len = 0x200;
	t->complete = false;
	t->success = false;
	dev->hcIntr(dev, t);
	kprintf("q");
	t->endp = endpointIn;
	t->req = 0;
	t->data = buf;
	t->len = 0xd;
	t->complete = false;
	t->success = false;
	dev->hcIntr(dev, t);

	while (!t->complete);
	if (!t->success)
		kprintf("SCSI Reques fail!\n");


	kprintf("\n%x\n",buf);
	for (int i = 0; i < 40; i++)
	{
		kprintf("%x ", buf[i]);
	}
	kprintf("\n");



}