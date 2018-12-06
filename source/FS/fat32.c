#pragma GCC push_options
#pragma GCC optimize ("Ofast")
char upcase(char s)
{

	if (s >= 'a'&&s <= 'z')
		return s + ('A' - 'a');
	else return s;
}
typedef  struct  __attribute__((packed)) _F32_e
{
	char name[8];
	char ext[3];
	unsigned char attributes;
	unsigned char firstDelChar;
	unsigned char firstDelChar2;
	u16 createdTime;
	u16 createdDate;
	u16 lastAccessDate;
	u16 clusterHi;
	u16 lastModifiedTime;
	u16 lastModifiedDate;
	u16 clusterLo;
	uint size;
} F32E;
typedef  struct __attribute__((packed)) _fil
{
	uint startCluster;
	uint nool;
	uint nool1;
	uint size;
} FileInfoF32;
char F32OkName(char q)
{
	if ((q >= 'A'&&q <= 'Z') ||
		(q >= 'a'&&q <= 'z') ||
		(q >= 128 && q <= 228) ||
		(q >= 230 && q <= 255) ||
		(q == '!' || q == '#' || q == '$' || q == '%' || q == '\'' || q == '(' || q == ')' || q == '-' || q == '@' || q == '^' || q == '_' || q == '`' || q == '{' || q == '}' || q == '~'))
		return 1;
	return 0;
}
typedef  struct  __attribute__((packed)) dentr_y
{
	char name[255];
	uint modified;
	uint size;
	uchar attrs;
	struct dentr_y * next;
} direntry;
direntry * FAT32GetDir(uint diskId, char * fileName)
{
	char bootSect[512];
	ReadFromDisk(0, 1, &bootSect, diskId);
	char sectorsPerCluster = bootSect[0x0D];
	u16 reserved = *((u16*)&bootSect[0xE]);
	char FATTableCount = bootSect[0x10];
	uint RootEntry = *((uint*)&bootSect[0x2C]);
	uint SectorsPerFat = *((uint*)&bootSect[0x24]);
	uint FatStart = SectorsPerFat * FATTableCount + reserved;
	char FATTablePart[512];
	uint lastCluster = RootEntry, currentCluster = RootEntry;
	ReadFromDisk(reserved, 1, &FATTablePart, diskId);
	char * cluster = (char*)malloc(512 * sectorsPerCluster);
	char found = 0, lastDir = 1;
	char * curChar = fileName;
	//kprintf("%s\n", fileName);
	while (*curChar) {
		if ((*curChar) == '\\')
		{
			lastDir = 0;
			break;
		};
		++curChar;
	}
	F32E * lastcluster = (F32E*)malloc(512 * sectorsPerCluster);
	direntry * res = 0;
	uint size = 0;
	char longFileName[256];

	while (!found)
	{
		ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);
		F32E * e = (F32E*)cluster;
		ReadFromDisk(FatStart + (lastCluster - 2) * sectorsPerCluster, sectorsPerCluster, lastcluster, diskId);

		uint uu = 0;
		uint locF = 0; int i;

		for (i = 0; i < 16 * sectorsPerCluster; i++)
		{
			if ((!((e[i].name[0] == 0xE5))) && (!(e[i].attributes == 0xF)))
				if (F32OkName(e[i].name[0])) {
					locF = 1;
					if (((i > 0) && (e[i - 1].attributes == 0xF))
						|| (lastcluster[16 * sectorsPerCluster - 1].attributes == 0xF))
					{
						uint len = 0, reread = 0;
						uint j = i - 1;
						if (j == -1) {
							memcpy(cluster, (unsigned char*)lastcluster, 512 * sectorsPerCluster);
							j = 16 * sectorsPerCluster - 1;
							reread = 1;
						}
						memset(&longFileName, 0, 256);
						while (1) {
							for (int k = 0; k < 5; k++)
								longFileName[len++] = cluster[j * 0x20 + 1 + 2 * k];
							for (int k = 0; k < 6; k++)
								longFileName[len++] = cluster[j * 0x20 + 0xe + 2 * k];
							for (int k = 0; k < 2; k++)
								longFileName[len++] = cluster[j * 0x20 + 0x1c + 2 * k];
							if ((e[j].name[0] & (1 << 6)))
								break;
							j--;
							if (j == -1) {
								memcpy(cluster, (unsigned char*)lastcluster, 512 * sectorsPerCluster);
								j = 16 * sectorsPerCluster - 1;
								reread = 1;
							}
						}

						for (int k = 0; k < 256; k++)
							if (longFileName[k] == 0xFF)
								longFileName[k] = 0;

						if (reread)
							ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);
					}
					else
					{
						if (e[i].attributes & 0x10)
						{
							int j = 0, len = 0;
							memset(&longFileName, 0, 256);

							while ((!(e[i].name[j] == 0x20)) && (j < 8))
							{
								longFileName[len++] = e[i].name[j];
								j++;
							}

						}
						else {
							int j = 0, len = 0;
							memset(&longFileName, 0, 256);

							while ((!(e[i].name[j] == 0x20)) && (j < 8))
							{
								longFileName[len++] = e[i].name[j];
								j++;
							}

							j = 0;
							if (!(e[i].ext[j] == ' '))
								longFileName[len++] = '.';
							while (!(e[i].ext[j] == ' '))
							{
								longFileName[len++] = e[i].ext[j];
								j++;
								if (j == 3)break;
							}


						}
					}
					//File/Folder name parsed.
					if (lastDir) {
						direntry * o = (direntry*)malloc(sizeof(direntry));
						o->next = res;
						char * z = (char*)&longFileName;
						uint oo = 0;
						while (*z)
						{
							o->name[oo] = *z;
							oo++;
							++z;
						}
						o->size = e[i].size;
						o->attrs = e[i].attributes;
						o->modified = (e[i].lastModifiedTime << 16) + e[i].lastModifiedDate;
						res = o;
					}
					else
					{
						int j = 0;
						curChar = fileName;

						while (*curChar != '\\')
						{
							if (upcase(*curChar) != upcase(longFileName[j]))
							{
								locF = 0;
								break;
							}
							++curChar;
							j++;
						}
						if (locF)
							if (longFileName[j] != 0)
								locF = 0;
						if (locF) {
							uu = 1;
							fileName = (char*)((uint)curChar + 1);
							locF = 0;
							lastCluster = currentCluster;
							currentCluster = (e[i].clusterHi << 16) + (e[i].clusterLo);
							break;
						}
					}
				}
		}
		curChar = fileName;
		lastDir = 1;
		////kprintf("%x->", currentCluster);
		if (!uu)
			currentCluster = f32drives[diskId].FATTable[currentCluster];

		while (*curChar) {
			if ((*curChar) == '\\')
			{
				lastDir = 0;
				break;
			};
			++curChar;
		}
		if (currentCluster == 0xFFFFFFF)
			break;
		//	Wait(10000);
	}
	free(cluster);
	free(lastcluster);

	return res;
}
FileInfoF32 * FAT32Seek(uint diskId, char * fileName)
{
	char bootSect[512];
	ReadFromDisk(0, 1, &bootSect, diskId);
	char sectorsPerCluster = bootSect[0x0D];
	u16 reserved = *((u16*)&bootSect[0xE]);
	char FATTableCount = bootSect[0x10];
	uint RootEntry = *((uint*)&bootSect[0x2C]);
	uint SectorsPerFat = *((uint*)&bootSect[0x24]);
	uint FatStart = SectorsPerFat * FATTableCount + reserved;
	uint lastCluster = RootEntry, currentCluster = RootEntry;
	//printMem(&bootSect, 16);
	////kprintf("%x",reserved);
	char * cluster = (char*)malloc(512 * sectorsPerCluster);
	char found = 0, lastDir = 1;
	char * curChar = fileName;
	while (*curChar) {
		if ((*curChar) == '\\')
		{
			lastDir = 0;
			break;
		};
		++curChar;
	}
	F32E * lastcluster = (F32E*)malloc(512 * sectorsPerCluster);
	uint size = 0;

	while (!found)
	{
		ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);
		F32E * e = (F32E*)cluster;
		char longFileName[256];
		ReadFromDisk(FatStart + (lastCluster - 2) * sectorsPerCluster, sectorsPerCluster, lastcluster, diskId);

		uint uu = 0;
		uint locF = 0; int i;

		for (i = 0; i < 16 * sectorsPerCluster; i++)
		{
			if ((!((e[i].name[0] == 0xE5))) && (!(e[i].attributes == 0xF)))
				if (F32OkName(e[i].name[0])) {
					locF = 1;
					if (((i > 0) && (e[i - 1].attributes == 0xF))
						|| (lastcluster[16 * sectorsPerCluster - 1].attributes == 0xF))
					{
						uint len = 0, reread = 0;
						uint j = i - 1;
						if (j == -1) {
							memcpy(cluster, (unsigned char*)lastcluster, 512 * sectorsPerCluster);
							j = 16 * sectorsPerCluster - 1;
							reread = 1;
						}
						memset(&longFileName, 0, 256);
						while (1) {
							for (int k = 0; k < 5; k++)
								longFileName[len++] = cluster[j * 0x20 + 1 + 2 * k];
							for (int k = 0; k < 6; k++)
								longFileName[len++] = cluster[j * 0x20 + 0xe + 2 * k];
							for (int k = 0; k < 2; k++)
								longFileName[len++] = cluster[j * 0x20 + 0x1c + 2 * k];
							if ((e[j].name[0] & (1 << 6)))
								break;
							j--;
							if (j == -1) {
								memcpy(cluster, (unsigned char*)lastcluster, 512 * sectorsPerCluster);
								j = 16 * sectorsPerCluster - 1;
								reread = 1;
							}
						}

						for (int k = 0; k < 256; k++)
							if (longFileName[k] == 0xFF)
								longFileName[k] = 0;

						if (reread)
							ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);
					}
					else
					{
						if (e[i].attributes & 0x10)
						{
							int j = 0, len = 0;
							memset(&longFileName, 0, 256);

							while ((!(e[i].name[j] == 0x20)) && (j < 8))
							{
								longFileName[len++] = e[i].name[j];
								j++;
							}

						}
						else {
							int j = 0, len = 0;
							memset(&longFileName, 0, 256);

							while ((!(e[i].name[j] == 0x20)) && (j < 8))
							{
								longFileName[len++] = e[i].name[j];
								j++;
							}

							j = 0;
							if (!(e[i].ext[j] == ' '))
								longFileName[len++] = '.';
							while (!(e[i].ext[j] == ' ') && j < 3)
							{
								longFileName[len++] = e[i].ext[j];
								j++;
								if (j == 3)break;
							}


						}
					}
					//kprintf("%s\n", &longFileName);
					//File/Folder name parsed.
					if ((!(e[i].attributes & 0x10)) && lastDir) {
						int j = 0;
						curChar = fileName;

						while (*curChar)
						{
							if (upcase(*curChar) != upcase(longFileName[j]))
							{
								locF = 0;
								break;
							}
							++curChar;
							j++;
						}

						if (locF)
							if (longFileName[j] != 0)
								locF = 0;
						if (locF)
							break;
					}
					else
					{
						int j = 0;
						curChar = fileName;

						while (*curChar != '\\')
						{
							if (upcase(*curChar) != upcase(longFileName[j]))
							{
								locF = 0;
								break;
							}
							++curChar;
							j++;
						}
						if (locF)
							if (longFileName[j] != 0)
								locF = 0;
						if (locF) {
							uu = 1;
							fileName = (char*)((uint)curChar + 1);
							locF = 0;
							lastCluster = currentCluster;
							currentCluster = (e[i].clusterHi << 16) + (e[i].clusterLo);
							break;
						}
					}
				}
		}
		curChar = fileName;
		lastDir = 1;
		//kprintf("->%x", currentCluster);
		//
		if (locF) {
			lastCluster = currentCluster;

			currentCluster = (e[i].clusterHi << 16) + (e[i].clusterLo);
			size = e[i].size;
			found = i + 1;
			break;
		}
		else if (!uu)
			currentCluster = f32drives[diskId].FATTable[currentCluster % 128];

		while (*curChar) {
			if ((*curChar) == '\\')
			{
				lastDir = 0;
				break;
			};
			++curChar;
		}
		if (currentCluster == 0xFFFFFFF)
			break;
		//Wait(1);
	}
	//kprintf("\n");
	if (!found)
	{
		free(cluster);
		free(lastcluster);
		return 0;
	}
	found--;
	FileInfoF32 * q = (FileInfoF32*)malloc(sizeof(FileInfoF32));
	q->startCluster = currentCluster;
	q->size = size;
	q->nool = lastCluster;
	q->nool1 = found;
	free(cluster);
	free(lastcluster);
	return q;
}


