
typedef struct __attribute__((packed)) {
	uint8_t status;
	uint32_t size;
} alloc_t;
#define MAX_PAGE_ALIGNED_ALLOCS 32

uint32_t last_alloc = 0;
uint32_t heap_end = 0;
uint32_t heap_begin = 0;
uint32_t pheap_begin = 0;
uint32_t pheap_end = 0;
uint8_t * pheap_desc = 0;
uint32_t memory_used = 0;
void memset(void * addr, char s, size_t count) {
	for (int i = 0; i < count; i++)
		(*((unsigned char *)addr + i)) = s;
}
void memcpy(unsigned char * s, unsigned char * d, size_t count) {
	__asm__("pusha\n\
			mov %2,%%ecx\n\
			mov %0,%%esi\n\
			mov %1,%%edi\n\
			test %%ecx,%%ecx\n\
			jz zr\n\
			memcpySSE:\
				movups (%%esi),%%xmm0	\n\
				movups %%xmm0,(%%edi)	\n\
				add $16, %%esi			\n\
				add $16, %%edi			\n\
				dec %%ecx				\n\
				test %%ecx,%%ecx		\n\
				jnz memcpySSE			\n\
			zr:							\n\
			mov %3, %%ecx				\n\
			test %%ecx,%%ecx			\n\
			jz send						\n\
			memcpySSE_1:				\
				movsb					\n\
				dec %%ecx				\n\
				jnz memcpySSE_1			\n\
			send:						\
			popa"
		::"r"(s), "r"(d), "r"(count >> 4), "r"(count % 16));
}

void * memchr(const void * buf, int c, size_t n) {
	unsigned char * p = (unsigned char *)buf;
	unsigned char * end = p + n;

	while (p != end) {
		if (*p == c) {
			return p;
		}

		++p;
	}

	return 0;
}

unsigned int count_memory(void) {
	register unsigned long long * mem;
	unsigned long long mem_count, a;
	unsigned int memkb;
	unsigned char irq1, irq2;
	unsigned long long cr0;

	/* save IRQ's */
	irq1 = inportb(0x21);
	irq2 = inportb(0xA1);

	/* kill all irq's */
	outportb(0x21, 0xFF);
	outportb(0xA1, 0xFF);

	mem_count = 0x200000;
	memkb = 0;

	// store a copy of CR0
	__asm__("movl %%cr0, %%eax": "=g" (cr0)::"eax");

	// invalidate the cache
	// write-back and invalidate the cache
	//__asm__  ("wbinvd");

	// plug cr0 with just PE/CD/NW
	// cache disable(486+), no-writeback(486+), 32bit mode(386+)
	//__asm__("movl %%eax, %%cr0" :: "g" (cr0 | 0x00000001 | 0x40000000 | 0x20000000) : "eax");

	do {
		memkb++;
		mem_count += 1024 * 1024 * 1;
		mem = (unsigned long long *) mem_count;

		a = *mem; *mem = 0x55AA55AA;

		// the empty asm calls tell gcc not to rely on what's in its registers
		// as saved variables (this avoids GCC optimisations)
		__asm__(""::: "memory");
		if (*mem != 0x55AA55AA) mem_count = 0;
		else {
			*mem = 0xAA55AA55;
			__asm__(""::: "memory");
			if (*mem != 0xAA55AA55)
				mem_count = 0;
		}

		__asm__(""::: "memory"); *mem = a;
		//int x=cursor;
		//kprintf("Testing Mem: 0x%x",mem);

		//for(int i=0;i<1000;i++) i = i;
	} while (memkb < 128 && mem_count != 0);

	//if(mem/1024>=1024
	//__asm__("movl %%eax, %%cr0" :: "g" (cr0) : "eax");

	unsigned int mem_end = memkb << 20;
	//mem = (unsigned long long*) 0x413;
	//unsigned int bse_end= (*mem & 0xFFFF) <<6;
	outportb(0x21, irq1);
	outportb(0xA1, irq2);
	return mem_end;
}

