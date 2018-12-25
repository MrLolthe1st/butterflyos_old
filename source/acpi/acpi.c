

#define MAX_CPU_COUNT 16

uint g_acpiCpuCount;
u8 g_acpiCpuIds[MAX_CPU_COUNT];

// ------------------------------------------------------------------------------------------------
typedef struct AcpiHeader
{
	u32 signature;
	u32 length;
	u8 revision;
	u8 checksum;
	u8 oem[6];
	u8 oemTableId[8];
	u32 oemRevision;
	u32 creatorId;
	u32 creatorRevision;
} PACKED AcpiHeader;

// ------------------------------------------------------------------------------------------------
typedef struct AcpiFadt
{
	AcpiHeader header;
	u32 firmwareControl;
	u32 dsdt;
	u8 reserved;
	u8 preferredPMProfile;
	u16 sciInterrupt;
	u32 smiCommandPort;
	u8 acpiEnable;
	u8 acpiDisable;
	// TODO - fill in rest of data
} PACKED AcpiFadt;

// ------------------------------------------------------------------------------------------------
typedef struct AcpiMadt
{
	AcpiHeader header;
	u32 localApicAddr;
	u32 flags;
} PACKED AcpiMadt;

// ------------------------------------------------------------------------------------------------
typedef struct ApicHeader
{
	u8 type;
	u8 length;
} PACKED ApicHeader;

// APIC structure types
#define APIC_TYPE_LOCAL_APIC            0
#define APIC_TYPE_IO_APIC               1
#define APIC_TYPE_INTERRUPT_OVERRIDE    2

// ------------------------------------------------------------------------------------------------
typedef struct ApicLocalApic
{
	ApicHeader header;
	u8 acpiProcessorId;
	u8 apicId;
	u32 flags;
} PACKED ApicLocalApic;


u8 *g_ioApicAddr;
// ------------------------------------------------------------------------------------------------
typedef struct ApicIoApic
{
	ApicHeader header;
	u8 ioApicId;
	u8 reserved;
	u32 ioApicAddress;
	u32 globalSystemInterruptBase;
} PACKED ApicIoApic;

// ------------------------------------------------------------------------------------------------
typedef struct ApicInterruptOverride
{
	ApicHeader header;
	u8 bus;
	u8 source;
	u32 interrupt;
	u16 flags;
} PACKED ApicInterruptOverride;


struct address_structure
{
	uint8_t address_space_id;    // 0 - system memory, 1 - system I/O
	uint8_t register_bit_width;
	uint8_t register_bit_offset;
	uint8_t reserved;
	uint32_t address;
	uint32_t address1;
} __attribute__((packed));

struct description_table_header
{
	char signature[4];    // 'HPET' in case of HPET table
	uint32_t length;
	uint8_t revision;
	uint8_t checksum;
	char oemid[6];
	uint64_t oem_tableid;
	uint32_t oem_revision;
	uint32_t creator_id;
	uint32_t creator_revision;
} __attribute__((packed));

typedef struct
{
	struct description_table_header header;
	uint32_t addresss;
	struct address_structure address;
	uint8_t hpet_number;
	uint16_t minimum_tick;
	uint8_t page_protection;
} __attribute__((packed)) hpet;


// ------------------------------------------------------------------------------------------------
static AcpiMadt *s_madt;

// ------------------------------------------------------------------------------------------------
static void AcpiParseFacp(AcpiFadt *facp)
{
	if (facp->smiCommandPort)
	{
		kprintf("Enabling ACPI\n");
		IoWrite8(facp->smiCommandPort, facp->acpiEnable);

		// TODO - wait for SCI_EN bit
		//Wait(100);
	}
	else
	{
		kprintf("ACPI already enabled\n");
	}
}
volatile uint  *g_localApicAddr = (uint*)0x2550;
volatile uint  *g_activeCpuCount = (uint*)0x2555;
// ------------------------------------------------------------------------------------------------
static void AcpiParseApic(AcpiMadt *madt)
{
	s_madt = madt;

	kprintf("Local APIC Address = 0x%x\n", madt->localApicAddr);
	*g_localApicAddr = (uintptr_t)madt->localApicAddr;

	u8 *p = (u8 *)(madt + 1);
	u8 *end = (u8 *)madt + madt->header.length;

	while (p < end)
	{
		ApicHeader *header = (ApicHeader *)p;
		u8 type = header->type;
		u8 length = header->length;

		if (type == APIC_TYPE_LOCAL_APIC)
		{
			ApicLocalApic *s = (ApicLocalApic *)p;

			kprintf("Found CPU: %d %d %x\n", s->acpiProcessorId, s->apicId, s->flags);
			if (g_acpiCpuCount < MAX_CPU_COUNT)
			{
				g_acpiCpuIds[g_acpiCpuCount] = s->apicId;
				++g_acpiCpuCount;
			}
		}
		else if (type == APIC_TYPE_IO_APIC)
		{
			ApicIoApic *s = (ApicIoApic *)p;

			kprintf("Found I/O APIC: %d 0x%x %d\n", s->ioApicId, s->ioApicAddress, s->globalSystemInterruptBase);
			g_ioApicAddr = (u8 *)(uintptr_t)s->ioApicAddress;
		}
		else if (type == APIC_TYPE_INTERRUPT_OVERRIDE)
		{
			ApicInterruptOverride *s = (ApicInterruptOverride *)p;

			kprintf("Found Interrupt Override: %d %d %d 0x%x\n", s->bus, s->source, s->interrupt, s->flags);
		}
		else
		{
			kprintf("Unknown APIC structure %d\n", type);
		}

		p += length;
	}
}
#define HPET_REG32(off) (*(volatile unsigned int *)(long)			\
		       (memms + (off)))