void * FAT32ReadFileB(uint diskId, uint clu, uint st, uint cnt, void* buf)
{
	char bootSect[512];
	ReadFromDisk(0, 1, &bootSect, diskId);
	char sectorsPerCluster = bootSect[0x0D];
	u16 reserved = *((u16*)&bootSect[0xE]);
	char FATTableCount = bootSect[0x10];
	uint RootEntry = *((uint*)&bootSect[0x2C]);
	uint SectorsPerFat = *((uint*)&bootSect[0x24]);
	uint FatStart = SectorsPerFat * FATTableCount + reserved;
	uint lastCluster = RootEntry, currentCluster = RootEntry;
	char * cluster = malloc(512 * sectorsPerCluster);
	char found = 0, lastDir = 1;
	uint ofs = 0;
	currentCluster = clu;
	lastCluster = currentCluster;
	void * bufStart = buf;
	while (currentCluster != 0xFFFFFFF && currentCluster != 0)
	{

		if ((ofs + 1) * 512 * sectorsPerCluster > st && ofs * 512 * sectorsPerCluster <= st)
		{
			ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);
			//Cluster Cluster+1
			//.|..|.  .........
			//.^ start here(1)
			//....^ end here(4)
			uint countR = min((ofs + 1)*sectorsPerCluster * 512, st + cnt) - st;
			memcpy(buf, (unsigned char*)&cluster[st - ofs * 512 * sectorsPerCluster], countR);
			buf += countR;
		}
		else
			if (ofs * 512 * sectorsPerCluster > st + cnt - 1)
				break;
			else if ((ofs + 1) * 512 * sectorsPerCluster > st)
			{
				ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);
				uint countR = min((ofs + 1)*sectorsPerCluster * 512, st + cnt) - st - ((uint)buf - (uint)bufStart);
				memcpy((unsigned char*)buf, (unsigned char*)cluster, countR);
				buf += countR;
			}

		lastCluster = currentCluster;
		currentCluster = f32drives[diskId].FATTable[currentCluster];
		ofs++;
	}
	free(cluster);

}

