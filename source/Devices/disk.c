#define ATA_DEV_BUSY 0x80
#define ATA_DEV_DRQ 0x08

int _write10usb(void * ss, uint lba, uint count, void * buf);
int _read10usb(void * ss, uint lba, uint count, void * buf);
int ide_read_sectors(unsigned char drive, unsigned char numsects, unsigned int lba,
	unsigned short es, unsigned int edi);
int WriteToDisk(unsigned long long LBA, uint count, void * buf, char letter);
int ReadFromDisk(unsigned long long LBA, uint count, void * buf, char letter);
int ide_write_sectors(unsigned char drive, unsigned char numsects, unsigned int lba,
	unsigned short es, unsigned int edi);
unsigned int AHCI_BASE = 0;

#define HBA_PxCMD_ST    0x0001
#define HBA_PxCMD_FRE   0x0010
#define HBA_PxCMD_FR    0x4000
#define HBA_PxCMD_CR    0x8000


#define	SATA_SIG_ATA	0x00000101	// SATA drive
#define	SATA_SIG_ATAPI	0xEB140101	// SATAPI drive
#define	SATA_SIG_SEMB	0xC33C0101	// Enclosure management bridge
#define	SATA_SIG_PM	0x96690101	// Port multiplier

#define AHCI_DEV_NULL 0
#define AHCI_DEV_SATA 1
#define AHCI_DEV_SEMB 2
#define AHCI_DEV_PM 3
#define AHCI_DEV_SATAPI 4

#define HBA_PORT_IPM_ACTIVE 1
#define HBA_PORT_DET_PRESENT 3

#define ATA_SECTSIZE 512

#define ATA_LBA_MODE (1<<6)

#define ATA_MAXLBA28 ((1 << 28) - 1)
#define ATA_MAXLBA48 ((1l << 48) - 1)

// status
#define ATA_STS_ERR (1 << 0)    // error
#define ATA_STS_DRQ (1 << 3)    // data transfer requested
#define ATA_STS_BSY (1 << 7)    // busy

// commands
#define ATA_CMD_READ_SECTORS 0x20
#define ATA_CMD_READ_DMA_EXT 0x25

#define DISK_TYPE_SATA 	0x00
#define DISK_TYPE_SATAPI 0x01
#define DISK_TYPE_SATA_AHCI	0x02
#define DISK_TYPE_USB	0x3
#define DISK_TYPE_PCI_IDE	0x4


typedef enum
{
	FIS_TYPE_REG_H2D = 0x27,	// Register FIS - host to device
	FIS_TYPE_REG_D2H = 0x34,	// Register FIS - device to host
	FIS_TYPE_DMA_ACT = 0x39,	// DMA activate FIS - device to host
	FIS_TYPE_DMA_SETUP = 0x41,	// DMA setup FIS - bidirectional
	FIS_TYPE_DATA = 0x46,	// Data FIS - bidirectional
	FIS_TYPE_BIST = 0x58,	// BIST activate FIS - bidirectional
	FIS_TYPE_PIO_SETUP = 0x5F,	// PIO setup FIS - device to host
	FIS_TYPE_DEV_BITS = 0xA1,	// Set device bits FIS - device to host
} FIS_TYPE;
typedef struct tagFIS_REG_H2D
{
	// unsigned int 0
	uint8_t  fis_type;	// FIS_TYPE_REG_H2D

	uint8_t  pmport : 4;	// Port multiplier
	uint8_t  rsv0 : 3;		// Reserved
	uint8_t  c : 1;		// 1: Command, 0: Control

	uint8_t  command;	// Command register
	uint8_t  featurel;	// Feature register, 7:0

						// unsigned int 1
	uint8_t  lba0;		// LBA low register, 7:0
	uint8_t  lba1;		// LBA mid register, 15:8
	uint8_t  lba2;		// LBA high register, 23:16
	uint8_t  device;		// Device register

							// unsigned int 2
	uint8_t  lba3;		// LBA register, 31:24
	uint8_t  lba4;		// LBA register, 39:32
	uint8_t  lba5;		// LBA register, 47:40
	uint8_t  featureh;	// Feature register, 15:8

						// unsigned int 3
	uint8_t  countl;		// Count register, 7:0
	uint8_t  counth;		// Count register, 15:8
	uint8_t  icc;		// Isochronous command completion
	uint8_t  control;	// Control register

						// unsigned int 4
	uint8_t  rsv1[4];	// Reserved
} FIS_REG_H2D;
typedef struct tagFIS_REG_D2H
{
	// unsigned int 0
	uint8_t  fis_type;    // FIS_TYPE_REG_D2H

	uint8_t  pmport : 4;    // Port multiplier
	uint8_t  rsv0 : 2;      // Reserved
	uint8_t  i : 1;         // Interrupt bit
	uint8_t  rsv1 : 1;      // Reserved

	uint8_t  status;      // Status register
	uint8_t  error;       // Error register

						  // unsigned int 1
	uint8_t  lba0;        // LBA low register, 7:0
	uint8_t  lba1;        // LBA mid register, 15:8
	uint8_t  lba2;        // LBA high register, 23:16
	uint8_t  device;      // Device register

						  // unsigned int 2
	uint8_t  lba3;        // LBA register, 31:24
	uint8_t  lba4;        // LBA register, 39:32
	uint8_t  lba5;        // LBA register, 47:40
	uint8_t  rsv2;        // Reserved

						  // unsigned int 3
	uint8_t  countl;      // Count register, 7:0
	uint8_t  counth;      // Count register, 15:8
	uint8_t  rsv3[2];     // Reserved

						  // unsigned int 4
	uint8_t  rsv4[4];     // Reserved
} FIS_REG_D2H;
typedef struct tagFIS_DATA
{
	// unsigned int 0
	uint8_t  fis_type;	// FIS_TYPE_DATA

	uint8_t  pmport : 4;	// Port multiplier
	uint8_t  rsv0 : 4;		// Reserved

	uint8_t  rsv1[2];	// Reserved

						// unsigned int 1 ~ N
	uint32_t data[1];	// Payload
} FIS_DATA;
typedef struct tagFIS_PIO_SETUP
{
	// unsigned int 0
	uint8_t  fis_type;	// FIS_TYPE_PIO_SETUP

	uint8_t  pmport : 4;	// Port multiplier
	uint8_t  rsv0 : 1;		// Reserved
	uint8_t  d : 1;		// Data transfer direction, 1 - device to host
	uint8_t  i : 1;		// Interrupt bit
	uint8_t  rsv1 : 1;

	uint8_t  status;		// Status register
	uint8_t  error;		// Error register

						// unsigned int 1
	uint8_t  lba0;		// LBA low register, 7:0
	uint8_t  lba1;		// LBA mid register, 15:8
	uint8_t  lba2;		// LBA high register, 23:16
	uint8_t  device;		// Device register

							// unsigned int 2
	uint8_t  lba3;		// LBA register, 31:24
	uint8_t  lba4;		// LBA register, 39:32
	uint8_t  lba5;		// LBA register, 47:40
	uint8_t  rsv2;		// Reserved

						// unsigned int 3
	uint8_t  countl;		// Count register, 7:0
	uint8_t  counth;		// Count register, 15:8
	uint8_t  rsv3;		// Reserved
	uint8_t  e_status;	// New value of status register

						// unsigned int 4
	uint16_t tc;		// Transfer count
	uint8_t  rsv4[2];	// Reserved
} FIS_PIO_SETUP;
typedef struct tagFIS_DMA_SETUP
{
	// unsigned int 0
	uint8_t  fis_type;	// FIS_TYPE_DMA_SETUP

	uint8_t  pmport : 4;	// Port multiplier
	uint8_t  rsv0 : 1;		// Reserved
	uint8_t  d : 1;		// Data transfer direction, 1 - device to host
	uint8_t  i : 1;		// Interrupt bit
	uint8_t  a : 1;            // Auto-activate. Specifies if DMA Activate FIS is needed

	uint8_t  rsved[2];       // Reserved

							 //unsigned int 1&2

	uint64_t DMAbufferID;    // DMA Buffer Identifier. Used to Identify DMA buffer in host memory. SATA Spec says host specific and not in Spec. Trying AHCI spec might work.

							 //unsigned int 3
	uint32_t rsvd;           //More reserved

							 //unsigned int 4
	uint32_t DMAbufOffset;   //unsigned char offset into buffer. First 2 bits must be 0

							 //unsigned int 5
	uint32_t TransferCount;  //Number of unsigned chars to transfer. Bit 0 must be 0

							 //unsigned int 6
	uint32_t resvd;          //Reserved

} FIS_DMA_SETUP;

