#define Elf32_Half unsigned short
#define Elf32_Addr unsigned int
#define Elf32_Word unsigned int
#define Elf32_Off  unsigned int
typedef struct
{
	unsigned int magic;	 	/* сигнатура и прочая информация										  */
	unsigned int magic2;	 	/* сигнатура и прочая информация										  */
	unsigned int magic3;	 	/* сигнатура и прочая информация										  */
	unsigned int magic4;	 	/* сигнатура и прочая информация										  */
	Elf32_Half	  e_type;				 	/* тип объектного файла												   */
	Elf32_Half	  e_machine;			  /* архитектура аппаратной платформы									   */
	Elf32_Word	  e_version;			  /* номер версии формата												   */
	Elf32_Addr	  e_entry;				/* адрес точки входа (стартовый адрес программы)						  */
	Elf32_Off	  e_phoff;				/* смещение от начала файла таблицы программных заголовков				*/
	Elf32_Off	  e_shoff;				/* смещение от начала файла таблицы заголовков секций					 */
	Elf32_Word	  e_flags;				/* специфичные флаги процессора (не используется в архитектуре i386)	  */
	Elf32_Half	  e_ehsize;			   /* размер ELF-заголовка файла в байтах									*/
	Elf32_Half	  e_phentsize;			/* размер записи в таблице программных заголовков						 */
	Elf32_Half	  e_phnum;				/* число заголовков - количество записей в таблице программных заголовков */
	Elf32_Half	  e_shentsize;			/* размер записи в таблице заголовков секций							  */
	Elf32_Half	  e_shnum;				/* количество записей в таблице заголовков секций						 */
	Elf32_Half	  e_shstrndx;			 /* расположение сегмента, содержащего таблицy стpок					   */
} EHeader;
typedef struct
{
	Elf32_Word      sh_name;                /* имя секции                            */
	Elf32_Word      sh_type;                /* тип секции                            */
	Elf32_Word      sh_flags;               /* флаги секции                          */
	Elf32_Addr      sh_addr;                /* виртуальный адрес начала секции       */
	Elf32_Off       sh_offset;              /* физическое смещение секции в файле    */
	Elf32_Word      sh_size;                /* размер секции в байтах                */
	Elf32_Word      sh_link;                /* связка с другой секцией               */
	Elf32_Word      sh_info;                /* дополнительная информация о секции    */
	Elf32_Word      sh_addralign;           /* кратность выравнивания секции         */
	Elf32_Word      sh_entsize;             /* размер вложенного элемента, если есть */
} ESHeader;

static inline EHeader *elf_sheader(EHeader *hdr) {
	return (ESHeader*)((int)hdr + hdr->e_shoff);
}

static inline ESHeader *elf_section(EHeader *hdr, int idx) {
	return &elf_sheader(hdr)[idx];
}

typedef struct {
	Elf32_Word		st_name;
	Elf32_Addr		st_value;
	Elf32_Word		st_size;
	unsigned char	st_info;
	unsigned char	st_other;
	Elf32_Half		st_shndx;
} ESymbol;
unsigned int getSymAdr(EHeader *hdr, int table, unsigned int idx)
{
	//if(table == SHN_UNDEF || idx == SHN_UNDEF) return 0;
	ESHeader *symtab = (int)hdr + (hdr->e_shoff) + 0x28 * table;

	unsigned int symtab_entries = symtab->sh_size / symtab->sh_entsize;

	int symaddr = (int)hdr + symtab->sh_offset;
	ESymbol *symbol = &((ESymbol *)symaddr)[idx];

	if (symbol->st_shndx == 0xFFF1)
	{
		//printTextToWindow(7,mywin,"****%x***",symbol->st_value);
		return symbol->st_value;
	}
	else if (symbol->st_shndx < 0xFFF0)
	{
		ESHeader *target = (int)hdr + (hdr->e_shoff) + 0x28 * symbol->st_shndx;
		//printTextToWindow(4,mywin,"****%x***",(target->sh_offset)) + symbol->st_value ;
		return symbol->st_value + (int)hdr + target->sh_offset;
	}
	else
		if (symbol->st_shndx == 0xFFF2)
		{
			return symtab->sh_offset + (int)hdr;
		}
	//printTextToWindow(1,mywin,"%x",symbol->st_size);
}

typedef struct {
	Elf32_Addr		r_offset;
	Elf32_Word		r_info;
} RelTab;

typedef struct {
	Elf32_Addr		r_offset;
	Elf32_Word		r_info;
	unsigned int		r_addend;
} RelaTab;

