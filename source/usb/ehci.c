#pragma GCC push_options
#pragma GCC optimize ("O0")

// ------------------------------------------------------------------------------------------------
// Limits

#define MAX_QH                          8
#define MAX_TD                          32

// ------------------------------------------------------------------------------------------------
// PCI Configuration Registers

// EECP-based
#define USBLEGSUP                       0x00        // USB Legacy Support Extended Capability
#define UBSLEGCTLSTS                    0x04        // USB Legacy Support Control/Status

// ------------------------------------------------------------------------------------------------
// USB Legacy Support Register

#define USBLEGSUP_HC_OS                 0x01000000  // HC OS Owned Semaphore
#define USBLEGSUP_HC_BIOS               0x00010000  // HC BIOS Owned Semaphore
#define USBLEGSUP_NCP_MASK              0x0000ff00  // Next EHCI Extended Capability Pointer
#define USBLEGSUP_CAPID                 0x000000ff  // Capability ID

// ------------------------------------------------------------------------------------------------
// Host Controller Capability Registers

typedef struct EhciCapRegs
{
	u8 capLength;
	u8 reserved;
	u16 hciVersion;
	u32 hcsParams;
	u32 hccParams;
	u64 hcspPortRoute;
} PACKED EhciCapRegs;
#define hcsParamsO  4
#define hccParamsO  8

// ------------------------------------------------------------------------------------------------
// Host Controller Structural Parameters Register

#define HCSPARAMS_N_PORTS_MASK          (15 << 0)   // Number of Ports
#define HCSPARAMS_PPC                   (1 << 4)    // Port Power Control
#define HCSPARAMS_PORT_ROUTE            (1 << 7)    // Port Routing Rules
#define HCSPARAMS_N_PCC_MASK            (15 << 8)   // Number of Ports per Companion Controller
#define HCSPARAMS_N_PCC_SHIFT           8
#define HCSPARAMS_N_CC_MASK             (15 << 12)  // Number of Companion Controllers
#define HCSPARAMS_N_CC_SHIFT            12
#define HCSPARAMS_P_INDICATOR           (1 << 16)   // Port Indicator
#define HCSPARAMS_DPN_MASK              (15 << 20)  // Debug Port Number
#define HCSPARAMS_DPN_SHIFT             20

// ------------------------------------------------------------------------------------------------
// Host Controller Capability Parameters Register

#define HCCPARAMS_64_BIT                (1 << 0)    // 64-bit Addressing Capability
#define HCCPARAMS_PFLF                  (1 << 1)    // Programmable Frame List Flag
#define HCCPARAMS_ASPC                  (1 << 2)    // Asynchronous Schedule Park Capability
#define HCCPARAMS_IST_MASK              (15 << 4)   // Isochronous Sheduling Threshold
#define HCCPARAMS_EECP_MASK             (255 << 8)  // EHCI Extended Capabilities Pointer
#define HCCPARAMS_EECP_SHIFT            8

// ------------------------------------------------------------------------------------------------
// Host Controller Operational Registers

typedef struct EhciOpRegs
{
	volatile u32 usbCmd;
	volatile u32 usbSts;
	volatile u32 usbIntr;
	volatile u32 frameIndex;
	volatile u32 ctrlDsSegment;
	volatile u32 periodicListBase;
	volatile u32 asyncListAddr;
	volatile u32 reserved[9];
	volatile u32 configFlag;
	volatile u32 ports[];
} EhciOpRegs;
#define usbCmdO				0
#define usbStsO				4
#define usbIntrO			8
#define frameIndexO			12
#define ctrlDsSegmentO		16
#define periodicListBaseO	20
#define asyncListAddrO		24
//+36 + 4
#define configFlagO			64
#define portsO				68

#define bit32u uint
bit32u MRIR(const bit32u base, const bit32u offset) {
	return *((volatile bit32u *)(base + offset));
}

void MWIR(const bit32u base, const bit32u offset, const bit32u val) {
	volatile bit32u *ptr = (volatile bit32u *)(base + offset);
	*ptr = val;
}

// ------------------------------------------------------------------------------------------------
// USB Command Register

#define CMD_RS                          (1 << 0)    // Run/Stop
#define CMD_HCRESET                     (1 << 1)    // Host Controller Reset
#define CMD_FLS_MASK                    (3 << 2)    // Frame List Size
#define CMD_FLS_SHIFT                   2
#define CMD_PSE                         (1 << 4)    // Periodic Schedule Enable
#define CMD_ASE                         (1 << 5)    // Asynchronous Schedule Enable
#define CMD_IOAAD                       (1 << 6)    // Interrupt on Async Advance Doorbell
#define CMD_LHCR                        (1 << 7)    // Light Host Controller Reset
#define CMD_ASPMC_MASK                  (3 << 8)    // Asynchronous Schedule Park Mode Count
#define CMD_ASPMC_SHIFT                 8
#define CMD_ASPME                       (1 << 11)   // Asynchronous Schedule Park Mode Enable
#define CMD_ITC_MASK                    (255 << 16) // Interrupt Threshold Control
#define CMD_ITC_SHIFT                   16

