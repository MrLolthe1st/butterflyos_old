gcc -ffreestanding hello.c -c -o qq.o -w
objcopy qq.o -O elf32-i386
copy qq.o A:\qq.o
pause