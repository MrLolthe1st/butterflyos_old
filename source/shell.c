char * about_msg = "Butterfly OS version 0.0.1 alpha\nCommands:\ncd - change directory\nmem - memory information\ndir - files/directories in current directory\nhelp - this text\nmd - creates directory\nreader - simple text viewer\n";
char * cmd_help = "help";
char * cmd_dir = "dir";
char * cmd_cd = "cd";
char * cmd_mem = "mem";
char * cmd_md = "md";
char * cmd_reader = "reader";
char cprintFname(char * name) {
	char pc = 0;
	if (name[0] < 10 || name[0] == 0xff) return 1;
	if (name[8] < 10 || name[8] == 0xff) return 1;
	for (int i = 0; i < 8; i++) {
		if (name[i] == 0) pc = 1;
		if (name[i] != ' '&&name[i] != 0) pc = 2;
		// if (name[i] != 0 && pc == 1) return 1;
		if (name[i] == ' '&&pc == 0) return 1;
	}

	return 0;
}

char printFname(char * name) {
	char pc = 0;
	if (name[0] < 10 || name[0] == 0xff) return 1;
	if (name[8] < 10 || name[8] == 0xff) return 1;
	for (int i = 0; i < 8; i++) {
		if (name[i] == 0) pc = 1;
		if (name[i] != ' '&&name[i] != 0) pc = 2;
		if (name[i] != 0 && pc == 1) return 1;
		if (name[i] == ' '&&pc == 0) return 1;
	}
	pc = 0;
	for (int i = 0; i < 8; i++) {
		if (name[i] == ' ')
			break;
		pc++;
		printChar(name[i]);
	}
	if (name[8] != ' ') {
		printChar('.');
		pc++;
	}
	for (int i = 0; i < 3; i++) {
		if (name[8 + i] == ' ')
			break;
		printChar(name[8 + i]);
		pc++;
	}
	for (int i = pc; i < 12; i++)
		printChar(' ');
	return 0;
}

