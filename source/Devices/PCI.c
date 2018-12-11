#define PCI_MAKE_ID(bus, dev, func)     ((bus) << 16) | ((dev) << 11) | ((func) << 8)

#define PCI_C_STORAGE 0x1

#define PCI_SC_AHCI   0x6
// I/O Ports
#define PCI_CONFIG_ADDR                 0xcf8
#define PCI_CONFIG_DATA                 0xcfC

// Header Type
#define PCI_TYPE_MULTIFUNC              0x80
#define PCI_TYPE_GENERIC                0x00
#define PCI_TYPE_PCI_BRIDGE             0x01
#define PCI_TYPE_CARDBUS_BRIDGE         0x02

// PCI Configuration Registers
#define PCI_CONFIG_VENDOR_ID            0x00
#define PCI_CONFIG_DEVICE_ID            0x02
#define PCI_CONFIG_COMMAND              0x04
#define PCI_CONFIG_STATUS               0x06
#define PCI_CONFIG_REVISION_ID          0x08
#define PCI_CONFIG_PROG_INTF            0x09
#define PCI_CONFIG_SUBCLASS             0x0a
#define PCI_CONFIG_CLASS_CODE           0x0b
#define PCI_CONFIG_CACHELINE_SIZE       0x0c
#define PCI_CONFIG_LATENCY              0x0d
#define PCI_CONFIG_HEADER_TYPE          0x0e
#define PCI_CONFIG_BIST                 0x0f

// Type 0x00 (Generic) Configuration Registers
#define PCI_CONFIG_BAR0                 0x10
#define PCI_CONFIG_BAR1                 0x14
#define PCI_CONFIG_BAR2                 0x18
#define PCI_CONFIG_BAR3                 0x1c
#define PCI_CONFIG_BAR4                 0x20
#define PCI_CONFIG_BAR5                 0x24
#define PCI_CONFIG_CARDBUS_CIS          0x28
#define PCI_CONFIG_SUBSYSTEM_VENDOR_ID  0x2c
#define PCI_CONFIG_SUBSYSTEM_DEVICE_ID  0x2e
#define PCI_CONFIG_EXPANSION_ROM        0x30
#define PCI_CONFIG_CAPABILITIES         0x34
#define PCI_CONFIG_INTERRUPT_LINE       0x3c
#define PCI_CONFIG_INTERRUPT_PIN        0x3d
#define PCI_CONFIG_MIN_GRANT            0x3e
#define PCI_CONFIG_MAX_LATENCY          0x3f

// ------------------------------------------------------------------------------------------------
// PCI BAR

#define PCI_BAR_IO                      0x01
#define PCI_BAR_LOWMEM                  0x02
#define PCI_BAR_64                      0x04
#define PCI_BAR_PREFETCH                0x08

#define VENDOR_INTEL                    0x8086

// PCI Classes
#define PCI_CLASS_LEGACY                0x00
#define PCI_CLASS_STORAGE               0x01
#define PCI_CLASS_NETWORK               0x02
#define PCI_CLASS_DISPLAY               0x03
#define PCI_CLASS_MULTIMEDIA            0x04
#define PCI_CLASS_MEMORY                0x05
#define PCI_CLASS_BRIDGE_DEVICE         0x06
#define PCI_CLASS_COMMUNICATION         0x07
#define PCI_CLASS_PERIHPERALS           0x08
#define PCI_CLASS_INPUT_DEVICES         0x09
#define PCI_CLASS_DOCKING_STATION       0x0a
#define PCI_CLASS_PROCESSOR             0x0b
#define PCI_CLASS_SERIAL_BUS            0x0c
#define PCI_CLASS_WIRELESS              0x0d
#define PCI_CLASS_INTELLIGENT_IO        0x0e
#define PCI_CLASS_SATELLITE             0x0f
#define PCI_CLASS_CRYPT                 0x10
#define PCI_CLASS_SIGNAL_PROCESSING     0x11
#define PCI_CLASS_UNDEFINED             0xff

