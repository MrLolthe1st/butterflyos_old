gcc -ffreestanding programs\edit\edit.c -c -o programs\edit\qq.o -w -std=c99
objcopy programs\edit\qq.o -O elf32-i386
copy programs\edit\qq.o A:\SYSTEM32\EDIT.O
sync64 A