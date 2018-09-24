typedef struct {
	UsbDevice * d;
	UsbTransfer * t;
	unsigned long long sectorsCount;
	unsigned char lunCount;
	UsbEndpoint * endpointIn, *endpointOut;
	uint tag;
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
	t->len = 0x1f;
	t->complete = false;
	t->success = false;
	dev->hcIntr(dev, t);
	unsigned char res[12];
	t->endp = endpointIn;
	t->req = 0;
	t->data = &res;
	t->len = 0x8;
	t->complete = false;
	t->success = false;
	dev->hcIntr(dev, t);
	free(cbw);
	//printMem(&res, 8);
	printMem(&res, 8);
	t->endp = endpointIn;
	t->req = 0;
	t->data = cbw;
	t->len = 13;
	t->complete = false;
	t->success = false;
	dev->hcIntr(dev, t);
	//printMem(cbw, 13);
	//kprintf("!%x!", (res[0] << 24) + (res[1] << 16) + (res[2] << 8) + res[3]);
	return (res[0] << 24) + (res[1] << 16) + (res[2] << 8) + res[3];
}

uint readcapacity16(UsbStorage * s)
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
	t->w = 1;
	dev->hcIntr(dev, t);
	unsigned char res[12];
	t->endp = endpointIn;
	t->req = 0;
	t->data = &res;
	t->len = 0x8;
	t->complete = false;
	t->success = false;
	dev->hcIntr(dev, t);
	free(cbw);
	kprintf("!!!");
	printMem(&res, 8);
	t->endp = endpointIn;
	t->req = 0;
	t->data = cbw;
	t->len = 13;
	t->complete = false;
	t->success = false;
	t->w = 1;
	dev->hcIntr(dev, t);

	//printMem(&res, 13);
	//kprintf("!%x!", (res[0] << 24) + (res[1] << 16) + (res[2] << 8) + res[3]);
	return (res[0] << 24) + (res[1] << 16) + (res[2] << 8) + res[3];
}

typedef struct PACKED _cmd_rw10_t {
	uint8_t op;     // read=0x28
	uint8_t flags;  // bits: 1=fua_nv, 3=fua, 4=dpo, 7:5=rdprotect
	uint32_t lba;
	uint8_t group;
	uint16_t len;
	uint8_t control;
} cmd_rw10_t;

#define bswap_32_m(n) \
    (((n) >> 24) | \
    (((n) >> 8) & 0xFF00U) | \
    (((n) << 8) & 0xFF0000U) | \
    (((n) << 24) & 0xFF000000U))

void poll()
{

}
typedef struct PACKED {
	u8 op;
	u8 res;
	u8 pgoropcode;
	u8 res2;
	u16 alloc;
	u8 ctrl;
} inquiry_cmd;
typedef struct PACKED {
	u8 op;
	u8 action;
	u16 res;
	u16 rest;
	u32 len;
	u8 type;
	u8 ctrl;
} identify_cmd;

