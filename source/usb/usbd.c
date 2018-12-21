#define USB_CLASS_INTF                  0x00
#define USB_CLASS_AUDIO                 0x01
#define USB_CLASS_COMM                  0x02
#define USB_CLASS_HID                   0x03
#define USB_CLASS_PHYSICAL              0x05
#define USB_CLASS_IMAGE                 0x06
#define USB_CLASS_PRINTER               0x07
#define USB_CLASS_STORAGE               0x08
#define USB_CLASS_HUB                   0x09
#define USB_CLASS_CDC_DATA              0x0a
#define USB_CLASS_SMART_CARD            0x0b
#define USB_CLASS_SECURITY              0x0d
#define USB_CLASS_VIDEO                 0x0e
#define USB_CLASS_HEALTHCARE            0x0f
#define USB_CLASS_DIAGNOSTIC            0xdc
#define USB_CLASS_WIRELESS              0xe0
#define USB_CLASS_MISC                  0xef
#define USB_CLASS_APP                   0xfe
#define USB_CLASS_VENDOR                0xff

// ------------------------------------------------------------------------------------------------
// USB Request Type

#define RT_TRANSFER_MASK                0x80
#define RT_DEV_TO_HOST                  0x80
#define RT_HOST_TO_DEV                  0x00

#define RT_TYPE_MASK                    0x60
#define RT_STANDARD                     0x00
#define RT_CLASS                        0x20
#define RT_VENDOR                       0x40

#define RT_RECIPIENT_MASK               0x1f
#define RT_DEV                          0x00
#define RT_INTF                         0x01
#define RT_ENDP                         0x02
#define RT_OTHER                        0x03

// ------------------------------------------------------------------------------------------------
// USB Device Requests

#define REQ_GET_STATUS                  0x00
#define REQ_CLEAR_FEATURE               0x01
#define REQ_SET_FEATURE                 0x03
#define REQ_SET_ADDR                    0x05
#define REQ_GET_DESC                    0x06
#define REQ_SET_DESC                    0x07
#define REQ_GET_CONF                    0x08
#define REQ_SET_CONF                    0x09
#define REQ_GET_INTF                    0x0a
#define REQ_SET_INTF                    0x0b
#define REQ_SYNC_FRAME                  0x0c

// ------------------------------------------------------------------------------------------------
// USB Hub Class Requests

#define REQ_CLEAR_TT_BUFFER             0x08
#define REQ_RESET_TT                    0x09
#define REQ_GET_TT_STATE                0x0a
#define REQ_STOP_TT                     0x0b

// ------------------------------------------------------------------------------------------------
// USB HID Interface Requests

#define REQ_GET_REPORT                  0x01
#define REQ_GET_IDLE                    0x02
#define REQ_GET_PROTOCOL                0x03
#define REQ_SET_REPORT                  0x09
#define REQ_SET_IDLE                    0x0a
#define REQ_SET_PROTOCOL                0x0b

// ------------------------------------------------------------------------------------------------
// USB Standard Feature Selectors

#define F_DEVICE_REMOTE_WAKEUP          1   // Device
#define F_ENDPOINT_HALT                 2   // Endpoint
#define F_TEST_MODE                     3   // Device

// ------------------------------------------------------------------------------------------------
// USB Hub Feature Seletcors

#define F_C_HUB_LOCAL_POWER             0   // Hub
#define F_C_HUB_OVER_CURRENT            1   // Hub
#define F_PORT_CONNECTION               0   // Port
#define F_PORT_ENABLE                   1   // Port
#define F_PORT_SUSPEND                  2   // Port
#define F_PORT_OVER_CURRENT             3   // Port
#define F_PORT_RESET                    4   // Port
#define F_PORT_POWER                    8   // Port
#define F_PORT_LOW_SPEED                9   // Port
#define F_C_PORT_CONNECTION             16  // Port
#define F_C_PORT_ENABLE                 17  // Port
#define F_C_PORT_SUSPEND                18  // Port
#define F_C_PORT_OVER_CURRENT           19  // Port
#define F_C_PORT_RESET                  20  // Port
#define F_PORT_TEST                     21  // Port
#define F_PORT_INDICATOR                22  // Port

