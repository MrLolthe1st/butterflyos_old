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
	return (EHeader*)((int)hdr + hdr->e_shoff);
}

static inline ESHeader *elf_section(EHeader *hdr, int idx) {
	return (ESHeader *)&elf_sheader(hdr)[idx];
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
	ESHeader *symtab = (ESHeader *)((int)hdr + (hdr->e_shoff) + 0x28 * table);

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
		ESHeader *target = (ESHeader *)((int)hdr + (hdr->e_shoff) + 0x28 * symbol->st_shndx);
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




ELF_Process *  relocELF(void * p)
{
	EHeader * elf = p;
	//Check magic
	if (elf->magic == 0x464c457f)
	{
	
		unsigned int TText = 0;
		ELF_Process * proc = (ELF_Process*)mmalloc(sizeof(ELF_Process));
		for (int i = 0; i < elf->e_shnum; i++)
		{
			ESHeader *sh = (ESHeader *)(0x28 * i + (int)elf + elf->e_shoff);
			if (sh->sh_type == 8)
			{
				if (!sh->sh_size) continue;
				if (sh->sh_flags & 2)
				{
					unsigned int mem = (unsigned int)mmalloc(sh->sh_size);
					addProcessAlloc(proc, mem);
					memset((char*)mem, 0, sh->sh_size);
					sh->sh_offset = (int)mem - (int)elf;
				}
			}
		}
		//Calculate common section length
		unsigned int commonSectionLength = 0;
		for (int i = 0; i < elf->e_shnum; i++)
		{
			ESHeader *sh = (ESHeader *)(0x28 * i + (int)elf + elf->e_shoff);
			if (sh->sh_type == 2)
			{
				ESymbol * st = (ESymbol *)(sh->sh_offset + (int)elf);
				for (int i = 0; i < sh->sh_size / 0x10; i++)
					if (st[i].st_shndx == 0xFFF2)
					{
						commonSectionLength += st[i].st_size;
						//	kprintf("z");
					}
			}
		}
		int offset_main = -1;
		//Find undefined functions and variables
		ESHeader * names = 0;
		for (int i = 0; i < elf->e_shnum; i++)
		{
			ESHeader *sh = (ESHeader *)(0x28 * i + (int)elf + elf->e_shoff);
			if (sh->sh_type == 2)
			{
				ESymbol * st = (ESymbol *)(sh->sh_offset + (int)elf);
				names = (ESHeader *)(sh->sh_link * 0x28 + (int)elf + elf->e_shoff);
				for (int i = 1; i < sh->sh_size / 0x10; i++)
				{
					char * varName = (char*)(names->sh_offset + st[i].st_name + (int)elf);
					if (st[i].st_shndx == 0x0)
					{

						uint zz = getVariableAddress((char*)((int)varName + 1));
						if (zz) {
							*((unsigned short*)(sh->sh_offset + (int)elf + 0x10 * i + 0xE)) = 0xfff1;
							*((unsigned int*)(sh->sh_offset + (int)elf + 0x10 * i + 0x4)) = zz;
						}

					}
					//printTextToWindow(3, mywin, "%s\n", varName);
					if (varName[1] == 'm'&&varName[2] == 'a'&&varName[3] == 'i'&&varName[4] == 'n'&&varName[5] == 0) {
						offset_main = *((unsigned int*)(sh->sh_offset + (int)elf + 0x10 * i + 0x4));
					}


				}
			}
		}
		unsigned int commonSectionPtr = (uint)mmalloc(commonSectionLength + 4);//Allocate common section
		addProcessAlloc(proc, commonSectionPtr);
		unsigned int comId = 0;
		for (int i = 0; i < elf->e_shnum; i++)
		{
			ESHeader *sh = (ESHeader *)(0x28 * i + (int)elf + elf->e_shoff);
			if (sh->sh_type == 2)
			{
				ESymbol * st = (ESymbol*)(sh->sh_offset + (int)elf);
				for (int i = 0; i < sh->sh_size / 0x10; i++)
				{
					if (st[i].st_shndx == 0xFFF2)
					{
						*((unsigned short*)(sh->sh_offset + (int)elf + 0x10 * i + 0xE)) = 0xFFF1;		//Absolute offset
						*((unsigned int*)(sh->sh_offset + (int)elf + 0x10 * i + 0x4)) = commonSectionPtr + comId;	//Set offset

						comId += st[i].st_size;

					}
				}
			}
		}
		names = names->sh_offset + (uint)elf;
		for (int i = 0; i < elf->e_shnum; i++)
		{
			ESHeader *section = (ESHeader*)(0x28 * i + (int)elf + elf->e_shoff);
			if (section->sh_type == 0x09)
			{
				RelTab * relocTable = (RelTab*)(section->sh_offset + (int)elf);
				unsigned int RelocationCount = section->sh_size / 0x08;
				unsigned int sectionForId = section->sh_info;
				ESHeader *relocSection = (ESHeader*)(0x28 * sectionForId + (int)elf + elf->e_shoff);
				unsigned int relocSectionOffset = relocSection->sh_offset + (int)elf;


				for (int j = 0; j < RelocationCount; j++)
				{
					unsigned int relocationSymbol = relocTable[j].r_info >> 8;

					unsigned int sectionOffset = relocTable[j].r_offset;
					unsigned int additional = getSymAdr(elf, section->sh_link, relocationSymbol);

					ESHeader *symtab = (ESHeader *)((int)elf + (elf->e_shoff) + 0x28 * section->sh_link);

					unsigned int symtab_entries = symtab->sh_size / symtab->sh_entsize;

					int symaddr = (uint)elf + symtab->sh_offset;
					ESymbol *symbol = &((ESymbol *)symaddr)[relocationSymbol];

					char * vn = (uint)names + symbol->st_name;
					if (vn[2] == '_'&&vn[3] == 'm'&&vn[4] == 'a'&&vn[5] == 'i'&&vn[6] == 'n'&&vn[7] == 0)
					{
						*((unsigned char*)(sectionOffset + (int)relocSectionOffset - 1)) = 0x90;
						*((unsigned int*)(sectionOffset + (int)relocSectionOffset)) = 0x90909090;
						relocTable[j].r_info = 0;
						continue;
					}
					if (relocTable[j].r_info & 1)
						*((unsigned int*)(sectionOffset + (int)relocSectionOffset)) = *((unsigned int*)(sectionOffset + (int)relocSectionOffset)) + additional;
					else if (relocTable[j].r_info & 2)
						*((int*)(sectionOffset + (int)relocSectionOffset)) = *((int*)(sectionOffset + (int)relocSectionOffset)) + additional - (sectionOffset + (int)relocSectionOffset) - 4;



				}
			}
		}
		proc->entry = 0x34 + offset_main + (uint)elf;
		//printTextToWindow(3, mywin, "!!!%x!!", elf->e_entry + (uint)elf);
		return proc;
	}
	else
		return (int)0;
}