// Undefined Class
#define PCI_UNCLASSIFIED                0x0000
#define PCI_VGA_COMPATIBLE              0x0001

// Mass Storage Controller
#define PCI_STORAGE_SCSI                0x0100
#define PCI_STORAGE_IDE                 0x0101
#define PCI_STORAGE_FLOPPY              0x0102
#define PCI_STORAGE_IPI                 0x0103
#define PCI_STORAGE_RAID                0x0104
#define PCI_STORAGE_ATA                 0x0105
#define PCI_STORAGE_SATA                0x0106
#define PCI_STORAGE_OTHER               0x0180

// Network Controller
#define PCI_NETWORK_ETHERNET            0x0200
#define PCI_NETWORK_TOKEN_RING          0x0201
#define PCI_NETWORK_FDDI                0x0202
#define PCI_NETWORK_ATM                 0x0203
#define PCI_NETWORK_ISDN                0x0204
#define PCI_NETWORK_WORLDFIP            0x0205
#define PCI_NETWORK_PICGMG              0x0206
#define PCI_NETWORK_OTHER               0x0280

// Display Controller
#define PCI_DISPLAY_VGA                 0x0300
#define PCI_DISPLAY_XGA                 0x0301
#define PCI_DISPLAY_3D                  0x0302
#define PCI_DISPLAY_OTHER               0x0380

// Multimedia Controller
#define PCI_MULTIMEDIA_VIDEO            0x0400
#define PCI_MULTIMEDIA_AUDIO            0x0401
#define PCI_MULTIMEDIA_PHONE            0x0402
#define PCI_MULTIMEDIA_AUDIO_DEVICE     0x0403
#define PCI_MULTIMEDIA_OTHER            0x0480

// Memory Controller
#define PCI_MEMORY_RAM                  0x0500
#define PCI_MEMORY_FLASH                0x0501
#define PCI_MEMORY_OTHER                0x0580

// Bridge Device
#define PCI_BRIDGE_HOST                 0x0600
#define PCI_BRIDGE_ISA                  0x0601
#define PCI_BRIDGE_EISA                 0x0602
#define PCI_BRIDGE_MCA                  0x0603
#define PCI_BRIDGE_PCI                  0x0604
#define PCI_BRIDGE_PCMCIA               0x0605
#define PCI_BRIDGE_NUBUS                0x0606
#define PCI_BRIDGE_CARDBUS              0x0607
#define PCI_BRIDGE_RACEWAY              0x0608
#define PCI_BRIDGE_OTHER                0x0680

// Simple Communication Controller
#define PCI_COMM_SERIAL                 0x0700
#define PCI_COMM_PARALLEL               0x0701
#define PCI_COMM_MULTIPORT              0x0702
#define PCI_COMM_MODEM                  0x0703
#define PCI_COMM_GPIB                   0x0704
#define PCI_COMM_SMARTCARD              0x0705
#define PCI_COMM_OTHER                  0x0780

// Base System Peripherals
#define PCI_SYSTEM_PIC                  0x0800
#define PCI_SYSTEM_DMA                  0x0801
#define PCI_SYSTEM_TIMER                0x0802
#define PCI_SYSTEM_RTC                  0x0803
#define PCI_SYSTEM_PCI_HOTPLUG          0x0804
#define PCI_SYSTEM_SD                   0x0805
#define PCI_SYSTEM_OTHER                0x0880

// Input Devices
#define PCI_INPUT_KEYBOARD              0x0900
#define PCI_INPUT_PEN                   0x0901
#define PCI_INPUT_MOUSE                 0x0902
#define PCI_INPUT_SCANNER               0x0903
#define PCI_INPUT_GAMEPORT              0x0904
#define PCI_INPUT_OTHER                 0x0980

// Docking Stations
#define PCI_DOCKING_GENERIC             0x0a00
#define PCI_DOCKING_OTHER               0x0a80

// Processors
#define PCI_PROCESSOR_386               0x0b00
#define PCI_PROCESSOR_486               0x0b01
#define PCI_PROCESSOR_PENTIUM           0x0b02
#define PCI_PROCESSOR_ALPHA             0x0b10
#define PCI_PROCESSOR_POWERPC           0x0b20
#define PCI_PROCESSOR_MIPS              0x0b30
#define PCI_PROCESSOR_CO                0x0b40

