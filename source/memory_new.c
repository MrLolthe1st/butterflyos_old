
typedef struct __attribute__((packed)) {
	uint32_t prev_size;
	uint32_t status;
	uint32_t size;
	uint32_t a1;
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
void memcpy(unsigned char * d, unsigned char * s, size_t count) {
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
				#test %%ecx,%%ecx		\n\
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

void memcpy1(unsigned char * d, unsigned char * s, size_t count) {
	__asm__("pusha\n\
			mov %2,%%ecx\n\
			mov %0,%%esi\n\
			mov %1,%%edi\n\
			test %%ecx,%%ecx\n\
			jz zrz\n\
			sub $16, %%esi			\n\
			sub $16, %%edi			\n\
			memcpySSE2:\
				movups (%%esi),%%xmm0	\n\
				movups %%xmm0,(%%edi)	\n\
				sub $16, %%esi			\n\
				sub $16, %%edi			\n\
				dec %%ecx				\n\
				#test %%ecx,%%ecx		\n\
				jnz memcpySSE2			\n\
			inc %%edi\n\
			inc %%esi\n\
			zrz:							\n\
			mov %3, %%ecx				\n\
			test %%ecx,%%ecx			\n\
			jz send2					\n\
			pushf\n\
			std\n\
			dec %%edi\n\
			dec %%esi\n\
			memcpySSE_12:				\
				movsb					\n\
				dec %%ecx				\n\
				jnz memcpySSE_12			\n\
			popf\n\
			send2:						\
			popa"
		::"r"(s + count), "r"(d + count), "r"(count >> 4), "r"(count & 0xF));
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

#pragma GCC push_options
#pragma GCC optimize ("Ofast")
unsigned int count_memory(void) {
	register unsigned int * mem;
	unsigned  int  mem_count, a;
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
		mem = (unsigned int *)mem_count;

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
	} while (memkb < 512 && mem_count != 0);

	//if(mem/1024>=1024
	//__asm__("movl %%eax, %%cr0" :: "g" (cr0) : "eax");

	unsigned int mem_end = memkb << 20;
	//mem = (unsigned long long*) 0x413;
	//unsigned int bse_end= (*mem & 0xFFFF) <<6;
	outportb(0x21, irq1);
	outportb(0xA1, irq2);
	return mem_end;
}


char * mmalloc(size_t size) {
	if (!size) {
		return 0;
	}
	lockTaskSwitch(1);
	char * addr = 0;
	int i;
	if (size < 4080)
		size = 4080;
	size--;
	size /= 16;
	size *= 16;
	size += 16;
	//	printTextToWindow(3, mywin, "!");
	for (i = 0; i < allocationAvlTree.size; )
	{
		int r;
		node_t *n;

		n = &allocationAvlTree.nodes[i];

		/* couldn't find it */
		if (!n->key) {
			unlockTaskSwitch();
			return NULL;

		}

		r = allocationAvlTree.cmp(n->key, size);

		if (r <= 0)
		{
			//We're lucky today.
			//Get memory block header
			alloc_t * block = (size_t)n->val - sizeof(alloc_t);
			//Set to used
			block->status = 1;
			//Set size
			block->size = size;
			alloc_t * next = (size_t)n->val + size;
			next->prev_size = size;
			next->status = 0;
			next->size = n->key - size - 16;
			avltree_remove1(&allocationAvlTree, n->key, n->val);
			//printTextToWindow(3, mywin, "%d %dKB;",size, next->size>>10);
			if (next->size) {
				avltree_insert(&allocationAvlTree, next->size, (size_t)next + sizeof(alloc_t));
			}
			memset((size_t)block + sizeof(alloc_t), 0, block->size); 
			block->a1 = 0xDEADBEEF;
			unlockTaskSwitch();
			return (size_t)block + sizeof(alloc_t);
		}
		else if (r > 0)
		{
			i = __child_r(i);
		}
		else
		{
			//assert(0);
		}
	}
	unlockTaskSwitch();
	return 0;
}
#pragma GCC pop_options
void addProcessAlloc(ELF_Process * p, void * addr);
int rb_mem_cmp(struct rb_tree *self, struct rb_node *node_a, struct rb_node *node_b) {
	int addr1 = (uint)node_a->value;
	int addr2 = (uint)node_b->value;
	return addr1 - addr2;
}
char * malloc(size_t size)
{
	char * addr = mmalloc(size);
	addProcessAlloc(procTable[currentRunning].elf_process, addr);
	return addr;
}

void insertTreapAlloc(processAlloc * t, processAlloc * e)
{

}

void addProcessAlloc(ELF_Process * p, void * addr)
{
	if (!p->tree)
	{
		p->tree = rb_tree_create(rb_mem_cmp);
	}
	rb_tree_insert(p->tree, addr);
	//printTextToWindow(3, mywin, "~%d~", p->tree->size);
/*
processAlloc * z = (processAlloc*)mmalloc(sizeof(processAlloc));
z->next = p->allocs;
z->addr = addr;
p->allocs = z;*/
}
void mm_init(uint32_t kernel_end) {
	last_alloc = kernel_end + 0x1000;
	heap_begin = last_alloc;
	pheap_end = count_memory();
	pheap_begin = pheap_end - (MAX_PAGE_ALIGNED_ALLOCS * 4096);
	heap_end = pheap_end;
	memset((char *)heap_begin, 0, heap_end - heap_begin);
	//pheap_desc = (uint8_t *)malloc(MAX_PAGE_ALIGNED_ALLOCS);
	unsigned int heapSize = heap_end - heap_begin;
	avltree_insert(&allocationAvlTree, heapSize, heap_begin);
	kprintf("Kernel heap starts at 0x%x 0x%x\n", avltree_get1(&allocationAvlTree, heapSize, heap_begin), heap_end);
	alloc_t * first = (size_t)kernel_end - sizeof(alloc_t);
	first->status = 0;
	first->a1 = 0xDEADBEEF;
	first->size = heapSize;
	first->prev_size = 0;

}

void mm_print_out() {

	printTextToWindow(3, mywin, "Memory used: %d bytes\n", memory_used);
	printTextToWindow(3, mywin, "Memory free: %d bytes\n", heap_end - heap_begin - memory_used);
	printTextToWindow(3, mywin, "Heap size: %d bytes\n", heap_end - heap_begin);
	printTextToWindow(3, mywin, "Heap start: 0x%x\n", heap_begin);
	printTextToWindow(3, mywin, "Heap end: 0x%x\n", heap_end);
	printTextToWindow(3, mywin, "PHeap start: 0x%x\nPHeap end: 0x%x\n", pheap_begin, pheap_end);
}

void ffree(void * mem) {
	if (!mem)
		return;
	//Get current alloc
	alloc_t * alloc = ((unsigned int)mem - sizeof(alloc_t));
	//for (;;);
	if (alloc->a1 != 0xDEADBEEF)
		return;
	alloc->status = 0;
	/*alloc_t * left = ((unsigned int)alloc - sizeof(alloc_t) - alloc->prev_size);
	printTextToWindow(3, mywin, "Free: %d %d\n", alloc->prev_size, left->size);
	if (left->status == 0&&left->size==alloc->prev_size)
	{
		//Merge blocks
		if (avltree_remove1(&allocationAvlTree, left->size, (uint)left + sizeof(alloc_t))) {
			left->size += sizeof(alloc_t) + alloc->size;
			alloc = left;
		}
		else printTextToWindow(3, mywin, "Unable remove");
	}
	alloc_t * right = (uint)alloc + sizeof(alloc_t) + alloc->size;
	if (right->prev_size&&right->status == 0)
	{
		if (avltree_remove1(&allocationAvlTree, right->size, (uint)right + sizeof(alloc_t))) {
			alloc->size += sizeof(alloc_t) + right->size;
		}
		else printTextToWindow(3, mywin, "Unable remove1");
	}
	avltree_insert1(&allocationAvlTree, alloc->size, (uint)alloc + sizeof(alloc_t));*/
	avltree_get1(&allocationAvlTree, alloc->size, (uint)alloc + sizeof(alloc_t));

}
void * calloc(size_t mem)
{
	return malloc(mem);
}
void realloc(char * addr, size_t mem)
{
	free(addr);
	return malloc(mem);
}
void free(void * mem)
{
	if (!procTable[currentRunning].elf_process)
		//May send segfault?
		return;
	if (!procTable[currentRunning].elf_process->tree)
		return;
	if (rb_tree_remove(procTable[currentRunning].elf_process->tree, mem)) {
		//printTextToWindow(3, mywin, "$%d:%d$", currentRunning, procTable[currentRunning].elf_process->tree->size);
		ffree(mem);
	}
	/*
	processAlloc * p = procTable[currentRunning].elf_process->allocs;
	if (!p)
		return;
	//printTextToWindow(3, mywin, "Free:\n");
	processAlloc * prev = 0;
	while (p)
	{
		if (p->addr == mem)
		{
			if (prev)
			{
				prev->next = p->next;
			}
			else
			{
				procTable[currentRunning].elf_process->allocs = p->next;
			}
			ffree(p->addr);
			ffree(p);
			return;
		}
		prev = p;
		p = p->next;
	}*/
}

void pfree(void * mem) {
	if ((size_t*)mem < (size_t*)pheap_begin || (size_t*)mem >(size_t*) pheap_end) return;
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
