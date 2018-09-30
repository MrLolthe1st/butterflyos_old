#pragma GCC optimize ("O0")
typedef __attribute__((packed)) struct _F32_e
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
typedef __attribute__((packed)) struct _fil
{
	uint startCluster;
	uint nool;
	uint nool1;
	uint size;
} FileInfoF32;
char F32OkName(char q)
{
	if ((q >= 'A'&&q <= 'Z') ||
		(q >= 128 && q <= 228) ||
		(q >= 230 && q <= 255) ||
		(q == '!' || q == '#' || q == '$' || q == '%' || q == '\'' || q == '(' || q == ')' || q == '-' || q == '@' || q == '^' || q == '_' || q == '`' || q == '{' || q == '}' || q == '~'))
		return 1;
	return 0;
}
typedef struct dentr_y
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
	kprintf("&");

	ReadFromDisk(0, 1, &bootSect, diskId);
	kprintf("!");
	char sectorsPerCluster = bootSect[0x0D];
	u16 reserved = *((u16*)&bootSect[0xE]);
	char FATTableCount = bootSect[0x10];
	uint RootEntry = *((uint*)&bootSect[0x2C]);
	uint SectorsPerFat = *((uint*)&bootSect[0x24]);
	uint FatStart = SectorsPerFat * FATTableCount + reserved;
	char * FATTablePart = malloc(512);
	uint lastCluster = RootEntry, currentCluster = RootEntry;
	ReadFromDisk(reserved, 1, FATTablePart, diskId);
	char * cluster = malloc(512 * sectorsPerCluster);
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
	F32E * lastcluster = malloc(512 * sectorsPerCluster);
	direntry * res = 0;
	uint size = 0;
	kprintf("FAT start: %x, Reserved %d\n", FatStart, reserved);
	ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);
	while (!found)
	{
		if ((lastCluster >> 7) != (currentCluster >> 7))
			ReadFromDisk(reserved + (currentCluster >> 7), 1, FATTablePart, diskId);
		memcpy(cluster, lastcluster, 512 * sectorsPerCluster);
		if ((lastCluster) != (currentCluster))
			ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);
		F32E * e = cluster;
		char longFileName[256];

		kprintf("Trying cluster %x\n", currentCluster);
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
							memcpy(lastcluster, cluster, 512 * sectorsPerCluster);
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
							if (j == -1 && reread)
								break;
							if (j == -1) {
								memcpy(lastcluster, cluster, 512 * sectorsPerCluster);
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
							}


						}
					}
					//File/Folder name parsed.
					kprintf("%s\n", &longFileName);
					if (lastDir) {
						direntry * o = malloc(sizeof(direntry));
						o->next = res;
						char * z = &longFileName;
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
							if (*curChar != longFileName[j])
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
							fileName = (uint)curChar + 1;
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
		kprintf("%x->", currentCluster);
		if (!uu)
			currentCluster = ((uint*)FATTablePart)[currentCluster % 128];
		kprintf("%x\n", currentCluster);
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
		Wait(10000);
	}
	free(cluster);
	free(FATTablePart);
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
	char FATTablePart[512];
	uint lastCluster = RootEntry, currentCluster = RootEntry;
	ReadFromDisk(reserved, 1, &FATTablePart, diskId);
	char * cluster = malloc(512 * sectorsPerCluster);
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
	F32E * lastcluster = malloc(512 * sectorsPerCluster);
	uint size = 0;

	while (!found)
	{
		if ((lastCluster >> 7) != (currentCluster >> 7))
			ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
		ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);
		F32E * e = cluster;
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
							memcpy(lastcluster, cluster, 512 * sectorsPerCluster);
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
								memcpy(lastcluster, cluster, 512 * sectorsPerCluster);
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
							}


						}
					}
					//File/Folder name parsed.
					if ((!(e[i].attributes & 0x10)) && lastDir) {
						int j = 0;
						curChar = fileName;

						while (*curChar)
						{
							if (*curChar != longFileName[j])
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
							if (*curChar != longFileName[j])
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
							fileName = (uint)curChar + 1;
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
		//
		if (locF) {
			lastCluster = currentCluster;

			currentCluster = (e[i].clusterHi << 16) + (e[i].clusterLo);
			size = e[i].size;
			found = i + 1;
			break;
		}
		else if (!uu)
			currentCluster = ((uint*)&FATTablePart)[currentCluster % 128];

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
	if (!found)
	{
		free(cluster);
		return 0;
	}
	found--;
	FileInfoF32 * q = malloc(sizeof(FileInfoF32));
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
	char FATTablePart[512];
	uint lastCluster = RootEntry, currentCluster = RootEntry;
	ReadFromDisk(reserved, 1, &FATTablePart, diskId);
	char * cluster = malloc(512 * sectorsPerCluster);
	char found = 0, lastDir = 1;
	uint ofs = 0;
	currentCluster = clu;
	lastCluster = currentCluster;
	void * qf = buf;
	ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
	while (currentCluster != 0xFFFFFFF)
	{
		if ((lastCluster >> 7) != (currentCluster >> 7))
			ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);

		if ((ofs + 1) * 512 * sectorsPerCluster > st && ofs * 512 * sectorsPerCluster <= st)
		{
			ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);
			//Cluster Cluster+1
			//.|..|.  .........
			//.^ start here(1)
			//....^ end here(4)
			uint countR = min((ofs + 1)*sectorsPerCluster * 512, st + cnt) - st;
			memcpy(&cluster[st - ofs * 512 * sectorsPerCluster], buf, countR);
			buf += countR;
		}
		else
			if (ofs * 512 * sectorsPerCluster > st + cnt - 1)
				break;
			else if ((ofs + 1) * 512 * sectorsPerCluster > st)
			{
				ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);
				uint countR = min((ofs + 1)*sectorsPerCluster * 512, st + cnt) - st - ((uint)buf - (uint)qf);
				memcpy(cluster, buf, countR);
				buf += countR;
			}

		lastCluster = currentCluster;
		currentCluster = ((uint*)&FATTablePart)[currentCluster % 128];
		ofs++;
	}
	free(cluster);
	free(lastCluster);

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
	char * cluster = malloc(512 * sectorsPerCluster);
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
	F32E * lastcluster = malloc(512 * sectorsPerCluster);
	uint size = 0;
	while (!found)
	{
		if ((lastCluster >> 7) != (currentCluster >> 7))
			ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
		ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);
		F32E * e = cluster;
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
							memcpy(lastcluster, cluster, 512 * sectorsPerCluster);
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
								memcpy(lastcluster, cluster, 512 * sectorsPerCluster);
								j = 16 * sectorsPerCluster - 1;
								reread = 1;
							}
						}

						for (int k = 0; k < 256; k++)
							if (longFileName[k] == 0xFF)
								longFileName[k] = 0;
						//kprintf("%s", &longFileName);
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
							}


						}
					}
					//File/Folder name parsed.

					if ((!(e[i].attributes & 0x10)) && lastDir) {
						int j = 0;
						curChar = fileName;

						while (*curChar)
						{
							if (*curChar != longFileName[j])
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
							if (*curChar != longFileName[j])
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
							fileName = (uint)curChar + 1;
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
		free(lastCluster);
		return 0;
	}
	void * file = malloc(size);
	uint ofs = 0;
	while (currentCluster != 0xFFFFFFF)
	{
		if ((lastCluster >> 7) != (currentCluster >> 7))
			ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
		ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, (uint)file + sectorsPerCluster * 512 * ofs, diskId);
		lastCluster = currentCluster;
		currentCluster = ((uint*)&FATTablePart)[currentCluster % 128];
		ofs++;
	}
	printMem(file, 40);
	free(cluster);
	free(lastCluster);
	return file;
}
uint findFreeFATEntry(uint diskId, uint reserved)
{
	uint currentCluster = 4;
	uchar found = 0;
	uint FATTablePart[128]; uint z = 4 * 128;
	while (!found) {
		ReadFromDisk(reserved + (currentCluster), 1, &FATTablePart, diskId);
		for (int i = 0; i < 128; i++)
			if (FATTablePart[i] == 0)
				return i + z;
		currentCluster++;
		z += 128;
	}
}
void * FAT32Append(uint diskId, uint startingCluster, uint clustIndex, void* buf, uint cnt)
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
	char * cluster = malloc(512 * sectorsPerCluster);
	char found = 0, lastDir = 1;
	uint ofs = 0;
	lastCluster = 0;
	void * qf = buf;
	ReadFromDisk(FatStart + startingCluster - 2, sectorsPerCluster, cluster, diskId);
	F32E * entrs = cluster;
	currentCluster = entrs[clustIndex].clusterLo + (entrs[clustIndex].clusterHi << 16); uint sz = entrs[clustIndex].size;
	if (currentCluster == 0)
	{
		uint nw = findFreeFATEntry(diskId, reserved);
		entrs[clustIndex].clusterLo = nw & 0xFFFF;
		entrs[clustIndex].clusterHi = (nw >> 16) & 0xffff;
		currentCluster = nw;
		ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
		((uint*)(&FATTablePart))[lastCluster % 128] = 0xFFFFFFF;
		WriteToDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);

	}

	entrs[clustIndex].size += cnt;

	WriteToDisk(FatStart + startingCluster - 2, sectorsPerCluster, cluster, diskId);
	//Size changed, find last entry of file
	if (currentCluster != 0)
		ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);

	while (currentCluster != 0xFFFFFFF && currentCluster != 0)
	{
		if ((lastCluster >> 7) != (currentCluster >> 7))
			ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
		lastCluster = currentCluster;
		currentCluster = ((uint*)(&FATTablePart))[currentCluster % 128];
	}
	uint curOffs = sz % (512 * sectorsPerCluster);
	ReadFromDisk(FatStart + lastCluster - 2, sectorsPerCluster, cluster, diskId);
	currentCluster = lastCluster;
	for (int i = 0; i < cnt; i++)
	{
		if ((lastCluster >> 7) != (currentCluster >> 7))
			ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);

		if (!curOffs)
		{
			uint nw = findFreeFATEntry(diskId, reserved);
			((uint*)(&FATTablePart))[currentCluster % 128] = nw;
			WriteToDisk(FatStart + currentCluster - 2, sectorsPerCluster, cluster, diskId);
			memset(cluster, 0, 512 * sectorsPerCluster);
			((uint*)(&FATTablePart))[currentCluster % 128] = nw;
			WriteToDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);

			lastCluster = currentCluster;
			currentCluster = nw;

		}
		cluster[curOffs] = ((uchar*)buf)[i];
		curOffs = (curOffs + 1) % (512 * sectorsPerCluster);
	}
	WriteToDisk(FatStart + currentCluster - 2, sectorsPerCluster, cluster, diskId);
	((uint*)(&FATTablePart))[currentCluster % 128] = 0xfFFFFFF;
	WriteToDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);

}
void * FAT32ClearChain(uint diskId, uint startingCluster, uint clustIndex)
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
	char * cluster = malloc(512 * sectorsPerCluster);
	char found = 0, lastDir = 1;
	uint ofs = 0;
	lastCluster = 0;
	ReadFromDisk(FatStart + startingCluster - 2, sectorsPerCluster, cluster, diskId);
	F32E * entrs = cluster;
	currentCluster = entrs[clustIndex].clusterLo + (entrs[clustIndex].clusterHi << 16); uint sz = entrs[clustIndex].size;
	entrs[clustIndex].clusterLo = 0;
	entrs[clustIndex].clusterHi = 0;

	entrs[clustIndex].size = 0;

	WriteToDisk(FatStart + startingCluster - 2, sectorsPerCluster, cluster, diskId);
	//Size changed, find last entry of file
	ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
	uint fst = 1;

	while (currentCluster != 0xFFFFFFF)
	{
		if ((lastCluster >> 7) != (currentCluster >> 7))
			ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
		lastCluster = currentCluster;
		currentCluster = ((uint*)(&FATTablePart))[currentCluster % 128];
		((uint*)(&FATTablePart))[lastCluster % 128] = 0;
		WriteToDisk(reserved + (lastCluster >> 7), 1, &FATTablePart, diskId);
		fst = 0;
	}
	kprintf("z");
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
	char FATTablePart[512];
	uint lastCluster = RootEntry, currentCluster = RootEntry;
	ReadFromDisk(reserved, 1, &FATTablePart, diskId);
	char * cluster = malloc(512 * sectorsPerCluster);
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
	F32E * lastcluster = malloc(512 * sectorsPerCluster);
	uint size = 0;
	while (!found)
	{
		if ((lastCluster >> 7) != (currentCluster >> 7))
			ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
		ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);
		F32E * e = cluster;
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
							memcpy(lastcluster, cluster, 512 * sectorsPerCluster);
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
								memcpy(lastcluster, cluster, 512 * sectorsPerCluster);
								j = 16 * sectorsPerCluster - 1;
								reread = 1;
							}
						}

						for (int k = 0; k < 256; k++)
							if (longFileName[k] == 0xFF)
								longFileName[k] = 0;
						//kprintf("%s", &longFileName);
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
							if (*curChar != longFileName[j])
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
							fileName = (uint)curChar + 1;
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
		currentCluster = ((uint*)&FATTablePart)[currentCluster % 128];
		if (lastDir)
			break;
		if (currentCluster == 0xFFFFFFF)
			break;
	}
	currentCluster = lastCluster;
	ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);

	F32E * e = cluster;
	uint ffound = 0;
	uint avaliable = 0;
	while (currentCluster != 0xFFFFFFF && !avaliable) {
		if ((lastCluster >> 7) != (currentCluster >> 7))
			ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
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
			currentCluster = ((uint*)&FATTablePart)[currentCluster % 128];
		}
	}
	if (!avaliable)
	{
		uint nw = findFreeFATEntry(diskId, reserved);
		((uint*)&FATTablePart)[lastCluster % 128] = nw;
		WriteToDisk(reserved + (lastCluster >> 7), 1, &FATTablePart, diskId);
		currentCluster = nw;
		memset(cluster, 0, 512 * sectorsPerCluster);
		avaliable = 1;
		ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
		((uint*)&FATTablePart)[currentCluster % 128] = 0xFFFFFFF;
		WriteToDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
	}
	kprintf("Cluster: %x\n", *sec100);
	avaliable--;
	uint t = avaliable;
	e[t].size = 0;
	e[t].clusterHi = 0;
	e[t].clusterLo = 0;
	e[t].lastModifiedTime = ((((*sec100) / ticksPerSecond) % 60) / 2) + (((((*sec100) / ticksPerSecond) / 60) % 60) << 5) + ((((((*sec100) / ticksPerSecond) / 60) / 60) % 24) << 11);
	e[t].lastModifiedDate = 26 + (9 << 5) + (38 << 9);
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
	///kprintf("%s %x\n", fileName, cdot);
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
	WriteToDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);


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
	char FATTablePart[512];
	uint lastCluster = RootEntry, currentCluster = RootEntry;
	ReadFromDisk(reserved, 1, &FATTablePart, diskId);
	char * cluster = malloc(512 * sectorsPerCluster);
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
	F32E * lastcluster = malloc(512 * sectorsPerCluster);
	uint size = 0;
	while (!found)
	{
		if ((lastCluster >> 7) != (currentCluster >> 7))
			ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
		ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);
		F32E * e = cluster;
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
							memcpy(lastcluster, cluster, 512 * sectorsPerCluster);
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
								memcpy(lastcluster, cluster, 512 * sectorsPerCluster);
								j = 16 * sectorsPerCluster - 1;
								reread = 1;
							}
						}

						for (int k = 0; k < 256; k++)
							if (longFileName[k] == 0xFF)
								longFileName[k] = 0;
						//kprintf("%s", &longFileName);
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
							if (*curChar != longFileName[j])
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
							fileName = (uint)curChar + 1;
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
		currentCluster = ((uint*)&FATTablePart)[currentCluster % 128];
		if (lastDir)
			break;
		if (currentCluster == 0xFFFFFFF)
			break;
	}
	currentCluster = lastCluster;
	ReadFromDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);

	F32E * e = cluster;
	uint ffound = 0;
	uint avaliable = 0;
	while (currentCluster != 0xFFFFFFF && !avaliable) {
		if ((lastCluster >> 7) != (currentCluster >> 7))
			ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
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
			currentCluster = ((uint*)&FATTablePart)[currentCluster % 128];
		}
	}
	if (!avaliable)
	{
		uint nw = findFreeFATEntry(diskId, reserved);
		((uint*)&FATTablePart)[lastCluster % 128] = nw;
		WriteToDisk(reserved + (lastCluster >> 7), 1, &FATTablePart, diskId);
		currentCluster = nw;
		memset(cluster, 0, 512 * sectorsPerCluster);
		avaliable = 1;
		ReadFromDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
		((uint*)&FATTablePart)[currentCluster % 128] = 0xFFFFFFF;
		WriteToDisk(reserved + (currentCluster >> 7), 1, &FATTablePart, diskId);
	}
	kprintf("Cluster: %x\n", currentCluster);
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

	///kprintf("%s %x\n", fileName, cdot);

	WriteToDisk(FatStart + (currentCluster - 2) * sectorsPerCluster, sectorsPerCluster, cluster, diskId);

	ReadFromDisk(reserved + (zz >> 7), 1, &FATTablePart, diskId);
	((uint*)&FATTablePart)[zz % 128] = 0xFFFFFFF;
	WriteToDisk(reserved + (zz >> 7), 1, &FATTablePart, diskId);
}
#pragma GCC pop_options