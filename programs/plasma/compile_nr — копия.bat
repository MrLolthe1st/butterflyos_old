gcc -ffreestanding plasma.c -c -o qq.o -w -std=c99 
objcopy qq.o -O elf32-i386
copy qq.o A:\SYSTEM32\PLASMA
pause