// Serial Bus Controllers
#define PCI_SERIAL_FIREWIRE             0x0c00
#define PCI_SERIAL_ACCESS               0x0c01
#define PCI_SERIAL_SSA                  0x0c02
#define PCI_SERIAL_USB                  0x0c03
#define PCI_SERIAL_FIBER                0x0c04
#define PCI_SERIAL_SMBUS                0x0c05

#define PCI_SERIAL_USB_UHCI             0x00
#define PCI_SERIAL_USB_OHCI             0x10
#define PCI_SERIAL_USB_EHCI             0x20
#define PCI_SERIAL_USB_XHCI             0x30
#define PCI_SERIAL_USB_OTHER            0x80

// Wireless Controllers
#define PCI_WIRELESS_IRDA               0x0d00
#define PCI_WIRLESSS_IR                 0x0d01
#define PCI_WIRLESSS_RF                 0x0d10
#define PCI_WIRLESSS_BLUETOOTH          0x0d11
#define PCI_WIRLESSS_BROADBAND          0x0d12
#define PCI_WIRLESSS_ETHERNET_A         0x0d20
#define PCI_WIRLESSS_ETHERNET_B         0x0d21
#define PCI_WIRELESS_OTHER              0x0d80

// Intelligent I/O Controllers
#define PCI_INTELLIGENT_I2O             0x0e00

// Satellite Communication Controllers
#define PCI_SATELLITE_TV                0x0f00
#define PCI_SATELLITE_AUDIO             0x0f01
#define PCI_SATELLITE_VOICE             0x0f03
#define PCI_SATELLITE_DATA              0x0f04

// Encryption/Decryption Controllers
#define PCI_CRYPT_NETWORK               0x1000
#define PCI_CRYPT_ENTERTAINMENT         0x1001
#define PCI_CRYPT_OTHER                 0x1080

// Data Acquisition and Signal Processing Controllers
#define PCI_SP_DPIO                     0x1100
#define PCI_SP_OTHER                    0x1180

// ------------------------------------------------------------------------------------------------
const char *PciDeviceName(unsigned int vendorId, unsigned int deviceId)
{
	return "Unknown Device";
}

