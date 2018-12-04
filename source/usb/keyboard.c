// ------------------------------------------------------------------------------------------------
typedef struct UsbKbd
{
	UsbTransfer dataTransfer;
	u8 data[8];
	u8 lastData[8];
} UsbKbd;

#define KBD_LSHIFT                      0x01
#define KBD_RSHIFT                      0x02
#define KBD_CAPS_LOCK                   0x04
#define KBD_NUM_LOCK                    0x08
static u8 s_flags;
#define KEY_MOD_LCTRL  0x01
#define KEY_MOD_LSHIFT 0x02
#define KEY_MOD_LALT   0x04
#define KEY_MOD_LMETA  0x08
#define KEY_MOD_RCTRL  0x10
#define KEY_MOD_RSHIFT 0x20
#define KEY_MOD_RALT   0x40
#define KEY_MOD_RMETA  0x80
// ------------------------------------------------------------------------------------------------
void InputOnKey(uint code, uint val)
{

	//kprintf("%x\n", code);
	if (val)
	{
		// key press
		//addKey(code);

		if (code == 512)
		{
			s_flags |= KBD_LSHIFT;
		}
		else if (code == 8192)
		{
			s_flags |= KBD_RSHIFT;
		}
		else if (code == KEY_CAPS_LOCK)
		{
			s_flags ^= KBD_CAPS_LOCK;
		}
		else if (code == KEY_NUM_LOCK)
		{
			s_flags ^= KBD_NUM_LOCK;
		}
		else
		{
			// character mapping
			u8 ch = 0;
			if (code < 0x80)
			{
				if (s_flags & KBD_NUM_LOCK)
				{
					ch = usb_k_base[code];
				}

				if (!ch)
				{
					if (s_flags & (KBD_LSHIFT | KBD_RSHIFT))
					{
						ch = usb_k_shift[code];
					}
					else
					{
						ch = usb_k_base[code];
					}
				}
			}
			if (ch)
			{
				// Apply caps lock modifier
				if (s_flags & KBD_CAPS_LOCK)
				{
					if (ch >= 'a' && ch <= 'z')
					{
						ch += 'A' - 'a';
					}
					else if (ch >= 'A' && ch <= 'Z')
					{
						ch += 'a' - 'A';
					}
				}

				addKey(ch);
			}
		}
	}
	else
	{
		// key release
		//ConsoleOnKeyUp(code);

		if (code == 512)
		{
			s_flags &= ~KBD_LSHIFT;
		}
		else if (code == 8192)
		{
			s_flags &= ~KBD_RSHIFT;
		}
	}
}

// ------------------------------------------------------------------------------------------------
static void UsbKbdProcess(UsbKbd *kbd)
{
	u8 *data = kbd->data;
	bool error = false;
	// Modifier keys
	uint modDelta = data[0] ^ kbd->lastData[0];
	for (uint i = 0; i < 8; ++i)
	{
		uint mask = 1 << i;
		if (modDelta & mask)
		{
			InputOnKey(mask << 8, data[0] & mask);
		}
	}

	// Release keys
	for (uint i = 2; i < 8; ++i)
	{
		uint usage = kbd->lastData[i];

		if (usage)
		{
			if (!memchr(data + 2, usage, 6))
			{
				InputOnKey(usage, 0);
			}
		}
	}

	// Press keys
	for (uint i = 2; i < 8; ++i)
	{
		uint usage = data[i];

		if (usage >= 4)
		{
			if (!memchr(kbd->lastData + 2, usage, 6))
			{
				InputOnKey(usage, 1);
			}
		}
		else if (usage > 0)
		{
			//printTextToWindow(3, mywin, "[WWWW: %x!]", i);
			error = true;
		}
	}

	// Update keystate
	if (!error)
	{
		memcpy(kbd->lastData, data, 8);
	}
}

// ------------------------------------------------------------------------------------------------
static void UsbKbdPoll(UsbDevice *dev)
{
	UsbKbd *kbd = dev->drv;

	UsbTransfer *t = &kbd->dataTransfer;

	if (t->complete)
	{
		if (t->success)
		{
			t->complete = false;
			dev->hcIntr(dev, t);
			UsbKbdProcess(kbd);
		}
	}
}

// ------------------------------------------------------------------------------------------------
void _UsbKbdInit(UsbDevice *dev)
{
	if (dev->intfDesc->intfClass == USB_CLASS_HID &&
		dev->intfDesc->intfSubClass == USB_SUBCLASS_BOOT &&
		dev->intfDesc->intfProtocol == USB_PROTOCOL_KBD)
	{
		printTextToWindow(2, mywin, "      Initializing Keyboard\n");

		UsbKbd *kbd = malloc(sizeof(UsbKbd));
		memset(kbd->lastData, 0, 8);

		dev->drv = kbd;
		dev->drvPoll = UsbKbdPoll;

		uint intfIndex = dev->intfDesc->intfIndex;
		kprintf("IntfIndex: %x", intfIndex);
		// Only send interrupt report when data changes
		/*UsbDevRequest(dev,
			RT_HOST_TO_DEV | RT_CLASS | RT_INTF,
			REQ_SET_IDLE, 0, intfIndex,
			0, 0);*/
		UsbEndpoint * endp = malloc(sizeof(UsbEndpoint));
		endp->toggle = 0;
		endp->desc = dev->intfDesc->endpoints;

		// Prepare transfer
		UsbTransfer *t = &kbd->dataTransfer;
		t->endp = endp;
		t->req = 0;
		t->data = kbd->data;
		t->len = 8;
		t->complete = false;
		t->success = false;
		t->w = 0;
		dev->hcIntr(dev, t);
		kprintf("Keyboard ENDPOINT = %x", endp->desc->addr);

		return true;
	}

	return false;
}