typedef volatile struct tagHBA_PORT
{
	uint32_t clb;		// 0x00, command list base address, 1K-unsigned char aligned
	uint32_t clbu;		// 0x04, command list base address upper 32 bits
	uint32_t fb;		// 0x08, FIS base address, 256-unsigned char aligned
	uint32_t fbu;		// 0x0C, FIS base address upper 32 bits
	uint32_t is;		// 0x10, interrupt status
	uint32_t ie;		// 0x14, interrupt enable
	uint32_t cmd;		// 0x18, command and status
	uint32_t rsv0;		// 0x1C, Reserved
	uint32_t tfd;		// 0x20, task file data
	uint32_t sig;		// 0x24, signature
	uint32_t ssts;		// 0x28, SATA status (SCR0:SStatus)
	uint32_t sctl;		// 0x2C, SATA control (SCR2:SControl)
	uint32_t serr;		// 0x30, SATA error (SCR1:SError)
	uint32_t sact;		// 0x34, SATA active (SCR3:SActive)
	uint32_t ci;		// 0x38, command issue
	uint32_t sntf;		// 0x3C, SATA notification (SCR4:SNotification)
	uint32_t fbs;		// 0x40, FIS-based switch control
	uint32_t rsv1[11];	// 0x44 ~ 0x6F, Reserved
	uint32_t vendor[4];	// 0x70 ~ 0x7F, vendor specific
} HBA_PORT;
typedef volatile struct tagHBA_MEM
{
	// 0x00 - 0x2B, Generic Host Control
	uint32_t cap;		// 0x00, Host capability
	uint32_t ghc;		// 0x04, Global host control
	uint32_t is;		// 0x08, Interrupt status
	uint32_t pi;		// 0x0C, Port implemented
	uint32_t vs;		// 0x10, Version
	uint32_t ccc_ctl;	// 0x14, Command completion coalescing control
	uint32_t ccc_pts;	// 0x18, Command completion coalescing ports
	uint32_t em_loc;		// 0x1C, Enclosure management location
	uint32_t em_ctl;		// 0x20, Enclosure management control
	uint32_t cap2;		// 0x24, Host capabilities extended
	uint32_t bohc;		// 0x28, BIOS/OS handoff control and status

						// 0x2C - 0x9F, Reserved
	uint8_t  rsv[0xA0 - 0x2C];

	// 0xA0 - 0xFF, Vendor specific registers
	uint8_t  vendor[0x100 - 0xA0];

	// 0x100 - 0x10FF, Port control registers
	HBA_PORT	ports[1];	// 1 ~ 32
} HBA_MEM;

typedef struct tagHBA_CMD_HEADER
{
	// DW0
	uint8_t  cfl : 5;		// Command FIS length in unsigned intS, 2 ~ 16
	uint8_t  a : 1;		// ATAPI
	uint8_t  w : 1;		// Write, 1: H2D, 0: D2H
	uint8_t  p : 1;		// Prefetchable

	uint8_t  r : 1;		// Reset
	uint8_t  b : 1;		// BIST
	uint8_t  c : 1;		// Clear busy upon R_OK
	uint8_t  rsv0 : 1;		// Reserved
	uint8_t  pmp : 4;		// Port multiplier port

	uint16_t prdtl;		// Physical region descriptor table length in entries

						// DW1
	volatile
		uint32_t prdbc;		// Physical region descriptor unsigned char count transferred

							// DW2, 3
	uint32_t ctba;		// Command table descriptor base address
	uint32_t ctbau;		// Command table descriptor base address upper 32 bits

						// DW4 - 7
	uint32_t rsv1[4];	// Reserved
} HBA_CMD_HEADER;

typedef struct tagHBA_PRDT_ENTRY
{
	uint32_t dba;		// Data base address
	uint32_t dbau;		// Data base address upper 32 bits
	uint32_t rsv0;		// Reserved

						// DW3
	uint32_t dbc : 22;		// unsigned char count, 4M max
	uint32_t rsv1 : 9;		// Reserved
	uint32_t i : 1;		// Interrupt on completion
} HBA_PRDT_ENTRY;