void * FAT32ReadFile(uint diskId, char * fileName)
{
	char bootSect[512];
	ReadFromDisk(0, 1, &bootSect, diskId);
	char sectorsPerCluster = bootSect[0x0D];
	u16 reserved = *((u16*)&bootSect[0xE]);
	char FATTableCount = bootSect[0x10];
	uint RootEntry = *((uint*)&bootSect[0x2C]);
	uint SectorsPerFat = *((uint*)&bootSect[0x24]);
	uint FatStart = SectorsPerFat * FATTableCount + reserved;
	char FATTablePart[512];
	uint lastCluster = RootEntry, currentCluster = RootEntry;
	ReadFromDisk(reserved, 1, &FATTablePart, diskId);
	char * cluster = (char*)malloc(512 * sectorsPerCluster);
	char found = 0, lastDir = 1;
	char * curChar = fileName;
	while (*curChar) {
		if ((*curChar) == '\\')
		{
			lastDir = 0;
			break;
		};
		++curChar;
	}
	F32E * lastcluster = (F32E*)malloc(512 * sectorsPerCluster);
	uint size = 0;
	while (!found)
	{
		if ((lastCluster >> 7) != (currentCluster >> 7))
			ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
		ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);
		F32E * e = (F32E*)cluster;
		char longFileName[256];
		ReadFromDisk(FatStart + (lastCluster - 2) * sectorsPerCluster, sectorsPerCluster, lastcluster, diskId);

		uint uu = 0;
		uint locF = 0; int i;
		for (i = 0; i < 16 * sectorsPerCluster; i++)
		{
			if ((!((e[i].name[0] == 0xE5))) && (!(e[i].attributes == 0xF)))
				if (F32OkName(e[i].name[0])) {
					locF = 1;
					if (((i > 0) && (e[i - 1].attributes == 0xF))
						|| (lastcluster[16 * sectorsPerCluster - 1].attributes == 0xF))
					{
						uint len = 0, reread = 0;
						uint j = i - 1;
						if (j == -1) {
							memcpy(cluster, (unsigned char*)lastcluster, 512 * sectorsPerCluster);
							j = 16 * sectorsPerCluster - 1;
							reread = 1;
						}
						memset(&longFileName, 0, 256);
						while (1) {
							for (int k = 0; k < 5; k++)
								longFileName[len++] = cluster[j * 0x20 + 1 + 2 * k];
							for (int k = 0; k < 6; k++)
								longFileName[len++] = cluster[j * 0x20 + 0xe + 2 * k];
							for (int k = 0; k < 2; k++)
								longFileName[len++] = cluster[j * 0x20 + 0x1c + 2 * k];
							if ((e[j].name[0] & (1 << 6)))
								break;
							j--;
							if (j == -1) {
								memcpy(cluster, (unsigned char*)lastcluster, 512 * sectorsPerCluster);
								j = 16 * sectorsPerCluster - 1;
								reread = 1;
							}
						}

						for (int k = 0; k < 256; k++)
							if (longFileName[k] == 0xFF)
								longFileName[k] = 0;
						////kprintf("%s", &longFileName);
						if (reread)
							ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);
					}
					else
					{
						if (e[i].attributes & 0x10)
						{
							int j = 0, len = 0;
							memset(&longFileName, 0, 256);

							while ((!(e[i].name[j] == 0x20)) && (j < 8))
							{
								longFileName[len++] = e[i].name[j];
								j++;
							}

						}
						else {
							int j = 0, len = 0;
							memset(&longFileName, 0, 256);

							while ((!(e[i].name[j] == 0x20)) && (j < 8))
							{
								longFileName[len++] = e[i].name[j];
								j++;
							}

							j = 0;
							if (!(e[i].ext[j] == ' '))
								longFileName[len++] = '.';
							while (!(e[i].ext[j] == ' ') && j < 3)
							{
								longFileName[len++] = e[i].ext[j];
								j++;
								if (j == 3)break;
							}



						}
					}
					//File/Folder name parsed.

					if ((!(e[i].attributes & 0x10)) && lastDir) {
						int j = 0;
						curChar = fileName;

						while (*curChar)
						{
							if (upcase(*curChar) != upcase(longFileName[j]))
							{
								locF = 0;
								break;
							}
							++curChar;
							j++;
						}
						if (locF)
							if (longFileName[j] != 0)
								locF = 0;
						if (locF)
							break;
					}
					else
					{
						int j = 0;
						curChar = fileName;

						while (*curChar != '\\')
						{
							if (upcase(*curChar) != upcase(longFileName[j]))
							{
								locF = 0;
								break;
							}
							++curChar;
							j++;
						}
						if (locF)
							if (longFileName[j] != 0)
								locF = 0;
						if (locF) {
							uu = 1;
							fileName = (char*)((uint)curChar + 1);
							locF = 0;
							lastCluster = currentCluster;
							currentCluster = (e[i].clusterHi << 16) + (e[i].clusterLo);
							break;
						}
					}
				}
		}
		curChar = fileName;
		lastDir = 1;
		while (*curChar) {
			if ((*curChar) == '\\')
			{
				lastDir = 0;
				break;
			};
			++curChar;
		}
		if (locF) {
			lastCluster = currentCluster;
			currentCluster = (e[i].clusterHi << 16) + (e[i].clusterLo);
			size = e[i].size;
			found = 1;
			break;
		}
		else if (!uu)
			currentCluster = ((uint*)&FATTablePart)[currentCluster % 128];

		if (currentCluster == 0xFFFFFFF)
			break;
	}
	if (!found)
	{
		free(cluster);
		free(lastcluster);
		return 0;
	}
	void * file = (void*)malloc(size);
	uint ofs = 0;
	while (currentCluster != 0xFFFFFFF)
	{
		if ((lastCluster >> 7) != (currentCluster >> 7))
			ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
		ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, (void*)((uint)file + sectorsPerCluster * 512 * ofs), diskId);
		lastCluster = currentCluster;
		currentCluster = ((uint*)&FATTablePart)[currentCluster % 128];
		ofs++;
	}
	printMem(file, 40);
	free(cluster);
	free(lastcluster);
	return file;
}
uint findFreeFATEntry(uint diskId, uint reserved)
{
	for (int i = 0; i < 0xFFFFFF; i++)
	{
		if (f32drives[diskId].FATTable[i] == 0)
		{
			f32drives[diskId].FATTable[i] = 0xFFFFFFF;
			return i;
		}
	}
}
int FAT32Append(uint diskId, uint startingCluster, uint clustIndex, void* buf, uint cnt)
{
	char bootSect[512];
	ReadFromDisk(0, 1, &bootSect, diskId);
	char sectorsPerCluster = bootSect[0x0D];
	u16 reserved = *((u16*)&bootSect[0xE]);
	char FATTableCount = bootSect[0x10];
	uint RootEntry = *((uint*)&bootSect[0x2C]);
	uint SectorsPerFat = *((uint*)&bootSect[0x24]);
	uint FatStart = SectorsPerFat * FATTableCount + reserved;
	char FATTablePart[512];
	uint lastCluster = RootEntry, currentCluster = RootEntry;
	ReadFromDisk(reserved, 1, &FATTablePart, diskId);
	char * cluster = (char*)malloc(512 * sectorsPerCluster);
	char found = 0, lastDir = 1;
	uint ofs = 0;
	lastCluster = 0;
	void * qf = buf;
	ReadFromDisk(FatStart + startingCluster - 2, sectorsPerCluster, cluster, diskId);
	F32E * entrs = (F32E*)cluster;
	currentCluster = entrs[clustIndex].clusterLo + (entrs[clustIndex].clusterHi << 16); uint sz = entrs[clustIndex].size;
	if (currentCluster == 0)
	{
		uint nw = findFreeFATEntry(diskId, reserved);
		entrs[clustIndex].clusterLo = nw & 0xFFFF;
		entrs[clustIndex].clusterHi = (nw >> 16) & 0xffff;
		currentCluster = nw;
		ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
		((uint*)(&FATTablePart))[currentCluster % 128] = 0xFFFFFFF;
		WriteToDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
		lastCluster = currentCluster;
		printTextToWindow(6, mywin, "zzz%xzzz", currentCluster);
	}

	entrs[clustIndex].size += cnt;

	WriteToDisk(FatStart + startingCluster - 2, sectorsPerCluster, cluster, diskId);
	//Size changed, find last entry of file
	if (currentCluster != 0 && (lastCluster >> 7) != (currentCluster >> 7)) {
		ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
		lastCluster = currentCluster;
	}

	while (currentCluster != 0xFFFFFFF && currentCluster != 0)
	{
		if ((lastCluster >> 7) != (currentCluster >> 7))
			ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
		lastCluster = currentCluster;
		currentCluster = ((uint*)(&FATTablePart))[currentCluster % 128];
		//Wait(100);
	}
	//kprintf("appending...\n");
	uint curOffs = (sz) % (512 * sectorsPerCluster);
	ReadFromDisk(FatStart + lastCluster - 2, sectorsPerCluster, cluster, diskId);
	currentCluster = lastCluster;
	for (int i = 0; i < cnt; i++)
	{
		if (curOffs == 0 && sz > 0)
		{
			uint nw = findFreeFATEntry(diskId, reserved);
			WriteToDisk(FatStart + currentCluster - 2, sectorsPerCluster, cluster, diskId);

			memset(cluster, 0, 512 * sectorsPerCluster);
			f32drives[diskId].FATTable[currentCluster] = nw;
			((uint*)(&FATTablePart))[currentCluster % 128] = (uint)nw;
			if ((nw >> 7) != (currentCluster >> 7))
				WriteToDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
			currentCluster = nw;
			if ((lastCluster >> 7) != (currentCluster >> 7))
				ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
			((uint*)(&FATTablePart))[currentCluster % 128] = 0xfffffff;
			if ((lastCluster >> 7) != (currentCluster >> 7))
				WriteToDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
			lastCluster = currentCluster;
		}
		cluster[curOffs] = ((uchar*)buf)[i];
		curOffs = (curOffs + 1) % (512 * sectorsPerCluster);
		if (!curOffs)
			sz = 1;
	}
	WriteToDisk(FatStart + currentCluster - 2, sectorsPerCluster, cluster, diskId);
	((uint*)(&FATTablePart))[currentCluster % 128] = 0xfFFFFFF;
	WriteToDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
	free(cluster);
	return 0;
}
/*
*/
int  FAT32ClearChain(uint diskId, uint startingCluster, uint clustIndex)
{
	printTextToWindow(2, mywin, "Clearing file chain...\n");
	char bootSect[512];
	ReadFromDisk(0, 1, &bootSect, diskId);
	char sectorsPerCluster = bootSect[0x0D];
	u16 reserved = *((u16*)&bootSect[0xE]);
	char FATTableCount = bootSect[0x10];
	uint RootEntry = *((uint*)&bootSect[0x2C]);
	uint SectorsPerFat = *((uint*)&bootSect[0x24]);
	uint FatStart = SectorsPerFat * FATTableCount + reserved;
	//char FATTablePart[512];
	uint lastCluster = RootEntry, currentCluster = RootEntry;
	//	ReadFromDisk(reserved, 1, &FATTablePart, diskId);
	char * cluster = (char*)malloc(512 * sectorsPerCluster);
	char found = 0, lastDir = 1;
	uint ofs = 0;
	lastCluster = 0;
	ReadFromDisk(FatStart + startingCluster - 2, sectorsPerCluster, cluster, diskId);
	F32E * entrs = (F32E*) cluster;
	currentCluster = entrs[clustIndex].clusterLo + (entrs[clustIndex].clusterHi << 16); uint sz = entrs[clustIndex].size;
	printTextToWindow(2, mywin, "Starting cluster %x\n", currentCluster);
	//kprintf("Starting at: %x\n", currentCluster);
	entrs[clustIndex].clusterLo = 0;
	entrs[clustIndex].clusterHi = 0;

	entrs[clustIndex].size = 0;

	WriteToDisk(FatStart + startingCluster - 2, sectorsPerCluster, cluster, diskId);
	//Size changed, find last entry of file
//	ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
	uint fst = 1;
	lastCluster = currentCluster;
	printTextToWindow(2, mywin, "%x", currentCluster);
	while (currentCluster != 0xFFFFFFF && currentCluster != 0)
	{
		//	if ((lastCluster >> 7) != (currentCluster >> 7))
		//		ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
		lastCluster = currentCluster;
		currentCluster = f32drives[diskId].FATTable[currentCluster];
		f32drives[diskId].FATTable[lastCluster] = 0;
		if ((lastCluster >> 7) != (currentCluster >> 7))
			WriteToDisk(reserved + (lastCluster >> 7), 1, (void*)((uint)f32drives[diskId].FATTable + (lastCluster >> 7) * 128), diskId);
		fst = 0;
		printTextToWindow(2, mywin, "->%x", currentCluster);
	}
	printTextToWindow(2, mywin, "\n");
	WriteToDisk(reserved + (lastCluster >> 7), 1, (void*)((uint)f32drives[diskId].FATTable + (lastCluster >> 7) * 128), diskId);
}