void exec_cmd(char * cmd, char * cur_dir) {
	if (pos(cmd, cmd_help) == 0) {
		printString(about_msg);
	}
	else if (pos(cmd, cmd_md) == 0) {
		int j = 0;
		for (j = 2; j < 4096; j++) {
			if (cmd[j] == 0 || j > 511 || cmd[j] == '.' || cmd[j] == '\\' || cmd[j] == '/') {
				kprintf("Invalid syntax!\nSyntax: md <DIR_NAME_WITHOUT_SPACES_AND_DOTS>\nDirectory/Filename must excludes: \\,/,],[ characters!\n");
				return;
			}
			if (cmd[j] != ' ' && cmd[j] != 9) {
				break;
			}
		}

		for (int i = j; i < 512; i++)
			cmd[i] = upCase(cmd[i]);
		if (cmd[j] == '/') FAT32MkDir(0, "", cmd + j);
		else
			FAT32MkDir(0, cur_dir, cmd + j);
	}
	else if (pos(cmd, cmd_dir) == 0) {
		dirEntry * e = FAT32Dir(0, cur_dir);
		printString("Content of ");
		printString(cur_dir);
		printString(":\n");
		int x = 0, y = 0;
		//for(int i=0;i<
		//if (e -> entries[0].name[0] == 0) goto noo;
		printChar(201);
		for (int i = 1; i < 79; i++) {
			if (i % 40 == 15)
				printChar(209);
			else
				if (i % 40 == 22)
					printChar(209);
				else
					if (i == 40)
						printChar(203);
					else
						printChar(205);
		}
		printChar(187);
		//printChar(186);

		int uuq = 79;
		int oop = 0;
		do {
			oop = 0;
			for (int i = 0; i < 16; i++) {
				if (e->entries[i].name[0] != 0 && e->entries[i].name[0] != 0xE5) {
					if (cprintFname(e->entries[i].name) == 0) {
						if (oop % 2 == 0)
							printChar(186);
						printChar(32);
					} //kprintf("0x%x",e -> entries[i].name);
					if (printFname(e->entries[i].name) == 0) {
						printChar(' ');
						printChar(179);
						if (e->entries[i].attributes & 0x10) {
							printString(" DIR  ");
							y++;
						}
						else {
							printString(" FILE ");
							x++;
						}
						printChar(179);
						printChar(' ');
						printInt((e->entries[i].lastEditedDate) & 0b11111, 2);
						printChar('.');
						printInt((e->entries[i].lastEditedDate >> 5) & 0xf, 2);
						printChar('.');
						printInt(1980 + (e->entries[i].lastEditedDate >> 9), 2);
						printChar(' ');
						printInt((e->entries[i].lastEditedTime >> 11), 2);
						printChar(':');
						printInt((e->entries[i].lastEditedTime >> 5) & 0b111111, 2);
						if (oop % 2 == 1) {
							printString(" ");
							printChar(186);
						}
						else {
							printString("  ");
							printChar(186);
						}
						//	x++;
					}
					oop++;
				}
			}
			if ((cursor % 160)) {
				for (int i = 41; i < 79; i++) {
					if (i % 40 == 15)
						printChar(179);
					else
						if (i % 40 == 22)
							printChar(179);
						else
							printChar(' ');
				}
				printChar(186);

				//uuq=40;
			}
			dirEntry * x = e;
			e = e->next;
			free(x);
		} while (e != 0);
		printChar(200);
		for (int i = 1; i < uuq; i++) {
			if (i % 40 == 15)
				printChar(207);
			else
				if (i % 40 == 22)
					printChar(207);
				else
					if (i == 40)
						printChar(202);
					else
						printChar(205);
		}
		printChar(188);
		if (uuq != 79) printString("\n");
	noo:;
		if (y > 1 || y == 0)
			kprintf("Total: %d file(s) and %d directories.\n", x, y);
		else
			kprintf("Total: %d file(s) and %d directory.\n", x, y);

	}
	else if (pos(cmd, cmd_reader) == 0) {
		int j = 0;//reader
		for (j = 6; j < 4096; j++) {
			if (cmd[j] == 0 || j > 511) {
				kprintf("Invalid syntax!\nSyntax: reader path\nExample: reader FILE.TXT\n");
				return;
			}
			if (cmd[j] != ' ' && cmd[j] != 9) {
				break;
			}
		}
		for (int i = j; i < 512; i++)
			cmd[i] = upCase(cmd[i]);
		void * q = malloc(512);
		memcpy(cur_dir, q, 512);
		if (cmd[j] != '/') {
			strcat((cmd + j), q);

		}
		else {
			memcpy(cmd + j, q, 512);
		}
		unsigned int fsize = FAT32ReadFileSizeATA(0, q);
		void *f = FAT32ReadFileATA(0, q);
		if (f == 0)
		{
			kprintf("File %s not found!\n", q);
		}
		else
		{
			setCursor(0);
			clearScreen();
			GotoXY(0, 0);
			printString("BFReader: ");
			printString(cmd + j);
			GotoXY(0, 24);
			printString("Press enter to return, 'q' for last page, 'e' for next page");
			unsigned int p = 0, lp = 0;
			unsigned int pp[256];
			GotoXY(0, 1); char aaf = attr;
			attr = 0x0F;
			pp[0] = 0;
			for (int i = 0; i < 2000; i++) {
				if (i + pp[p] >= fsize) {
					p++;
					pp[p] = pp[p - 1] + i;
					break;
				}
				if ((*((unsigned char *)f + pp[0] + i) == 10 && * ((unsigned char *)f + pp[0] + 1 + i) == 13) || (*((unsigned char *)f + pp[0] + i) == 13 && * ((unsigned char *)f + pp[0] + 1 + i) == 10)) {
					i++;
					printChar(10);
				}
				else if (*((unsigned char *)f + pp[0] + i) == 10 || *((unsigned char *)f + pp[0] + i) == 13) {
					printChar(10);
				}
				else {
					printChar(*((unsigned char *)f + pp[0] + i));
				}
				//printHex(cursor,2);
				if (cursor - 160 >= 23 * 160) {
					if ((*((unsigned char *)f + pp[p] + i) == 10 && * ((unsigned char *)f + pp[p] - 1 + i) == 13) || (*((unsigned char *)f + pp[p] + i) == 13 && * ((unsigned char *)f + pp[p] - 1 + i) == 10))
						i++;
					p++;
					pp[p] = pp[p - 1] + i;
					break;
				}
			}
			char key = 0;
			while (key != 0x0A) {
				key = 0;
				while (key == 0) key = getKey();
				if (key == 'e') {
					if (pp[p] >= fsize) continue;
					GotoXY(0, 1);
					for (int i = 0; i < 23 * 80; i++)
						printChar(' ');
					GotoXY(0, 1);

					for (int i = 0; i < 2000; i++) {
						if (i + pp[p] >= fsize) {
							p++;
							pp[p] = pp[p - 1] + i;
							break;
						}
						if ((*((unsigned char *)f + pp[p] + i) == 10 && * ((unsigned char *)f + pp[p] + 1 + i) == 13) || (*((unsigned char *)f + pp[p] + i) == 13 && * ((unsigned char *)f + pp[p] + 1 + i) == 10)) {
							i++;
							printChar(10);
						}
						else if (*((unsigned char *)f + pp[p] + i) == 10 || *((unsigned char *)f + pp[p] + i) == 13) {
							printChar(10);
						}
						else {
							printChar(*((unsigned char *)f + pp[p] + i));
						}
						//printHex(cursor,2);
						if (cursor - 160 >= 23 * 160) {
							if ((*((unsigned char *)f + pp[p] + i) == 10 && * ((unsigned char *)f + pp[p] - 1 + i) == 13) || (*((unsigned char *)f + pp[p] + i) == 13 && * ((unsigned char *)f + pp[p] - 1 + i) == 10))
								i++;
							p++;
							pp[p] = pp[p - 1] + i;
							break;
						}
					}
				}
				else if (key == 'q') {
					if (p < 1) continue;
					GotoXY(0, 1);
					for (int i = 0; i < 23 * 80; i++)
						printChar(' ');
					GotoXY(0, 1);
					p -= 2;
					for (int i = 0; i < 2000; i++) {
						if (i + pp[p] >= fsize) {
							p++;
							pp[p] = pp[p - 1] + i;
							break;
						}
						if ((*((unsigned char *)f + pp[p] + i) == 10 && * ((unsigned char *)f + pp[p] + 1 + i) == 13) || (*((unsigned char *)f + pp[p] + i) == 13 && * ((unsigned char *)f + pp[p] + 1 + i) == 10)) {
							i++;
							printChar(10);
						}
						else if (*((unsigned char *)f + pp[p] + i) == 10 || *((unsigned char *)f + pp[p] + i) == 13) {
							printChar(10);
						}
						else {
							printChar(*((unsigned char *)f + pp[p] + i));
						}
						//printHex(cursor,2);
						if (cursor - 160 >= 23 * 160) {
							if ((*((unsigned char *)f + pp[p] + i) == 10 && * ((unsigned char *)f + pp[p] - 1 + i) == 13) || (*((unsigned char *)f + pp[p] + i) == 13 && * ((unsigned char *)f + pp[p] - 1 + i) == 10))
								i++;
							p++;
							pp[p] = pp[p - 1] + i;
							break;
						}
					}

				}
				//printChar('q');

			}
			attr = aaf;
			clearScreen();
			GotoXY(0, 0);
			free(f);
			//printString("\n");
		} free(q);

	}
	else if (pos(cmd, cmd_cd) == 0) {
		int j = 0;
		for (j = 2; j < 4096; j++) {
			if (cmd[j] == 0 || j > 511) {
				kprintf("Invalid syntax!\nSyntax: cd path\nExample: cd .. - up one directory\ncd MUSIC/ABBA - enter in <curr. dir>/MUSIC/ABBA\n");
				return;
			}
			if (cmd[j] != ' ' && cmd[j] != 9) {
				break;
			}
		}
		for (int i = j; i < 512; i++)
			cmd[i] = upCase(cmd[i]);
		if (cmd[j] == '.') {
			int x = llastIndexOf(cur_dir, "/");
			if (x < 0) {
				printString("Root entry!\n");
				return;
			}
			cur_dir[x + 1] = 0;
		}
		else {
			void * q = malloc(512);
			memcpy(cur_dir, q, 512);
			strcat((cmd + j), cur_dir);
			if (cur_dir[strlen(cur_dir) - 1] != '/')
				strcat("/", cur_dir);
			dirEntry * e = FAT32Dir(0, cur_dir);
			if (e->f == 0) {
				printString("Directory not exists!\n");
				memcpy(q, cur_dir, 512);
			}
			do {
				unsigned int xx = e->next;
				free(e);
				e = xx;
			} while (e != 0);
			free(q);
		}
	}
	else if (pos(cmd, cmd_mem) == 0) {
		mm_print_out();
	}
	else {
		printString("Command not found!\n");
	}
}