typedef struct tagHBA_CMD_TBL
{
	// 0x00
	uint8_t  cfis[64];	// Command FIS

						// 0x40
	uint8_t  acmd[16];	// ATAPI command, 12 or 16 unsigned chars

						// 0x50
	uint8_t  rsv[48];	// Reserved

						// 0x80
	HBA_PRDT_ENTRY	prdt_entry[1];	// Physical region descriptor table entries, 0 ~ 65535
} HBA_CMD_TBL;


// Check device type
int check_type(HBA_PORT *port)
{
	uint32_t ssts = port->ssts;

	uint8_t ipm = (ssts >> 8) & 0x0F;
	uint8_t det = ssts & 0x0F;

	if (det != HBA_PORT_DET_PRESENT)	// Check drive status
		return AHCI_DEV_NULL;
	if (ipm != HBA_PORT_IPM_ACTIVE)
		return AHCI_DEV_NULL;

	switch (port->sig)
	{
	case SATA_SIG_ATAPI:
		return AHCI_DEV_SATAPI;
	case SATA_SIG_SEMB:
		return AHCI_DEV_SEMB;
	case SATA_SIG_PM:
		return AHCI_DEV_PM;
	default:
		return AHCI_DEV_SATA;
	}
}


typedef struct __attribute__((packed)) tDiskDev {
	unsigned long long sectorsCount;
	unsigned char type;
	unsigned char structNo;
	void * link;
	char data[512];
}
DiskDev;
typedef struct __attribute__((packed)) tATA {
	unsigned short port;
	unsigned short slavebit;
	unsigned int LBA28;
	unsigned long long LBA48;
	unsigned char isLBA48Supported;
}
ATA;
typedef struct __attribute__((packed)) _AHCI {
	HBA_PORT * port;
} AHCI;
ATA ATADevices[4];
AHCI AHCIDevices[32];
uint AHCICount = 0, ataCount = 0;
DiskDev diskDevices[64];
char deviceCount = 0, dcount = 0;
unsigned short returned[256];

void detectAta();
void ATAInit() {
	deviceCount = 0;
	dcount = 0;
	detectAta();
}
int ataRead28(char drive_id, unsigned long long LBA, char cnt, void * addr);
int ataWrite28(char drive_id, unsigned long long LBA, char cnt, void * addr);
int ataWrite48(char drive_id, unsigned long long LBA, char cnt, void * addr);
int ataRead48(char drive_id, unsigned long long LBA, char cnt, void * addr);
//Чтение
void ataRead(char drive_id, unsigned long long LBA, char cnt, void * addr) {
	if (ATADevices[drive_id].isLBA48Supported == 1)
		return ataRead48(drive_id, LBA, cnt, addr);
	else
		return ataRead28(drive_id, LBA, cnt, addr);
}
//Запись
int ataWrite(char drive_id, unsigned long long LBA, char cnt, void * addr) {
	if (ATADevices[drive_id].isLBA48Supported == 1)
		return ataWrite48(drive_id, LBA, cnt, addr);
	else
		return ataWrite28(drive_id, LBA, cnt, addr);
}

int ataRead28(char drive_id, unsigned long long LBA, char cnt, void * addr) {
	ATA device = ATADevices[drive_id];
	unsigned short port = device.port;
	unsigned char slavebit = device.slavebit;
	//LBA 28 PIO
	outportb(port + 6, 0xE0 | (slavebit) | ((LBA >> 24) & 0x0F));
	outportb(port + 2, cnt);
	outportb(port + 3, LBA & 0xFF);
	outportb(port + 4, (LBA >> 8) & 0xFF);
	outportb(port + 5, (LBA >> 16) & 0xFF);
	outportb(port + 7, 0x20);
	unsigned short dcr = 0x3F6;
	if (port == 0x170) dcr = 0x376;
	char x = inportb(port + 7);
	x = inportb(port + 7);
	x = inportb(port + 7);
	x = inportb(port + 7);
	while (x & 0x80)
		x = inportb(port + 7);
	for (int i = 0; i < 256 * cnt; i++) {
		unsigned short h = inportw(port); *((unsigned char *)addr + i * 2) = h & 0xFF; *((unsigned char *)addr + i * 2 + 1) = (h >> 8) & 0xFF;
	}
	return 1;
}

int ataWrite28(char drive_id, unsigned long long LBA, char cnt, void * addr) {
	ATA device = ATADevices[drive_id];
	unsigned short port = device.port;
	unsigned char slavebit = device.slavebit;
	//LBA 48
	outportb(port + 6, 0xE0 | (slavebit) | ((LBA >> 24) & 0x0F));
	outportb(port + 2, cnt);
	outportb(port + 3, LBA & 0xFF);
	outportb(port + 4, (LBA >> 8) & 0xFF);
	outportb(port + 5, (LBA >> 16) & 0xFF);
	outportb(port + 7, 0x30);
	unsigned short dcr = 0x3F6;
	if (port == 0x170) dcr = 0x376;
	char xx = inportb(port + 7);
	while (xx & 0x80) xx = inportb(port + 7);
	for (int i = 0; i < 256 * cnt; i++) {
		outportw(port, ((*((unsigned char *)addr + i * 2 + 1)) << 8) + (*((unsigned char *)addr + i * 2)));
		//Flush command
		outportb(port + 7, 0xE7);
		char x = inportb(port + 7);
		while (x & 0x80) x = inportb(port + 7); //Wait until not busy
	}
	return 1;
}

int ataWrite48(char drive_id, unsigned long long LBA, char cnt, void * addr) {
	ATA device = ATADevices[drive_id];
	unsigned short port = device.port;
	unsigned char slavebit = device.slavebit;
	outportb(port + 6, 0x40 | slavebit);
	outportb(port + 2, 0);
	outportb(port + 3, (LBA >> 24) & 0xFF); //LBA4
	outportb(port + 4, (LBA >> 32) & 0xFF); //LBA5
	outportb(port + 5, (LBA >> 40) & 0xFF); //LBA6
	outportb(port + 2, cnt);
	outportb(port + 3, (LBA >> 0) & 0xFF); //LBA1
	outportb(port + 4, (LBA >> 8) & 0xFF); //LBA2
	outportb(port + 5, (LBA >> 16) & 0xFF); //LBA3
	outportb(port + 7, 0x34);
	unsigned short dcr = 0x3F6;
	if (port == 0x170) dcr = 0x376;
	char xx = inportb(port + 7);
	while (xx & 0x80) xx = inportb(port + 7);
	for (int i = 0; i < 256 * cnt; i++) {
		outportw(port, ((*((unsigned char *)addr + i * 2 + 1)) << 8) + (*((unsigned char *)addr + i * 2)));
		//Flush command
		outportb(port + 7, 0xE7);
		char x = inportb(port + 7);
		while (x & 0x80) x = inportb(port + 7); //Wait until not busy
	}
	return 1;
}

