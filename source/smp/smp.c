#pragma GCC push_options
#pragma GCC optimize ("O0")
// ------------------------------------------------------------------------------------------------
void smp_core(uint procId)
{
	//initCoProc();

	//for (;;);
	if (procId == 1)
	{
		WindowEvent we;
		//kprintf("%x!", &videoMemory);
		ushort uyt;
		//we.data = mmalloc(2);
		if (!(*((uchar*)0x3FF)))
			for (;;)
			{
				Window * currentActive = windows;

				while (currentActive)
				{
					if (currentActive->id == activeWindow)
						break;
					currentActive = currentActive->next;
				}
				unsigned short key = 0;
				while (key = getKey())
				{
					if (currentActive)
					{
						we.code = WINDOWS_KEY_DOWN;
						*((unsigned short*)we.data) = key;
						currentActive->handler(&we);
					}
				}

				//Wait(1);
			}
		CopyFromVMemory(width / 2, height / 2, 17, 17, under);
		int tttt = 0;
		//Bar(0,0,400,600,50);
		//for(;;);
		int bb = 1;
		//runProcess("OO.O");
		//runProcess("OO.O");	
		//runProcess("OO.O");	
		mywin->type = 1;
		char key = 0;
		mywin->x = 250;

		//for (;;);
		swapBuffer();//   for (;;);
		for (;;)
		{
			tttt++;
			//printTextToWindow(1, mywin, "!@#$%x&&&",&_UsbMouseInit);

			//NetPoll();
			unsigned int x = *sec100;
			unsigned short key = 0;
			Window * currentActive = windows;

			while (currentActive)
			{
				if (currentActive->id == activeWindow)
					break;
				currentActive = currentActive->next;
			}
			while (key = getKey())
			{
				if (currentActive)
				{
					we.code = WINDOWS_KEY_DOWN;
					*((unsigned short*)we.data) = key;
					currentActive->handler(&we);
				}
			}
			//draw3D(640, 680, tttt, mywin->video);
			drawed = 0;
			while (locked);
			drawed1 = 1;
			updateWindows();
			int a = mouseX, b = mouseY;
			lastX = a; lastY = b;
			CopyFromVMemory(a - 1, b - 1, 19, 19, under);
			CopyFromVMemory(a - 1, b - 1, 19, 19, under2);
			//OutTextXY(0, 680, mo, 0xFF0000, 0x2);
			CopyToVMemoryTransparentD(a, b, (unsigned short)16, (unsigned short)16, mouse_cur);
			swapBuffer();
			CopyToVMemoryD(a - 1, b - 1, 19, 19, under2);
			CopyFromVMemoryD(mouseX - 1, mouseY - 1, 19, 19, under);
			CopyToVMemoryTransparent(mouseX, mouseY, (unsigned short)16, (unsigned short)16, mouse_cur);
			drawed = 1;
			unsigned int o = *sec100;
			if (tttt % 10 == 0)
				bb = o - x;
			drawed1 = 0;
			//Wait(1);
		}
	}
	else
	{
		for (;;);
	}
}
#pragma GCC pop_options