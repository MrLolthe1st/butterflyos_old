#define DEVICE_UNKOWN 0x00
#define DEVICE_ATA 0x01
#define DEVICE_PCI 0x02
#define DEVICE_USB 0x03
char a[4][8] = {
	"UNKNOWN\0",
	"ATA\0",
	"PCI\0",
	"0"
};
typedef struct __attribute__((packed)) _Device {
	unsigned short port;
	unsigned short bits;
	unsigned int UID;
	unsigned char deviceType;
}
device;
device devices[64];
char devicesCount = 0;
void initDevices() {
	devicesCount = 0;
	//memset(&devices, 0, 64 * sizeof(device));
	printString("Devices module initialized!\n");
};
unsigned int last = 0;
unsigned int GenerateUID() {
	unsigned int id = (last + 1);
	for (int i = 0; i < last % 16; i++)
		id += (id % 6) * ((id % 4) + 1);
	last = id;
	return last;
}
device addDevice(unsigned short port, unsigned char bits, unsigned char deviceType) {
	printString("Added device #");
	// printInt(devicesCount + 1, 2);

	unsigned int UID = GenerateUID();

	kprintf(" at port 0x%x UID = 0x%x", port, UID);
	printString(" DevType: ");
	printString(&a[deviceType + 1]);
	printString("\n");
	devices[devicesCount].port = port;
	devices[devicesCount].UID = UID;
	devices[devicesCount].bits = bits;
	devicesCount++;
	return devices[devicesCount - 1];
}