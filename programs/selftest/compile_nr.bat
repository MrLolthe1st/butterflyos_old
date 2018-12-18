gcc -ffreestanding programs\selftest\jpeg.c -c -o programs\selftest\qq.o -w -std=c99 
objcopy programs\selftest\qq.o -O elf32-i386
copy programs\selftest\qq.o A:\SYSTEM32\JPEG