#define CLK_PERIOD_REG        HPET_REG32(0x04) /* High dword of caps reg */
#define GENERAL_CONF_REG      HPET_REG32(0x10)
#define MAIN_COUNTER_REG      HPET_REG32(0xf0)
#define TIMER0_CONF_REG       HPET_REG32(0x120)
#define TIMER0_COMPARATOR_REG HPET_REG32(0x128)
#define BIT 1<<
/* GENERAL_CONF_REG bits */
#define GCONF_ENABLE BIT(0)
#define GCONF_LR     BIT(1) /* legacy interrupt routing, disables PIT */

/* TIMERn_CONF_REG bits */
#define TCONF_INT_ENABLE BIT(2)
#define TCONF_PERIODIC   BIT(3)
#define TCONF_VAL_SET    BIT(6)
#define TCONF_MODE32     BIT(8)
int log2(int val)
{
	int k = 0;
	while (val > 0)
	{
		k++;
		val >>= 1;
	}
	return k;
}
unsigned long long cyc_per_tick = 0;
unsigned int memms;
// ------------------------------------------------------------------------------------------------
void AcpiParseDT(AcpiHeader *header)
{
	u32 signature = header->signature;

	char sigStr[5];
	memcpy(sigStr, (char*)&signature, 4);
	sigStr[4] = 0;
	printTextToWindow(7, mywin, "!%s 0x%x\n", &sigStr, header);
	if (signature == 0x54455048)
	{
		//Hpet
		hpet * w = header;
		memms = w->address.address;
		return;
		//HPET_REG32(0x20) = HPET_REG32(0x20);
		uint val = (TIMER0_CONF_REG & ~(0x1f << 9)) | ((0 & 0x1f) << 9);
		//return;
		TIMER0_CONF_REG = val;

		printTextToWindow(7, mywin, "!%x 0x%x\n", 1, CLK_PERIOD_REG);
		unsigned long long hz = (unsigned long long)((unsigned long long)1000000000 / (unsigned long long)CLK_PERIOD_REG);

		// (1e10 / some) 
		cyc_per_tick = hz * 10;
		GENERAL_CONF_REG |= GCONF_LR | GCONF_ENABLE;

		TIMER0_CONF_REG |= TCONF_MODE32;
		TIMER0_CONF_REG |= TCONF_INT_ENABLE;
		TIMER0_CONF_REG |= (1 << 3) | (1 << 2) | (1 << 6);
		TIMER0_COMPARATOR_REG = MAIN_COUNTER_REG + cyc_per_tick;
		TIMER0_COMPARATOR_REG = (0 + cyc_per_tick) & 0xFFFFFFFF;
		//HPET_REG32(0x10C) = (0 + cyc_per_tick)>>32;
		//TIMER0_CONF_REG |= 1<<2;
	}
	else
		if (signature == 0x50434146)
		{
			AcpiParseFacp((AcpiFadt *)header);
		}
		else if (signature == 0x43495041)
		{
			AcpiParseApic((AcpiMadt *)header);
		}
}

// ------------------------------------------------------------------------------------------------
static void AcpiParseRsdt(AcpiHeader *rsdt)
{
	u32 *p = (u32 *)(rsdt + 1);
	u32 *end = (u32 *)((u8*)rsdt + rsdt->length);
	kprintf("^%x\n", p);
	while (p < end)
	{
		u32 address = *p++;
		AcpiParseDT((AcpiHeader *)(uintptr_t)address);
	}
}

