gcc -ffreestanding hello.c -c -o binaries\qq.o -w

objcopy binaries\qq.o -O elf32-i386
copy binaries\qq.o A:\OO.O
pause