@echo off
color 0A
echo Compiling bootloader...
"compilers\nasm\nasm.exe" -f bin  "source\bootloader.asm" -o "binaries\bootloader.bin"
"compilers\nasm\nasm.exe" -f elf "source\elf.asm" -o "binaries\elf.o"
echo Compiling kernel...
cpp -ffreestanding -std=c99 source\kernel.c -w>temp\formattedKernel.c
gcc -ffreestanding -std=c99 -c -o binaries\kernell.o source\kernel.c -w
gcc -S source\kernel.c -std=c99 -w -o temp\kernel_ASM_version.asm
echo Linking kernel...
ld -Ttext 0x100000 -o binaries\kernel.o binaries\elf.o binaries\kernell.o
objcopy binaries\kernel.o -O binary
"compilers\nasm\nasm.exe"  "source\boot.asm" -o "binaries\BOOT"
echo Ready, copying kernel to FS.
copy binaries\BOOT A:\STARTUP
echo Cloning disk image.
copy images\disk.img images\boot.img
chcp 65001
echo Making boot...
utils\BootMaker.exe binaries\bootloader.bin images\boot.img 0
echo Ready!!!!!!!!!!!
pause