// ------------------------------------------------------------------------------------------------
// USB Status Register

#define STS_USBINT                      (1 << 0)    // USB Interrupt
#define STS_ERROR                       (1 << 1)    // USB Error Interrupt
#define STS_PCD                         (1 << 2)    // Port Change Detect
#define STS_FLR                         (1 << 3)    // Frame List Rollover
#define STS_HSE                         (1 << 4)    // Host System Error
#define STS_IOAA                        (1 << 5)    // Interrupt on Async Advance
#define STS_HCHALTED                    (1 << 12)   // Host Controller Halted
#define STS_RECLAMATION                 (1 << 13)   // Reclamation
#define STS_PSS                         (1 << 14)   // Periodic Schedule Status
#define STS_ASS                         (1 << 15)   // Asynchronous Schedule Status

// ------------------------------------------------------------------------------------------------
// USB Interrupt Enable Register

#define INTR_USBINT                     (1 << 0)    // USB Interrupt Enable
#define INTR_ERROR                      (1 << 1)    // USB Error Interrupt Enable
#define INTR_PCD                        (1 << 2)    // Port Change Interrupt Enable
#define INTR_FLR                        (1 << 3)    // Frame List Rollover Enable
#define INTR_HSE                        (1 << 4)    // Host System Error Enable
#define INTR_IOAA                       (1 << 5)    // Interrupt on Async Advance Enable

// ------------------------------------------------------------------------------------------------
// Frame Index Register

#define FR_MASK                         0x3fff

// ------------------------------------------------------------------------------------------------
// Configure Flag Register

#define CF_PORT_ROUTE                   (1 << 0)    // Configure Flag (CF)

// ------------------------------------------------------------------------------------------------
// Port Status and Control Registers

#define PORT_CONNECTION                 (1 << 0)    // Current Connect Status
#define PORT_CONNECTION_CHANGE          (1 << 1)    // Connect Status Change
#define PORT_ENABLE                     (1 << 2)    // Port Enabled
#define PORT_ENABLE_CHANGE              (1 << 3)    // Port Enable Change
#define PORT_OVER_CURRENT               (1 << 4)    // Over-current Active
#define PORT_OVER_CURRENT_CHANGE        (1 << 5)    // Over-current Change
#define PORT_FPR                        (1 << 6)    // Force Port Resume
#define PORT_SUSPEND                    (1 << 7)    // Suspend
#define PORT_RESET                      (1 << 8)    // Port Reset
#define PORT_LS_MASK                    (3 << 10)   // Line Status
#define PORT_LS_SHIFT                   10
#define PORT_POWER                      (1 << 12)   // Port Power
#define PORT_OWNER                      (1 << 13)   // Port Owner
#define PORT_IC_MASK                    (3 << 14)   // Port Indicator Control
#define PORT_IC_SHIFT                   14
#define PORT_TC_MASK                    (15 << 16)  // Port Test Control
#define PORT_TC_SHIFT                   16
#define PORT_WKCNNT_E                   (1 << 20)   // Wake on Connect Enable
#define PORT_WKDSCNNT_E                 (1 << 21)   // Wake on Disconnect Enable
#define PORT_WKOC_E                     (1 << 22)   // Wake on Over-current Enable
#define PORT_RWC                        (PORT_CONNECTION_CHANGE | PORT_ENABLE_CHANGE | PORT_OVER_CURRENT_CHANGE)

// ------------------------------------------------------------------------------------------------
// Transfer Descriptor

typedef struct EhciTD
{
	volatile u32 link;
	volatile u32 altLink;
	volatile u32 token;
	volatile u32 buffer[5];
	volatile u32 extBuffer[5];

	// internal fields
	u32 tdNext;
	u32 active;
	u8 pad[4 + (128 - 0x40)];
} EhciTD;

// TD Link Pointer
#define PTR_TERMINATE                   (1 << 0)

#define PTR_TYPE_MASK                   (3 << 1)
#define PTR_ITD                         (0 << 1)
#define PTR_QH                          (1 << 1)
#define PTR_SITD                        (2 << 1)
#define PTR_FSTN                        (3 << 1)

// TD Token
#define TD_TOK_PING                     (1 << 0)    // Ping State
#define TD_TOK_STS                      (1 << 1)    // Split Transaction State
#define TD_TOK_MMF                      (1 << 2)    // Missed Micro-Frame
#define TD_TOK_XACT                     (1 << 3)    // Transaction Error
#define TD_TOK_BABBLE                   (1 << 4)    // Babble Detected
#define TD_TOK_DATABUFFER               (1 << 5)    // Data Buffer Error
#define TD_TOK_HALTED                   (1 << 6)    // Halted
#define TD_TOK_ACTIVE                   (1 << 7)    // Active
#define TD_TOK_PID_MASK                 (3 << 8)    // PID Code
#define TD_TOK_PID_SHIFT                8
#define TD_TOK_CERR_MASK                (3 << 10)   // Error Counter
#define TD_TOK_CERR_SHIFT               10
#define TD_TOK_C_PAGE_MASK              (7 << 12)   // Current Page
#define TD_TOK_C_PAGE_SHIFT             12
#define TD_TOK_IOC                      (1 << 15)   // Interrupt on Complete
#define TD_TOK_LEN_MASK                 0x7fff0000  // Total Bytes to Transfer
#define TD_TOK_LEN_SHIFT                16
#define TD_TOK_D                        (1 << 31)   // Data Toggle
#define TD_TOK_D_SHIFT                  31

