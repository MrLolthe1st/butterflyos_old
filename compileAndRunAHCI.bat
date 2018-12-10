call programs\edit\compile.bat
@echo off

:: BatchGotAdmin
:-------------------------------------
REM  --> Check for permissions
    IF "%PROCESSOR_ARCHITECTURE%" EQU "amd64" (
>nul 2>&1 "%SYSTEMROOT%\SysWOW64\cacls.exe" "%SYSTEMROOT%\SysWOW64\config\system"
) ELSE (
>nul 2>&1 "%SYSTEMROOT%\system32\cacls.exe" "%SYSTEMROOT%\system32\config\system"
)

REM --> If error flag set, we do not have admin.
if '%errorlevel%' NEQ '0' (
    echo Requesting administrative privileges...
    goto UACPrompt
) else ( goto gotAdmin )

:UACPrompt
    echo Set UAC = CreateObject^("Shell.Application"^) > "%temp%\getadmin.vbs"
    set params= %*
    echo UAC.ShellExecute "cmd.exe", "/c ""%~s0"" %params:"=""%", "", "runas", 1 >> "%temp%\getadmin.vbs"

    "%temp%\getadmin.vbs"
    del "%temp%\getadmin.vbs"
    exit /B

:gotAdmin
    pushd "%CD%"
    CD /D "%~dp0"
:--------------------------------------    
@echo on
"compilers\nasm\nasm.exe" -f elf "source\elf.asm" -o "binaries\elf.o"
gcc -ffreestanding -std=c11 -c -o binaries\kernell.o source\kernel.c -w
ld -Ttext 0x100000 -o binaries\kernel.o binaries\elf.o binaries\kernell.o 
objcopy binaries\kernel.o -O binary
"compilers\nasm\nasm.exe"  "source\boot.asm" -o "binaries\BOOT"
copy binaries\BOOT A:\STARTUP
del Images\boot.img.lock
del Images\bb.img.lock
utils\sync64.exe A
copy images\disk.img images\boot.img
chcp 65001
utils\dd.exe if=images\boot.img of=e:\butterflyos\images\dq.vhd
#$ping 127.0.0.1 -n 16 > nul
qemu\qemu-system-x86_64.exe -trace usb_host  -smp cpus=3,cores=3 -m 120 -drive id=disk,file=images\boot.img,if=none -device ahci,id=ahci -device ide-drive,drive=disk,bus=ahci.0  -no-reboot -vga std -D aa.txt -monitor stdio -usbdevice keyboard -netdev user,id=n1,ipv6=off -device e1000,netdev=n1,mac=52:54:98:76:54:32
pause