char * malloc(size_t size) {
	if (!size) return 0;

	/* Loop through blocks and find a block sized the same or bigger */
	uint8_t * mem = (uint8_t *)heap_begin;
	while ((uint32_t)mem < last_alloc) {
		alloc_t * a = (alloc_t *)mem;
		/* If the alloc has no size, we have reaced the end of allocation */
		//kprintf("mem=0x%x a={.status=%d, .size=%d}\n", mem, a->status, a->size);
		if (!a->size)
			goto nalloc;
		/* If the alloc has a status of 1 (allocated), then add its size
		 * and the sizeof alloc_t to the memory and continue looking.
		 */
		if (a->status) {
			mem += a->size;
			mem += sizeof(alloc_t);
			mem += 4;
			continue;
		}
		/* If the is not allocated, and its size is bigger or equal to the
		 * requested size, then adjust its size, set status and return the location.
		 */
		if (a->size >= size) {
			/* Set to allocated */
			a->status = 1;

			//kprintf("RE:Allocated %d bytes from 0x%x to 0x%x\n", size, mem + sizeof(alloc_t), mem + sizeof(alloc_t) + size);
			memset(mem + sizeof(alloc_t), 0, size);
			memory_used += size + sizeof(alloc_t);
			return (char *)(mem + sizeof(alloc_t));
		}
		/* If it isn't allocated, but the size is not good, then
		 * add its size and the sizeof alloc_t to the pointer and
		 * continue;
		 */
		mem += a->size;
		mem += sizeof(alloc_t);
		mem += 4;
	}

nalloc:;
	if (last_alloc + size + sizeof(alloc_t) >= heap_end) {
		//set_task(0);
		printString("Cannot allocate %d bytes! Out of memory.\n");
	}
	alloc_t * alloc = (alloc_t *)last_alloc;
	alloc->status = 1;
	alloc->size = size;

	last_alloc += size;
	last_alloc += sizeof(alloc_t);
	last_alloc += 4;
	//kprintf("Allocated %d bytes from 0x%x to 0x%x\n", size, (uint32_t)alloc + sizeof(alloc_t), last_alloc);
	memory_used += size + 4 + sizeof(alloc_t);
	memset((char *)((uint32_t)alloc + sizeof(alloc_t)), 0, size);
	return (char *)((uint32_t)alloc + sizeof(alloc_t));
	/*
		char* ret = (char*)last_alloc;
		last_alloc += size;
		if(last_alloc >= heap_end)
		{
			set_task(0);
			panic("Cannot allocate %d bytes! Out of memory.\n", size);
		}
		kprintf("Allocated %d bytes from 0x%x to 0x%x\n", size, ret, last_alloc);
		return ret;*/
}
void mm_init(uint32_t kernel_end) {
	last_alloc = kernel_end + 0x1000;
	heap_begin = last_alloc;
	pheap_end = count_memory();
	pheap_begin = pheap_end - (MAX_PAGE_ALIGNED_ALLOCS * 4096);
	heap_end = pheap_begin;
	memset((char *)heap_begin, 0, heap_end - heap_begin);
	pheap_desc = (uint8_t *)malloc(MAX_PAGE_ALIGNED_ALLOCS);
	/*kprintf("Kernel heap starts at 0x%x\n", last_alloc);
	kprintf("All memory: 0x%x bytes\n", pheap_end);*/
}

void mm_print_out() {
	_abc();
	/*kprintf("Memory used: %d bytes\n", memory_used);
	kprintf("Memory free: %d bytes\n", heap_end - heap_begin - memory_used);
	kprintf("Heap size: %d bytes\n", heap_end - heap_begin);
	kprintf("Heap start: 0x%x\n", heap_begin);
	kprintf("Heap end: 0x%x\n", heap_end);
	kprintf("PHeap start: 0x%x\nPHeap end: 0x%x\n", pheap_begin, pheap_end);*/
}

void free(void * mem) {
	alloc_t * alloc = (mem - sizeof(alloc_t));
	memory_used -= alloc->size + sizeof(alloc_t);
	alloc->status = 0;
}

void pfree(void * mem) {
	if (mem < pheap_begin || mem > pheap_end) return;
	/* Determine which page is it */
	uint32_t ad = (uint32_t)mem;
	ad -= pheap_begin;
	ad /= 4096;
	/* Now, ad has the id of the page */
	pheap_desc[ad] = 0;
	return;
}

char * pmalloc(size_t size) {
	/* Loop through the avail_list */
	for (int i = 0; i < MAX_PAGE_ALIGNED_ALLOCS; i++) {
		if (pheap_desc[i]) continue;
		pheap_desc[i] = 1;
		// kprintf("PAllocated from 0x%x to 0x%x\n", pheap_begin + i * 4096, pheap_begin + (i + 1) * 4096);
		return (char *)(pheap_begin + i * 4096);
	}
	//kprintf("pmalloc: FATAL: failure!\n");
	return 0;
}