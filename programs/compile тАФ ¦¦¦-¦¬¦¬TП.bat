gcc -ffreestanding hello.c -c -o binaries\qq.o -w
ld -o binaries\oo.o binaries\qq.o
objcopy binaries\oo.o -O binary
pause