int ataRead48(char drive_id, unsigned long long LBA, char cnt, void * addr) {
	ATA device = ATADevices[drive_id];
	unsigned short port = device.port;
	unsigned char slavebit = device.slavebit;
	outportb(port + 6, 0x40 | slavebit);
	outportb(port + 2, 0);
	outportb(port + 3, (LBA >> 24) & 0xFF);
	outportb(port + 4, (LBA >> 32) & 0xFF);
	outportb(port + 5, (LBA >> 40) & 0xFF);
	outportb(port + 2, cnt);
	outportb(port + 3, (LBA >> 0) & 0xFF);
	outportb(port + 4, (LBA >> 8) & 0xFF);
	outportb(port + 5, (LBA >> 16) & 0xFF);
	outportb(port + 7, 0x24);
	unsigned short dcr = 0x3F6;
	if (port == 0x170) dcr = 0x376;
	char x = inportb(port + 7);
	x = inportb(port + 7);
	x = inportb(port + 7);
	x = inportb(port + 7);
	while (x & 0x80)
		x = inportb(port + 7);
	for (int i = 0; i < 256 * cnt; i++) {
		unsigned short h = inportw(port); *((unsigned char *)addr + i * 2) = h & 0xFF; *((unsigned char *)addr + i * 2 + 1) = (h >> 8) & 0xFF;
	}
	return 1;

}
void checkDiskPatritions(uint i);
int detect_devtype(int port, int slavebit) {

	//Выбираем диск
	outportb(port + 6, 0xA0 | slavebit);
	//Кол-во секторов 0
	outportb(port + 2, 0);
	//LBA 0
	outportb(port + 3, 0);
	outportb(port + 4, 0);
	outportb(port + 5, 0);
	//IDENTIFY command
	outportb(port + 7, 0xEC);
	char x = inportb(port + 7);
	while (x & 0x80) {
		x = inportb(port + 7);
		if (x & 1) break;
	}
	if (x == 0 || x & 1) {
		//Диска нету/ошибка
		return 0;
	}
	unsigned short u = inportw(port);
	returned[0] = u;
	for (int i = 1; i < 256; i++)
	{
		returned[i] = inportw(port);
	}
	ATADevices[deviceCount].port = port;
	ATADevices[deviceCount].slavebit = slavebit;
	if (returned[83] & (1 << 10)) {
		ATADevices[deviceCount].isLBA48Supported = 1;
		ATADevices[deviceCount].LBA48 = ((long long)returned[103] << 48) + ((long long)returned[102] << 32) + ((long long)returned[101] << 16) + (long long)returned[100];
		diskDevices[dcount].sectorsCount = ATADevices[deviceCount].LBA48;

		//	diskDevices[dcount].readSectors = &ReadController;
		//	diskDevices[dcount].writeSectors = &WriteController;
		diskDevices[dcount].structNo = deviceCount;
		diskDevices[dcount].type = DISK_TYPE_SATA;
		if (ATADevices[deviceCount].LBA48 == 0)
			return 0;
	}
	else {
		ATADevices[deviceCount].isLBA48Supported = 0;
		ATADevices[deviceCount].LBA28 = (returned[61] << 16) + returned[60];
		diskDevices[dcount].sectorsCount = ATADevices[deviceCount].LBA28;
		//	diskDevices[dcount].readSectors = &ReadController;
			//diskDevices[dcount].writeSectors = &WriteController;
		diskDevices[dcount].structNo = deviceCount;
		diskDevices[dcount].type = DISK_TYPE_SATA;
		if (ATADevices[deviceCount].LBA28 == 0)
			return 0;
	}
	for (int oou1 = 0; oou1 < 256; oou1++) {
		diskDevices[dcount].data[oou1 * 2] = returned[oou1] >> 8;
		diskDevices[dcount].data[oou1 * 2 + 1] = returned[oou1] & 0xFF;
	}

	checkDiskPatritions(dcount);
	dcount++;
	deviceCount++;
	return 1;
}


void detectAta() {
	detect_devtype(0x170, 00);
	detect_devtype(0x170, 16);
	detect_devtype(0x1F0, 00);
	detect_devtype(0x1F0, 16);
	kprintf("Detected %d ATA disks!\n", deviceCount);
	for (int i = 0; i < deviceCount; i++)
		addDevice(ATADevices[i].port, ATADevices[i].slavebit, 0);
}
void start_cmd(HBA_PORT *port);
void stop_cmd(HBA_PORT *port);
int find_cmdslot(HBA_PORT *m_port);
HBA_MEM * abar;
void port_rebase(HBA_PORT *port, int portno)
{
	stop_cmd(port);	// Stop command engine

					// Command list offset: 1K*portno
					// Command list entry size = 32
					// Command list entry maxim count = 32
					// Command list maxim size = 32*32 = 1K per port
	port->clb = (uint)malloc(1024 + 4196);
	port->clb = (((uint)port->clb) / 2048) * 2048 + 2048;
	port->clbu = 0;
	memset((void*)(port->clb), 0, 1024);

	// FIS offset: 32K+256*portno
	// FIS entry size = 256 unsigned chars per port
	port->fb = (uint)malloc(256 + 4196);
	port->fb = (((uint)port->fb) / 2048) * 2048 + 2048;
	port->fbu = 0;
	memset((void*)(port->fb), 0, 256);

	// Command table offset: 40K + 8K*portno
	// Command table size = 256*32 = 8K per port
	HBA_CMD_HEADER *cmdheader = (HBA_CMD_HEADER*)(port->clb);
	for (int i = 0; i < 32; i++)
	{
		cmdheader[i].prdtl = 8;	// 8 prdt entries per command table
								// 256 unsigned chars per command table, 64+16+48+16*8
								// Command table offset: 40K + 8K*portno + cmdheader_index*256
		cmdheader[i].ctba = (uint)malloc(256 + 4196);
		cmdheader[i].ctba = (((uint)cmdheader[i].ctba) / 2048) * 2048 + 2048;
		cmdheader[i].ctbau = 0;
		memset((void*)cmdheader[i].ctba, 0, 256);
	}

	start_cmd(port);	// Start command engine
}

