// ------------------------------------------------------------------------------------------------
typedef struct UsbKbd
{
    UsbTransfer dataTransfer;
    u8 data[8];
    u8 lastData[8];
} UsbKbd;
#define CH_ESCAPE                       0x1B
#define KEY_A                           0x04
#define KEY_B                           0x05
#define KEY_C                           0x06
#define KEY_D                           0x07
#define KEY_E                           0x08
#define KEY_F                           0x09
#define KEY_G                           0x0a
#define KEY_H                           0x0b
#define KEY_I                           0x0c
#define KEY_J                           0x0d
#define KEY_K                           0x0e
#define KEY_L                           0x0f
#define KEY_M                           0x10
#define KEY_N                           0x11
#define KEY_O                           0x12
#define KEY_P                           0x13
#define KEY_Q                           0x14
#define KEY_R                           0x15
#define KEY_S                           0x16
#define KEY_T                           0x17
#define KEY_U                           0x18
#define KEY_V                           0x19
#define KEY_W                           0x1a
#define KEY_X                           0x1b
#define KEY_Y                           0x1c
#define KEY_Z                           0x1d
#define KEY_1                           0x1e
#define KEY_2                           0x1f
#define KEY_3                           0x20
#define KEY_4                           0x21
#define KEY_5                           0x22
#define KEY_6                           0x23
#define KEY_7                           0x24
#define KEY_8                           0x25
#define KEY_9                           0x26
#define KEY_0                           0x27
#define KEY_RETURN                      0x28
#define KEY_ESCAPE                      0x29
#define KEY_BACKSPACE                   0x2a
#define KEY_TAB                         0x2b
#define KEY_SPACE                       0x2c
#define KEY_MINUS                       0x2d
#define KEY_EQUALS                      0x2e
#define KEY_LBRACKET                    0x2f
#define KEY_RBRACKET                    0x30
#define KEY_BACKSLASH                   0x31
#define KEY_SEMICOLON                   0x33
#define KEY_APOSTROPHE                  0x34
#define KEY_GRAVE                       0x35
#define KEY_COMMA                       0x36
#define KEY_PERIOD                      0x37
#define KEY_SLASH                       0x38
#define KEY_CAPS_LOCK                   0x39
#define KEY_F1                          0x3a
#define KEY_F2                          0x3b
#define KEY_F3                          0x3c
#define KEY_F4                          0x3d
#define KEY_F5                          0x3e
#define KEY_F6                          0x3f
#define KEY_F7                          0x40
#define KEY_F8                          0x41
#define KEY_F9                          0x42
#define KEY_F10                         0x43
#define KEY_F11                         0x44
#define KEY_F12                         0x45
#define KEY_PRINT                       0x46
#define KEY_SCROLL_LOCK                 0x47
#define KEY_PAUSE                       0x48
#define KEY_INSERT                      0x49
#define KEY_HOME                        0x4a
#define KEY_PAGE_UP                     0x4b
#define KEY_DELETE                      0x4c
#define KEY_END                         0x4d
#define KEY_PAGE_DOWN                   0x4e
#define KEY_RIGHT                       0x4f
#define KEY_LEFT                        0x50
#define KEY_DOWN                        0x51
#define KEY_UP                          0x52
#define KEY_NUM_LOCK                    0x53
#define KEY_KP_DIV                      0x54
#define KEY_KP_MUL                      0x55
#define KEY_KP_SUB                      0x56
#define KEY_KP_ADD                      0x57
#define KEY_ENTER                       0x58
#define KEY_KP1                         0x59
#define KEY_KP2                         0x5a
#define KEY_KP3                         0x5b
#define KEY_KP4                         0x5c
#define KEY_KP5                         0x5d
#define KEY_KP6                         0x5e
#define KEY_KP7                         0x5f
#define KEY_KP8                         0x60
#define KEY_KP9                         0x61
#define KEY_KP0                         0x62
#define KEY_KP_DEC                      0x63

#define KEY_LCONTROL                    0x0100
#define KEY_LSHIFT                      0x0200
#define KEY_LALT                        0x0400
#define KEY_LWIN                        0x0800
#define KEY_RCONTROL                    0x1000
#define KEY_RSHIFT                      0x2000
#define KEY_RALT                        0x4000
#define KEY_RWIN                        0x8000
typedef struct Keymap
{
    u8 base[128];
    u8 shift[128];
    u8 numlock[128];
} Keymap;

