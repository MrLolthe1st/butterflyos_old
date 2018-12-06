#define NET_BUF_SIZE        2048
#define NET_BUF_START       256     // Room for various protocol headers + header below

typedef struct NetBuf
{
    Link            link;
    u8             *start;          // offset to data start
    u8             *end;            // offset to data end exclusive
    uint            refCount;
    u32             seq;            // Data from TCP header used for out-of-order/retransmit
    u8              flags;          // Data from TCP header used for out-of-order/retransmit
} NetBuf;

// ------------------------------------------------------------------------------------------------
// Globals

extern int g_netBufAllocCount;

// ------------------------------------------------------------------------------------------------
// Functions

NetBuf *NetAllocBuf();
void NetReleaseBuf(NetBuf *buf);

// ------------------------------------------------------------------------------------------------
static Link s_netFreeBufs = { &s_netFreeBufs, &s_netFreeBufs };
int g_netBufAllocCount;

// ------------------------------------------------------------------------------------------------
NetBuf *NetAllocBuf()
{
    NetBuf *buf;

    if (ListIsEmpty(&s_netFreeBufs))
    {
        buf = (NetBuf*) VMAlloc(NET_BUF_SIZE);
    }
    else
    {
        buf = (NetBuf*)LinkData(s_netFreeBufs.next, NetBuf, link);
        LinkRemove(&buf->link);
    }

    buf->link.prev = 0;
    buf->link.next = 0;
    buf->start = (u8 *)buf + NET_BUF_START;
    buf->end = (u8 *)buf + NET_BUF_START;
    buf->refCount = 1;

    ++g_netBufAllocCount;
    return buf;
}

// ------------------------------------------------------------------------------------------------
void NetReleaseBuf(NetBuf *buf)
{
    if (!--buf->refCount)
    {
        --g_netBufAllocCount;

        LinkAfter(&s_netFreeBufs, &buf->link);
    }
}