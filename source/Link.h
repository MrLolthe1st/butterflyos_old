typedef unsigned int                 uintptr_t;
typedef unsigned int                 uintptr;
typedef unsigned char                uchar;
typedef unsigned short               ushort;
typedef unsigned long long           ulong;
typedef char                i8;
typedef unsigned char       u8;
typedef short               i16;
typedef unsigned short      u16;
typedef int                 i32;
typedef unsigned int        u32;
typedef long long           i64;
typedef unsigned long long  u64;

typedef float               f32;
typedef double              f64;
typedef unsigned int        uint;
unsigned int KERNBASE = 0;
#define KB 1024l
#define MB (1024l*1024)
#define GB (1024l*1024*1024)
//#define printTextToWindow(qq,bb,cc,...) kprintf(cc,__VA_ARGS__)
void nopee(uint a)
{

}
#define PitWait Wait
#define IoWrite32 outportd
#define IoWrite16 outportw
#define IoWrite8 outportb
#define IoRead8 inportb
#define IoRead16 inportw
#define IoRead32 inportd
#define PACKED __attribute__((__packed__))
#define typeof __typeof__

#define bool char
#define true 1
#define false 0

// ------------------------------------------------------------------------------------------------
typedef struct Link
{
	struct Link *prev;
	struct Link *next;
} Link;

// ------------------------------------------------------------------------------------------------
void LinkInit(Link *x)
{
	x->prev = x;
	x->next = x;
}

// ------------------------------------------------------------------------------------------------
void LinkAfter(Link *a, Link *x)
{
	Link *p = a;
	Link *n = a->next;
	n->prev = x;
	x->next = n;
	x->prev = p;
	p->next = x;
}

// ------------------------------------------------------------------------------------------------
void LinkBefore(Link *a, Link *x)
{
	Link *p = a->prev;
	Link *n = a;
	n->prev = x;
	x->next = n;
	x->prev = p;
	p->next = x;
}

// ------------------------------------------------------------------------------------------------
void LinkRemove(Link *x)
{
	Link *p = x->prev;
	Link *n = x->next;
	n->prev = p;
	p->next = n;
	x->next = 0;
	x->prev = 0;
}

// ------------------------------------------------------------------------------------------------
void LinkMoveAfter(Link *a, Link *x)
{
	Link *p = x->prev;
	Link *n = x->next;
	n->prev = p;
	p->next = n;

	p = a;
	n = a->next;
	n->prev = x;
	x->next = n;
	x->prev = p;
	p->next = x;
}

// ------------------------------------------------------------------------------------------------
void LinkMoveBefore(Link *a, Link *x)
{
	Link *p = x->prev;
	Link *n = x->next;
	n->prev = p;
	p->next = n;

	p = a->prev;
	n = a;
	n->prev = x;
	x->next = n;
	x->prev = p;
	p->next = x;
}

// ------------------------------------------------------------------------------------------------
bool ListIsEmpty(Link *x)
{
	return x->next == x;
}

// ------------------------------------------------------------------------------------------------
#define LinkData(link,T,m) \
    (T *)((char *)(link) - (unsigned int)(&(((T*)0)->m)))

// ------------------------------------------------------------------------------------------------
#define ListForEach(it, list, m) \
    for (it = LinkData((list).next, typeof(*it), m); \
        &it->m != &(list); \
        it = LinkData(it->m.next, typeof(*it), m))

// ------------------------------------------------------------------------------------------------
#define ListForEachSafe(it, n, list, m) \
    for (it = LinkData((list).next, typeof(*it), m), \
        n = LinkData(it->m.next, typeof(*it), m); \
        &it->m != &(list); \
        it = n, \
        n = LinkData(n->m.next, typeof(*it), m))
