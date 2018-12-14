gcc -ffreestanding programs\cmd\cmd.c -c -o programs\cmd\qq.o -w -std=c99
objcopy programs\cmd\qq.o -O elf32-i386
copy programs\cmd\qq.o A:\SYSTEM32\CMD.O
sync64 A