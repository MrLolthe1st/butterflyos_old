typedef struct {
	char use16bcmds;
	UsbDevice * d;
	UsbTransfer * t;
	unsigned long long sectorsCount;
	unsigned char lunCount;
	unsigned int bytesPerBlock;
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
	unsigned char res[8];
	t->endp = endpointIn;
	t->req = 0;
	t->data = &res;
	t->len = 0x8;
	t->complete = false;
	t->success = false;
	dev->hcIntr(dev, t);
	t->endp = endpointIn;
	t->req = 0;
	t->data = cbw;
	t->len = 13;
	t->complete = false;
	t->success = false;
	dev->hcIntr(dev, t);
	free(cbw);
	s->bytesPerBlock = (res[4] << 24) + (res[5] << 16) + (res[6] << 8) + res[7];
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
	cbw->wcb_len = 16;
	cbw->flags = 0x80;
	cbw->xfer_len = 12;
	cmd_rdcap_10_t * cmd = (uint)cbw + 15;
	cmd->op = 0x9E;
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
	t->len = 12;
	t->complete = false;
	t->success = false;
	dev->hcIntr(dev, t);
	t->endp = endpointIn;
	t->req = 0;
	t->data = cbw;
	t->len = 13;
	t->complete = false;
	t->success = false;
	t->w = 1;
	dev->hcIntr(dev, t);
	free(cbw);
	if ((res[0] << 56) + (res[1] << 48) + (res[2] << 40) + (res[3] << 32) + (res[4] << 24) + (res[5] << 16) + (res[6] << 8) + res[7] == 0)
		return 0;
	s->bytesPerBlock = (res[8] << 24) + (res[9] << 16) + (res[10] << 8) + res[11];
	return (res[0] << 56) + (res[1] << 48) + (res[2] << 40) + (res[3] << 32) + (res[4] << 24) + (res[5] << 16) + (res[6] << 8) + res[7];
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

void inquiryRequest(UsbStorage * s)
{
	UsbDevice * dev = s->d;
	UsbTransfer *t = s->t;
	UsbEndpoint * endpointIn = s->endpointIn, *endpointOut = s->endpointOut;

	cbw_t * cbw = malloc(sizeof(cbw_t) + 20);
	cbw->lun = 0;
	cbw->tag = 0x10000;
	cbw->sig = 0x43425355;
	cbw->wcb_len = 10;

	cbw->flags = 0x80;
	cbw->xfer_len = 0x24;
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
	free(cbw);
	return *((u8*)((uint)cbw + 12));
}
typedef struct _sense_data {
	u8 d[252];
} sense_data;
void requestSense(UsbStorage * s)
{
	UsbDevice * dev = s->d;
	UsbTransfer *t = s->t;
	UsbEndpoint * endpointIn = s->endpointIn, *endpointOut = s->endpointOut;

	cbw_t * cbw = malloc(sizeof(cbw_t) + 20);
	cbw->lun = 0;
	cbw->tag = 0x1000;
	cbw->sig = 0x43425355;
	cbw->wcb_len = 10;

	cbw->flags = 0x80;
	cbw->xfer_len = 0x12;
	*((u8*)((uint)cbw + 15)) = 0x03;
	*((u8*)((uint)cbw + 16)) = 0x01;
	*((u8*)((uint)cbw + 19)) = 0x12;//252 bytes - full sense(see SCSI spec.)
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
	t->len = 0x12;
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
	printMem(cbw, 14);
		free(cbw);
}
uint MassStorageReset(UsbDevice * dev, UsbEndpoint * out)
{
	//MassStorage Reset command
	if (!UsbDevRequest(dev, RT_HOST_TO_DEV | RT_CLASS | RT_INTF, 0xff, 0, dev->intfDesc->intfIndex, 0, 0)) {
		kprintf("Can't reset mass storage, exiting....\n");
		return 1;
	}
	//Clear halt for out endpoint
	if (!UsbDevRequest(dev, 0x2, 0x01, 0, out->desc->addr & 0xf, 0, 0)) {
		kprintf("Can't clear halt for endpoint %x, exiting...\n", out->desc->addr & 0xf);
		return 1;
	}
	return 0;
}

void _read10usb(UsbStorage * s, uint lba, uint count, void * buf)
{
	//Get device and endpoints
	UsbDevice * dev = s->d; char *ut = buf;
	UsbTransfer *t = s->t;
	UsbEndpoint * endpointIn = s->endpointIn, *endpointOut = s->endpointOut;
	//Allocate Control Block Wrapper
	cbw_t * cbw = malloc(31);
retry_read:;
	cbw->lun = 0;
	cbw->tag = s->tag;
	s->tag++;
	cbw->sig = 0x43425355;
	cbw->wcb_len = 10;
	cbw->flags = 0x80;
	//Transfer length
	cbw->xfer_len = s->bytesPerBlock * count;
	cmd_rw10_t * cmd = (void*)((uint)cbw + 15);
	cmd->op = 0x28;
	cmd->group = 0;
	cmd->control = 0;
	*((uint*)((uint)cbw + 15 + 2)) = bswap_32_m(lba);//LBA for CBW is big-endian
	*((u16*)((uint)cbw + 15 + 7)) = ((count & 0xFF) << 8);//Count of sectors also
	*((u8*)((uint)cbw + 15 + 1)) = 0;//Count of sectors also
	t->endp = endpointOut;//bulk Out
	t->req = 0;
	t->data = cbw;
	t->len = 0x1F;
	t->complete = false;
	t->success = false;
	t->w = 1;// kprintf("{^%x}", lba);
	dev->hcIntr(dev, t);
	
	
	for (int i = 0; i < count*(s->bytesPerBlock / endpointIn->desc->maxPacketSize); i++)
	{
		//Read by one sector
		t->endp = endpointIn;
		t->req = 0;
		t->data = buf;
		t->len = endpointIn->desc->maxPacketSize;
		t->complete = false;
		t->success = false;
		dev->hcIntr(dev, t);
		buf += endpointIn->desc->maxPacketSize;
	}
	t->endp = endpointIn;
	t->req = 0;
	t->data = cbw;
	t->len = 13;
	t->complete = false;
	t->success = false;
	//Read CSW
	dev->hcIntr(dev, t);
	//Invalid signature - soft reset
	if (cbw->sig != 0x53425355) {
		if (!UsbDevRequest(dev, RT_HOST_TO_DEV | RT_CLASS | RT_INTF, 0xff, 0, dev->intfDesc->intfIndex, 0, 0)) {
			kprintf("Can't reset mass storage, exiting....\n");	
		}
		endpointIn->toggle = 0;
		endpointOut->toggle = 0;
		kprintf("Sig isn't valid!");
		while (testUnitReady(s)) {
			//Request sense from device
			requestSense(s);
			Wait(100);
		}
		uint sectorCount = readcapacity10(s);
		kprintf("%x", sectorCount);
		Wait(70000);
		buf = ut;
		goto retry_read;
	}
	free(cbw);
}
long long bswap64(long long a)
{
	char * res = &a;
	return (res[0] << 56) + (res[1] << 48) + (res[2] << 40) + (res[3] << 32) + (res[4] << 24) + (res[5] << 16) + (res[6] << 8) + res[7];
}
void _read16usb(UsbStorage * s, long long lba, uint count, void * buf)
{
	//Get device and endpoints
	UsbDevice * dev = s->d;
	UsbTransfer *t = s->t;
	UsbEndpoint * endpointIn = s->endpointIn, *endpointOut = s->endpointOut;
	//Allocate Control Block Wrapper
	cbw_t * cbw = malloc(sizeof(cbw_t) + 20);
	cbw->lun = 0;
	cbw->tag = 0x10011;
	cbw->sig = 0x43425355;
	cbw->wcb_len = 16;
	cbw->flags = 0x80;
	//Transfer length
	cbw->xfer_len = s->bytesPerBlock * count;
	cmd_rw10_t * cmd = (void*)((uint)cbw + 15);
	*((u8*)((uint)cbw + 15 + 0)) = 0x88;
	*((long long*)((uint)cbw + 15 + 2)) = bswap64(lba);//LBA for CBW is big-endian
	
	*((uint*)((uint)cbw + 15 + 10)) = bswap_32_m(count);//Count of sectors also
	printMem(cbw, 31);
	t->endp = endpointOut;//bulk Out
	t->req = 0;
	t->data = cbw;
	t->len = 0x1F;
	t->complete = false;
	t->success = false;
	t->w = 1;
	dev->hcIntr(dev, t);
	for (int i = 0; i < count*(s->bytesPerBlock/ dev->maxPacketSize); i++)
	{
		//Read by one sector
		t->endp = endpointIn;
		t->req = 0;
		t->data = buf;
		t->len = dev->maxPacketSize;
		t->complete = false;
		t->success = false;
		dev->hcIntr(dev, t);
		buf += dev->maxPacketSize;
	}
	t->endp = endpointIn;
	t->req = 0;
	t->data = cbw;
	t->len = 13;
	t->complete = false;
	t->success = false;
	//Read CSW
	dev->hcIntr(dev, t);
	//Invalid signature - soft reset
	if (cbw->sig != 0x53425355)
		MassStorageReset(dev, endpointIn);
	if (testUnitReady(s))
	{
		requestSense(s);
	}
	free(cbw);
}

void _write16usb(UsbStorage * s, long long lba, uint count, void * buf)
{
	//Get device and endpoints
	UsbDevice * dev = s->d;
	UsbTransfer *t = s->t;
	UsbEndpoint * endpointIn = s->endpointIn, *endpointOut = s->endpointOut;
	//Allocate Control Block Wrapper
	cbw_t * cbw = malloc(sizeof(cbw_t) + 20);
	cbw->lun = 0;
	cbw->tag = 0x10012;
	cbw->sig = 0x43425355;
	cbw->wcb_len = 16;
	cbw->flags = 0x00;
	//Transfer length
	cbw->xfer_len = s->bytesPerBlock * count;
	cmd_rw10_t * cmd = (void*)((uint)cbw + 15);
	cmd->op = 0x8A;
	cmd->group = 0;
	cmd->control = 0;
	*((long long*)((uint)cbw + 15 + 2)) = bswap64(lba);//LBA for CBW is big-endian
	*((uint*)((uint)cbw + 15 + 10)) = bswap_32_m(count);//Count of sectors also
	t->endp = endpointOut;//bulk Out
	t->req = 0;
	t->data = cbw;
	t->len = 0x1F;
	t->complete = false;
	t->success = false;
	t->w = 1;
	dev->hcIntr(dev, t);
	for (int i = 0; i < count; i++)
	{
		//Read by one sector
		t->endp = endpointOut;
		t->req = 0;
		t->data = buf;
		t->len = s->bytesPerBlock;
		t->complete = false;
		t->success = false;
		dev->hcIntr(dev, t);
		buf += s->bytesPerBlock;
	}
	t->endp = endpointIn;
	t->req = 0;
	t->data = cbw;
	t->len = 13;
	t->complete = false;
	t->success = false;
	//Read CSW
	dev->hcIntr(dev, t);
	//Invalid signature - soft reset
	if (cbw->sig != 0x53425355)
		MassStorageReset(dev, endpointIn);
	free(cbw);
}

void _write10usb(UsbStorage * s, uint lba, uint count, void * buf)
{
	//Get device and endpoints
	UsbDevice * dev = s->d;
	UsbTransfer *t = s->t;
	UsbEndpoint * endpointIn = s->endpointIn, *endpointOut = s->endpointOut;
	//Allocate Control Block Wrapper
	char abg[35];

	cbw_t * cbw = &abg;
	memset(cbw, 0, 31);
	cbw->lun = 0;
	cbw->tag = s->tag;
	s->tag++;
	cbw->sig = 0x43425355;
	cbw->wcb_len = 10;
	cbw->flags = 0x00;
	//Transfer length
	cbw->xfer_len = count * s->bytesPerBlock;
	cmd_rw10_t * cmd = (void*)((uint)cbw + 15);
	cmd->op = 0x2A;
	cmd->group = 0;
	cmd->control = 0;
	*((uint*)((uint)cbw + 15 + 2)) = bswap_32_m(lba);//LBA for CBW is big-endian
	*((u16*)((uint)cbw + 15 + 7)) = ((count & 0xFF) << 8);//Count of sectors also
	*((u8*)((uint)cbw + 15 + 1)) = 0;//Count of sectors also
	t->endp = endpointOut;//bulk Out
	t->req = 0;
	t->data = cbw;
	t->len = 0x1F;
	t->complete = false;
	t->success = false;
	t->w = 1;
	dev->hcIntr(dev, t);
//	kprintf("{*%x}", lba);
	for (int i = 0; i < count*(s->bytesPerBlock / endpointOut->desc->maxPacketSize); i++)
	{
		//Read by one sector
		t->endp = endpointOut;
		t->req = 0;
		t->data = buf;
		t->len = endpointOut->desc->maxPacketSize;
		t->complete = false;
		t->success = false;
		dev->hcIntr(dev, t);
		buf += endpointOut->desc->maxPacketSize;
	}
	t->endp = endpointIn;
	t->req = 0;
	t->data = cbw;
	t->len = 13;
	t->complete = false;
	t->success = false;
	//Read CSW
	dev->hcIntr(dev, t);
	//Invalid signature - soft reset
}

void storageDisconnect(UsbDevice *d)
{
	UsbStorage * s = d->drv; uint did = 0;
	for (int i = 0; i < dcount; i++)
	{
		if ((uint)diskDevices[i].link ==(uint) s)
		{
			did = i;
		}
	}
	for (int i = 0; i < lastLetter; i++)
	{
		if (drives[i].diskId == did)
		{
			drives[i].avaliable = 0;
		}
		if (drives[i].diskId == dcount - 1)
		{
			drives[i].diskId = did;
		}
	}
	dcount--;
	diskDevices[dcount].sectorsCount = diskDevices[did].sectorsCount;
	diskDevices[dcount].type = diskDevices[did].type;
	diskDevices[dcount].structNo = diskDevices[did].structNo;
	diskDevices[dcount].link = diskDevices[did].link;
	free(s->endpointIn);
	free(s->t);
	free(s->endpointOut);
	free(s);
	kprintf("Storage successfully disconected!\n");
}

void _storageInit(UsbDevice * dev)
{
	//MassStorage Class/Subclass checked, try to initialize
	printTextToWindow(1, mywin, "Initializing mass storage device....\n");
	//Check out for endpoints for in/out
	UsbEndpoint * endpointIn, *endpointOut;
	endpointIn = malloc(sizeof(UsbEndpoint));
	endpointIn->toggle = 0;//Initial toggle state is zero(In spec no information about,
	//but it works and do not touch it!
	if (dev->intfDesc->endpoints->addr & 0x80)
		endpointIn->desc = dev->intfDesc->endpoints;
	else
		endpointIn->desc = dev->intfDesc->endpoints->next;
	endpointOut = malloc(sizeof(UsbEndpoint));
	endpointOut->toggle = 0;//Initial toggle state is zero(In spec no information about,
	//but it works and do not touch it!
	if (dev->intfDesc->endpoints->addr & 0x80)
		endpointOut->desc = dev->intfDesc->endpoints->next;
	else
		endpointOut->desc = dev->intfDesc->endpoints;
	//Reset MassStorage
	if (MassStorageReset(dev, endpointOut))
		return; //Haven't reseted, get out from here!
	u8 lunCnt = 0;
	if (!UsbDevRequest(dev, 0b10100001, 0xfe, 0, dev->intfDesc->intfIndex, 1, &lunCnt))
		kprintf("Can't get LUN count!\n");
	dev->drvPoll = &poll;
	
	kprintf("LUN count:%x\n", lunCnt);
	//Preapare transfer
	UsbTransfer *t = malloc(sizeof(UsbTransfer));
	//Allocate memory for storage structures
	UsbStorage * storage = malloc(sizeof(UsbStorage));
	dev->drv = storage;
	dev->onDisconnect = &storageDisconnect;
	t->w = 1;
	storage->t = t;
	storage->tag = 0x20000;
	storage->d = dev;
	storage->endpointIn = endpointIn;
	storage->endpointOut = endpointOut;
	storage->use16bcmds = 0;
	long long sectorCount = 0;
	for (int lun = 0; lun <= lunCnt; ++lun) {
		//Test for ready
		while (testUnitReady(storage)) {
			//Request sense from device
			requestSense(storage);
			Wait(100);
		}
		sectorCount = readcapacity10(storage);
		long long z = readcapacity16(storage);
		if (z > 0) {
			sectorCount = z;
		}
		else
			storage->use16bcmds = 0;
		inquiryRequest(storage);
	};
	kprintf("Sectors count: %x\n", sectorCount);
	storage->sectorsCount = sectorCount;
	//Try read to clear chache
	char * b = malloc(1024);
	_read10usb(storage, 0, 2, b);
	//Add disk to disk devices, nextly we will check it for patritions.
	diskDevices[dcount].structNo = 0;
	diskDevices[dcount].type = DISK_TYPE_USB;
	diskDevices[dcount].link = storage;
	diskDevices[dcount].sectorsCount = sectorCount;
	kprintf("Added disk device #%d, structNo = %x, type = %x, size %dMBytes\n", dcount, diskDevices[dcount].structNo, diskDevices[dcount].type, diskDevices[dcount].sectorsCount >> 11);
	checkDiskPatritions(dcount);

	dcount++;
	
	free(b);
}