// ------------------------------------------------------------------------------------------------
const char *PciClassName(unsigned int classCode, unsigned int subclass, unsigned int progIntf)
{
	switch ((classCode << 8) | subclass)
	{
	case PCI_VGA_COMPATIBLE:            return "VGA-Compatible Device";
	case PCI_STORAGE_SCSI:              return "SCSI Storage Controller";
	case PCI_STORAGE_IDE:               return "IDE Interface";
	case PCI_STORAGE_FLOPPY:            return "Floppy Disk Controller";
	case PCI_STORAGE_IPI:               return "IPI Bus Controller";
	case PCI_STORAGE_RAID:              return "RAID Bus Controller";
	case PCI_STORAGE_ATA:               return "ATA Controller";
	case PCI_STORAGE_SATA:              return "SATA Controller";
	case PCI_STORAGE_OTHER:             return "Mass Storage Controller";
	case PCI_NETWORK_ETHERNET:          return "Ethernet Controller";
	case PCI_NETWORK_TOKEN_RING:        return "Token Ring Controller";
	case PCI_NETWORK_FDDI:              return "FDDI Controller";
	case PCI_NETWORK_ATM:               return "ATM Controller";
	case PCI_NETWORK_ISDN:              return "ISDN Controller";
	case PCI_NETWORK_WORLDFIP:          return "WorldFip Controller";
	case PCI_NETWORK_PICGMG:            return "PICMG Controller";
	case PCI_NETWORK_OTHER:             return "Network Controller";
	case PCI_DISPLAY_VGA:               return "VGA-Compatible Controller";
	case PCI_DISPLAY_XGA:               return "XGA-Compatible Controller";
	case PCI_DISPLAY_3D:                return "3D Controller";
	case PCI_DISPLAY_OTHER:             return "Display Controller";
	case PCI_MULTIMEDIA_VIDEO:          return "Multimedia Video Controller";
	case PCI_MULTIMEDIA_AUDIO:          return "Multimedia Audio Controller";
	case PCI_MULTIMEDIA_PHONE:          return "Computer Telephony Device";
	case PCI_MULTIMEDIA_AUDIO_DEVICE:   return "Audio Device";
	case PCI_MULTIMEDIA_OTHER:          return "Multimedia Controller";
	case PCI_MEMORY_RAM:                return "RAM Memory";
	case PCI_MEMORY_FLASH:              return "Flash Memory";
	case PCI_MEMORY_OTHER:              return "Memory Controller";
	case PCI_BRIDGE_HOST:               return "Host Bridge";
	case PCI_BRIDGE_ISA:                return "ISA Bridge";
	case PCI_BRIDGE_EISA:               return "EISA Bridge";
	case PCI_BRIDGE_MCA:                return "MicroChannel Bridge";
	case PCI_BRIDGE_PCI:                return "PCI Bridge";
	case PCI_BRIDGE_PCMCIA:             return "PCMCIA Bridge";
	case PCI_BRIDGE_NUBUS:              return "NuBus Bridge";
	case PCI_BRIDGE_CARDBUS:            return "CardBus Bridge";
	case PCI_BRIDGE_RACEWAY:            return "RACEway Bridge";
	case PCI_BRIDGE_OTHER:              return "Bridge Device";
	case PCI_COMM_SERIAL:               return "Serial Controller";
	case PCI_COMM_PARALLEL:             return "Parallel Controller";
	case PCI_COMM_MULTIPORT:            return "Multiport Serial Controller";
	case PCI_COMM_MODEM:                return "Modem";
	case PCI_COMM_OTHER:                return "Communication Controller";
	case PCI_SYSTEM_PIC:                return "PIC";
	case PCI_SYSTEM_DMA:                return "DMA Controller";
	case PCI_SYSTEM_TIMER:              return "Timer";
	case PCI_SYSTEM_RTC:                return "RTC";
	case PCI_SYSTEM_PCI_HOTPLUG:        return "PCI Hot-Plug Controller";
	case PCI_SYSTEM_SD:                 return "SD Host Controller";
	case PCI_SYSTEM_OTHER:              return "System Peripheral";
	case PCI_INPUT_KEYBOARD:            return "Keyboard Controller";
	case PCI_INPUT_PEN:                 return "Pen Controller";
	case PCI_INPUT_MOUSE:               return "Mouse Controller";
	case PCI_INPUT_SCANNER:             return "Scanner Controller";
	case PCI_INPUT_GAMEPORT:            return "Gameport Controller";
	case PCI_INPUT_OTHER:               return "Input Controller";
	case PCI_DOCKING_GENERIC:           return "Generic Docking Station";
	case PCI_DOCKING_OTHER:             return "Docking Station";
	case PCI_PROCESSOR_386:             return "386";
	case PCI_PROCESSOR_486:             return "486";
	case PCI_PROCESSOR_PENTIUM:         return "Pentium";
	case PCI_PROCESSOR_ALPHA:           return "Alpha";
	case PCI_PROCESSOR_MIPS:            return "MIPS";
	case PCI_PROCESSOR_CO:              return "CO-Processor";
	case PCI_SERIAL_FIREWIRE:           return "FireWire (IEEE 1394)";
	case PCI_SERIAL_SSA:                return "SSA";
	case PCI_SERIAL_USB:
		switch (progIntf)
		{
		case PCI_SERIAL_USB_UHCI:       return "USB (UHCI)";
		case PCI_SERIAL_USB_OHCI:       return "USB (OHCI)";
		case PCI_SERIAL_USB_EHCI:       return "USB2";
		case PCI_SERIAL_USB_XHCI:       return "USB3";
		case PCI_SERIAL_USB_OTHER:      return "USB Controller";
		default:                        return "Unknown USB Class";
		}
		break;
	case PCI_SERIAL_FIBER:              return "Fiber Channel";
	case PCI_SERIAL_SMBUS:              return "SMBus";
	case PCI_WIRELESS_IRDA:             return "iRDA Compatible Controller";
	case PCI_WIRLESSS_IR:               return "Consumer IR Controller";
	case PCI_WIRLESSS_RF:               return "RF Controller";
	case PCI_WIRLESSS_BLUETOOTH:        return "Bluetooth";
	case PCI_WIRLESSS_BROADBAND:        return "Broadband";
	case PCI_WIRLESSS_ETHERNET_A:       return "802.1a Controller";
	case PCI_WIRLESSS_ETHERNET_B:       return "802.1b Controller";
	case PCI_WIRELESS_OTHER:            return "Wireless Controller";
	case PCI_INTELLIGENT_I2O:           return "I2O Controller";
	case PCI_SATELLITE_TV:              return "Satellite TV Controller";
	case PCI_SATELLITE_AUDIO:           return "Satellite Audio Controller";
	case PCI_SATELLITE_VOICE:           return "Satellite Voice Controller";
	case PCI_SATELLITE_DATA:            return "Satellite Data Controller";
	case PCI_CRYPT_NETWORK:             return "Network and Computing Encryption Device";
	case PCI_CRYPT_ENTERTAINMENT:       return "Entertainment Encryption Device";
	case PCI_CRYPT_OTHER:               return "Encryption Device";
	case PCI_SP_DPIO:                   return "DPIO Modules";
	case PCI_SP_OTHER:                  return "Signal Processing Controller";
	}

	return "Unknown PCI Class";
}
typedef struct PciBar
{
	union
	{
		void *address;
		unsigned short port;
	} u;
	unsigned int size;
	unsigned int flags;
} PciBar;