// Start command engine
void start_cmd(HBA_PORT *port)
{
	// Wait until CR (bit15) is cleared
	while (port->cmd & HBA_PxCMD_CR)
		//kprintf("cmd: %d %d\n", port->cmd, port->cmd & HBA_PxCMD_CR);
		;
	port->cmd |= HBA_PxCMD_FRE;
	port->cmd |= HBA_PxCMD_ST;
}

// Stop command engine
void stop_cmd(HBA_PORT *port)
{
	//	kprintf("%x\n", port->cmd);
		// Clear ST (bit0)
	port->cmd &= ~HBA_PxCMD_ST;
	port->cmd &= ~HBA_PxCMD_FRE;

	//port->cmd &= ~HBA_PxCMD_FRE;
	// Wait until FR (bit14), CR (bit15) are cleared
	while (1)
	{
		if (port->cmd & HBA_PxCMD_FR)
			continue;
		if (port->cmd & HBA_PxCMD_CR)
			continue;
		break;
	}

	// Clear FRE (bit4)
}

#define HBA_PxIS_TFES   (1 << 30)
void DMA_SETUP(HBA_PORT *port)
{

}
bool _read(HBA_PORT *port, unsigned long long starth, unsigned long long count, uint16_t *buf)
{
	port->is = (uint32_t)-1;		// Clear pending interrupt bits
	int spin = 0; // Spin lock timeout counter
	int slot = find_cmdslot(port);
	if (slot == -1)
		return false;

	HBA_CMD_HEADER *cmdheader = (HBA_CMD_HEADER*)port->clb;
	cmdheader += slot;
	cmdheader->cfl = sizeof(FIS_REG_H2D) / sizeof(uint32_t);	// Command FIS size
	cmdheader->w = 0;		// Read from device
	cmdheader->prdtl = (uint16_t)((count - 1) >> 4) + 1;	// PRDT entries count

	HBA_CMD_TBL *cmdtbl = (HBA_CMD_TBL*)(cmdheader->ctba);
	memset(cmdtbl, 0, sizeof(HBA_CMD_TBL) +
		(cmdheader->prdtl - 1) * sizeof(HBA_PRDT_ENTRY));
	int i = 0;
	// 8K u8s (16 sectors) per PRDT
	for (i = 0; i < cmdheader->prdtl - 1; i++)
	{
		cmdtbl->prdt_entry[i].dba = (uint32_t)buf;
		cmdtbl->prdt_entry[i].dbc = 8 * 1024 - 1;	// 8K u8s (this value should always be set to 1 less than the actual value)
		cmdtbl->prdt_entry[i].i = 1;
		buf += 4 * 1024;	// 4K u16s
		count -= 16;	// 16 sectors
	}
	// Last entry
	cmdtbl->prdt_entry[i].dba = (uint32_t)buf;
	cmdtbl->prdt_entry[i].dbc = (count << 9) - 1;	// 512 u8s per sector
	cmdtbl->prdt_entry[i].i = 1;

	// Setup command
	FIS_REG_H2D *cmdfis = (FIS_REG_H2D*)(&cmdtbl->cfis);

	cmdfis->fis_type = FIS_TYPE_REG_H2D;
	cmdfis->c = 1;	// Command
	cmdfis->command = 0x25;

	cmdfis->lba0 = (uint8_t)starth;
	cmdfis->lba1 = (uint8_t)(starth >> 8);
	cmdfis->lba2 = (uint8_t)(starth >> 16);
	cmdfis->device = 1 << 6;	// LBA mode

	cmdfis->lba3 = (uint8_t)(starth >> 24);
	cmdfis->lba4 = (uint8_t)(starth >> 32);
	cmdfis->lba5 = (uint8_t)(starth >> 40);

	cmdfis->countl = count & 0xFF;
	cmdfis->counth = (count >> 8) & 0xFF;

	// The below loop waits until the port is no longer busy before issuing a new command
	while ((port->tfd & (ATA_DEV_BUSY | ATA_DEV_DRQ)) && spin < 1000000)
	{
		spin++;
	}
	if (spin == 1000000)
	{
		kprintf("Port is hung\n");
		return 0;
	}

	port->ci = 1 << slot;	// Issue command

							// Wait for completion
	while (1)
	{
		// In some longer duration reads, it may be helpful to spin on the DPS bit 
		// in the PxIS port field as well (1 << 5)
		Wait(1);
		if ((port->ci & (1 << slot)) == 0)
			break;
		if (port->is & HBA_PxIS_TFES)	// Task file error
		{
			kprintf("Read disk error %x\n", (uint)starth);
			return 0;
		}
	}

	// Check again
	if (port->is & HBA_PxIS_TFES)
	{
		kprintf("Read disk error %x\n", (uint)starth);
		return 0;
	}

	return true;
}

bool _rread(HBA_PORT *port, uint16_t *buf)
{
	port->is = (uint32_t)-1;		// Clear pending interrupt bits
	int spin = 0; // Spin lock timeout counter
	int slot = find_cmdslot(port);
	if (slot == -1)
		return false;

	HBA_CMD_HEADER *cmdheader = (HBA_CMD_HEADER*)port->clb;
	cmdheader += slot;
	cmdheader->cfl = sizeof(FIS_REG_H2D) / sizeof(uint32_t);	// Command FIS size
	cmdheader->w = 0;		// Read from device
	cmdheader->prdtl = 1;	// PRDT entries count

	HBA_CMD_TBL *cmdtbl = (HBA_CMD_TBL*)(cmdheader->ctba);
	memset(cmdtbl, 0, sizeof(HBA_CMD_TBL) +
		(cmdheader->prdtl - 1) * sizeof(HBA_PRDT_ENTRY));
	int i = 0;
	cmdtbl->prdt_entry[0].dba = (uint32_t)buf;
	cmdtbl->prdt_entry[0].dbc = 511;	// 512 u8s per sector
	cmdtbl->prdt_entry[0].i = 1;
	// Setup command
	FIS_REG_H2D *cmdfis = (FIS_REG_H2D*)(&cmdtbl->cfis);
	memset(cmdfis, 0, sizeof(FIS_REG_H2D));
	cmdfis->fis_type = FIS_TYPE_REG_H2D;
	cmdfis->c = 1;	// Command
	cmdfis->command = 0xEC;

	// The below loop waits until the port is no longer busy before issuing a new command
	while ((port->tfd & (ATA_DEV_BUSY | ATA_DEV_DRQ)) && spin < 1000000)
	{
		spin++;
	}
	if (spin == 1000000)
	{
		kprintf("Port is hung\n");
		return 0;
	}

	port->ci = 1 << slot;	// Issue command

							// Wait for completion
	while (1)
	{
		// In some longer duration reads, it may be helpful to spin on the DPS bit 
		// in the PxIS port field as well (1 << 5)
		Wait(1);
		if ((port->ci & (1 << slot)) == 0)
			break;
		if (port->is & HBA_PxIS_TFES)	// Task file error
		{
			kprintf("Read disk error\n");
			return 0;
		}
	}

	// Check again
	if (port->is & HBA_PxIS_TFES)
	{
		kprintf("Read disk error\n");
		return 0;
	}

	return true;
}


