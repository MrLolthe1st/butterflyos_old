[org 0x8000]

loadermain:
lap:
		jmp short bsp
		xor ax,ax
		mov ss,ax
		mov sp, 0x7c00
		xor ax,ax
		mov ds,ax
        ; Mark CPU as active
        lock
		inc byte [ds:0x2555]
		jmp zop
	bsp:
	xor ax,ax
	mov ds,ax
	mov dword[ds:0x2550],0
	mov dword[ds:0x2555],0
	mov word [ds:0x8000], 0x9090
	xor di,di
	mov ax,0x4F0A
	mov bx,0
	int 10h
	push es
	pop ds
	mov si,di
	push ax
	mov di,256 + 16*256
	mov ax,0x5000
	mov es,ax
	;mov ax,si
	pop ax
	stosw
	mov ax,ds
	stosw
	
	mov ax,0x5000
	mov es,ax
	mov [es:0x0000],byte 1
	mov di,0x0000
	mov dx,0x11e
	retry1:
	sub dx,3
	mov cx,dx
	mov ax,0x4F01
	int 0x10
	mov ax,0x4F02
	mov bx,dx
	or bx,0x4000
	%if 1;Set it to 0, if you won't use GUI.
	int 10h
	jc retry1
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
	
	mov ax,0x5000
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
	zop:
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
	mov eax,dword[ds:0x2555]
	cmp eax,0
	jnz bsp_ok
    mov esp, 0ffffh
	mov ecx,0x40000
	mov edi,0x100000
	mov esi,kernel
	rep movsd
	mov eax,cr4
	or eax,0x200
	mov cr4,eax
	mov edi,0xb8000
	movaps 	[edi],xmm0
	jmp 0x100000
bsp_ok:
	 mov esp, 0x10000
     lock
     xadd [0x9925], esp
	 add esp,0x10000
	mov eax,cr4
	or eax,0x200
	mov cr4,eax
	mov edi,0xb8000
	movaps 	[edi],xmm0
	 
	 mov eax,esp
	 sub eax,dword[0x9929]
	 shr eax,16
	 push eax
	 push eax
	 mov edi,dword[0x9933]
	 jmp edi
;times 1024-($-$$) db 0

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
kernel incbin 'binaries\kernel.o'




