// ------------------------------------------------------------------------------------------------
// USB Device Request

typedef struct UsbDevReq
{
	u8 type;
	u8 req;
	u16 value;
	u16 index;
	u16 len;
}  UsbDevReq;
// ------------------------------------------------------------------------------------------------
// USB HID Subclass Codes

#define USB_SUBCLASS_BOOT               0x01

// ------------------------------------------------------------------------------------------------
// USB HID Protocol Codes

#define USB_PROTOCOL_KBD                0x01
#define USB_PROTOCOL_MOUSE              0x02
#define USB_DESC_DEVICE                 0x01
#define USB_DESC_CONF                   0x02
#define USB_DESC_STRING                 0x03
#define USB_DESC_INTF                   0x04
#define USB_DESC_ENDP                   0x05

// ------------------------------------------------------------------------------------------------
// USB HID Descriptor Types

#define USB_DESC_HID                    0x21
#define USB_DESC_REPORT                 0x22
#define USB_DESC_PHYSICAL               0x23

// ------------------------------------------------------------------------------------------------
// USB HUB Descriptor Types

#define USB_DESC_HUB                    0x29

// ------------------------------------------------------------------------------------------------
// USB Device Descriptor

typedef struct UsbDeviceDesc
{
	u8 len;
	u8 type;
	u16 usbVer;
	u8 devClass;
	u8 devSubClass;
	u8 devProtocol;
	u8 maxPacketSize;
	u16 vendorId;
	u16 productId;
	u16 deviceVer;
	u8 vendorStr;
	u8 productStr;
	u8 serialStr;
	u8 confCount;
} PACKED UsbDeviceDesc;

// ------------------------------------------------------------------------------------------------
// USB Configuration Descriptor

typedef struct UsbConfDesc
{
	u8 len;
	u8 type;
	u16 totalLen;
	u8 intfCount;
	u8 confValue;
	u8 confStr;
	u8 attributes;
	u8 maxPower;
} PACKED UsbConfDesc;

// ------------------------------------------------------------------------------------------------
// USB String Descriptor

typedef struct UsbStringDesc
{
	u8 len;
	u8 type;
	u16 str[];
} PACKED UsbStringDesc;

// ------------------------------------------------------------------------------------------------
// USB Interface Descriptor

typedef struct UsbEndpDesc
{
	u8 len;
	u8 type;
	u8 addr;
	u8 attributes;
	u16 maxPacketSize;
	u8 interval;
	struct UsbEndpDesc * next;
} PACKED UsbEndpDesc;

typedef struct __attribute__((packed))  UsbIntfDesc
{
	u8 len;
	u8 type;
	u8 intfIndex;
	u8 altSetting;
	u8 endpCount;
	u8 intfClass;
	u8 intfSubClass;
	u8 intfProtocol;
	u8 intfStr;
	struct UsbIntfDesc * next;
	UsbEndpDesc * endpoints;
} PACKED UsbIntfDesc;

// ------------------------------------------------------------------------------------------------
// USB Endpoint Descriptor

// ------------------------------------------------------------------------------------------------
// USB HID Desciptor

typedef struct __attribute__((packed))  UsbHidDesc
{
	u8 len;
	u8 type;
	u16 hidVer;
	u8 countryCode;
	u8 descCount;
	u8 descType;
	u16 descLen;
} PACKED UsbHidDesc;

// ------------------------------------------------------------------------------------------------
// USB Hub Descriptor

typedef struct __attribute__((packed)) UsbHubDesc
{
	u8 len;
	u8 type;
	u8 portCount;
	u16 chars;
	u8 portPowerTime;
	u8 current;
	// removable/power control bits vary in size
} PACKED UsbHubDesc;

// Hub Characteristics
#define HUB_POWER_MASK                  0x03        // Logical Power Switching Mode
#define HUB_POWER_GLOBAL                0x00
#define HUB_POWER_INDIVIDUAL            0x01
#define HUB_COMPOUND                    0x04        // Part of a Compound Device
#define HUB_CURRENT_MASK                0x18        // Over-current Protection Mode
#define HUB_TT_TTI_MASK                 0x60        // TT Think Time
#define HUB_PORT_INDICATORS             0x80        // Port Indicators

