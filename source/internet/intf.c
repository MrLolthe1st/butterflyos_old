
// ------------------------------------------------------------------------------------------------
// Net Interface

typedef struct NetIntf
{
	Link link;
	EthAddr ethAddr;
	Ipv4Addr ipAddr;
	Ipv4Addr broadcastAddr;
	const char *name;

	void(*poll)(struct NetIntf *intf);
	void(*send)(struct NetIntf *intf, const void *dstAddr, u16 etherType, NetBuf *buf);
	void(*devSend)(NetBuf *buf);
} NetIntf;

// ------------------------------------------------------------------------------------------------
// Globals

extern Link g_netIntfList;

// ------------------------------------------------------------------------------------------------
// Functions

NetIntf *NetIntfCreate();
void NetIntfAdd(NetIntf *intf);
// ------------------------------------------------------------------------------------------------
// Globals

Link g_netIntfList = { &g_netIntfList, &g_netIntfList };

// ------------------------------------------------------------------------------------------------
NetIntf *NetIntfCreate()
{
	NetIntf *intf = (NetIntf *)VMAlloc(sizeof(NetIntf));
	memset(intf, 0, sizeof(NetIntf));
	LinkInit(&intf->link);

	return intf;
}

// ------------------------------------------------------------------------------------------------
void NetIntfAdd(NetIntf *intf)
{
	LinkBefore(&g_netIntfList, &intf->link);
}