// ------------------------------------------------------------------------------------------------
typedef struct PciDeviceInfo
{
	unsigned short vendorId;
	unsigned short deviceId;
	unsigned char classCode;
	unsigned char subclass;
	unsigned char progIntf;
} PciDeviceInfo;
typedef struct PciFunction {
	unsigned short vendorid;
	unsigned char bus;
	unsigned char dev;
	unsigned char func;
	unsigned char class;
	unsigned char subclass;
} PciFunction;
typedef struct PciDriver
{
	void(*init)(unsigned int id, PciDeviceInfo *info);
} PciDriver;


// ------------------------------------------------------------------------------------------------
void PciWrite32(unsigned int id, unsigned int reg, unsigned int data)
{
	unsigned int address = 0x80000000 | id | (reg & 0xfc);
	outportd(PCI_CONFIG_ADDR, address);
	outportd(PCI_CONFIG_DATA, data);
}

unsigned char PciRead8(unsigned int id, unsigned int reg)
{
	unsigned int addr = 0x80000000 | id | (reg & 0xfc);
	outportd(PCI_CONFIG_ADDR, addr);
	return inportb(PCI_CONFIG_DATA + (reg & 0x03));
}

// ------------------------------------------------------------------------------------------------
unsigned short PciRead16(unsigned int id, unsigned int reg)
{
	unsigned int addr = 0x80000000 | id | (reg & 0xfc);
	outportd(PCI_CONFIG_ADDR, addr);
	return inportw(PCI_CONFIG_DATA + (reg & 0x02));
}

// ------------------------------------------------------------------------------------------------
unsigned int PciRead32(unsigned int id, unsigned int reg)
{
	unsigned int addr = 0x80000000 | id | (reg & 0xfc);
	outportd(PCI_CONFIG_ADDR, addr);
	return inportd(PCI_CONFIG_DATA);
}
// ------------------------------------------------------------------------------------------------
void PciWrite16(unsigned int id, unsigned int reg, unsigned short data)
{
	unsigned int address = 0x80000000 | id | (reg & 0xfc);
	outportd(PCI_CONFIG_ADDR, address);
	outportw(PCI_CONFIG_DATA + (reg & 0x02), data);
}