void identifyRequest(UsbStorage * s)
{
	UsbDevice * dev = s->d;
	UsbTransfer *t = s->t;
	UsbEndpoint * endpointIn = s->endpointIn, *endpointOut = s->endpointOut;

	cbw_t * cbw = malloc(sizeof(cbw_t) + 66);
	cbw->lun = 0;
	cbw->tag = 0x10100;
	cbw->sig = 0x43425355;
	cbw->wcb_len = 10;

	cbw->flags = 0x80;
	cbw->xfer_len = 4;
	identify_cmd * cmd = (void*)((uint)cbw + 15);
	cmd->op = 0xa3;
	cmd->len = 16;
	cmd->type = 0b0000010;
	t->endp = endpointOut;
	t->req = 0;
	t->data = cbw;
	t->len = 0x1F;
	t->complete = false;
	t->success = false;
	t->w = 1;
	dev->hcIntr(dev, t);
	t->endp = endpointIn;
	t->req = 0;
	t->data = cbw;
	t->len = 0x4;
	t->complete = false;
	t->success = false;
	t->w = 1;
	dev->hcIntr(dev, t);

}
void inquiryRequest(UsbStorage * s)
{
	UsbDevice * dev = s->d;
	UsbTransfer *t = s->t;
	UsbEndpoint * endpointIn = s->endpointIn, *endpointOut = s->endpointOut;

	cbw_t * cbw = malloc(sizeof(cbw_t) + 66);
	cbw->lun = 0;
	cbw->tag = 0x10000;
	cbw->sig = 0x43425355;
	cbw->wcb_len = 10;

	cbw->flags = 0x80;
	cbw->xfer_len =0x24;
	inquiry_cmd * cmd = (void*)((uint)cbw + 15);
	cmd->op = 0x12;
	cmd->alloc = 0x24;
	t->endp = endpointOut;
	t->req = 0;
	t->data = cbw;
	t->len = 0x1F;
	t->complete = false;
	t->success = false;
	t->w = 1;
	dev->hcIntr(dev, t);


	t->endp = endpointIn;
	t->req = 0;
	t->data = cbw;
	t->len = 0x24;
	t->complete = false;
	t->success = false;
	t->w = 1;
	dev->hcIntr(dev, t);


	t->endp = endpointIn;
	t->req = 0;
	t->data = cbw;
	t->len = 13;
	t->complete = false;
	t->success = false;
	t->w = 1;
	dev->hcIntr(dev, t);
	

}
typedef struct PACKED
{
	u8 op;
	u16 res;
	u8 power;
	u8 pow2;
	u8 ctrl;
} startStop_cmd;
void startUnit(UsbStorage * s)
{
	UsbDevice * dev = s->d;
	UsbTransfer *t = s->t;
	UsbEndpoint * endpointIn = s->endpointIn, *endpointOut = s->endpointOut;

	cbw_t * cbw = malloc(sizeof(cbw_t) + 66);
	cbw->lun = 0;
	cbw->tag = 0x10;
	cbw->sig = 0x43425355;
	cbw->wcb_len = 10;
	cbw->flags = 0x00;
	cbw->xfer_len = 0;
	startStop_cmd * cmd = (uint)cbw + 15;
	cmd->op = 0x1b;
	cmd->pow2 = 1 |(3<<4) ;
	
	t->endp = endpointOut;
	t->req = 0;
	t->data = cbw;
	t->len = 0x1F;
	t->complete = false;
	t->success = false;
	t->w = 1;
	dev->hcIntr(dev, t);
	t->endp = endpointOut;
	t->req = 0;
	t->data = cbw;
	t->len = 0x1F;
	t->complete = false;
	t->success = false;
	t->w = 1;
	dev->hcIntr(dev, t);
	t->endp = endpointIn;
	t->req = 0;
	t->data = cbw;
	t->len = 13;
	t->complete = false;
	t->success = false;
	t->w = 1;
	dev->hcIntr(dev, t);
}

