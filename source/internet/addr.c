// ------------------------------------------------------------------------------------------------
// Ethernet Address

typedef struct EthAddr
{
	u8 n[6];
} PACKED EthAddr;

#define ETH_ADDR_STRING_SIZE            18

// ------------------------------------------------------------------------------------------------
// IPv4 Address

typedef struct Ipv4Addr
{
	union
	{
		u8 n[4];
		u32 bits;
	} u;
} PACKED Ipv4Addr;

#define IPV4_ADDR_STRING_SIZE           16
#define IPV4_ADDR_PORT_STRING_SIZE      22

// ------------------------------------------------------------------------------------------------
// Globals

extern const EthAddr g_nullEthAddr;
extern const EthAddr g_broadcastEthAddr;

extern const Ipv4Addr g_nullIpv4Addr;
extern const Ipv4Addr g_broadcastIpv4Addr;

// ------------------------------------------------------------------------------------------------
// Functions

bool EthAddrEq(const EthAddr *x, const EthAddr *y);
bool Ipv4AddrEq(const Ipv4Addr *x, const Ipv4Addr *y);

void EthAddrToStr(char *str, size_t size, const EthAddr *addr);
void Ipv4AddrToStr(char *str, size_t size, const Ipv4Addr *addr);
void Ipv4AddrPortToStr(char *str, size_t size, const Ipv4Addr *addr, u16 port);

bool StrToIpv4Addr(Ipv4Addr *addr, const char *str);
bool StrToIpv4AddrPort(Ipv4Addr *addr, const char *str, u16 *port);

// ------------------------------------------------------------------------------------------------
const EthAddr g_nullEthAddr = { { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } };
const EthAddr g_broadcastEthAddr = { { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff } };

const Ipv4Addr g_nullIpv4Addr = { { { 0x00, 0x00, 0x00, 0x00 } } };
const Ipv4Addr g_broadcastIpv4Addr = { { { 0xff, 0xff, 0xff, 0xff } } };

// ------------------------------------------------------------------------------------------------
bool EthAddrEq(const EthAddr *x, const EthAddr *y)
{
	for (uint i = 0; i < 6; ++i)
	{
		if (x->n[i] != y->n[i])
		{
			return false;
		}
	}

	return true;
}

// ------------------------------------------------------------------------------------------------
bool Ipv4AddrEq(const Ipv4Addr *x, const Ipv4Addr *y)
{
	return x->u.bits == y->u.bits;
}

// ------------------------------------------------------------------------------------------------
void EthAddrToStr(char *str, size_t size, const EthAddr *addr)
{
	snprintf(str, size, "%02x:%02x:%02x:%02x:%02x:%02x",
		addr->n[0], addr->n[1], addr->n[2], addr->n[3], addr->n[4], addr->n[5]);
}

// ------------------------------------------------------------------------------------------------
void Ipv4AddrToStr(char *str, size_t size, const Ipv4Addr *addr)
{
	snprintf(str, size, "%d.%d.%d.%d",
		addr->u.n[0], addr->u.n[1], addr->u.n[2], addr->u.n[3]);
}

// ------------------------------------------------------------------------------------------------
void Ipv4AddrPortToStr(char *str, size_t size, const Ipv4Addr *addr, u16 port)
{
	snprintf(str, size, "%d.%d.%d.%d:%d",
		addr->u.n[0], addr->u.n[1], addr->u.n[2], addr->u.n[3], port);
}

// ------------------------------------------------------------------------------------------------
bool StrToIpv4Addr(Ipv4Addr *addr, const char *str)
{
	int a[4];
	if (sscanf(str, "%d.%d.%d.%d", &a[0], &a[1], &a[2], &a[3]) == 4)
	{
		addr->u.n[0] = a[0];
		addr->u.n[1] = a[1];
		addr->u.n[2] = a[2];
		addr->u.n[3] = a[3];
		return true;
	}

	return false;
}

// ------------------------------------------------------------------------------------------------
bool StrToIpv4AddrPort(Ipv4Addr *addr, const char *str, u16 *port)
{
	int a[4];
	int n;
	if (sscanf(str, "%d.%d.%d.%d:%d", &a[0], &a[1], &a[2], &a[3], &n) == 5)
	{
		addr->u.n[0] = a[0];
		addr->u.n[1] = a[1];
		addr->u.n[2] = a[2];
		addr->u.n[3] = a[3];
		*port = n;
		return true;
	}

	return false;
}