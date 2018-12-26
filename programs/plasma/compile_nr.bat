gcc -ffreestanding programs\plasma\plasma.c -c -o programs\plasma\qq.o -w -std=c99 
objcopy programs\plasma\qq.o -O elf32-i386
copy programs\plasma\qq.o A:\SYSTEM32\PLASMA
