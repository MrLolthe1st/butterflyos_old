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
	uint size;
	uint nool;
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
	FileInfoF32 * q = malloc(sizeof(FileInfoF32));
	q->startCluster = currentCluster;
	q->size = size;
	q->nool = 0;
	free(cluster);
	free(lastCluster);
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
				uint countR = min((ofs + 1)*sectorsPerCluster * 512, st + cnt - 1) - st + 1 - ((uint)buf - (uint)qf);
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

#pragma GCC pop_options