// ------------------------------------------------------------------------------------------------
static void AcpiParseXsdt(AcpiHeader *xsdt)
{
	u64 *p = (u64 *)(xsdt + 1);
	u64 *end = (u64 *)((u8*)xsdt + xsdt->length);

	while (p < end)
	{
		u64 address = *p++;
		AcpiParseDT((AcpiHeader *)(uintptr_t)address);
	}
}

// ------------------------------------------------------------------------------------------------
static bool AcpiParseRsdp(u8 *p)
{
	// Parse Root System Description Pointer
	kprintf("RSDP found %x\n", p);

	// Verify checksum
	u8 sum = 0;
	for (uint i = 0; i < 20; ++i)
	{
		sum += p[i];
	}

	if (sum)
	{
		kprintf("Checksum failed\n");
		return false;
	}
	//printMem(p,0x2c);
	// Print OEM
	char oem[7];
	memcpy((char*)&oem, (char*)((uint)p + 9), 6);
	oem[6] = '\0';
	kprintf("OEM = %s\n", &oem);

	// Check version
	u8 revision = p[15];
	if (revision == 0)
	{
		kprintf("Version 1\n");

		u32 rsdtAddr = *(u32 *)((uint)p + 16);
		//printMem((uint)p+16,4);
		AcpiParseRsdt((AcpiHeader *)(uintptr_t)rsdtAddr);
	}
	else if (revision == 2)
	{
		kprintf("Version 2,%x\n", (u32 *)(p + 16));

		u32 rsdtAddr = *(u32 *)(p + 16);
		u64 xsdtAddr = *(u64 *)(p + 24);
		AcpiParseRsdt((AcpiHeader *)(uintptr_t)rsdtAddr);
	}
	else
	{
		kprintf("Unsupported ACPI version %d\n", revision);
	}

	return true;
}

// ------------------------------------------------------------------------------------------------
void AcpiInit()
{
	// TODO - Search Extended BIOS Area

	// Search main BIOS area below 1MB
	u8 *p = (u8 *)0x000e0000;
	u8 *end = (u8 *)0x000fffff;

	while (p < end)
	{
		u64 signature = *((u64 *)p);
		if (signature == 0x2052545020445352) // 'RSD PTR '
		{
			if (AcpiParseRsdp(p))
			{
				break;
			}
		}

		p += 16;
	}
}
// ------------------------------------------------------------------------------------------------
uint AcpiRemapIrq(uint irq)
{
	AcpiMadt *madt = s_madt;

	kprintf("%x*", madt);
	u8 *p = (u8 *)(madt + 1);
	u8 *end = (u8 *)madt + madt->header.length;

	while (p < end)
	{
		ApicHeader *header = (ApicHeader *)p;
		u8 type = header->type;
		u8 length = header->length;

		if (type == APIC_TYPE_INTERRUPT_OVERRIDE)
		{
			ApicInterruptOverride *s = (ApicInterruptOverride *)p;

			if (s->source == irq)
			{
				return s->interrupt;
			}
		}

		p += length;
	}
	return irq;
}

// ------------------------------------------------------------------------------------------------
// Local APIC Registers
#define LAPIC_ID                        0x0020  // Local APIC ID
#define LAPIC_VER                       0x0030  // Local APIC Version
#define LAPIC_TPR                       0x0080  // Task Priority
#define LAPIC_APR                       0x0090  // Arbitration Priority
#define LAPIC_PPR                       0x00a0  // Processor Priority
#define LAPIC_EOI                       0x00b0  // EOI
#define LAPIC_RRD                       0x00c0  // Remote Read
#define LAPIC_LDR                       0x00d0  // Logical Destination
#define LAPIC_DFR                       0x00e0  // Destination Format
#define LAPIC_SVR                       0x00f0  // Spurious Interrupt Vector
#define LAPIC_ISR                       0x0100  // In-Service (8 registers)
#define LAPIC_TMR                       0x0180  // Trigger Mode (8 registers)
#define LAPIC_IRR                       0x0200  // Interrupt Request (8 registers)
#define LAPIC_ESR                       0x0280  // Error Status
#define LAPIC_ICRLO                     0x0300  // Interrupt Command
#define LAPIC_ICRHI                     0x0310  // Interrupt Command [63:32]
#define LAPIC_TIMER                     0x0320  // LVT Timer
#define LAPIC_THERMAL                   0x0330  // LVT Thermal Sensor
#define LAPIC_PERF                      0x0340  // LVT Performance Counter
#define LAPIC_LINT0                     0x0350  // LVT LINT0
#define LAPIC_LINT1                     0x0360  // LVT LINT1
#define LAPIC_ERROR                     0x0370  // LVT Error
#define LAPIC_TICR                      0x0380  // Initial Count (for Timer)
#define LAPIC_TCCR                      0x0390  // Current Count (for Timer)
#define LAPIC_TDCR                      0x03e0  // Divide Configuration (for Timer)