void  FAT32CreateFile(uint diskId, char * fileName)
{
	char bootSect[512];
	ReadFromDisk(0, 1, &bootSect, diskId);
	char sectorsPerCluster = bootSect[0x0D];
	u16 reserved = *((u16*)&bootSect[0xE]);
	char FATTableCount = bootSect[0x10];
	uint RootEntry = *((uint*)&bootSect[0x2C]);
	uint SectorsPerFat = *((uint*)&bootSect[0x24]);
	uint FatStart = SectorsPerFat * FATTableCount + reserved;
	//char FATTablePart[512];
	uint lastCluster = RootEntry, currentCluster = RootEntry;
	//ReadFromDisk(reserved, 1, &FATTablePart, diskId);
	char * cluster = (char*)malloc(512 * sectorsPerCluster);
	char found = 0, lastDir = 1;
	char * curChar = fileName;
	while (*curChar) {
		if ((*curChar) == '\\')
		{
			lastDir = 0;
			break;
		};
		++curChar;
	}
	F32E * lastcluster = (F32E*)malloc(512 * sectorsPerCluster);
	uint size = 0;
	while (!found)
	{
		ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);
		F32E * e = (F32E*)cluster;
		char longFileName[256];
		ReadFromDisk(FatStart + (lastCluster - 2) * sectorsPerCluster, sectorsPerCluster, lastcluster, diskId);

		uint uu = 0;
		uint locF = 0; int i;
		for (i = 0; i < 16 * sectorsPerCluster; i++)
		{
			if ((!((e[i].name[0] == 0xE5))) && (!(e[i].attributes == 0xF)))
				if (F32OkName(e[i].name[0])) {
					locF = 1;
					if (((i > 0) && (e[i - 1].attributes == 0xF))
						|| (lastcluster[16 * sectorsPerCluster - 1].attributes == 0xF))
					{
						uint len = 0, reread = 0;
						uint j = i - 1;
						if (j == -1) {
							memcpy(cluster, (unsigned char*)lastcluster, 512 * sectorsPerCluster);
							j = 16 * sectorsPerCluster - 1;
							reread = 1;
						}
						memset(&longFileName, 0, 256);
						while (1) {
							for (int k = 0; k < 5; k++)
								longFileName[len++] = cluster[j * 0x20 + 1 + 2 * k];
							for (int k = 0; k < 6; k++)
								longFileName[len++] = cluster[j * 0x20 + 0xe + 2 * k];
							for (int k = 0; k < 2; k++)
								longFileName[len++] = cluster[j * 0x20 + 0x1c + 2 * k];
							if ((e[j].name[0] & (1 << 6)))
								break;
							j--;
							if (j == -1) {
								memcpy(cluster, (unsigned char*)lastcluster, 512 * sectorsPerCluster);
								j = 16 * sectorsPerCluster - 1;
								reread = 1;
							}
						}

						for (int k = 0; k < 256; k++)
							if (longFileName[k] == 0xFF)
								longFileName[k] = 0;
						////kprintf("%s", &longFileName);
						if (reread)
							ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);
					}
					else
					{
						if (e[i].attributes & 0x10)
						{
							int j = 0, len = 0;
							memset(&longFileName, 0, 256);

							while ((!(e[i].name[j] == 0x20)) && (j < 8))
							{
								longFileName[len++] = e[i].name[j];
								j++;
							}

						}
						else {
							int j = 0, len = 0;
							memset(&longFileName, 0, 256);

							while ((!(e[i].name[j] == 0x20)) && (j < 8))
							{
								longFileName[len++] = e[i].name[j];
								j++;
							}

							j = 0;
							if (!(e[i].ext[j] == ' '))
								longFileName[len++] = '.';
							while (!(e[i].ext[j] == ' ') && j < 3)
							{
								longFileName[len++] = e[i].ext[j];
								j++; if (j == 3)break;
							}


						}
					}
					//File/Folder name parsed.

					if ((!(e[i].attributes & 0x10)) && lastDir) {

					}
					else
					{
						int j = 0;
						curChar = fileName;

						while (*curChar != '\\')
						{
							if (upcase(*curChar) != upcase(longFileName[j]))
							{
								locF = 0;
								break;
							}
							++curChar;
							j++;
						}
						if (locF)
							if (longFileName[j] != 0)
								locF = 0;
						if (locF) {
							uu = 1;
							fileName = (char*)((uint)curChar + 1);
							locF = 0;
							lastCluster = currentCluster;
							currentCluster = (e[i].clusterHi << 16) + (e[i].clusterLo);
							break;
						}
					}
				}
		}
		curChar = fileName;
		lastDir = 1;
		while (*curChar) {
			if ((*curChar) == '\\')
			{
				lastDir = 0;
				break;
			};
			++curChar;
		}
		lastCluster = currentCluster;
		currentCluster = f32drives[diskId].FATTable[currentCluster];
		if (lastDir)
			break;
		if (currentCluster == 0xFFFFFFF)
			break;
	}
	currentCluster = lastCluster;
	ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, (void*)cluster, diskId);

	F32E * e = (F32E*)cluster;
	uint ffound = 0;
	uint avaliable = 0;
	while (currentCluster != 0xFFFFFFF && !avaliable) {
		ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, (void*)cluster, diskId);
		for (int i = 0; i < 16 * sectorsPerCluster; i++) {
			if (e[i].name[0] == 0) {
				avaliable = i + 1;
				break;
			}
		}
		if (!avaliable)
		{
			lastCluster = currentCluster;
			currentCluster = f32drives[diskId].FATTable[currentCluster];
		}
	}
	if (!avaliable)
	{
		uint nw = findFreeFATEntry(diskId, reserved);
		f32drives[diskId].FATTable[lastCluster] = nw;
		WriteToDisk((long long)reserved + (lastCluster >> 7), 1, (void*)((uint)f32drives[diskId].FATTable + (lastCluster / 128) * 128), diskId);
		currentCluster = nw;
		memset(cluster, 0, 512 * sectorsPerCluster);
		avaliable = 1;
		f32drives[diskId].FATTable[currentCluster] = 0xFFFFFFF;
		WriteToDisk((long long)reserved + (currentCluster >> 7), 1, (void*)((uint)f32drives[diskId].FATTable + (currentCluster / 128) * 128), diskId);
	}
	//printTextToWindow(6,mywin,"Cluster: %x\n", currentCluster);
	avaliable--;
	uint t = avaliable;
	e[t].size = 0;
	uint zz = 0;
	e[t].clusterHi = zz << 16;
	e[t].clusterLo = zz & 0xFFFF;
	e[t].lastModifiedTime = ((((*sec100) / ticksPerSecond) % 60) / 2) + (((((*sec100) / ticksPerSecond) / 60) % 60) << 5) + ((((((*sec100) / ticksPerSecond) / 60) / 60) % 24) << 11);
	e[t].lastModifiedDate = 26 + (9 << 5) + (38 << 9);
	e[t].attributes = 0;


	uint cdot = 0;
	for (int i = 0; i < 8; i++)
	{
		if (cdot == 0)
			e[t].name[i] = fileName[i];
		else
			e[t].name[i] = ' ';
		if (cdot == 0 && (fileName[i + 1] == '.' || fileName[i + 1] == 0))
			cdot = i;
	}
	cdot += 2;
	/////kprintf("%s %x\n", fileName, cdot);
	for (int i = 0; i < 3; i++)
	{
		if (fileName[cdot + i] != 0)
			e[t].ext[i] = fileName[cdot + i];
		else
		{
			while (i < 3)
			{
				e[t].ext[i] = ' ';
				i++;
			}
		}
	}

	/////kprintf("%s %x\n", fileName, cdot);

	WriteToDisk((long long)FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);


	//f32drives[diskId].FATTable[zz] = 0xFFFFFFF;
	free(cluster);
	free(lastcluster);
}
void  FAT32CreateDirectory(uint diskId, char * fileName)
{
	char bootSect[512];
	ReadFromDisk(0, 1, &bootSect, diskId);
	char sectorsPerCluster = bootSect[0x0D];
	u16 reserved = *((u16*)&bootSect[0xE]);
	char FATTableCount = bootSect[0x10];
	uint RootEntry = *((uint*)&bootSect[0x2C]);
	uint SectorsPerFat = *((uint*)&bootSect[0x24]);
	uint FatStart = SectorsPerFat * FATTableCount + reserved;
	//char FATTablePart[512];
	uint lastCluster = RootEntry, currentCluster = RootEntry;
	//ReadFromDisk(reserved, 1, &FATTablePart, diskId);
	char * cluster = (char*)malloc(512 * sectorsPerCluster);
	char found = 0, lastDir = 1;
	char * curChar = fileName;
	while (*curChar) {
		if ((*curChar) == '\\')
		{
			lastDir = 0;
			break;
		};
		++curChar;
	}
	F32E * lastcluster = (F32E*)malloc(512 * sectorsPerCluster);
	uint size = 0;
	while (!found)
	{
		ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, (void*)cluster, diskId);
		F32E * e = (F32E*)cluster;
		char longFileName[256];
		ReadFromDisk(FatStart + (lastCluster - 2) * sectorsPerCluster, sectorsPerCluster, (void*)lastcluster, diskId);

		uint uu = 0;
		uint locF = 0; int i;
		for (i = 0; i < 16 * sectorsPerCluster; i++)
		{
			if ((!((e[i].name[0] == 0xE5))) && (!(e[i].attributes == 0xF)))
				if (F32OkName(e[i].name[0])) {
					locF = 1;
					if (((i > 0) && (e[i - 1].attributes == 0xF))
						|| (lastcluster[16 * sectorsPerCluster - 1].attributes == 0xF))
					{
						uint len = 0, reread = 0;
						uint j = i - 1;
						if (j == -1) {
							memcpy(cluster, (unsigned char*)lastcluster, 512 * sectorsPerCluster);
							j = 16 * sectorsPerCluster - 1;
							reread = 1;
						}
						memset(&longFileName, 0, 256);
						while (1) {
							for (int k = 0; k < 5; k++)
								longFileName[len++] = cluster[j * 0x20 + 1 + 2 * k];
							for (int k = 0; k < 6; k++)
								longFileName[len++] = cluster[j * 0x20 + 0xe + 2 * k];
							for (int k = 0; k < 2; k++)
								longFileName[len++] = cluster[j * 0x20 + 0x1c + 2 * k];
							if ((e[j].name[0] & (1 << 6)))
								break;
							j--;
							if (j == -1) {
								memcpy(cluster, (unsigned char*)lastcluster, 512 * sectorsPerCluster);
								j = 16 * sectorsPerCluster - 1;
								reread = 1;
							}
						}

						for (int k = 0; k < 256; k++)
							if (longFileName[k] == 0xFF)
								longFileName[k] = 0;
						////kprintf("%s", &longFileName);
						if (reread)
							ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);
					}
					else
					{
						if (e[i].attributes & 0x10)
						{
							int j = 0, len = 0;
							memset(&longFileName, 0, 256);

							while ((!(e[i].name[j] == 0x20)) && (j < 8))
							{
								longFileName[len++] = e[i].name[j];
								j++;
							}

						}
						else {
							int j = 0, len = 0;
							memset(&longFileName, 0, 256);

							while ((!(e[i].name[j] == 0x20)) && (j < 8))
							{
								longFileName[len++] = e[i].name[j];
								j++;
							}

							j = 0;
							if (!(e[i].ext[j] == ' '))
								longFileName[len++] = '.';
							while (!(e[i].ext[j] == ' ') && j < 3)
							{
								longFileName[len++] = e[i].ext[j];
								j++; if (j == 3)break;
							}


						}
					}
					//File/Folder name parsed.

					if ((!(e[i].attributes & 0x10)) && lastDir) {

					}
					else
					{
						int j = 0;
						curChar = fileName;

						while (*curChar != '\\')
						{
							if (upcase(*curChar) != upcase(longFileName[j]))
							{
								locF = 0;
								break;
							}
							++curChar;
							j++;
						}
						if (locF)
							if (longFileName[j] != 0)
								locF = 0;
						if (locF) {
							uu = 1;
							fileName = (char*)((uint)curChar + 1);
							locF = 0;
							lastCluster = currentCluster;
							currentCluster = (e[i].clusterHi << 16) + (e[i].clusterLo);
							break;
						}
					}
				}
		}
		curChar = fileName;
		lastDir = 1;
		while (*curChar) {
			if ((*curChar) == '\\')
			{
				lastDir = 0;
				break;
			};
			++curChar;
		}
		lastCluster = currentCluster;
		currentCluster = f32drives[diskId].FATTable[currentCluster];
		if (lastDir)
			break;
		if (currentCluster == 0xFFFFFFF)
			break;
	}
	currentCluster = lastCluster;
	ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);

	F32E * e = (F32E*)cluster;
	uint ffound = 0;
	uint avaliable = 0;
	while (currentCluster != 0xFFFFFFF && !avaliable) {
		ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);
		for (int i = 0; i < 16 * sectorsPerCluster; i++) {
			if (e[i].name[0] == 0) {
				avaliable = i + 1;
				break;
			}
		}
		if (!avaliable)
		{
			lastCluster = currentCluster;
			currentCluster = f32drives[diskId].FATTable[currentCluster];
		}
	}
	if (!avaliable)
	{
		uint nw = findFreeFATEntry(diskId, reserved);
		f32drives[diskId].FATTable[lastCluster] = nw;
		WriteToDisk((long long)reserved + (lastCluster >> 7), 1, (void*)((uint)f32drives[diskId].FATTable + (lastCluster / 128) * 128), diskId);
		currentCluster = nw;
		memset(cluster, 0, 512 * sectorsPerCluster);
		avaliable = 1;
		f32drives[diskId].FATTable[currentCluster] = 0xFFFFFFF;
		WriteToDisk((long long)reserved + (currentCluster >> 7), 1, (void*)((uint)f32drives[diskId].FATTable + (currentCluster / 128) * 128), diskId);
	}
	//printTextToWindow(6, mywin, "Cluster: %x\n", currentCluster);
	avaliable--;
	uint t = avaliable;
	e[t].size = 0;
	uint zz = findFreeFATEntry(diskId, reserved);
	e[t].clusterHi = zz << 16;
	e[t].clusterLo = zz & 0xFFFF;
	e[t].lastModifiedTime = ((((*sec100) / ticksPerSecond) % 60) / 2) + (((((*sec100) / ticksPerSecond) / 60) % 60) << 5) + ((((((*sec100) / ticksPerSecond) / 60) / 60) % 24) << 11);
	e[t].lastModifiedDate = 26 + (9 << 5) + (38 << 9);
	e[t].attributes = 0x10;
	uint cdot = 0;
	for (int i = 0; i < 8; i++)
	{
		if (cdot == 0)
			e[t].name[i] = fileName[i];
		else
			e[t].name[i] = ' ';
		if (cdot == 0 && (fileName[i + 1] == '.' || fileName[i + 1] == 0))
			cdot = i;
	}
	cdot += 2;
	e[t].ext[0] = ' ';
	e[t].ext[1] = ' ';
	e[t].ext[2] = ' ';
	WriteToDisk((long long)FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);
	f32drives[diskId].FATTable[zz] = 0xFFFFFFF;
	WriteToDisk((long long)reserved + (zz >> 7), 1, (void*)((uint)f32drives[diskId].FATTable + (zz / 128) * 128), diskId);
	memset(cluster, 0, 512 * sectorsPerCluster);
	WriteToDisk((long long)FatStart + (zz - 2) * sectorsPerCluster, sectorsPerCluster, (void*)cluster, diskId);
	free(cluster);
	free(lastcluster);
}
#pragma GCC pop_options