// ------------------------------------------------------------------------------------------------
void PciWrite8(unsigned int id, unsigned int reg, unsigned char data)
{
	unsigned int address = 0x80000000 | id | (reg & 0xfc);
	outportd(PCI_CONFIG_ADDR, address);
	outportb(PCI_CONFIG_DATA + (reg & 0x03), data);
}




// ------------------------------------------------------------------------------------------------
static void PciReadBar(unsigned int id, unsigned int index, unsigned int *address, unsigned int *mask)
{
	unsigned int reg = PCI_CONFIG_BAR0 + index * sizeof(unsigned int);

	// Get address
	*address = PciRead32(id, reg);

	// Find out size of the bar
	PciWrite32(id, reg, 0xffffffff);
	*mask = PciRead32(id, reg);

	// Restore adddress
	PciWrite32(id, reg, *address);
}
#define ADDR 0xCF8
#define DATA 0xCFC
#define ENABLE (1 << 31)
static uint
pcireadl(uchar bus, uchar dev, uchar func, uchar offset)
{
	ulong addr;

	addr = ENABLE | (bus << 16) | (dev << 11) | (func << 8) | (offset & 0xFC);

	outportd(ADDR, addr);
	return inportd(DATA);
}
uint
pcibar(PciFunction *f, uchar bar)
{
	return pcireadl(f->bus, f->dev, f->func, 0x10 + 4 * bar);
}
// ------------------------------------------------------------------------------------------------
void PciGetBar(PciBar *bar, unsigned int id, unsigned int index)
{
	// Read pci bar register
	unsigned int addressLow;
	unsigned int maskLow;
	PciReadBar(id, index, &addressLow, &maskLow);

	if (addressLow & PCI_BAR_64)
	{
		// 64-bit mmio
		unsigned int addressHigh;
		unsigned int maskHigh;
		PciReadBar(id, index + 1, &addressHigh, &maskHigh);

		bar->u.address = (void *)((0) | (addressLow & ~0xf));
		bar->size = ~((0) | (maskLow & ~0xf)) + 1;
		bar->flags = addressLow & 0xf;
	}
	else if (addressLow & PCI_BAR_IO)
	{
		// i/o register
		bar->u.port = (unsigned short)(addressLow & ~0x3);
		bar->size = (unsigned short)(~(maskLow & ~0x3) + 1);
		bar->flags = addressLow & 0x3;
	}
	else
	{
		// 32-bit mmio
		bar->u.address = (void *)(addressLow & ~0xf);
		bar->size = ~(maskLow & ~0xf) + 1;
		bar->flags = addressLow & 0xf;
	}
}
/*
const PciDriver g_pciDriverTable[] =
{
	{ UhciInit },
	{ EhciInit },
	{ 0 },
};
*/
struct pci_func
{
	uint32_t vendor_id;
	uint32_t device_id;
	uint32_t bus_num;
	uint32_t slot_num;
	uint32_t mmio_reg;
	uint32_t interrupt_reg;
	uint32_t mmio_reg_addr;
	uint32_t mmio_reg_size;
	uint32_t irq_line;
	uint64_t start_virtual_address;
};