int write_port(HBA_PORT *port, unsigned long long starth, unsigned int count,
	uint buf)
{
	port->is = (uint32_t)-1;		// Clear pending interrupt bits
	int spin = 0; // Spin lock timeout counter
	int slot = find_cmdslot(port);
	if (slot == -1)
		return false;

	HBA_CMD_HEADER *cmdheader = (HBA_CMD_HEADER*)port->clb;
	cmdheader += slot;
	cmdheader->cfl = sizeof(FIS_REG_H2D) / sizeof(uint32_t);	// Command FIS size
	cmdheader->w = 1;		// Read from device
	cmdheader->prdtl = (uint16_t)((count - 1) >> 4) + 1;	// PRDT entries count

	HBA_CMD_TBL *cmdtbl = (HBA_CMD_TBL*)(cmdheader->ctba);
	memset(cmdtbl, 0, sizeof(HBA_CMD_TBL) +
		(cmdheader->prdtl - 1) * sizeof(HBA_PRDT_ENTRY));
	int i = 0;
	// 8K u8s (16 sectors) per PRDT
	for (i = 0; i < cmdheader->prdtl - 1; i++)
	{
		cmdtbl->prdt_entry[i].dba = (uint32_t)buf;
		cmdtbl->prdt_entry[i].dbc = 8 * 1024 - 1;	// 8K u8s (this value should always be set to 1 less than the actual value)
		cmdtbl->prdt_entry[i].i = 1;
		buf += 4 * 1024;	// 4K u16s
		count -= 16;	// 16 sectors
	}
	// Last entry
	cmdtbl->prdt_entry[i].dba = (uint32_t)buf;
	cmdtbl->prdt_entry[i].dbc = (count << 9) - 1;	// 512 u8s per sector
	cmdtbl->prdt_entry[i].i = 1;

	// Setup command
	FIS_REG_H2D *cmdfis = (FIS_REG_H2D*)(&cmdtbl->cfis);

	cmdfis->fis_type = FIS_TYPE_REG_H2D;
	cmdfis->c = 1;	// Command
	cmdfis->command = 0x35;

	cmdfis->lba0 = (uint8_t)starth;
	cmdfis->lba1 = (uint8_t)(starth >> 8);
	cmdfis->lba2 = (uint8_t)(starth >> 16);
	cmdfis->device = 1 << 6;	// LBA mode

	cmdfis->lba3 = (uint8_t)(starth >> 24);
	cmdfis->lba4 = (uint8_t)(starth >> 32);
	cmdfis->lba5 = (uint8_t)(starth >> 40);

	cmdfis->countl = count & 0xFF;
	cmdfis->counth = (count >> 8) & 0xFF;

	// The below loop waits until the port is no longer busy before issuing a new command
	while ((port->tfd & (ATA_DEV_BUSY | ATA_DEV_DRQ)) && spin < 1000000)
	{
		spin++;
	}
	if (spin == 1000000)
	{
		kprintf("Port is hung\n");
		return 0;
	}

	port->ci = 1 << slot;	// Issue command

							// Wait for completion
	while (1)
	{
		// In some longer duration reads, it may be helpful to spin on the DPS bit 
		// in the PxIS port field as well (1 << 5)
		Wait(1);
		if ((port->ci & (1 << slot)) == 0)
			break;
		if (port->is & HBA_PxIS_TFES)	// Task file error
		{
			kprintf("Read disk error\n");
			return 0;
		}
	}

	// Check again
	if (port->is & HBA_PxIS_TFES)
	{
		kprintf("Read disk error\n");
		return 0;
	}

	return true;
}
// Find a free command list slot
int find_cmdslot(HBA_PORT *m_port)
{
	// If not set in SACT and CI, the slot is free
	uint32_t slots = (m_port->sact | m_port->ci);
	//kprintf("Slots: %x\n", slots);
	uint qq = (abar->cap & 0x0f00) >> 8;
	for (int i = 0; i < qq; i++)
	{
		if ((slots & 1) == 0)
			return i;
		slots >>= 1;
	}
	kprintf("Cannot find free command list entry\n");
	return -1;
}
typedef struct PACKED identify_data
{
	uint16_t flags; // 0
	uint16_t unused1[9]; // 9
	char     serial[20]; // 19
	uint16_t unused2[3]; // 22
	char     firmware[8]; // 26
	char    model[40]; // 46
	uint16_t sectors_per_int; // 47
	uint16_t unused3; // 48
	uint16_t capabilities[2]; // 50
	uint16_t unused4[2]; // 52
	uint16_t valid_ext_data; // 53
	uint16_t unused5[5]; // 58
	uint16_t size_of_rw_mult; // 59
	uint32_t sectors_28; // 61
	uint16_t unused6[38]; // 99
	uint64_t sectors_48; // 103
	uint16_t unused7[2]; // 105
	uint16_t phys_log_size; // 106
	uint16_t unused8[10]; // 116
	uint32_t sector_size; // 118
	uint16_t unused9[137];
} identify_data;

