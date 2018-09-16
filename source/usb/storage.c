typedef struct {
	UsbDevice * d;
	UsbTransfer * t;
	unsigned long long sectorsCount;
	unsigned char lunCount;
	UsbEndpoint * endpointIn, *endpointOut;
} UsbStorage;

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
	u8 lun;
	u8 cmdLength;
	u8 opcode;
	u8 sm;
	uint LBA;
	u8 smm;
	u16 cnt;
	u8 ctrl;
	u8 qz[6];
}Read10;

typedef struct  __attribute__((__packed__)) _q1__q {
	uint32_t sig;
	uint32_t tag;
	uint32_t xfer_len;
	uint8_t flags;
	uint8_t lun;
	uint8_t wcb_len;
	u8 cmd;
} cbw_t;
uint32_t cbw_sig = 0x43425355;
typedef struct __attribute__((__packed__)) __cmd_rdcap_10_t {
	u8 op;  // 0x25
	u8 reserved;
	uint lba;
	u16 reserved2;
	u8 pmi;
	u8 control;
} cmd_rdcap_10_t;
uint sectCount = 0;
uint readcapacity10(UsbStorage * s)
{
	UsbDevice * dev = s->d;
	UsbTransfer *t = s->t;
	UsbEndpoint * endpointIn = s->endpointIn, *endpointOut = s->endpointOut;
	cbw_t * cbw = malloc(sizeof(cbw_t) + 66);
	cbw->lun = 0;
	cbw->sig = 0x43425355;
	cbw->wcb_len = 10;
	cbw->flags = 0x80;
	cbw->xfer_len = 8;
	cmd_rdcap_10_t * cmd = (uint)cbw + 15;
	cmd->op = 0x25;
	t->endp = endpointOut;
	t->req = 0;
	t->data = cbw;
	t->len = 0x1F;
	t->complete = false;
	t->success = false;
	dev->hcIntr(dev, t);
	unsigned char res[8];
	t->endp = endpointIn;
	t->req = 0;
	t->data = &res;
	t->len = 0x8;
	t->complete = false;
	t->success = false;
	dev->hcIntr(dev, t);
	free(cbw);
	//printMem(&res, 4);
	//kprintf("!%x!", (res[0] << 24) + (res[1] << 16) + (res[2] << 8) + res[3]);
	return (res[0] << 24) + (res[1] << 16) + (res[2] << 8) + res[3];
}
void read10(UsbStorage * s, void * buf)
{
	UsbDevice * dev = s->d;
	UsbTransfer *t = s->t;
	UsbEndpoint * endpointIn = s->endpointIn, *endpointOut = s->endpointOut;

}

void _storageInit(UsbDevice * dev)
{
	printTextToWindow(1, mywin, "Initializing mass storage device....\n");
	UsbDevRequest(dev, RT_HOST_TO_DEV | RT_CLASS | RT_INTF, 0xff, 0, dev->intfDesc->intfIndex, 0, 0);
	UsbDevClearHalt(dev);
	u8 lunCnt = 0;
	UsbDevRequest(dev, 0b10100001, 0xfe, 0, dev->intfDesc->intfIndex, 1, &lunCnt);
	UsbEndpoint * endpointIn, *endpointOut;
	endpointIn = malloc(sizeof(UsbEndpoint));
	endpointIn->toggle = 0;
	if (dev->intfDesc->endpoints->addr & 0x80)
		endpointIn->desc = dev->intfDesc->endpoints;
	else
		endpointIn->desc = dev->intfDesc->endpoints->next;
	endpointOut = malloc(sizeof(UsbEndpoint));
	endpointOut->toggle = 1;
	if (dev->intfDesc->endpoints->addr & 0x80)
		endpointOut->desc = dev->intfDesc->endpoints->next;
	else
		endpointOut->desc = dev->intfDesc->endpoints;
	UsbTransfer *t = malloc(sizeof(UsbTransfer));
	UsbStorage * storage = malloc(sizeof(UsbStorage));
	t->w = 1;
	storage->t = t;
	storage->d = dev;
	storage->endpointIn = endpointIn;
	storage->endpointOut = endpointOut;

	uint sectorCount = 0;
	for (int lun = 0; lun <= lunCnt; ++lun) {
		sectorCount = readcapacity10(storage);
	};
	kprintf("Sectors count: %d\n", sectorCount);
	char *buf = malloc(512);
	read10(storage, buf);
	printMem(buf, 16);
}