unsigned long long *pages_for_ahci_start;
unsigned long long *pages_for_ahci_end;
struct pci_func pci_e1000, pci_ahci;
static inline void sysOutLong(unsigned short port, uint32_t val)
{
	__asm__("outl %0, %1"
		: : "a"(val), "Nd"(port));
}
static inline uint32_t sysInLong(unsigned short port)
{
	uint32_t ret;
	__asm__("inl %1, %0"
		: "=a"(ret) : "Nd"(port));
	return ret;
}
unsigned short pciConfigReadWord(unsigned short bus, unsigned short slot,
	unsigned short func, unsigned short offset)
{
	uint32_t address;
	uint32_t lbus = (uint32_t)bus;
	uint32_t lslot = (uint32_t)slot;
	uint32_t lfunc = (uint32_t)func;
	unsigned short tmp = 0;
	address = (uint32_t)((lbus << 16) | (lslot << 11) | (lfunc << 8)
		| (offset & 0xfc) | ((uint32_t)0x80000000));
	sysOutLong(0xCF8, address);
	tmp = (unsigned short)((sysInLong(0xCFC) >> ((offset & 2) * 8)) & 0xffff);
	return (tmp);
}
uint32_t ReadWord(unsigned short bus, unsigned short slot, unsigned short func,
	unsigned short offset)
{
	uint32_t address;
	uint32_t lbus = (uint32_t)bus;
	uint32_t lslot = (uint32_t)slot;
	uint32_t lfunc = (uint32_t)func;
	uint32_t tmp = 0;
	address = (uint32_t)((lbus << 16) | (lslot << 11) | (lfunc << 8)
		| (offset & 0xfc) | ((uint32_t)0x80000000));
	sysOutLong(0xCF8, address);
	tmp = (uint32_t)(sysInLong(0xCFC) /* & 0xffff*/);
	return (tmp);
}
#define AHCI_MMIO_BUFFER 0xfebf0000
#define e1000_MMIO_BUFFER 0xfebc0000
void get_mmio_space_size(struct pci_func *pci_device)
{
	uint32_t address;
	uint32_t lbus = pci_device->bus_num;
	uint32_t lslot = pci_device->slot_num;
	uint32_t lfunc = 0;
	uint32_t tmp = 0;
	unsigned short offset = (unsigned short)(pci_device->mmio_reg | 0x0);
	address = (uint32_t)((lbus << 16) | (lslot << 11) | (lfunc << 8)
		| (offset & 0xfc) | ((uint32_t)0x80000000));
	kprintf("#%x#", address);
	pci_device->start_virtual_address = address;
	sysOutLong(0xCF8, address);
	sysOutLong(0xCFC, 0xffffffff);
	tmp = (ReadWord(pci_device->bus_num, pci_device->slot_num, 0,
		(pci_device->mmio_reg | 0x0)));
	kprintf("#%x#", tmp);
	pci_device->mmio_reg_size = (~tmp) + 1;
	sysOutLong(0xCF8, address);
	sysOutLong(0xCFC, pci_device->mmio_reg_addr);
}

void _rtl39_init(uint id, PciDeviceInfo *info);
void _ide_irq();
void _ehci_init(uint id, PciDeviceInfo *info);
void _uhci_init(unsigned int id, PciDeviceInfo *info);
void EthIntelInit(uint id, PciDeviceInfo *info);
int pci_scan_bus(struct pci_func *pci_device)
{
	int bus;
	int slot;
	unsigned short vendor, device;
	for (bus = 0; bus < 256; bus++)
	{
		for (slot = 0; slot < 32; slot++)
		{
			unsigned int id = PCI_MAKE_ID(bus, slot, 0);
			vendor = PciRead8(id, PCI_CONFIG_CLASS_CODE);
			device = PciRead8(id, PCI_CONFIG_SUBCLASS);
			if (vendor == 0x1
				&& device == 0x06)
			{
				pci_device->bus_num = bus;
				pci_device->slot_num = slot;
				pci_device->mmio_reg_addr = ReadWord(bus, slot, 0,
					(pci_device->mmio_reg | 0x0));
				pci_device->irq_line = (ReadWord(bus, slot, 0,
					(pci_device->interrupt_reg | 0x0)) & 0xff);
				return 1;
			}
		}
	}
	return 0;
}
uint iddd = 0;
IRQ_HANDLER1(irq_ideMast)
{
	_ide_irq();
}
IRQ_HANDLER1(irq_ideSlave)
{
	_ide_irq();
}