void UsbPrintDeviceDesc(UsbDeviceDesc *desc)
{
	/*printTextToWindow(2, mywin, "  USB: Version=%d.%d Vendor ID=%x Product ID=%x Configs=%d\n",
		(int)desc->usbVer >> 8, (int)(desc->usbVer >> 4) & 0xf,
		(int)desc->vendorId, (int)desc->productId,
		(int)desc->confCount);*/
}

// ------------------------------------------------------------------------------------------------
void UsbPrintConfDesc(UsbConfDesc *desc)
{
	/*printTextToWindow(2, mywin, "  Configuration: totalLen=%d intfCount=%d confValue=%d confStr=%d\n",
		(int)desc->totalLen,
		(int)desc->intfCount,
		(int)desc->confValue,
		(int)desc->confStr);*/
}

// ------------------------------------------------------------------------------------------------
void UsbPrintIntfDesc(UsbIntfDesc *desc)
{
	/*printTextToWindow(2, mywin, "   Interface: altSetting=%d endpCount=%d class=%d subclass=%d protocol=%d str=%d\n",
		(int)desc->altSetting,
		(int)desc->endpCount,
		(int)desc->intfClass,
		(int)desc->intfSubClass,
		(int)desc->intfProtocol,
		(int)desc->intfStr);*/
}

// ------------------------------------------------------------------------------------------------
void UsbPrintEndpDesc(UsbEndpDesc *desc)
{
	/*printTextToWindow(2, mywin, "    EndPoint: addr=0x%x attributes=%d maxPacketSize=%d interval=%d\n",
		(int)desc->addr,
		(int)desc->attributes,
		(int)desc->maxPacketSize,
		(int)desc->interval);*/
}

// ------------------------------------------------------------------------------------------------
void UsbPrintHidDesc(UsbHidDesc *desc)
{
}

// ------------------------------------------------------------------------------------------------
void UsbPrintHubDesc(UsbHubDesc *desc)
{
	/*kprintf(" Hub: port count=%d characteristics=0x%x power time=%d current=%d\n",
		desc->portCount,
		desc->chars,
		desc->portPowerTime,
		desc->current);*/
}
#define USB_STRING_SIZE                 127



// ------------------------------------------------------------------------------------------------
// USB Speeds

#define USB_FULL_SPEED                  0x00
#define USB_LOW_SPEED                   0x01
#define USB_HIGH_SPEED                  0x02



typedef struct UsbController
{
	struct UsbController *next;
	void *hc;

	void(*poll)(struct UsbController *controller);
} UsbController;

// ------------------------------------------------------------------------------------------------
// Globals

UsbController *g_usbControllerList;

// ------------------------------------------------------------------------------------------------
// USB Endpoint

typedef struct UsbEndpoint
{
	UsbEndpDesc * desc;
	uint toggle;
} UsbEndpoint;

// ------------------------------------------------------------------------------------------------
// USB Transfer

typedef struct UsbTransfer
{
	UsbEndpoint *endp;
	UsbDevReq *req;
	void *data;
	uint len;
	bool complete;
	bool success;
	char w;
} UsbTransfer;

// ------------------------------------------------------------------------------------------------
// USB Device

typedef struct UsbDevice
{
	struct UsbDevice *parent;
	struct UsbDevice *next;
	void *hc;
	void *drv;

	uint port;
	uint speed;
	uint addr;
	uint maxPacketSize;

	UsbIntfDesc *intfDesc;

	void(*hcControl)(struct UsbDevice *dev, UsbTransfer *t);
	void(*hcIntr)(struct UsbDevice *dev, UsbTransfer *t);
	void(*drvPoll)(struct UsbDevice *dev);
	void(*onDisconnect)(struct UsbDevice *dev);

	u16 langs[USB_STRING_SIZE];
	char productStr[USB_STRING_SIZE];
	char vendorStr[USB_STRING_SIZE];
	char serialStr[USB_STRING_SIZE];
} UsbDevice;
typedef struct UsbDriver
{
	bool(*init)(UsbDevice *dev);
} UsbDriver;


