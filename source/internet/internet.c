// ------------------------------------------------------------------------------------------------
// Ethertypes
// ------------------------------------------------------------------------------------------------
// Trace mask
// ------------------------------------------------------------------------------------------------
// Internet Ports

#define PORT_DNS                        53
#define PORT_BOOTP_SERVER               67
#define PORT_BOOTP_CLIENT               68
#define PORT_NTP                        123
// ------------------------------------------------------------------------------------------------
static inline u16 NetSwap16(u16 x)
{
    return (x>>8) | (x<<8);
}

// ------------------------------------------------------------------------------------------------
static inline u32 NetSwap32(u32 x)
{
    return __builtin_bswap32(x);
}

// ------------------------------------------------------------------------------------------------
static inline u64 NetSwap64(u64 x)
{
    return __builtin_bswap64(x);
}
#define PORT_OSHELPER                   4950
#define TRACE_LINK      (1 << 0)
#define TRACE_NET       (1 << 1)
#define TRACE_TRANSPORT (1 << 2)
#define TRACE_APP       (1 << 3)
#define ET_IPV4                         0x0800
#define ET_ARP                          0x0806
#define ET_IPV6                         0x86DD

u8 g_netTrace = 0;
#include "addr.c"
#include "checksum.c"
#include "buf.c"
#include "intf.c"
#include "arp.c"
#include "eth.c"
#include "port.c"
#include "route.c"
#include "IPv4.c"
#include "IPv6.c"
#include "dns.c"
#include "dhcp.c"
#include "icmp.c"
#include "tcp.c"
#include "udp.c"
#include "loopback.c"
#include "ntp.c"
#include "intel.c"

// ------------------------------------------------------------------------------------------------
// Globals


// ------------------------------------------------------------------------------------------------
void NetInit()
{
    LoopbackInit();
    ArpInit();
    TcpInit();

    // Initialize interfaces
    NetIntf *intf;
    ListForEach(intf, g_netIntfList, link)
    {
		//printTextToWindow(4,mywin,"1111111111111111111111");
        // Check if interface needs IP address dynamically assigned
        if (!intf->ipAddr.u.bits)
        {
            DhcpDiscover(intf);
        }
    }
}

// ------------------------------------------------------------------------------------------------
void NetPoll()
{
    // Poll interfaces
    NetIntf *intf;
    ListForEach(intf, g_netIntfList, link)
    {
        intf->poll(intf);
    }

    TcpPoll();
}