static void PciVisit(unsigned int bus, unsigned int dev, unsigned int func)
{


	unsigned int id = PCI_MAKE_ID(bus, dev, func);

	PciDeviceInfo info;
	PciFunction p;
	info.vendorId = PciRead16(id, PCI_CONFIG_VENDOR_ID);

	if (info.vendorId == 0xffff)
	{
		return;
	}

	info.deviceId = PciRead16(id, PCI_CONFIG_DEVICE_ID);
	info.progIntf = PciRead8(id, PCI_CONFIG_PROG_INTF);
	info.subclass = PciRead8(id, PCI_CONFIG_SUBCLASS);
	info.classCode = PciRead8(id, PCI_CONFIG_CLASS_CODE);
	if (info.classCode == 0x1 && info.subclass == 0x6)
	{
		pci_ahci.vendor_id = info.vendorId;
		pci_ahci.device_id = info.deviceId;
		pci_ahci.bus_num = bus;
		pci_ahci.slot_num = dev;
		pci_ahci.mmio_reg_addr = PciRead16(id,
			(pci_ahci.mmio_reg | 0x0));
		pci_ahci.irq_line = (PciRead16(id,
			(pci_ahci.interrupt_reg | 0x0)) & 0xff);
		iddd = id;
	}
	p.class = info.classCode;
	p.subclass = info.subclass;
	p.bus = bus;
	p.vendorid = info.vendorId;
	p.dev = dev;
	p.func = func;
	if (info.classCode == 0x01 && info.subclass == 0x01 && (info.progIntf == 0x8A || info.progIntf == 0x80)) {

		outportd((1 << 31) | (bus << 16) | (dev << 11) | (func << 8) | 8, 0xCF8); // Send the parameters.
		if ((inportd(0xCFC) >> 16) != 0xFFFF) { // If device exists (class isn't 0xFFFF)
												// Check if this device needs an IRQ assignment:
			outportd((1 << 31) | (bus << 16) | (dev << 11) | (func << 8) | 0x3C, 0xCF8); // Read the interrupt line field
			outportb(0xCFC, 0xFE); // Change the IRQ field to 0xFE
			outportd((1 << 31) | (bus << 16) | (dev << 11) | (func << 8) | 0x3C, 0xCF8); // Read the interrupt line field
			if ((inportd(0xCFC) & 0xFF) == 0xFE) {
				// This device needs an IRQ assignment.
			}
			else {
				// The device doesn't use IRQs, check if this is an Parallel IDE:
					// This is a Parallel IDE Controller which uses IRQs 14 and 15.
				inst(0x3E, &irq_ideMast, 0x8e);
				inst(0x3E, &irq_ideSlave, 0x8e);
				ide_initialize(0x1F0, 0x3F6, 0x170, 0x376, 0x000);
			}
		}
	}
	printTextToWindow(4, mywin, "%x:%x:%d 0x%x/0x%x: %s\n",
		(int)info.classCode, (int)info.subclass, (int)info.progIntf,
		(int)info.vendorId, (int)info.deviceId,
		(uint)PciClassName(info.classCode, info.subclass, info.progIntf)
	);

	_ehci_init(id, &info);
	EthIntelInit(id, &info);
	_uhci_init(id, &info);
	_rtl39_init(id, &info);
	/////while (!getKey());
	//PitWait(1000);
	//__pci_ata(id, &info);
	/*
	const PciDriver *driver = g_pciDriverTable;
	while (driver->init)
	{
		driver->init(id, &info);
		++driver;
	}
	*/
}
struct mem_req {
	uint64_t phys_addr, dest_addr;
	size_t len;
};
void _probe_port(void *abar_temp);
// ------------------------------------------------------------------------------------------------
void PciInit()
{
	kprintf("PCI initialization...\n");
	for (unsigned int bus = 0; bus < 256; ++bus)
	{
		for (unsigned int dev = 0; dev < 32; ++dev)
		{
			unsigned int baseId = PCI_MAKE_ID(bus, dev, 0);
			unsigned char headerType = PciRead8(baseId, PCI_CONFIG_HEADER_TYPE);
			unsigned int funcCount = headerType & PCI_TYPE_MULTIFUNC ? 8 : 1;

			for (unsigned int func = 0; func < funcCount; ++func)
			{
				PciVisit(bus, dev, func);
			}
		}
	}
	//return;
	kprintf("AHCI initialization...\n");
	unsigned int q = PciRead32(iddd, 0x24);
	_probe_port((void*)q);
	pcidone = 1;

}

