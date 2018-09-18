
"compilers\nasm\nasm.exe" -f elf "source\elf.asm" -o "binaries\elf.o"
cpp -ffreestanding -std=c99 source\kernel.c -w>temp\formattedKernel.c
gcc -ffreestanding -std=c99 -c -o binaries\kernell.o source\kernel.c -w
gcc -S source\kernel.c -std=c99 -w -o temp\kernel_ASM_version.asm
ld -Ttext 0x100000 -o binaries\kernel.o binaries\elf.o binaries\kernell.o
objcopy binaries\kernel.o -O binary
"compilers\nasm\nasm.exe"  "source\boot.asm" -o "binaries\BOOT"
copy binaries\BOOT A:\STARTUP
copy images\disk.img images\boot.img
chcp 65001
utils\dd.exe if=images\boot.img of=E:\butterflyOs\images\dq.vhd
#$ping 127.0.0.1 -n 16 > nul
qemu\qemu-system-x86_64.exe -m 32 -net nic,model=rtl8139 -drive if=none,id=usbstick,file=images\boot.img -usb -device usb-ehci,id=ehci -device usb-storage,bus=ehci.0,drive=usbstick -no-reboot -vga std -D aa.txt -monitor stdio 
pause