#define USB_PACKET_OUT                  0           // token 0xe1
#define USB_PACKET_IN                   1           // token 0x69
#define USB_PACKET_SETUP                2           // token 0x2d

// ------------------------------------------------------------------------------------------------
// Queue Head

typedef struct EhciQH
{
	u32 qhlp;       // Queue Head Horizontal Link Pointer
	u32 ch;         // Endpoint Characteristics
	u32 caps;       // Endpoint Capabilities
	volatile u32 curLink;

	// matches a transfer descriptor
	volatile u32 nextLink;
	volatile u32 altLink;
	volatile u32 token;
	volatile u32 buffer[5];
	volatile u32 extBuffer[5];

	// internal fields
	UsbTransfer *transfer;
	Link qhLink;
	u32 tdHead;
	u32 active;
	u32 queries;
	u8 pad[36];
} EhciQH;

// Endpoint Characteristics
#define QH_CH_DEVADDR_MASK              0x0000007f  // Device Address
#define QH_CH_INACTIVE                  0x00000080  // Inactive on Next Transaction
#define QH_CH_ENDP_MASK                 0x00000f00  // Endpoint Number
#define QH_CH_ENDP_SHIFT                8
#define QH_CH_EPS_MASK                  0x00003000  // Endpoint Speed
#define QH_CH_EPS_SHIFT                 12
#define QH_CH_DTC                       0x00004000  // Data Toggle Control
#define QH_CH_H                         0x00008000  // Head of Reclamation List Flag
#define QH_CH_MPL_MASK                  0x07ff0000  // Maximum Packet Length
#define QH_CH_MPL_SHIFT                 16
#define QH_CH_CONTROL                   0x08000000  // Control Endpoint Flag
#define QH_CH_NAK_RL_MASK               0xf0000000  // Nak Count Reload
#define QH_CH_NAK_RL_SHIFT              28

// Endpoint Capabilities
#define QH_CAP_INT_SCHED_SHIFT          0
#define QH_CAP_INT_SCHED_MASK           0x000000ff  // Interrupt Schedule Mask
#define QH_CAP_SPLIT_C_SHIFT            8
#define QH_CAP_SPLIT_C_MASK             0x0000ff00  // Split Completion Mask
#define QH_CAP_HUB_ADDR_SHIFT           16
#define QH_CAP_HUB_ADDR_MASK            0x007f0000  // Hub Address
#define QH_CAP_PORT_MASK                0x3f800000  // Port Number
#define QH_CAP_PORT_SHIFT               23
#define QH_CAP_MULT_MASK                0xc0000000  // High-Bandwidth Pipe Multiplier
#define QH_CAP_MULT_SHIFT               30

// ------------------------------------------------------------------------------------------------
// Device

typedef struct EhciController
{
	EhciCapRegs *capRegs;
	EhciOpRegs *opRegs;
	u32 *frameList;
	EhciQH *qhPool;
	EhciTD *tdPool;
	EhciQH *asyncQH;
	EhciQH *periodicQH;
	uint ehcibase, ehcibase2;
} EhciController;


// ------------------------------------------------------------------------------------------------
static void EhciPrintTD(EhciTD *td)
{
	kprintf("td=0x%x\n", td);
	kprintf(" link=0x%x\n", td->link);
	kprintf(" altLink=0x%x\n", td->altLink);
	kprintf(" token=0x%x\n", td->token);
	kprintf(" buffer=0x%x\n", td->buffer[0]);
}
#if 0
// ------------------------------------------------------------------------------------------------
static void EhciPrintQH(EhciQH *qh)
{
	kprintf("qh=0x%08x\n", qh);
	kprintf(" qhlp=0x%08x\n", qh->qhlp);
	kprintf(" ch=0x%08x\n", qh->ch);
	kprintf(" caps=0x%08x\n", qh->caps);
	kprintf(" curLink=0x%08x\n", qh->curLink);
	kprintf(" nextLink=0x%08x\n", qh->nextLink);
	kprintf(" altLink=0x%08x\n", qh->altLink);
	kprintf(" token=0x%08x\n", qh->token);
	kprintf(" buffer=0x%08x\n", qh->buffer[0]);
	kprintf(" qhPrev=0x%08x\n", qh->qhPrev);
	kprintf(" qhNext=0x%08x\n", qh->qhNext);
}
#endif