// ------------------------------------------------------------------------------------------------
// Interrupt Command Register

// Delivery Mode
#define ICR_FIXED                       0x00000000
#define ICR_LOWEST                      0x00000100
#define ICR_SMI                         0x00000200
#define ICR_NMI                         0x00000400
#define ICR_INIT                        0x00000500
#define ICR_STARTUP                     0x00000600

// Destination Mode
#define ICR_PHYSICAL                    0x00000000
#define ICR_LOGICAL                     0x00000800

// Delivery Status
#define ICR_IDLE                        0x00000000
#define ICR_SEND_PENDING                0x00001000

// Level
#define ICR_DEASSERT                    0x00000000
#define ICR_ASSERT                      0x00004000

// Trigger Mode
#define ICR_EDGE                        0x00000000
#define ICR_LEVEL                       0x00008000

// Destination Shorthand
#define ICR_NO_SHORTHAND                0x00000000
#define ICR_SELF                        0x00040000
#define ICR_ALL_INCLUDING_SELF          0x00080000
#define ICR_ALL_EXCLUDING_SELF          0x000c0000

// Destination Field
#define ICR_DESTINATION_SHIFT           24

// ------------------------------------------------------------------------------------------------
static u32 LocalApicIn(uint reg)
{
	return MmioRead32((uint*)(*g_localApicAddr + reg));
}

// ------------------------------------------------------------------------------------------------
static void LocalApicOut(uint reg, u32 data)
{
	MmioWrite32((uint*)(*g_localApicAddr + reg), data);
}

// ------------------------------------------------------------------------------------------------
void LocalApicInit()
{
	// Clear task priority to enable all interrupts
	LocalApicOut(LAPIC_TPR, 0);

	// Logical Destination Mode
	LocalApicOut(LAPIC_DFR, 0xffffffff);   // Flat mode
	LocalApicOut(LAPIC_LDR, 0x01000000);   // All cpus use logical id 1

	// Configure Spurious Interrupt Vector Register
	LocalApicOut(LAPIC_SVR, 0x100 | 0xff);
}

// ------------------------------------------------------------------------------------------------
uint LocalApicGetId()
{
	return LocalApicIn(LAPIC_ID) >> 24;
}

// ------------------------------------------------------------------------------------------------
void LocalApicSendInit(uint apic_id)
{
	LocalApicOut(LAPIC_ICRHI, apic_id << ICR_DESTINATION_SHIFT);
	LocalApicOut(LAPIC_ICRLO, ICR_INIT | ICR_PHYSICAL
		| ICR_ASSERT | ICR_EDGE | ICR_NO_SHORTHAND);

	while (LocalApicIn(LAPIC_ICRLO) & ICR_SEND_PENDING)
		;
}

// ------------------------------------------------------------------------------------------------
void LocalApicSendStartup(uint apic_id, uint vector)
{
	LocalApicOut(LAPIC_ICRHI, apic_id << ICR_DESTINATION_SHIFT);
	LocalApicOut(LAPIC_ICRLO, vector | ICR_STARTUP
		| ICR_PHYSICAL | ICR_ASSERT | ICR_EDGE | ICR_NO_SHORTHAND);

	while (LocalApicIn(LAPIC_ICRLO) & ICR_SEND_PENDING)
		;
}
void SmpInit()
{
	printTextToWindow(3, mywin,"Waking up all %d CPUs\n", g_acpiCpuCount);

	*g_activeCpuCount = 1;
	uint localId = LocalApicGetId();

	// Send Init to all cpus except self
	for (uint i = 0; i < g_acpiCpuCount; ++i)
	{
		uint apicId = g_acpiCpuIds[i];
		if (apicId != localId)
		{
			LocalApicSendInit(apicId);
		}
	}

	// wait
	Wait(150);

	// Send Startup to all cpus except self
	for (uint i = 0; i < g_acpiCpuCount; ++i)
	{
		uint apicId = g_acpiCpuIds[i];
		if (apicId != localId)
		{
			LocalApicSendStartup(apicId, 0x8);
			Wait(50);
		}
	}

	// Wait for all cpus to be active
	PitWait(10);
	int cnt = 0;
	while (*g_activeCpuCount != g_acpiCpuCount)
	{
		kprintf("Waiting... %d %d\n", *g_activeCpuCount, g_acpiCpuCount);
		PitWait(10);
		cnt++;
		if (cnt > 300)
			return;
	}

	kprintf("All CPUs activated\n");
}