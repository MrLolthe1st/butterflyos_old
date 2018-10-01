E:
cd E:\BOS\programs\cmd
gcc -ffreestanding cmd.c -c -o qq.o -w -std=c99
objcopy qq.o -O elf32-i386
sync64 A
copy qq.o A:\CMD.O
pause