void WOR(EhciController * hc, uint reg, uint val)
{
	MWIR(hc->ehcibase, reg, val);
}
uint ROR(EhciController * hc, uint reg)
{
	return MRIR(hc->ehcibase, reg);
}
void WCR(EhciController * hc, uint reg, uint val)
{
	MWIR(hc->ehcibase2, reg, val);
}
uint RCR(EhciController * hc, uint reg)
{
	return MRIR(hc->ehcibase2, reg);
}

// ------------------------------------------------------------------------------------------------
static EhciTD *EhciAllocTD(EhciController *hc)
{
	// TODO - better memory management
	EhciTD *end = hc->tdPool + MAX_TD;
	for (EhciTD *td = hc->tdPool; td != end; ++td)
	{
		if (!td->active)
		{
			//kprintf("EhciAllocTD 0x%08x\n", td);
			td->active = 1;
			return td;
		}
	}

	kprintf("EhciAllocTD failed\n");
	return 0;
}

// ------------------------------------------------------------------------------------------------
static EhciQH *EhciAllocQH(EhciController *hc)
{
	// TODO - better memory management
	EhciQH *end = hc->qhPool + MAX_QH;
	for (EhciQH *qh = hc->qhPool; qh != end; ++qh)
	{
		if (!qh->active)
		{
			//kprintf("EhciAllocQH 0x%08x\n", qh);
			qh->active = 1;
			return qh;
		}
	}

	kprintf("EhciAllocQH failed\n");
	return 0;
}

// ------------------------------------------------------------------------------------------------
static void EhciFreeTD(EhciTD *td)
{
	//kprintf("EhciFreeTD 0x%08x\n", td);
	td->active = 0;
}

// ------------------------------------------------------------------------------------------------
static void EhciFreeQH(EhciQH *qh)
{
	//kprintf("EhciFreeQH 0x%08x\n", qh);
	qh->active = 0;
}

// ------------------------------------------------------------------------------------------------
static void EhciInsertAsyncQH(EhciQH *list, EhciQH *qh)
{
	EhciQH *end = LinkData(list->qhLink.prev, EhciQH, qhLink);

	qh->qhlp = (u32)(uintptr_t)list | PTR_QH;
	end->qhlp = (u32)(uintptr_t)qh | PTR_QH;

	LinkBefore(&list->qhLink, &qh->qhLink);
}

// ------------------------------------------------------------------------------------------------
static void EhciInsertPeriodicQH(EhciQH *list, EhciQH *qh)
{
	EhciQH *end = LinkData(list->qhLink.prev, EhciQH, qhLink);

	qh->qhlp = PTR_TERMINATE;
	end->qhlp = (u32)(uintptr_t)qh | PTR_QH;

	LinkBefore(&list->qhLink, &qh->qhLink);
}

// ------------------------------------------------------------------------------------------------
static void EhciRemoveQH(EhciQH *qh)
{
	EhciQH *prev = LinkData(qh->qhLink.prev, EhciQH, qhLink);

	prev->qhlp = qh->qhlp;
	LinkRemove(&qh->qhLink);
}

// ------------------------------------------------------------------------------------------------
static void EhciPortSet(volatile u32 *portReg, u32 data)
{
	u32 status = *portReg;
	status |= data;
	status &= ~PORT_RWC;
	*portReg = status;
}

// ------------------------------------------------------------------------------------------------
static void EhciPortClr(volatile u32 *portReg, u32 data)
{
	u32 status = *portReg;
	status &= ~PORT_RWC;
	status &= ~data;
	status |= PORT_RWC & data;
	*portReg = status;
}
// ------------------------------------------------------------------------------------------------
static uint EhciResetPort(EhciController *hc, uint port)
{
	volatile u32 *reg = &hc->opRegs->ports[port];

	// Reset the port

	*reg |= (1 << 12) | (1 << 20);
	Wait(1000);
	//kprintf("!Status: %x\n",*reg);
	EhciPortSet(reg, PORT_RESET | (1 << 12) | (1 << 20) | (1 << 6));
	Wait(600);
	EhciPortClr(reg, PORT_RESET);

	// Wait 100ms for port to enable (TODO - what is appropriate length of time?)
	uint status = 0;
	///	*reg |=  (1 << 12);
	for (uint i = 0; i < 5; ++i)
	{
		// Delay
		Wait(300);

		// Get current status
		status = *reg;
		//kprintf("Status: %x\n",status);
		// Check if device is attached to port
		if (~status & PORT_CONNECTION)
		{
			break;
		}

		// Acknowledge change in status
		if (status & (PORT_ENABLE_CHANGE | PORT_CONNECTION_CHANGE))
		{
			EhciPortClr(reg, PORT_ENABLE_CHANGE | PORT_CONNECTION_CHANGE);
			continue;
		}

		// Check if device is enabled
		if (status & PORT_ENABLE)
		{
			break;
		}
	}

	return status;
}
static void EhciInitTD(EhciTD *td, EhciTD *prev,
	uint toggle, uint packetType,
	uint len, const void *data)
{
	if (prev)
	{
		prev->link = (u32)(uintptr_t)td;
		prev->tdNext = (u32)(uintptr_t)td;
	}

	td->link = PTR_TERMINATE;
	td->altLink = PTR_TERMINATE;
	td->tdNext = 0;

	td->token =
		(toggle << TD_TOK_D_SHIFT) |
		(len << TD_TOK_LEN_SHIFT) |
		(3 << TD_TOK_CERR_SHIFT) |
		(packetType << TD_TOK_PID_SHIFT) |
		TD_TOK_ACTIVE;

	// Data buffer (not necessarily page aligned)
	uintptr_t p = (uintptr_t)data;
	td->buffer[0] = (u32)p;
	td->extBuffer[0] = 0;
	p &= ~0xfff;

	// Remaining pages of buffer memory.
	for (uint i = 1; i < 4; ++i)
	{
		p += 0x1000;
		td->buffer[i] = (u32)(p);
		td->extBuffer[i] = 0;
	}
}