void _probe_port(void *abar_temp1)
{
	HBA_MEM *abar_temp = (HBA_MEM *)abar_temp1;
	// Search disk in impelemented ports
	uint pi = abar_temp->pi;
	int i = 0;
	while (i < 32)
	{
		if (pi & 1)
		{
			uint cmd_st = (abar_temp->ports[i].cmd) & 0x1;
			uint cmd_fre = (abar_temp->ports[i].cmd) & 0x10;
			int dt = check_type((HBA_PORT *)&abar_temp->ports[i]);
			if (dt == AHCI_DEV_SATA)
			{
				kprintf("SATA drive found at port %d\n", i);
				abar = abar_temp;


				unsigned short * buf = (unsigned short *)malloc(16 * 512);
				buf[0] = 1;
				int res = 0;
				int jj = 0;

				port_rebase(&abar_temp->ports[i], i);

				abar_temp->ports[i].cmd |= 0x10;
				abar_temp->ports[i].cmd |= 0x1;
				kprintf(" AHCI device initialized\n");

				res = _read(&abar->ports[i], 0, 16, buf);
				if (res != 0) {
					_rread(&abar->ports[i], buf);
					kprintf(" Read test passed.\n");
					diskDevices[dcount].structNo = AHCICount;
					diskDevices[dcount].sectorsCount = ((identify_data*)buf)->sectors_48;

					for (int oou1 = 0; oou1 < 256; oou1++) {
						diskDevices[dcount].data[oou1 * 2] = buf[oou1] >> 8;
						diskDevices[dcount].data[oou1 * 2 + 1] = buf[oou1] & 0xFF;
					}
					AHCIDevices[AHCICount].port = &abar_temp->ports[i];

					diskDevices[dcount].type = DISK_TYPE_SATA_AHCI;
					AHCICount++;

					kprintf("Added disk device #%d, structNo = %x, type = %x, size %dMBytes\n", dcount, diskDevices[dcount].structNo, diskDevices[dcount].type, diskDevices[dcount].sectorsCount >> 11);
					checkDiskPatritions(dcount);
					dcount++;

				}
				free(buf);
			}
			else if (dt == AHCI_DEV_SATAPI)
			{
				//kprintf("\nSATAPI drive found at port %d\n", i);
			}
			else if (dt == AHCI_DEV_SEMB)
			{
				//kprintf("\nSEMB drive found at port %d\n", i);
			}
			else if (dt == AHCI_DEV_PM)
			{
				//kprintf("\nPM drive found at port %d\n", i);
			}
			else
			{
				//kprintf("\nNo drive found at port %d\n", i);
			}
		}
		pi >>= 1;
		i++;
	}

	kprintf("AHCI probing complete\n");
}

uint readingInProcess = 0, writingInProcess = 0;
//Чтение
uint ReadController(unsigned long long LBA, char cnt, void * addr, unsigned char param) {

	readingInProcess = 1;
	if (diskDevices[param].type == DISK_TYPE_SATA) {
		char drive_id = diskDevices[param].structNo;
		if (ATADevices[drive_id].isLBA48Supported == 1)
			return ataRead48(drive_id, LBA, cnt, addr);
		else
			return ataRead28(drive_id, LBA, cnt, addr);
	}
	else if (diskDevices[param].type == DISK_TYPE_SATA_AHCI)
	{
		return _read(AHCIDevices[diskDevices[param].structNo].port, (long long)LBA, cnt, (uint16_t*)addr);
	}
	else if (diskDevices[param].type == DISK_TYPE_USB)
	{
		uint z = LBA & 0xFFFFFFFF;
		return _read10usb(diskDevices[param].link, (uint)z, (uint)cnt, addr);

	}
	else if (diskDevices[param].type == DISK_TYPE_PCI_IDE)
	{
		return ide_read_sectors(diskDevices[param].structNo, (uchar)cnt, (uint)LBA, 0x8, (uint)addr);
	}
	readingInProcess = 0;

	//unlockTaskSwitch();
}
//Запись
uint WriteController(unsigned long long LBA, char cnt, void * addr, unsigned char param) {
	
	if (diskDevices[param].type == DISK_TYPE_SATA) {
		char drive_id = diskDevices[param].structNo;
		if (ATADevices[drive_id].isLBA48Supported == 1)
			return ataWrite48(drive_id, LBA, cnt, addr);
		else
			return ataWrite28(drive_id, LBA, cnt, addr);
	}
	else if (diskDevices[param].type == DISK_TYPE_SATA_AHCI)
	{
		return write_port(AHCIDevices[diskDevices[param].structNo].port, LBA, (unsigned long long)cnt, (uint)addr);
	}
	else if (diskDevices[param].type == DISK_TYPE_USB)
	{
		uint z = LBA & 0xFFFFFFFF;
		return _write10usb(diskDevices[param].link, (uint)z, (uint)cnt, addr);
	}
	else if (diskDevices[param].type == DISK_TYPE_PCI_IDE)
	{
		return ide_write_sectors(diskDevices[param].structNo, (uchar)cnt, (uint)LBA, 0x8, (uint)addr);
	}
	
}
#define ulon unsigned long long
typedef struct __attribute((packed)) _LogicDrive {
	uint avaliable;
	uint diskId;
	ulon size;
	ulon diskOffset;
	uint type;
	uint structId;
} LogicDrive;
typedef struct PACKED _fat32drive
{
	uint FatStart;
	uint reserved;
	uint RootEntry;
	uint * FATTable;

}f32drive;
f32drive f32drives[26];
LogicDrive drives[26];
void checkFS(uint di)
{
	char bootSect[512];
	ReadFromDisk((long long)0, 1, &bootSect, di);
	if (bootSect[0x52] == 'F'&&bootSect[0x53] == 'A'&&bootSect[0x54] == 'T'&&bootSect[0x55] == '3')
	{
		char sectorsPerCluster = bootSect[0x0D];
		u16 reserved = *((u16*)&bootSect[0xE]);
		char FATTableCount = bootSect[0x10];
		uint RootEntry = *((uint*)&bootSect[0x2C]);
		uint SectorsPerFat = *((uint*)&bootSect[0x24]);
		uint FatStart = SectorsPerFat * FATTableCount + reserved;
		//printTextToWindow(7, mywin, "~~%x %x~~~~~~~~~~~~~~", reserved);
		f32drives[di].FatStart = FatStart;
		f32drives[di].FATTable = (uint*)malloc(512 * SectorsPerFat);
		f32drives[di].reserved = reserved;
		f32drives[di].RootEntry = RootEntry;
		uint lost = SectorsPerFat;
		for (int i = 0; i < SectorsPerFat >> 4; i++) {
			ReadFromDisk((unsigned long long)reserved + (long long)i * 16, lost < 16 ? lost : 16, (void*)((uint)i * 16 * 512 + (uint)f32drives[di].FATTable), di);
			lost -= 16;
		}
		//kprintf("((((((%x %x)))))))", f32drives[di].FATTable[0x2bc], SectorsPerFat);
		//Wait(10000);
	}
	else
		drives[di].type = 0xff;
}
uint lastLetter = 0, bootedFrom = 999;
void printMem(unsigned char * a, uint c)
{
	for (int i = 0; i < c; i++)
	{
		if (a[i] < 0x10)
			kprintf("0%x", (int)a[i]);
		else
			kprintf("%x", (int)a[i]);
		if ((i % 24) != 23)
			kprintf("-");
		else if (i != c - 1)
			kprintf("\n");
	}

}
int checkPatrition(uint startSec, uint did)
{
	uchar * bootSect = malloc(512);
	uint res = ReadController(startSec, 1, bootSect, did); //printMem(bootSect, 512);
	if (!res)
		return 0;

	unsigned int * q = (uint*)bootSect;
	uint found = 0;
	for (int j = 0; j < 4; j++)
	{

		if (!((uchar)bootSect[0] == 0xEB))
		{
			if (*((uint*)((uint)q + 454 + j * 16)) > 0) {
				if (1)
				{
					int uy = 0;
					for (int lt = 0; lt < 26; lt++)
						if (!drives[lt].avaliable) {
							uy = lt;
							break;
						}

					kprintf("Found patrition. Letter: %c:, size %dMBytes\n", 'A' + uy, (*((uint*)&bootSect[446 + j * 16 + 12])) >> 11);
					found = 1;
					drives[uy].avaliable = 1;
					drives[uy].diskId = did;
					drives[uy].diskOffset = (*((uint*)&bootSect[446 + j * 16 + 8]));
					drives[uy].size = (*((uint*)&bootSect[446 + j * 16 + 12]));
					drives[uy].type = 0;
					if (check_sign(uy))
					{
						kprintf("We are booted from that patrition!\n");
						bootedFrom = uy;
					}
					checkFS(uy);
					if (uy == lastLetter)
						lastLetter++;
				}
			}
		}
		//kprintf()
	}
	free(bootSect);
	return found;
}
int ReadFromDisk(unsigned long long LBA, uint count, void * buf, char letter)
{
	if (drives[letter].avaliable)
		return ReadController(drives[letter].diskOffset + LBA, count, buf, drives[letter].diskId);
	else
		kprintf("No drive%x!", letter);
	return 1;
}
int WriteToDisk(unsigned long long LBA, uint count, void * buf, char letter)
{
	if (drives[letter].avaliable)
		return WriteController(drives[letter].diskOffset + LBA, count, buf, drives[letter].diskId);
	else
		kprintf("No drive!");
	return 1;
}

