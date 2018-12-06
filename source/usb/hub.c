#define PORT_CONNECTION                 (1 << 0)    // Current Connect Status
#define PORT_ENABLE                     (1 << 1)    // Port Enabled
#define PORT_SUSPEND                    (1 << 2)    // Suspend
#define PORT_OVER_CURRENT               (1 << 3)    // Over-current
#define PORT_RESET                      (1 << 4)    // Port Reset
#define PORT_POWER                      (1 << 8)    // Port Power
#define PORT_SPEED_MASK                 (3 << 9)    // Port Speed
#define PORT_SPEED_SHIFT                9
#define PORT_TEST                       (1 << 11)   // Port Test Control
#define PORT_INDICATOR                  (1 << 12)   // Port Indicator Control
#define PORT_CONNECTION_CHANGE          (1 << 16)   // Connect Status Change
#define PORT_ENABLE_CHANGE              (1 << 17)   // Port Enable Change
#define PORT_OVER_CURRENT_CHANGE        (1 << 19)   // Over-current Change

// ------------------------------------------------------------------------------------------------
typedef struct UsbHub
{
	UsbDevice *dev;
	UsbHubDesc desc;
} UsbHub;

// ------------------------------------------------------------------------------------------------
static uint UsbHubResetPort(UsbHub *hub, uint port)
{
	u32 status = 0;
	UsbDevice *dev = hub->dev;
	// Get current status
	// Reset the port
	if (!UsbDevRequest(dev,
		0x23,
		REQ_SET_FEATURE, F_PORT_RESET, port + 1,
		0, 0))
	{
		return 0;
	}
	Wait(100);
	// Wait 100ms for port to enable (TODO - remove after dynamic port detection)

	for (uint i = 0; i < 10; ++i)
	{
		// Delay
		Wait(150);

		// Get current status
		if (!UsbDevRequest(dev,
			RT_DEV_TO_HOST | RT_CLASS | RT_OTHER,
			REQ_GET_STATUS, 0, port + 1,
			sizeof(status), &status))
		{
			return 0;
		}
		// Check if device is attached to port
		if (~status & PORT_CONNECTION)
		{
			break;
		}

		
		// Acknowledge change in status
		if(status&PORT_CONNECTION_CHANGE)
		if (!UsbDevRequest(dev,
			0x23,
			REQ_CLEAR_FEATURE, F_C_PORT_CONNECTION, port + 1,
			0, 0))
		{

		}
		// Check if device is enabled
		if (status & PORT_ENABLE)
		{
			break;
		}
	}

	return status;
}

// ------------------------------------------------------------------------------------------------
static void UsbHubProbe(UsbHub *hub)
{
	UsbDevice *dev = hub->dev;
	uint portCount = hub->desc.portCount;
	// Enable power if needed

	for (uint port = 0; port < portCount; ++port)
	{
		if (!UsbDevRequest(dev,
			0x23,
			REQ_SET_FEATURE, F_PORT_POWER, port + 1,
			0, 0))
		{
			//////return;
		}

		Wait(hub->desc.portPowerTime * 20);
	}

	PitWait(150);
	// Reset ports
	for (uint port = 0; port < portCount; ++port)
	{
		Wait(5);
		uint status = UsbHubResetPort(hub, port);
		kprintf("Status: %x\n", status);
		Wait(1000);
		if (status & PORT_ENABLE)
		{
			uint speed = (status & PORT_SPEED_MASK) >> PORT_SPEED_SHIFT;

			UsbDevice *dev = UsbDevCreate();
			if (dev)
			{
				dev->parent = hub->dev;
				dev->hc = hub->dev->hc;
				dev->port = port;
				dev->speed = speed;
				dev->maxPacketSize = 8;

				dev->hcControl = hub->dev->hcControl;
				dev->hcIntr = hub->dev->hcIntr;

				if (!UsbDevInit(dev))
				{
					// TODO - cleanup
				}
			}
		}

	}
}

// ------------------------------------------------------------------------------------------------
static void UsbHubPoll(UsbDevice *dev)
{
	UsbHub * hub = dev->drv;
	uint portCount = hub->desc.portCount;
	for (uint port = 0; port < portCount; ++port)
	{

		uint status = 0;
		if (!UsbDevRequest(dev,
			RT_DEV_TO_HOST | RT_CLASS | RT_OTHER,
			REQ_GET_STATUS, 0, port + 1,
			sizeof(status), &status))
		{
			return 0;
		}
		if (status&PORT_CONNECTION_CHANGE && !(status&PORT_CONNECTION))
		{
			//kprintf("USB Hub device disconnected!\n");
			//Clear Connection change bit
			if (!UsbDevRequest(dev,
				0x23,
				REQ_CLEAR_FEATURE, F_C_PORT_CONNECTION, port + 1,
				0, 0))
			{
				
			}
			UsbDevice * cur = g_usbDeviceList, *ls = 0;
			while (cur)
			{
				if (cur->port == port && (uint)cur->hc == (uint)hub->dev->hc)
				{
					if (cur->onDisconnect)
						cur->onDisconnect(cur);
					if (ls)
					{						
						ls->next = cur->next;
						free(cur); break;
					}
					else
					{
						g_usbDeviceList = cur->next;
						free(cur); break;
					}
				}
				ls = cur;
				cur = cur->next;
			}
		}
		else if (status&PORT_CONNECTION_CHANGE && (status&PORT_CONNECTION))
		{
			//kprintf("USB Hub device connected!\n");
			if (!UsbDevRequest(dev,
				0x23,
				REQ_SET_FEATURE, F_PORT_POWER, port + 1,
				0, 0))
			{
			}

			Wait(hub->desc.portPowerTime * 20 + 150);
			uint status = UsbHubResetPort(hub, port);
			if (status & PORT_ENABLE)
			{
				uint speed = (status & PORT_SPEED_MASK) >> PORT_SPEED_SHIFT;

				UsbDevice *dev = UsbDevCreate();
				if (dev)
				{
					dev->parent = hub->dev;
					dev->hc = hub->dev->hc;
					dev->port = port;
					dev->speed = speed;
					dev->maxPacketSize = 8;

					dev->hcControl = hub->dev->hcControl;
					dev->hcIntr = hub->dev->hcIntr;

					if (!UsbDevInit(dev))
					{
					}
				}
			}
		}
	}

}

// ------------------------------------------------------------------------------------------------
void _usbhubinit(UsbDevice *dev)
{
	if (dev->intfDesc->intfClass == USB_CLASS_HUB)
	{
		kprintf("Initializing Hub\n");

		// Get Hub Descriptor
		UsbHubDesc desc;

		//return;
		if (!UsbDevRequest(dev,
			RT_DEV_TO_HOST | RT_CLASS | RT_DEV,
			REQ_GET_DESC, (USB_DESC_HUB << 8) | 0, 0,
			sizeof(UsbHubDesc), &desc))
		{
			return false;
		}

		UsbPrintHubDesc(&desc);

		UsbHub *hub = (UsbHub*) malloc(sizeof(UsbHub));
		hub->dev = dev;
		hub->desc = desc;

		dev->drv = hub;
		dev->drvPoll = UsbHubPoll;

		UsbHubProbe(hub);
		kprintf("ok.");
		return true;
	}

	return false;
}