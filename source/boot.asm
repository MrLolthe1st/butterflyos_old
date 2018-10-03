jmp loadermain
[org 0x600]

GDT:
NULLSELECTOR    EQU             $ - GDT
                DD 0x0
                DD 0x0

CODESELECTOR    EQU             $ - GDT          ; 4GB Flat Code at 0x0 with max 0xFFFFF limit
                DW              0FFFFh           ; Limit(2):0xFFFF
                DW              0h               ; Base(3)
                DB              0h               ; Base(2)
                DB              09Ah             ; Type: present,ring0,code,exec/read/accessed (10011000)
                DB              0CFh             ; Limit(1):0xF | Flags:4Kb inc,32bit (11001111)
                DB              0h               ; Base(1)

DATASELECTOR    EQU             $ - GDT          ; 4GB Flat Data at 0x0 with max 0xFFFFF limit
                DW              0FFFFh           ; Limit(2):0xFFFF
                DW              0h               ; Base(3)
                DB              0h               ; Base(2)
                DB              092h             ; Type: present,ring0,data/stack,read/write (10010010)
                DB              0CFh             ; Limit(1):0xF | Flags:4Kb inc,32bit (11001111)
                DB              0h               ; Base(1)
GDTEND:

GDTR:
GDTsize DW GDTEND - GDT - 1
GDTbase DD GDT
loadermain:
	xor di,di
	mov ax,0x4F0A
	mov bx,0
	int 10h
	push es
	pop ds
	mov si,di
	push ax
	mov di,256 + 16*256
	mov ax,0x3000
	mov es,ax
	;mov ax,si
	pop ax
	stosw
	mov ax,ds
	stosw
	
	mov ax,0x3000
	mov es,ax
	mov [es:0x0000],byte 1
	mov di,0x0000
	mov cx,0x118
	mov ax,0x4F01
	int 0x10
	mov ax,0x4F02
	mov bx,0x4118
	%if 0 ;Set it to 0, if you won't use GUI.
	int 10h
	pusha
	xor ax,ax
	mov es,ax
	mov di,0x3ff
	mov al,1
	stosb
	popa
	%else
	pusha
	xor ax,ax
	mov es,ax
	mov di,0x3ff
	stosb
	popa
	%endif
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov fs, ax
	
	mov ax,0x3000
	mov es,ax
	mov di,0x100
	push			ds
	push			es
	;ask BIOS to return VGA bitmap fonts
	mov			ax, 1130h
	mov			bh, 6
	int			10h
	;copy charmap
	push		es
	pop			ds
	pop			es
	mov			si, bp
	mov			cx, 1024
	rep			movsd
	pop			ds
	
    cli
    mov ax, 1D0h
    mov ss, ax
    mov sp, 0200h

    in al, 0x92;включаем A20
	or al, 2
	out 0x92, al
	
    sti

lMoveGDT:
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov si, GDT
    mov di, [GDTbase]
    mov cx, [GDTsize]
    cld
    rep movsb

lEnterPMode:
    cli
    mov eax, cr0
    or al, 1
    mov cr0, eax

    lgdt[GDTR]

    jmp CODESELECTOR:FlushPipeline  

[BITS 32]
FlushPipeline:
    mov eax, DATASELECTOR
    mov ds, eax
    mov es, eax
    mov fs, eax
    mov gs, eax
    mov ss, eax
    mov esp, 0ffffh
	mov ecx,165535
	mov edi,0x100000
	mov esi,kernel
	rep movsd
	
	
	
	jmp 0x100000	
;times 1024-($-$$) db 0
kernel incbin 'binaries\kernel.o'