void ferr(int i)
{
	for (;;);
}
unsigned int relocELF(void * p)
{
	EHeader * elf = p;//printTextToWindow(7,mywin,"%x\n",sizeof(EHeader));

	if (elf->magic == 0x464c457f)
	{
		unsigned int TText = 0;

		for (int i = 0; i < elf->e_shnum; i++)
		{
			ESHeader *sh = 0x28 * i + (int)elf + elf->e_shoff;
			if (sh->sh_type == 8)
			{
				if (!sh->sh_size) continue;
				if (sh->sh_flags & 2)
				{
					unsigned int mem = malloc(sh->sh_size);
					memset(mem, 0, sh->sh_size);
					sh->sh_offset = (int)mem - (int)elf;
					//printTextToWindow(7, mywin, "allocated %x bytes for %d section!\n", sh->sh_size, i);
				}
			}
		}
		//Calculate common section length
		unsigned int commonSectionLength = 0;
		for (int i = 0; i < elf->e_shnum; i++)
		{
			ESHeader *sh = 0x28 * i + (int)elf + elf->e_shoff;
			if (sh->sh_type == 2)
			{
				ESymbol * st = sh->sh_offset + (int)elf;
				for (int i = 0; i < sh->sh_size / 0x10; i++)
					if (st[i].st_shndx == 0xFFF2)
					{
						commonSectionLength += st[i].st_size;
					}
			}
		}
		//*((unsigned int*)(0)) = &ferr;
		//Find undefined functions and variables
		for (int i = 0; i < elf->e_shnum; i++)
		{
			ESHeader *sh = 0x28 * i + (int)elf + elf->e_shoff;
			if (sh->sh_type == 2)
			{
				ESymbol * st = sh->sh_offset + (int)elf;
				ESHeader * names = sh->sh_link * 0x28 + (int)elf + elf->e_shoff;
				for (int i = 1; i < sh->sh_size / 0x10; i++)
				{
					if (st[i].st_shndx == 0x0)
					{
						char * varName = names->sh_offset + st[i].st_name + (int)elf;
						*((unsigned short*)(sh->sh_offset + (int)elf + 0x10 * i + 0xE)) = 0xFFF1;
						*((unsigned int*)(sh->sh_offset + (int)elf + 0x10 * i + 0x4)) = getVariableAddress((int)varName + 1);

						//printTextToWindow(7, mywin, "Undef: %x %s %x\n", getVariableAddress((int)varName + 1), varName, &malloc);
					}
				}
			}
		}
		unsigned int commonSectionPtr = malloc(commonSectionLength + 4);//Allocate common section
		unsigned int comId = 0;
		for (int i = 0; i < elf->e_shnum; i++)
		{
			ESHeader *sh = 0x28 * i + (int)elf + elf->e_shoff;
			if (sh->sh_type == 2)
			{
				ESymbol * st = sh->sh_offset + (int)elf;
				for (int i = 0; i < sh->sh_size / 0x10; i++)
				{
					if (st[i].st_shndx == 0xFFF2)
					{
						*((unsigned short*)(sh->sh_offset + (int)elf + 0x10 * i + 0xE)) = 0xFFF1;		//Absolute offset
						*((unsigned int*)(sh->sh_offset + (int)elf + 0x10 * i + 0x4)) = commonSectionPtr + comId;	//Set offset
//						printTextToWindow(7, mywin, "Common: %x %x\n", i, comId);
						comId += st[i].st_size;

					}
				}
			}
		}

		for (int i = 0; i < elf->e_shnum; i++)
		{
			ESHeader *section = 0x28 * i + (int)elf + elf->e_shoff;
			if (section->sh_type == 0x09)
			{
				RelTab * relocTable = section->sh_offset + (int)elf;
				unsigned int RelocationCount = section->sh_size / 0x08;
				unsigned int sectionForId = section->sh_info;
				ESHeader *relocSection = 0x28 * sectionForId + (int)elf + elf->e_shoff;
				unsigned int relocSectionOffset = relocSection->sh_offset + (int)elf;
				for (int j = 0; j < RelocationCount; j++)
				{
					unsigned int relocationSymbol = relocTable[j].r_info >> 8;
					unsigned int sectionOffset = relocTable[j].r_offset;
					unsigned int additional = getSymAdr(elf, section->sh_link, relocationSymbol);
					if (relocTable[j].r_info & 1)
						*((unsigned int*)(sectionOffset + (int)relocSectionOffset)) = *((unsigned int*)(sectionOffset + (int)relocSectionOffset)) + additional;
					else if (relocTable[j].r_info & 2)
						*((int*)(sectionOffset + (int)relocSectionOffset)) = *((int*)(sectionOffset + (int)relocSectionOffset)) + additional - (sectionOffset + (int)relocSectionOffset) - 4;
					//printTextToWindow(7, mywin, "Reloc: %x \n", *((unsigned int*)(sectionOffset + (int)relocSectionOffset)));
				}
			}
		}
		return (int)elf + 0x34;
	}
	else
		return (int)elf;
}