static int s_nextUsbAddr;
UsbDevice *g_usbDeviceList;
// ------------------------------------------------------------------------------------------------
UsbDevice *UsbDevCreate()
{
	// Initialize structure
	UsbDevice *dev = (UsbDevice*)malloc(sizeof(UsbDevice));
	if (dev)
	{
		dev->parent = 0;
		dev->next = g_usbDeviceList;
		dev->hc = 0;
		dev->drv = 0;

		dev->port = 0;
		dev->speed = 0;
		dev->addr = 0;
		dev->maxPacketSize = 0;
		// dev->endp.toggle = 0;

		dev->hcControl = 0;
		dev->hcIntr = 0;
		dev->drvPoll = 0;

		g_usbDeviceList = dev;
	}

	return dev;
}
// ------------------------------------------------------------------------------------------------
bool UsbIntrRequest(UsbDevice *dev,
	uint type, uint request,
	uint value, uint index,
	uint len, void *data)
{
	UsbDevReq req;
	req.type = type;
	req.req = request;
	req.value = value;
	req.index = index;
	req.len = len;

	UsbTransfer t;
	t.endp = 0;
	t.req = &req;
	//t.toggle
	t.data = data;
	t.len = len;
	t.complete = false;
	t.success = false;

	dev->hcControl(dev, &t);

	return t.success;
}
// ------------------------------------------------------------------------------------------------
bool UsbEndpqRequest(UsbDevice *dev,
	uint type, uint request,
	uint value, uint index,
	uint len, void *data)
{
	UsbDevReq req;
	req.type = type;
	req.req = request;
	req.value = value;
	req.index = index;
	req.len = len;

	UsbTransfer t;
	t.endp = 0;
	t.req = &req;
	t.data = data;
	t.len = len;
	t.complete = false;
	t.success = false;

	dev->hcIntr(dev, &t);

	return t.success;
}
// ------------------------------------------------------------------------------------------------
bool UsbDevRequest(UsbDevice *dev,
	uint type, uint request,
	uint value, uint index,
	uint len, void *data)
{
	UsbDevReq req;
	req.type = type;
	req.req = request;
	req.value = value;
	req.index = index;
	req.len = len;

	UsbTransfer t;
	t.endp = 0;
	t.req = &req;
	t.data = data;
	t.len = len;
	t.complete = false;
	t.success = false;

	dev->hcControl(dev, &t);

	return t.success;
}

// ------------------------------------------------------------------------------------------------
bool UsbDevGetLangs(UsbDevice *dev, u16 *langs)
{
	langs[0] = 0;

	u8 buf[256];
	UsbStringDesc *desc = (UsbStringDesc *)&buf;

	// Get length
	if (!UsbDevRequest(dev,
		RT_DEV_TO_HOST | RT_STANDARD | RT_DEV,
		REQ_GET_DESC, (USB_DESC_STRING << 8) | 0, 0,
		1, desc))
	{
		return false;
	}
	// Get lang data
	if (!UsbDevRequest(dev,
		RT_DEV_TO_HOST | RT_STANDARD | RT_DEV,
		REQ_GET_DESC, (USB_DESC_STRING << 8) | 0, 0,
		desc->len, desc))
	{
		return false;
	}


	uint langLen = (desc->len - 2) / 2;
	for (uint i = 0; i < langLen; ++i)
	{
		langs[i] = desc->str[i];//printTextToWindow(1,mywin,"!%x!", (int)langs[i]);
	}
	langs[langLen] = 0;
	return true;
}

// ------------------------------------------------------------------------------------------------
bool UsbDevGetString(UsbDevice *dev, char *str, uint langId, uint strIndex)
{
	str[0] = '\0';


	u8 buf[256];
	UsbStringDesc *desc = (UsbStringDesc *)buf;

	// Get string length
	if (!UsbDevRequest(dev,
		RT_DEV_TO_HOST | RT_STANDARD | RT_DEV,
		REQ_GET_DESC, (USB_DESC_STRING << 8) | strIndex, langId,
		1, desc))
	{
		return false;
	}

	// Get string data
	if (!UsbDevRequest(dev,
		RT_DEV_TO_HOST | RT_STANDARD | RT_DEV,
		REQ_GET_DESC, (USB_DESC_STRING << 8) | strIndex, langId,
		desc->len, desc))
	{
		return false;
	}

	// Dumb Unicode to ASCII conversion
	uint strLen = (desc->len - 2) / 2;
	for (uint i = 0; i < strLen; ++i)
	{
		str[i] = desc->str[i];
	}
	//printTextToWindow(4,mywin,"@%s@",str);
	str[strLen] = '\0';
	return true;
}