int check_sign(int dr)
{
	char bootSect[512];
	ReadFromDisk(0, 1, &bootSect, dr);
	if (bootSect[512 - 13] == 'S')
		if (bootSect[512 - 12] == 'T')
			if (bootSect[512 - 11] == 'A')
				if (bootSect[512 - 10] == 'R')
					if (bootSect[512 - 9] == 'T')
						if (bootSect[512 - 8] == 'U')
							if (bootSect[512 - 7] == 'P')
								if (bootSect[512 - 6] == ' ')
									if (bootSect[512 - 5] == ' ')
										if (bootSect[512 - 4] == ' ')
											if (bootSect[512 - 3] == ' ')
												return 1;
	return 0;
}


void checkDiskPatritions(uint i)
{
	int uty = 0;
	for (int ltt = 0; ltt < 26; ltt++)
		if (!drives[ltt].avaliable) {
			uty = ltt; break;
		}

	char bootSect[512];
	uint *q = (uint*)&bootSect;
	checkPatrition(0, i);
	ReadController(1, 1, &bootSect, i);
	if (*((unsigned long long *)&bootSect) == 0x5452415020494645ULL)
	{
		q = (uint*)&bootSect;
		unsigned long long sect = *((unsigned long long*)((uint)q + 0x48));
		uint count = *((uint*)((uint)&bootSect + 0x50));
		for (int j = 0; j < count; j++) {
			ReadController(sect + ((j) >> 2), 1, &bootSect, i);
			ulon startLBA = *((ulon*)((uint)&bootSect + 0x20 + (j << 7)));
			ulon  endLBA = *((ulon*)((uint)&bootSect + 0x28 + (j << 7)));
			//kprintf("%x %x\n", (uint)startLBA, (uint)endLBA);
			ulon  attrs = *((ulon*)((uint)&bootSect + 0x30 + (j << 7)));
			uint copy = 0;
			for (int o = 0; o < 26; o++)
			{
				if (drives[o].diskId == i && drives[o].diskOffset == (uint)startLBA)
					copy = 1;
			}
			if (copy)
				continue;
			int uy = 0;
			for (int lt = 0; lt < 26; lt++)
				if (!drives[lt].avaliable) {
					uy = lt;
					break;
				}
			kprintf("%x", drives[0].avaliable);
			kprintf("Found patrition. Letter: %c:, size %dMBytes\n", 'A' + uy, (endLBA - startLBA + 1) >> 11);
			drives[uy].avaliable = 1;
			drives[uy].diskId = i;
			drives[uy].diskOffset = startLBA;
			drives[uy].size = endLBA - startLBA + 1; drives[uy].type = 0; //checkFS(uy);
			if (check_sign(uy))
			{
				kprintf("We are booted from that patrition!\n");
				bootedFrom = uy;
			}
			checkFS(uy);
			if (uy == lastLetter)
				lastLetter++;

		}
	}
	else if (!drives[uty].avaliable)
	{
		int uy = 0;
		for (int lt = 0; lt < 26; lt++)
			if (!drives[lt].avaliable) {
				uy = lt; break;
			}

		kprintf("Found patrition. Letter: %c:, size %dMBytes\n", 'A' + uy, diskDevices[i].sectorsCount >> 11);
		drives[uy].avaliable = 1;
		drives[uy].diskId = i;
		drives[uy].diskOffset = 0;
		drives[uy].size = diskDevices[i].sectorsCount; drives[uy].type = 0;// checkFS(uy);
		ReadController(0, 1, &bootSect, i);
		if(check_sign(uy))
		{
			kprintf("We are booted from that patrition!\n");
			bootedFrom = uy;
		}
		checkFS(uy);
		if (uy == lastLetter)
			lastLetter++;
	}
}
void makeLogicDrives()
{

}