// ------------------------------------------------------------------------------------------------
static void EhciInitQH(EhciQH *qh, UsbTransfer *t, EhciTD *td, UsbDevice *parent, bool interrupt, uint speed, uint addr, uint endp, uint maxSize)
{
	qh->transfer = t;

	uint ch =
		(maxSize << QH_CH_MPL_SHIFT) |
		QH_CH_DTC |
		(speed << QH_CH_EPS_SHIFT) |
		(endp << QH_CH_ENDP_SHIFT) |
		addr;
	uint caps =
		(1 << QH_CAP_MULT_SHIFT);

	if (!interrupt)
	{
		ch |= 5 << QH_CH_NAK_RL_SHIFT;
	}

	if (speed != USB_HIGH_SPEED && parent)
	{
		if (interrupt)
		{
			// split completion mask - complete on frames 2, 3, or 4
			caps |= (0x1c << QH_CAP_SPLIT_C_SHIFT);
		}
		else
		{
			ch |= QH_CH_CONTROL;
		}

		caps |=
			(parent->port << QH_CAP_PORT_SHIFT) |
			(parent->addr << QH_CAP_HUB_ADDR_SHIFT);
	}

	if (interrupt)
	{
		// interrupt schedule mask - start on frame 0
		caps |= (0x01 << QH_CAP_INT_SCHED_SHIFT);
	}

	qh->ch = ch;
	qh->caps = caps;
	qh->queries = 0;
	qh->tdHead = (u32)(uintptr_t)td;
	qh->nextLink = (u32)(uintptr_t)td;
	qh->token = 0;
}

void some()
{

}
// ------------------------------------------------------------------------------------------------
void EhciProcessQH(EhciController *hc, EhciQH *qh)
{
	UsbTransfer *t = qh->transfer;
	Wait(1);
	if (qh->token & TD_TOK_HALTED)
	{
		t->success = false;
		t->complete = true;
	}
	else if (qh->nextLink & PTR_TERMINATE)
	{
		if (~qh->token & TD_TOK_ACTIVE)
		{
			if (qh->token & TD_TOK_DATABUFFER)
			{
				kprintf(" Data Buffer Error\n");
			}
			if (qh->token & TD_TOK_BABBLE)
			{
				kprintf(" Babble Detected\n");
			}
			if (qh->token & TD_TOK_XACT)
			{
				kprintf(" Transaction Error\n");
			}
			if (qh->token & TD_TOK_MMF)
			{
				kprintf(" Missed Micro-Frame\n");
			}

			t->success = true;
			t->complete = true;
		}
	}

	if (t->complete)
	{
		// Clear transfer from queue
		qh->transfer = 0;

		// Update endpoint toggle state
		if (t->success && t->endp)
		{
			t->endp->toggle ^= 1;
		}

		// Remove queue from schedule
		EhciRemoveQH(qh);

		// Free transfer descriptors
		EhciTD *td = (EhciTD *)(uintptr_t)qh->tdHead;
		while (td)
		{
			EhciTD *next = (EhciTD *)(uintptr_t)td->tdNext;
			EhciFreeTD(td);
			td = next;
		}

		// Free queue head
		EhciFreeQH(qh);
		//Wait(1);
	}
}