const Keymap g_keymapUs101 =
{
	.base =
	{
		[KEY_1] = '1',
		[KEY_2] = '2',
		[KEY_3] = '3',
		[KEY_4] = '4',
		[KEY_5] = '5',
		[KEY_6] = '6',
		[KEY_7] = '7',
		[KEY_8] = '8',
		[KEY_9] = '9',
		[KEY_0] = '0',
		[KEY_MINUS] = '-',
		[KEY_EQUALS] = '=',
		[KEY_Q] = 'q',
		[KEY_W] = 'w',
		[KEY_E] = 'e',
		[KEY_R] = 'r',
		[KEY_T] = 't',
		[KEY_Y] = 'y',
		[KEY_U] = 'u',
		[KEY_I] = 'i',
		[KEY_O] = 'o',
		[KEY_P] = 'p',
		[KEY_LBRACKET] = '[',
		[KEY_RBRACKET] = ']',
		[KEY_A] = 'a',
		[KEY_S] = 's',
		[KEY_D] = 'd',
		[KEY_F] = 'f',
		[KEY_G] = 'g',
		[KEY_H] = 'h',
		[KEY_J] = 'j',
		[KEY_K] = 'k',
		[KEY_L] = 'l',
		[KEY_SEMICOLON] = ';',
		[KEY_APOSTROPHE] = '\'',
		[KEY_GRAVE] = '`',
		[KEY_BACKSLASH] = '\\',
		[KEY_Z] = 'z',
		[KEY_X] = 'x',
		[KEY_C] = 'c',
		[KEY_V] = 'v',
		[KEY_B] = 'b',
		[KEY_N] = 'n',
		[KEY_M] = 'm',
		[KEY_COMMA] = ',',
		[KEY_PERIOD] = '.',
		[KEY_SLASH] = '/',
		[KEY_KP_MUL] = '*',
		[KEY_SPACE] = ' ',
		[KEY_KP_SUB] = '-',
		[KEY_KP_ADD] = '+',
		[KEY_RETURN] = 10,
		[KEY_BACKSPACE] = 8,
		[0x2b] = 9,
		[0x29] = 27,
		[0x2c] = ' '
    },
    .shift =
    {
        [KEY_1] = '!',
        [KEY_2] = '@',
        [KEY_3] = '#',
        [KEY_4] = '$',
        [KEY_5] = '%',
        [KEY_6] = '^',
        [KEY_7] = '&',
        [KEY_8] = '*',
        [KEY_9] = '(',
        [KEY_0] = ')',
        [KEY_MINUS] = '_',
        [KEY_EQUALS] = '+',
        [KEY_Q] = 'Q',
        [KEY_W] = 'W',
        [KEY_E] = 'E',
        [KEY_R] = 'R',
        [KEY_T] = 'T',
        [KEY_Y] = 'Y',
        [KEY_U] = 'U',
        [KEY_I] = 'I',
        [KEY_O] = 'O',
        [KEY_P] = 'P',
        [KEY_LBRACKET] = '{',
        [KEY_RBRACKET] = '}',
        [KEY_A] = 'A',
        [KEY_S] = 'S',
        [KEY_D] = 'D',
        [KEY_F] = 'F',
        [KEY_G] = 'G',
        [KEY_H] = 'H',
        [KEY_J] = 'J',
        [KEY_K] = 'K',
        [KEY_L] = 'L',
        [KEY_SEMICOLON] = ':',
        [KEY_APOSTROPHE] = '"',
        [KEY_GRAVE] = '~',
        [KEY_BACKSLASH] = '|',
        [KEY_Z] = 'Z',
        [KEY_X] = 'X',
        [KEY_C] = 'C',
        [KEY_V] = 'V',
        [KEY_B] = 'B',
        [KEY_N] = 'N',
        [KEY_M] = 'M',
        [KEY_COMMA] = '<',
        [KEY_PERIOD] = '>',
        [KEY_SLASH] = '?',
        [KEY_KP_MUL] = '*',
        [KEY_SPACE] = ' ',
        [KEY_KP_SUB] = '-',
        [KEY_KP_ADD] = '+',
		[KEY_RETURN] = 10,
		[KEY_BACKSPACE] = 8,
		[0x2b] = 9,
		[0x29] = 27,
		[0x2c] = ' '
    },
    .numlock =
    {
        [KEY_KP0] = '0',
        [KEY_KP1] = '1',
        [KEY_KP2] = '2',
        [KEY_KP3] = '3',
        [KEY_KP4] = '4',
        [KEY_KP5] = '5',
        [KEY_KP6] = '6',
        [KEY_KP7] = '7',
        [KEY_KP8] = '8',
        [KEY_KP9] = '9',
    },
};
#define KBD_LSHIFT                      0x01
#define KBD_RSHIFT                      0x02
#define KBD_CAPS_LOCK                   0x04
#define KBD_NUM_LOCK                    0x08
static u8 s_flags;

// ------------------------------------------------------------------------------------------------
void InputOnKey(uint code, uint val)
{
    Keymap *keymap = &g_keymapUs101;

    if (val)
    {
        // key press
        //addKey(code);
		

        if (code == KEY_LSHIFT)
        {
            s_flags |= KBD_LSHIFT;
        }
        else if (code == KEY_RSHIFT)
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
                    ch = keymap->numlock[code];
                }

                if (!ch)
                {
                    if (s_flags & (KBD_LSHIFT | KBD_RSHIFT))
                    {
                        ch = keymap->shift[code];
                    }
                    else
                    {
                        ch = keymap->base[code];
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

        if (code == KEY_LSHIFT)
        {
            s_flags &= ~KBD_LSHIFT;
        }
        else if (code == KEY_RSHIFT)
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
            UsbKbdProcess(kbd);
        }

        t->complete = false;
        dev->hcIntr(dev, t);
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
		endp->toggle=0;
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