// ------------------------------------------------------------------------------------------------
bool UsbDevClearHalt(UsbDevice *dev)
{

}

// ------------------------------------------------------------------------------------------------
bool UsbDevEndpointRequest(UsbDevice *dev, uint type, uint reqe, uint value, uint endpointIndex, uint dataLen, void * data)
{
	UsbDevReq req;
	req.type = type & 0b11100000;
	//Request type - endpoint
	req.type = req.type | 2;

	req.req = reqe;
	req.value = value;
	req.index = endpointIndex;
	req.len = dataLen;

	UsbTransfer t;
	t.endp = 0;
	t.req = &req;
	t.data = data;
	t.len = dataLen;
	t.complete = false;
	t.success = false;

	dev->hcIntr(dev, &t);

	return t.success;
}
// ------------------------------------------------------------------------------------------------
static bool UsbDevInit(UsbDevice *dev)
{
	// Get first 8 bytes of device descriptor
	UsbDeviceDesc devDesc;
	if (!UsbDevRequest(dev,
		RT_DEV_TO_HOST | RT_STANDARD | RT_DEV,
		REQ_GET_DESC, (USB_DESC_DEVICE << 8) | 0, 0,
		8, &devDesc))
	{
		kprintf("11");
		return false;
	}
	//return;
	//UsbPrintDeviceDesc(&devDesc);
	dev->maxPacketSize = devDesc.maxPacketSize;
	kprintf("mxpcktsize=%x", devDesc.maxPacketSize);
	// Set address
	uint addr = ++s_nextUsbAddr;
	if (!UsbDevRequest(dev,
		RT_HOST_TO_DEV | RT_STANDARD | RT_DEV,
		REQ_SET_ADDR, addr, 0,
		0, 0))
	{
		return false;
	}

	dev->addr = addr;
	PitWait(40);    // Set address recovery time

	// Read entire descriptor
	if (!UsbDevRequest(dev,
		RT_DEV_TO_HOST | RT_STANDARD | RT_DEV,
		REQ_GET_DESC, (USB_DESC_DEVICE << 8) | 0, 0,
		sizeof(UsbDeviceDesc), &devDesc))
	{
		return false;
	}

	// Dump descriptor
	UsbPrintDeviceDesc(&devDesc);

	// String Info
	UsbDevGetLangs(dev, &dev->langs);

	uint langId = dev->langs[0];

	//printTextToWindow(1, mywin, "%x",(int)langs[0]);
	if (langId)
	{
		UsbDevGetString(dev, &dev->productStr, langId, devDesc.productStr);
		UsbDevGetString(dev, &dev->vendorStr, langId, devDesc.vendorStr);
		UsbDevGetString(dev, &dev->serialStr, langId, devDesc.serialStr);
		printTextToWindow(2, mywin, "  Product='%s' Vendor='%s' Serial=%s\n", &dev->productStr, &dev->vendorStr, &dev->serialStr);
	}
	// Pick configuration and interface - grab first for now
	u8 configBuf[256];
	uint pickedConfValue = 0;
	UsbIntfDesc *pickedIntfDesc = 0;
	UsbEndpDesc *pickedEndpDesc = 0;
	for (uint confIndex = 0; confIndex < devDesc.confCount; ++confIndex)
	{
		// Get configuration total length
		if (!UsbDevRequest(dev,
			RT_DEV_TO_HOST | RT_STANDARD | RT_DEV,
			REQ_GET_DESC, (USB_DESC_CONF << 8) | confIndex, 0,
			4, configBuf))
		{
			continue;
		}

		// Only static size supported for now
		UsbConfDesc *confDesc = (UsbConfDesc *)configBuf;
		if (confDesc->totalLen > sizeof(configBuf))
		{
			kprintf("  Configuration length %d greater than %d bytes",
				confDesc->totalLen, sizeof(configBuf));


			continue;
		}

		// Read all configuration data
		if (!UsbDevRequest(dev,
			RT_DEV_TO_HOST | RT_STANDARD | RT_DEV,
			REQ_GET_DESC, (USB_DESC_CONF << 8) | confIndex, 0,
			confDesc->totalLen, configBuf))
		{
			continue;
		}

		UsbPrintConfDesc(confDesc);

		if (!pickedConfValue)
		{
			pickedConfValue = confDesc->confValue;
		}

		// Parse configuration data
		u8 *data = configBuf + confDesc->len;
		u8 *end = configBuf + confDesc->totalLen;

		while (data < end)
		{
			u8 len = data[0];
			u8 type = data[1];
			//Assume, that data are sorted like:
			//..., Interface, endp, endp, ..., interface, endp, endp, ...
			switch (type)
			{
			case USB_DESC_INTF:
			{
				//printTextToWindow(1, mywin, "  De:\n");
				UsbIntfDesc *intfDesc = (UsbIntfDesc*)malloc(sizeof(UsbIntfDesc));
				memcpy(intfDesc, data, sizeof(UsbIntfDesc) - 8);
				intfDesc->next = 0;
				intfDesc->endpoints = 0;
				if (!pickedIntfDesc)
				{
					dev->intfDesc = intfDesc;
					//Set first

				}
				else {
					//Set next to last;
					UsbIntfDesc *last = dev->intfDesc;
					while (last->next) last = last->next;
					last->next = intfDesc;
				}
				pickedIntfDesc = intfDesc;
			}
			break;

			case USB_DESC_ENDP:
			{
				//Currently I'm checking last interface, add that endpoint to it.
				UsbEndpDesc *endp_desc = (UsbEndpDesc*)malloc(sizeof(UsbEndpDesc));
				memcpy(endp_desc, data, sizeof(UsbEndpDesc) - 4);
				endp_desc->next = 0;
				//UsbPrintEndpDesc(endp_desc);

				if (!pickedIntfDesc)
				{
					//Wtf is going on????
					printTextToWindow(4, mywin, "WTF??? We aren't receive interface first!");
					return;
					//pickedEndpDesc = endp_desc;
				}
				if (pickedEndpDesc)
				{
					pickedEndpDesc->next = endp_desc;
					pickedEndpDesc = endp_desc;
				}
				else
				{
					pickedIntfDesc->endpoints = endp_desc;
				}
				pickedEndpDesc = endp_desc;
			}
			break;
			}

			data += len;
		}
	}
	// Configure device
	if (pickedConfValue)
	{
		if (!UsbDevRequest(dev,
			RT_HOST_TO_DEV | RT_STANDARD | RT_DEV,
			REQ_SET_CONF, pickedConfValue, 0,
			0, 0))
		{
			return false;
		}
		UsbIntfDesc *cur = dev->intfDesc;
		while (cur)
		{
			UsbPrintIntfDesc(cur);
			UsbEndpDesc * cd = cur->endpoints;
			while (cd)
			{
				UsbPrintEndpDesc(cd);
				cd = cd->next;
			}
			cur = cur->next;
		}
		_usbhubinit(dev);
		_UsbMouseInit(dev); _UsbKbdInit(dev);
		//kprintf("%d %d %d %d~\n",pickedIntfDesc->intfClass, pickedIntfDesc->intfSubClass, pickedIntfDesc->intfProtocol);

		if (pickedIntfDesc->intfClass == 8 && pickedEndpDesc->attributes)
		{

			_storageInit(dev);
		}
	}

	return true;
}
void UsbService()
{
	while (1)
	{
		UsbPoll();
	}
}
void UsbPoll()
{
	//if (!pcidone) return;
	usbPoll = 0;
	
	for (UsbController *c = g_usbControllerList; c; c = c->next)
	{
		if (c->poll)
		{
			c->poll(c);
		}
	}

	for (UsbDevice *dev = g_usbDeviceList; dev; dev = dev->next)
	{
		if (dev->drvPoll)
		{
			dev->drvPoll(dev);
		}
	}
}