// ------------------------------------------------------------------------------------------------
static void EhciWaitForQH(EhciController *hc, EhciQH *qh)
{
	int st = *sec100;
	UsbTransfer *t = qh->transfer;
	while ((!t->complete))
	{
		EhciProcessQH(hc, qh);
	}

}
// ------------------------------------------------------------------------------------------------
static void EhciDevControl(UsbDevice *dev, UsbTransfer *t)
{
	EhciController *hc = (EhciController *)dev->hc;
	UsbDevReq *req = t->req;

	// Determine transfer properties
	uint speed = dev->speed;
	uint addr = dev->addr;
	uint maxSize = dev->maxPacketSize;
	uint type = req->type;
	uint len = req->len;

	// Create queue of transfer descriptors
	EhciTD *td = EhciAllocTD(hc);
	if (!td)
	{
		return;
	}

	EhciTD *head = td;
	EhciTD *prev = 0;

	// Setup packet
	uint toggle = 0;
	uint packetType = USB_PACKET_SETUP;
	uint packetSize = sizeof(UsbDevReq);
	EhciInitTD(td, prev, toggle, packetType, packetSize, req);
	prev = td;

	// Data in/out packets
	packetType = type & RT_DEV_TO_HOST ? USB_PACKET_IN : USB_PACKET_OUT;

	u8 *it = (u8 *)t->data;
	u8 *end = it + len;
	//EhciPrintTD(td);
	while (it < end)
	{
		td = EhciAllocTD(hc);
		if (!td)
		{
			return;
		}

		toggle ^= 1;
		packetSize = end - it;
		if (packetSize > maxSize)
		{
			packetSize = maxSize;
		}

		EhciInitTD(td, prev, toggle, packetType, packetSize, it);

		//EhciPrintTD(td);
		it += packetSize;
		prev = td;
	}

	// Status packet
	td = EhciAllocTD(hc);
	if (!td)
	{
		return;
	}

	toggle = 1;
	packetType = type & RT_DEV_TO_HOST ? USB_PACKET_OUT : USB_PACKET_IN;
	EhciInitTD(td, prev, toggle, packetType, 0, 0);

	// Initialize queue head
	EhciQH *qh = EhciAllocQH(hc);
	EhciInitQH(qh, t, head, dev->parent, false, speed, addr, 0, maxSize);
	//printQh(qh);
	// Wait until queue has been processed
	EhciInsertAsyncQH(hc->asyncQH, qh);
	EhciWaitForQH(hc, qh);
}
uint ehciInterval(UsbDevice * d, uint i)
{
	if (d->speed == 0)
	{
		uint z = 0;
		while (i > 0) {
			z++;
			i /= 2;
		}
		return z + 3;
	}
	else
	{
		return i + 1;
	}
}
// ------------------------------------------------------------------------------------------------
static void EhciDevIntr(UsbDevice *dev, UsbTransfer *t)
{
	EhciController *hc = (EhciController *)dev->hc;
	// Determine transfer properties
	uint speed = dev->speed;
	uint addr = dev->addr;
	uint maxSize = t->endp->desc->maxPacketSize;
	uint endp = t->endp->desc->addr & 0xf;
	//kprintf("$%x$", endp);
	// Create queue of transfer descriptors
	EhciTD *td = EhciAllocTD(hc);
	if (!td)
	{
		t->success = false;
		t->complete = true;
		return;
	}

	EhciTD *head = td;
	EhciTD *prev = 0;

	// Data in/out packets
	uint toggle = t->endp->toggle;
	uint packetType = USB_PACKET_IN;
	if (t->endp->desc->addr & 0x80)
		packetType = USB_PACKET_IN;
	else
		packetType = USB_PACKET_OUT;


	uint packetSize = t->len;

	EhciInitTD(td, prev, toggle, packetType, packetSize, t->data);
	// Initialize queue head
	EhciQH *qh = EhciAllocQH(hc);
	EhciInitQH(qh, t, head, dev->parent, true, speed, addr, endp, maxSize);
	// Schedule queue
	if (t->w)
		EhciInsertAsyncQH(hc->asyncQH, qh);
	else
		EhciInsertPeriodicQH(hc->periodicQH, qh);
	if (t->w)
		EhciWaitForQH(hc, qh);
}
void probeEhciPort(EhciController *hc, uint port)
{
	uint status = EhciResetPort(hc, port);
	//kprintf("Port probe status: %x\n", status);
	if (status & PORT_ENABLE)
	{
		uint speed = USB_HIGH_SPEED;
		kprintf("Detected device on port #%x\n", port);
		Wait(1000);
		UsbDevice *dev = UsbDevCreate();
		if (dev)
		{
			dev->parent = 0;
			dev->hc = hc;
			dev->port = port;
			dev->speed = speed;
			dev->maxPacketSize = 8;

			//kprintf("Status: %x\n", hc->opRegs->usbSts);

			dev->hcControl = EhciDevControl;
			dev->hcIntr = EhciDevIntr;

			if (!UsbDevInit(dev))
			{
				attr = 0x4E;
				kprintf("Some FUKIN BAD!");
				// TODO - cleanup
			}
		}
	}
}
// ------------------------------------------------------------------------------------------------
static void EhciProbe(EhciController *hc)
{
	// Port setup
	//kprintf("%x", hc->capRegs->hcsParams);
	uint portCount = RCR(hc, hcsParamsO) & HCSPARAMS_N_PORTS_MASK;

	for (uint port = 0; port < portCount; ++port)
	{
		// Reset port

		probeEhciPort(hc, port);
	}
}
void printQh(EhciQH * qh)
{
	uint q = attr;
	attr = 0x04;
	kprintf("Addr=%x, QueueHead info:\n", qh);
	kprintf(" QHLP = 0x%x, EndpCh = 0x%x, EndpCap = 0x%x\n\
 NextLink = 0x%x, AltLink = 0x%x, Token = 0x%x\n", qh->qhlp, qh->ch, qh->caps, qh->nextLink, qh->altLink, qh->token);
	kprintf(" Buffers:\n");
	for (int i = 0; i < 5; i++)
	{
		kprintf("  [%x,%x]", qh->buffer[i], qh->extBuffer[i]);
	}
	kprintf("\n");
	attr = q;
}
static void EhciControllerPollList(EhciController *hc, Link *list)
{
	EhciQH *qh;
	EhciQH *next;
	lockTaskSwitch(1);
	ListForEachSafe(qh, next, *list, qhLink)
	{
		if (qh->transfer && (qh->transfer->w == 0) && (!qh->transfer->complete))
		{
			EhciProcessQH(hc, qh);
		}
	}
	unlockTaskSwitch();
}

