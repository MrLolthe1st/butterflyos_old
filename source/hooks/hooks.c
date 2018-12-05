#define HOOK_KEY_DOWN				0x0001
#define HOOK_KEY_RELEASE			0x0002
#define HOOK_MOUSE_CLICK			0x0003
#define HOOK_MOUSE_SCROLL			0x0004
#define HOOK_MOUSE_MOVE				0x0005
#define HOOK_DEVICE_CONNECTION		0x0006
#define HOOK_DEVICE_DISCONNECT		0x0007
typedef struct {
	unsigned int code;
	void * data;
} HookEvent;
typedef struct _hook
{
	unsigned int type;
	void (*handler)(HookEvent * e);
	struct _hook * next;
	struct _hook * prev;
} Hook;
Hook * hookChain = 0;
//Installs an application-defined hook procedure into a hook chain. You would install a hook procedure to monitor the system for certain types of events. These events are associated either with a specific thread or with all threads in the same desktop as the calling thread.
Hook * SetHook(unsigned int hookType, void * handler)
{
	if (!hookChain)
	{
		//Hook chain isn't exists, just create a new one
		hookChain = (Hook *)malloc(sizeof(Hook));
		if (!hookChain)
			return 0;
		hookChain->next = 0;
		hookChain->prev = 0;
		hookChain->type = hookType;
		hookChain->handler = handler;
		return hookChain;
	}
	Hook * nhook = (Hook *) malloc(sizeof(Hook));
	if (!nhook)
		return 0;
	if (!hookChain->prev)
	{
		hookChain->next = nhook;
		hookChain->prev = nhook;
		nhook->next = hookChain;
		nhook->prev = hookChain;
	}
	else
	{
		nhook->next = hookChain;
		hookChain->prev->next = nhook;
	}
	nhook->type = hookType;
	nhook->handler = handler;
	return nhook;
}
//Removes a hook procedure installed in a hook chain by the SetHook function.
char UnhookHook(Hook * h)
{
	if (!h)
		return false;
	Hook * c = hookChain;
	while (c)
	{
		if (c == h)
		{
			c->prev->next = c->next;
			c->next->prev = c->prev;
			free(c);
			return true;
		}
		c = c->next;
	}
	return false;
}
//Sends event to all hooks from hook chain.
void hookEvent(unsigned int type, HookEvent * e)
{
	Hook * h = hookChain;
	while (h)
	{
		if (h->type == type)
			h->handler(e);
		h = h->next;
	}
}