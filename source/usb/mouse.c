typedef struct UsbMouse
{
    UsbTransfer dataTransfer;
    u8 data[4];
} UsbMouse;

// ------------------------------------------------------------------------------------------------
static void UsbMouseProcess(UsbMouse *mouse)
{
        lastButtonState = buttons;
    u8 *data = mouse->data;
	buttons=data[0]&7;
	mouseX+=(i8)data[1];
	mouseY+=(i8)data[2];
	
	mouseHandler();

}

// ------------------------------------------------------------------------------------------------
static void UsbMousePoll(UsbDevice *dev)
{
    UsbMouse *mouse = dev->drv;
    UsbTransfer *t = &mouse->dataTransfer;

    if (t->complete)
    {
        if (t->success)
        {
            UsbMouseProcess(mouse);
        }

        t->complete = false;
        dev->hcIntr(dev, t);
    }
}

// ------------------------------------------------------------------------------------------------
void _UsbMouseInit(UsbDevice *dev)
{	//printTextToWindow(1, mywin, "Initializing Mouse\n");
    if (dev->intfDesc->intfClass == USB_CLASS_HID &&
        dev->intfDesc->intfSubClass == USB_SUBCLASS_BOOT &&
        dev->intfDesc->intfProtocol == USB_PROTOCOL_MOUSE)
    {
        printTextToWindow(2, mywin, "      Initializing Mouse\n");
		//return;
        UsbMouse *mouse = malloc(sizeof(UsbMouse));
		//return;
        dev->drv = mouse;
        dev->drvPoll = UsbMousePoll;
		UsbEndpoint * endp = malloc(sizeof(UsbEndpoint));
		endp->toggle=0;
		endp->desc = dev->intfDesc->endpoints;
        // Prepare transfer
        UsbTransfer *t = &mouse->dataTransfer;
        t->endp = endp;
        t->req = 0;
        t->data = mouse->data;
        t->len = 4;
        t->complete = false;
        t->success = false;

        dev->hcIntr(dev, t);
        return true;
    }

    return false;
}