// ------------------------------------------------------------------------------------------------
static void EhciControllerPoll(UsbController *controller)
{
	EhciController *hc = (EhciController *)controller->hc;
	EhciControllerPollList(hc, &hc->asyncQH->qhLink);
	EhciControllerPollList(hc, &hc->periodicQH->qhLink);
	uint portCount = RCR(hc, hcsParamsO) & HCSPARAMS_N_PORTS_MASK;
	for (uint port = 0; port < portCount; ++port)
	{
		volatile u32 *reg = &hc->opRegs->ports[port];
		uint status = *reg;
		if (status & 2 && !(status & 1))
		{
			//Device disconnected
			kprintf("USB device has disconnected from EHCI!\n");
			UsbDevice * cur = g_usbDeviceList, *ls = 0;
			//Clear Connection change bit
			EhciPortClr(reg, PORT_CONNECTION_CHANGE);
			while (cur)
			{
				if (cur->port == port && (uint)cur->hc == (uint)hc)
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
		else if (status & 2 && (status & 1)) {
			kprintf("USB device connected to EHCI!\n");
			EhciPortClr(reg, PORT_CONNECTION_CHANGE);
			probeEhciPort(hc, port);
		}
	}
}
// ------------------------------------------------------------------------------------------------
void _ehci_init(uint id, PciDeviceInfo *info)
{
	if (!(((info->classCode << 8) | info->subclass) == PCI_SERIAL_USB &&
		info->progIntf == PCI_SERIAL_USB_EHCI))
	{
		return;
	}

	if (sizeof(EhciQH) != 128)
	{
		kprintf("Unexpected EhciQH size: %d\n", sizeof(EhciQH));
		return;
	}

	kprintf("Initializing EHCI\n");

	// Base I/O Address
	PciBar bar;
	PciGetBar(&bar, id, 0);
	if (bar.flags & PCI_BAR_IO)
	{
		// Only Memory Mapped I/O supported
		return;
	}
	//return;
	// Controller initialization
	EhciController *hc = (EhciController *)VMAlloc(sizeof(EhciController));
	hc->capRegs = (EhciCapRegs *)(uintptr_t)bar.u.address;
	hc->ehcibase2 = (uint)bar.u.address;
	hc->opRegs = (EhciOpRegs *)(uintptr_t)(bar.u.address + hc->capRegs->capLength);
	hc->ehcibase = (uint)&hc->opRegs->usbCmd;
	//return;
	//MWIR(ehcibase, usbStsO, 0x0);
	// Read the Command register
	kprintf("!!%x!", hc->capRegs->hcsParams);
	uint cmd = ROR(hc, usbCmdO);
	// Write it back, setting bit 2 (the Reset bit) 
	//  and making sure the two schedule Enable bits are clear.
	WOR(hc, usbCmdO, 2 | cmd & ~(CMD_ASE | CMD_PSE));
	// A small delay here would be good.  You don't want to read
	//  the register before it has a chance to actually set the bit
	ROR(hc, usbCmdO);
	// Now wait for the controller to clear the reset bit.
	// Note: A timeout would be a good idea too in case the bit
	//  never becomes clear.  (Bad controller: Bad address: etc.) (See note 1 below)
	while (ROR(hc, usbCmdO) & 2);
	// Again, a small delay here would be good to allow the
	//  reset to actually become complete.
	ROR(hc, usbCmdO);
	// wait for the halted bit to become set
	// again, see note 1 below)
	while (!(ROR(hc, usbStsO) & STS_HCHALTED));
	//kprintf("$%x,%x$", hc->opRegs->usbCmd, hc->opRegs->usbSts);
	hc->frameList = (u32 *)VMAlloc(1024 * sizeof(u32) + 8192 * 4);
	hc->frameList = (((uint)hc->frameList) / 16384) * 16384 + 16384;
	hc->qhPool = (EhciQH *)VMAlloc(sizeof(EhciQH) * MAX_QH + 8192 * 4);
	hc->tdPool = (EhciTD *)VMAlloc(sizeof(EhciTD) * MAX_TD + 8192 * 4);
	hc->qhPool = (((uint)hc->qhPool) / 16384) * 16384 + 16384;

	hc->tdPool = (((uint)hc->tdPool) / 16384) * 16384 + 16384;
	//kprintf("QHPool Address=0x%x, TDPool Address=0x%x, FrameList Address=0x%x\n", hc->qhPool, hc->tdPool, hc->frameList);
	// Asynchronous queue setup
	EhciQH *qh = EhciAllocQH(hc);
	qh->qhlp = (u32)(uintptr_t)qh | PTR_QH;
	qh->ch = QH_CH_H;
	qh->caps = 0;
	qh->curLink = 0;
	qh->nextLink = PTR_TERMINATE;
	qh->altLink = 0;
	qh->token = 0;
	for (uint i = 0; i < 5; ++i)
	{
		qh->buffer[i] = 0;
		qh->extBuffer[i] = 0;
	}
	qh->transfer = 0;
	qh->qhLink.prev = &qh->qhLink;
	qh->qhLink.next = &qh->qhLink;

	hc->asyncQH = qh;
	//kprintf("AsyncQH info:\n");
	//printQh(qh);
	// Periodic list queue setup
	qh = EhciAllocQH(hc);
	qh->qhlp = PTR_TERMINATE;
	qh->ch = 0;
	qh->caps = 0;
	qh->curLink = 0;
	qh->nextLink = PTR_TERMINATE;
	qh->altLink = 0;
	qh->token = 0;
	for (uint i = 0; i < 5; ++i)
	{
		qh->buffer[i] = 0;
		qh->extBuffer[i] = 0;
	}
	qh->transfer = 0;
	qh->qhLink.prev = &qh->qhLink;
	qh->qhLink.next = &qh->qhLink;

	hc->periodicQH = qh;
	//kprintf("PereodicQH info:\n");
	//printQh(qh);
	for (uint i = 0; i < 1024; ++i)
	{
		hc->frameList[i] = PTR_QH | (u32)(uintptr_t)qh;
	}
	kprintf("FrameList filled. Turning off Legacy BIOS support...");
	// Check extended capabilities
	uint eecp = (RCR(hc, hccParamsO) & HCCPARAMS_EECP_MASK) >> HCCPARAMS_EECP_SHIFT;
	if (eecp >= 0x40)
	{
		// Disable BIOS legacy support
		uint legsup = PciRead32(id, eecp + USBLEGSUP);
		kprintf(".");
		if (legsup & USBLEGSUP_HC_BIOS)
		{
			PciWrite32(id, eecp + USBLEGSUP, legsup | USBLEGSUP_HC_OS); kprintf(".");
			for (;;)
			{
				legsup = PciRead32(id, eecp + USBLEGSUP);
				kprintf(".");
				if (~legsup & USBLEGSUP_HC_BIOS && legsup & USBLEGSUP_HC_OS)
				{
					break;
				}
			}
		}
	}
	kprintf("Done\n");
	// Disable interrupts
	hc->opRegs->usbIntr = 0;
	//MWIR(hc->ehcibase, usbIntrO, 0);
	//return;
	// Setup frame list
	hc->opRegs->frameIndex = 0;
	//WOR(hc,frameIndexO, 0);
	hc->opRegs->periodicListBase = (u32)(uintptr_t)hc->frameList;
	//WOR(hc,periodicListBaseO, (u32)(uintptr_t)hc->frameList);
	hc->opRegs->asyncListAddr = (u32)(uintptr_t)hc->asyncQH;
	//WOR(hc,asyncListAddrO, (u32)(uintptr_t)hc->asyncQH);
	//	kprintf("[%x,%x]", &hc->opRegs->asyncListAddr, (uintptr_t)(bar.u.address + hc->capRegs->capLength));
	//	moveee((uintptr_t)(bar.u.address + hc->capRegs->capLength)+0x14, 0x4, (u32)(uintptr_t)hc->asyncQH);
	hc->opRegs->ctrlDsSegment = 0;
	//WOR(hc,ctrlDsSegmentO, 0);
	//PitWait(100);
	// Clear status
	hc->opRegs->usbSts = 0x3f;
	//WOR(hc,usbStsO, ~0);
	// Enable controller
	hc->opRegs->usbCmd = (8 << CMD_ITC_SHIFT) | CMD_PSE | CMD_ASE | CMD_RS;

	//WOR(hc,usbCmdO, (8 << CMD_ITC_SHIFT) | CMD_PSE | CMD_ASE | CMD_RS);
	while (ROR(hc, usbStsO)&STS_HCHALTED);

	// Configure all devices to be managed by the EHCI
	hc->opRegs->configFlag = 1;
	//WOR(hc,configFlagO, 1);
	PitWait(500);    // TODO - remove after dynamic port detection
	kprintf("Device configured. Probing ports...\n");
	// Probe devices
	EhciProbe(hc);

	// Register controller
	UsbController *controller = (UsbController *)malloc(sizeof(UsbController));
	controller->next = g_usbControllerList;
	controller->hc = hc;
	//controller->poll = &epoll;
	controller->poll = &EhciControllerPoll;

	g_usbControllerList = controller;
}
#pragma GCC pop_options