u8 testUnitReady(UsbStorage * s)
{
	UsbDevice * dev = s->d;
	UsbTransfer *t = s->t;
	UsbEndpoint * endpointIn = s->endpointIn, *endpointOut = s->endpointOut;

	cbw_t * cbw = malloc(sizeof(cbw_t) + 66);
	cbw->lun = 0;
	cbw->tag = 0x1000;
	cbw->sig = 0x43425355;
	cbw->wcb_len = 10;

	cbw->flags = 0x00;
	cbw->xfer_len = 0;
	t->endp = endpointOut;
	t->req = 0;
	t->data = cbw;
	t->len = 0x1F;
	t->complete = false;
	t->success = false;
	t->w = 1;
	dev->hcIntr(dev, t);
	t->endp = endpointIn;
	t->req = 0;
	t->data = cbw;
	t->len = 0;
	t->complete = false;
	t->success = false;
	t->w = 1;
	dev->hcIntr(dev, t);
	t->endp = endpointIn;
	t->req = 0;
	t->data = cbw;
	t->len = 13;
	t->complete = false;
	t->success = false;
	t->w = 1;
	dev->hcIntr(dev, t);

	return *((u8*)((uint)cbw + 12));
}
typedef struct _sense_data {
	u8 d[252];
} sense_data;
void reqSense(UsbStorage * s)
{
	UsbDevice * dev = s->d;
	UsbTransfer *t = s->t;
	UsbEndpoint * endpointIn = s->endpointIn, *endpointOut = s->endpointOut;

	cbw_t * cbw = malloc(sizeof(cbw_t) + 66);
	cbw->lun = 0;
	cbw->tag = 0x1000;
	cbw->sig = 0x43425355;
	cbw->wcb_len = 10;

	cbw->flags = 0x80;
	cbw->xfer_len = 64;
	*((u8*)((uint)cbw + 15)) = 0x03;
	*((u8*)((uint)cbw + 16)) = 0x01;
	*((u8*)((uint)cbw + 19)) = 252;
	t->endp = endpointOut;
	t->req = 0;
	t->data = cbw;
	t->len = 0x1F;
	t->complete = false;
	t->success = false;
	t->w = 1;
	dev->hcIntr(dev, t);
	sense_data z;

	t->endp = endpointIn;
	t->req = 0;
	t->data = &z;
	t->len = 64;
	t->complete = false;
	t->success = false;
	t->w = 1;
	dev->hcIntr(dev, t);
	t->endp = endpointIn;
	t->req = 0;
	t->data = cbw;
	t->len = 13;
	t->complete = false;
	t->success = false;
	t->w = 1;
	dev->hcIntr(dev, t);
//	kprintf("Sense:");
//	printMem(&z, sizeof(z));
	//kprintf("\n");
}
void resRec(UsbDevice * dev,UsbEndpoint * in)
{
	if (!UsbDevRequest(dev, RT_HOST_TO_DEV | RT_CLASS | RT_INTF, 0xff, 0, dev->intfDesc->intfIndex, 0, 0))
		kprintf("NoReset.");
	if (!UsbDevRequest(dev,
		0x2,
		0x01,
		0,
		in->desc->addr & 0xf,
		0, 0)
		)
		kprintf("&&&&%x!!!!", in->desc->addr);
}
void _read10usb(UsbStorage * s, uint lba, uint count, void * buf)
{
	//startUnit(s);
	//lba <<= 16;
	
	UsbDevice * dev = s->d;
	UsbTransfer *t = s->t;
	UsbEndpoint * endpointIn = s->endpointIn, *endpointOut = s->endpointOut;


	cbw_t * cbw = malloc(sizeof(cbw_t) + 66);
	cbw->lun = 0;
	cbw->tag = 0x10010;
	cbw->sig = 0x43425355;
	cbw->wcb_len = 10;

	cbw->flags = 0x80;
	cbw->xfer_len = count * 512;
	cmd_rw10_t * cmd = (void*)((uint)cbw + 15);
	cmd->op = 0x28;
	cmd->group = 0;
	cmd->control = 0;
	*((uint*)((uint)cbw + 15 + 2)) = bswap_32_m(lba);
	*((u16*)((uint)cbw + 15 + 7)) = (count & 0xFF) << 8;
	t->endp = endpointOut;
	t->req = 0;
	t->data = cbw;
	t->len = 0x1F;
	t->complete = false;
	t->success = false;
	t->w = 1;
	dev->hcIntr(dev, t);

	for (int i = 0; i < count; i++)
	{
		t->endp = endpointIn;
		t->req = 0;
		t->data = buf;
		t->len = 512;
		t->complete = false;
		t->success = false;
		dev->hcIntr(dev, t);
		buf += 512;
	}
	//t->w = 1;

		//UsbDevClearHalt(dev);
			t->endp = endpointIn;
			t->req = 0;
			t->data = cbw;
			t->len = 13;
			t->complete = false;
			t->success = false;
			dev->hcIntr(dev, t);
			if (cbw->sig != 0x53425355)
				resRec(dev,endpointIn);
	
	free(cbw);
	//t->w = w;
}
void _storageInit(UsbDevice * dev)
{
	printTextToWindow(1, mywin, "Initializing mass storage device....\n");
	//UsbDevClearHalt(dev);
	UsbEndpoint * endpointIn, *endpointOut;
	endpointIn = malloc(sizeof(UsbEndpoint));
	endpointIn->toggle = 0;
	if (dev->intfDesc->endpoints->addr & 0x80)
		endpointIn->desc = dev->intfDesc->endpoints;
	else
		endpointIn->desc = dev->intfDesc->endpoints->next;
	endpointOut = malloc(sizeof(UsbEndpoint));
	endpointOut->toggle = 0;
	if (dev->intfDesc->endpoints->addr & 0x80)
		endpointOut->desc = dev->intfDesc->endpoints->next;
	else
		endpointOut->desc = dev->intfDesc->endpoints;
	resRec(dev, endpointOut);

	
	u8 lunCnt = 0;
	if(!UsbDevRequest(dev, 0b10100001, 0xfe, 0, dev->intfDesc->intfIndex, 1, &lunCnt))
		kprintf("Nolun.");
	//UsbDevClearHalt(dev);
	 dev->drvPoll = &poll;
	kprintf("LUN count:%x\n", lunCnt);
	
	//attr = 0x4e;
	//kprintf("%x!", endpointIn->desc->addr);
	UsbTransfer *t = malloc(sizeof(UsbTransfer));
	UsbStorage * storage = malloc(sizeof(UsbStorage));
	t->w = 1;
	storage->t = t;
	storage->tag = 10;
	storage->d = dev;
	storage->endpointIn = endpointIn;
	storage->endpointOut = endpointOut;
	uint sectorCount = 0;
	for (int lun = 0; lun <= lunCnt; ++lun) {
		//reqSense(storage);
		while (testUnitReady(storage)) {
			reqSense(storage);
			Wait(100);
		}	
		
		sectorCount = readcapacity10(storage);
		inquiryRequest(storage);

	};
	kprintf("Sectors count: %x\n", sectorCount);
	char * b = malloc(1024);
//	_read10usb(storage, 0x0, 2, b);
	_read10usb(storage, 0x1, 2, b);
	free(b);
	diskDevices[dcount].structNo = 0;
	diskDevices[dcount].type = DISK_TYPE_USB;
	diskDevices[dcount].link = storage;
	
	dcount++;
	
}