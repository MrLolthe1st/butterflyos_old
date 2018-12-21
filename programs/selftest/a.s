	.file	"jpeg.c"
	.text
	.globl	_handle
	.def	_handle;	.scl	2;	.type	32;	.endef
_handle:
	pushl	%ebp
	movl	%esp, %ebp
	nop
	popl	%ebp
	ret
	.globl	_bswap16
	.def	_bswap16;	.scl	2;	.type	32;	.endef
_bswap16:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	8(%ebp), %eax
	movw	%ax, -4(%ebp)
	movzwl	-4(%ebp), %eax
	sall	$8, %eax
	movl	%eax, %edx
	movzwl	-4(%ebp), %eax
	shrw	$8, %ax
	addl	%edx, %eax
	leave
	ret
	.comm	_zigzag_table8, 64, 5
	.comm	_quant, 4096, 5
	.comm	_scan, 65536, 5
	.comm	_huf_codes, 131072, 5
	.comm	_huf_len, 1024, 5
	.comm	_dct, 512, 5
	.comm	_zigzagx, 128, 5
	.comm	_zigzagy, 128, 5
	.globl	_sqrt
	.def	_sqrt;	.scl	2;	.type	32;	.endef
_sqrt:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, -24(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -20(%ebp)
	fldl	-24(%ebp)
/APP
 # 26 "jpeg.c" 1
	fsqrt
 # 0 "" 2
/NO_APP
	fstpl	-8(%ebp)
	fldl	-8(%ebp)
	leave
	ret
	.globl	_cos
	.def	_cos;	.scl	2;	.type	32;	.endef
_cos:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, -24(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -20(%ebp)
	fldl	-24(%ebp)
/APP
 # 32 "jpeg.c" 1
	fcos
 # 0 "" 2
/NO_APP
	fstpl	-8(%ebp)
	fldl	-8(%ebp)
	leave
	ret
	.globl	_pi
	.data
	.align 8
_pi:
	.long	1413754133
	.long	1070146043
	.section .rdata,"dr"
LC1:
	.ascii " \0"
LC2:
	.ascii " /\12\0"
LC3:
	.ascii "%02x \12\0"
LC4:
	.ascii "!%02x! \12\0"
LC5:
	.ascii " \\\12\0"
	.text
	.globl	_ptree
	.def	_ptree;	.scl	2;	.type	32;	.endef
_ptree:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	cmpl	$0, 8(%ebp)
	je	L21
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	je	L10
	movl	12(%ebp), %eax
	leal	4(%eax), %ecx
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	movl	16(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	call	_ptree
L10:
	cmpl	$0, 12(%ebp)
	je	L11
	movl	$0, -12(%ebp)
	jmp	L12
L13:
	movl	$LC1, (%esp)
	call	_printf
	addl	$1, -12(%ebp)
L12:
	movl	-12(%ebp), %eax
	cmpl	12(%ebp), %eax
	jl	L13
L11:
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	je	L14
	movl	$LC2, (%esp)
	call	_printf
	movl	$0, -16(%ebp)
	jmp	L15
L16:
	movl	$LC1, (%esp)
	call	_printf
	addl	$1, -16(%ebp)
L15:
	movl	-16(%ebp), %eax
	cmpl	12(%ebp), %eax
	jl	L16
L14:
	movl	8(%ebp), %eax
	cmpl	16(%ebp), %eax
	je	L17
	movl	8(%ebp), %eax
	movzwl	(%eax), %eax
	cwtl
	movl	%eax, 4(%esp)
	movl	$LC3, (%esp)
	call	_printf
	jmp	L18
L17:
	movl	8(%ebp), %eax
	movzwl	(%eax), %eax
	cwtl
	movl	%eax, 4(%esp)
	movl	$LC4, (%esp)
	call	_printf
L18:
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	testl	%eax, %eax
	je	L21
	movl	$0, -20(%ebp)
	jmp	L19
L20:
	movl	$LC1, (%esp)
	call	_printf
	addl	$1, -20(%ebp)
L19:
	movl	-20(%ebp), %eax
	cmpl	12(%ebp), %eax
	jl	L20
	movl	$LC5, (%esp)
	call	_printf
	movl	12(%ebp), %eax
	leal	4(%eax), %ecx
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	16(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	%ecx, 4(%esp)
	movl	%eax, (%esp)
	call	_ptree
L21:
	nop
	leave
	ret
	.globl	_huffs
	.bss
	.align 32
_huffs:
	.space 128
	.comm	_last_insert, 4, 2
	.text
	.globl	_huf_insert
	.def	_huf_insert;	.scl	2;	.type	32;	.endef
_huf_insert:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	cmpl	$0, 8(%ebp)
	jne	L23
	movl	$16, (%esp)
	call	_malloc
	movl	%eax, 8(%ebp)
	movl	8(%ebp), %eax
	movl	$0, 4(%eax)
	movl	8(%ebp), %eax
	movl	$0, 8(%eax)
	movl	8(%ebp), %eax
	movl	$0, 12(%eax)
	movl	12(%ebp), %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movw	%dx, (%eax)
	movl	16(%ebp), %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movw	%dx, 2(%eax)
	movl	16(%ebp), %eax
	cmpl	20(%ebp), %eax
	jne	L23
	movl	8(%ebp), %eax
	movl	%eax, _last_insert
	movl	8(%ebp), %eax
	jmp	L24
L23:
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	testl	%eax, %eax
	jne	L25
	movl	16(%ebp), %eax
	leal	1(%eax), %ecx
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	20(%ebp), %edx
	movl	%edx, 12(%esp)
	movl	%ecx, 8(%esp)
	movl	12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_huf_insert
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 4(%eax)
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movl	8(%ebp), %edx
	movl	%edx, 12(%eax)
	movl	8(%ebp), %eax
	jmp	L24
L25:
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	jne	L26
	movl	16(%ebp), %eax
	leal	1(%eax), %ecx
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	movl	20(%ebp), %edx
	movl	%edx, 12(%esp)
	movl	%ecx, 8(%esp)
	movl	12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_huf_insert
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, 8(%eax)
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	movl	8(%ebp), %edx
	movl	%edx, 12(%eax)
	movl	8(%ebp), %eax
	jmp	L24
L26:
	movl	16(%ebp), %eax
	leal	-1(%eax), %ecx
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	movl	20(%ebp), %edx
	movl	%edx, 12(%esp)
	movl	%ecx, 8(%esp)
	movl	12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_huf_insert
L24:
	leave
	ret
	.comm	_matrix, 65536, 5
	.globl	_mcnt
	.bss
	.align 32
_mcnt:
	.space 64
	.comm	_sx, 262144, 5
	.text
	.def	_init_branches;	.scl	3;	.type	32;	.endef
_init_branches:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	$16, (%esp)
	call	_malloc
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, 12(%eax)
	movl	-12(%ebp), %eax
	movl	$0, 8(%eax)
	movl	-12(%ebp), %eax
	movl	$0, 4(%eax)
	movl	-12(%ebp), %eax
	leave
	ret
	.comm	_sxx, 65536, 5
	.comm	_table, 256, 5
	.globl	_tmp
	.bss
	.align 4
_tmp:
	.space 16
	.globl	_tmp2
	.align 4
_tmp2:
	.space 16
	.globl	_tmp3
	.data
	.align 4
_tmp3:
	.long	1048576000
	.long	1048576000
	.long	1048576000
	.long	1048576000
	.text
	.globl	_compute
	.def	_compute;	.scl	2;	.type	32;	.endef
_compute:
	flds	_tmp+8
	pushl	%ebp
	flds	_tmp+12
	movl	%esp, %ebp
	popl	%ebp
	faddp	%st, %st(1)
	flds	_tmp
	fadds	_tmp+4
	faddp	%st, %st(1)
	fmuls	LC6
	ret
	.globl	_preo
	.def	_preo;	.scl	2;	.type	32;	.endef
_preo:
	flds	_tmp
	pushl	%ebp
	movl	$_sxx, %eax
	flds	_tmp+4
	movl	%esp, %ebp
	pushl	%edi
	movl	12(%ebp), %edx
	pushl	%esi
	movl	$_tmp2, %esi
	faddp	%st, %st(1)
	pushl	%ebx
	movl	$_tmp, %ebx
	sall	$4, %edx
	addl	8(%ebp), %edx
	flds	_tmp+8
	fadds	_tmp+12
	movl	%edx, %ecx
	leal	_sx(,%edx,4), %edx
	sall	$8, %ecx
	addl	$_matrix, %ecx
	faddp	%st, %st(1)
	fmuls	LC6
L32:
/APP
 # 158 "jpeg.c" 1
				push %esi
			push %edi
			push %ecx
			movl %ecx, %edi
			movl %eax, %esi
			movups (%esi), %xmm1
			mov $16, %ecx
			.__uu1$:
				movups (%esi), %xmm0
				mulps (%edi), %xmm0
				addps %xmm0, %xmm1
				add $16, %esi
				add $16, %edi
				dec %ecx
				test %ecx, %ecx
				jnz .__uu1$
			movups %xmm1, (%ebx)
			pop %ecx
			pop %edi
			pop %esi
			
 # 0 "" 2
/NO_APP
	fsts	(%edx)
	leal	4096(%eax), %edi
/APP
 # 158 "jpeg.c" 1
				push %esi
			push %edi
			push %ecx
			movl %ecx, %edi
			movl %edi, %esi
			movups (%esi), %xmm1
			mov $16, %ecx
			.__uu1$:
				movups (%esi), %xmm0
				mulps (%edi), %xmm0
				addps %xmm0, %xmm1
				add $16, %esi
				add $16, %edi
				dec %ecx
				test %ecx, %ecx
				jnz .__uu1$
			movups %xmm1, (%ebx)
			pop %ecx
			pop %edi
			pop %esi
			
 # 0 "" 2
/NO_APP
	fsts	16384(%edx)
	leal	8192(%eax), %edi
/APP
 # 158 "jpeg.c" 1
				push %esi
			push %edi
			push %ecx
			movl %ecx, %edi
			movl %edi, %esi
			movups (%esi), %xmm1
			mov $16, %ecx
			.__uu1$:
				movups (%esi), %xmm0
				mulps (%edi), %xmm0
				addps %xmm0, %xmm1
				add $16, %esi
				add $16, %edi
				dec %ecx
				test %ecx, %ecx
				jnz .__uu1$
			movups %xmm1, (%ebx)
			pop %ecx
			pop %edi
			pop %esi
			
 # 0 "" 2
/NO_APP
	fsts	32768(%edx)
	leal	12288(%eax), %edi
/APP
 # 158 "jpeg.c" 1
				push %esi
			push %edi
			push %ecx
			movl %ecx, %edi
			movl %edi, %esi
			movups (%esi), %xmm1
			mov $16, %ecx
			.__uu1$:
				movups (%esi), %xmm0
				mulps (%edi), %xmm0
				addps %xmm0, %xmm1
				add $16, %esi
				add $16, %edi
				dec %ecx
				test %ecx, %ecx
				jnz .__uu1$
			movups %xmm1, (%ebx)
			pop %ecx
			pop %edi
			pop %esi
			
 # 0 "" 2
/NO_APP
	fsts	49152(%edx)
	leal	16384(%eax), %edi
/APP
 # 158 "jpeg.c" 1
				push %esi
			push %edi
			push %ecx
			movl %ecx, %edi
			movl %edi, %esi
			movups (%esi), %xmm1
			mov $16, %ecx
			.__uu1$:
				movups (%esi), %xmm0
				mulps (%edi), %xmm0
				addps %xmm0, %xmm1
				add $16, %esi
				add $16, %edi
				dec %ecx
				test %ecx, %ecx
				jnz .__uu1$
			movups %xmm1, (%ebx)
			pop %ecx
			pop %edi
			pop %esi
			
 # 0 "" 2
/NO_APP
	fsts	65536(%edx)
	leal	20480(%eax), %edi
/APP
 # 158 "jpeg.c" 1
				push %esi
			push %edi
			push %ecx
			movl %ecx, %edi
			movl %edi, %esi
			movups (%esi), %xmm1
			mov $16, %ecx
			.__uu1$:
				movups (%esi), %xmm0
				mulps (%edi), %xmm0
				addps %xmm0, %xmm1
				add $16, %esi
				add $16, %edi
				dec %ecx
				test %ecx, %ecx
				jnz .__uu1$
			movups %xmm1, (%ebx)
			pop %ecx
			pop %edi
			pop %esi
			
 # 0 "" 2
/NO_APP
	fsts	81920(%edx)
	leal	24576(%eax), %edi
/APP
 # 158 "jpeg.c" 1
				push %esi
			push %edi
			push %ecx
			movl %ecx, %edi
			movl %edi, %esi
			movups (%esi), %xmm1
			mov $16, %ecx
			.__uu1$:
				movups (%esi), %xmm0
				mulps (%edi), %xmm0
				addps %xmm0, %xmm1
				add $16, %esi
				add $16, %edi
				dec %ecx
				test %ecx, %ecx
				jnz .__uu1$
			movups %xmm1, (%ebx)
			pop %ecx
			pop %edi
			pop %esi
			
 # 0 "" 2
/NO_APP
	fsts	98304(%edx)
	leal	28672(%eax), %edi
/APP
 # 158 "jpeg.c" 1
				push %esi
			push %edi
			push %ecx
			movl %ecx, %edi
			movl %edi, %esi
			movups (%esi), %xmm1
			mov $16, %ecx
			.__uu1$:
				movups (%esi), %xmm0
				mulps (%edi), %xmm0
				addps %xmm0, %xmm1
				add $16, %esi
				add $16, %edi
				dec %ecx
				test %ecx, %ecx
				jnz .__uu1$
			movups %xmm1, (%ebx)
			pop %ecx
			pop %edi
			pop %esi
			
 # 0 "" 2
/NO_APP
	addl	$256, %eax
	fsts	114688(%edx)
	addl	$1024, %edx
	cmpl	$_sxx+2048, %eax
	jne	L32
	fstp	%st(0)
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.comm	_w, 4, 2
	.globl	_Imgsx
	.bss
	.align 4
_Imgsx:
	.space 4
	.globl	_Imgsy
	.align 4
_Imgsy:
	.space 4
	.text
	.globl	_draw
	.def	_draw;	.scl	2;	.type	32;	.endef
_draw:
	pushl	%ebp
	movl	%esp, %ebp
	popl	%ebp
	ret
	.comm	_comp, 64, 5
	.comm	_lcoef, 4, 2
	.comm	_lcoef1, 4, 2
	.comm	_lcoef2, 4, 2
	.globl	_prep
	.def	_prep;	.scl	2;	.type	32;	.endef
_prep:
	pushl	%ebp
	xorl	%edx, %edx
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$40, %esp
	movl	12(%ebp), %eax
	movl	(%eax), %edi
	movl	16(%ebp), %eax
	movzwl	(%eax), %esi
	movl	8(%ebp), %eax
	movl	_mcnt(,%eax,4), %eax
	movl	%eax, -20(%ebp)
	sall	$4, %eax
	addl	8(%ebp), %eax
	sall	$3, %eax
	movl	%eax, -16(%ebp)
L39:
	movswl	_zigzagx(%edx), %ecx
	movswl	_zigzagy(%edx), %ebx
	addl	$2, %edx
	movl	%ecx, %eax
	addl	-16(%ebp), %ecx
	sall	$4, %eax
	addl	%ebx, %eax
	sall	$4, %eax
	addl	-20(%ebp), %eax
	sall	$4, %eax
	addl	8(%ebp), %eax
	cmpl	$128, %edx
	movl	$0x00000000, _sx(,%eax,4)
	leal	(%ebx,%ecx,8), %eax
	movl	$0x00000000, _matrix(,%eax,4)
	jne	L39
	movl	8(%ebp), %eax
	movl	_comp(,%eax,4), %eax
	movl	%eax, -24(%ebp)
	sarl	$4, %eax
	andl	$15, %eax
	movl	_huffs(,%eax,8), %edx
	jmp	L40
L42:
	testl	%eax, %eax
	je	L70
L90:
	sarw	%si
	movl	%eax, %edx
L40:
	movl	8(%edx), %eax
	testl	%eax, %eax
	je	L89
L44:
	movl	20(%ebp), %ecx
	movl	%esi, %ebx
	testb	%bl, (%ecx,%edi)
	jne	L41
	movl	4(%edx), %eax
L41:
	cmpw	$1, %si
	jne	L42
	addl	$1, %edi
	testl	%eax, %eax
	movl	$256, %esi
	jne	L90
L70:
	addl	$40, %esp
	movl	$1, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L89:
	movl	4(%edx), %ecx
	testl	%ecx, %ecx
	jne	L44
	movl	20(%ebp), %eax
	movswl	(%edx), %ebx
	movzbl	(%eax,%edi), %eax
	testl	%ebx, %ebx
	movw	%bx, -28(%ebp)
	movl	%ebx, -16(%ebp)
	movb	%al, -32(%ebp)
	jle	L71
	movl	%eax, %edx
	xorl	%ecx, %ecx
	movl	%esi, %eax
	xorl	%ebx, %ebx
	jmp	L48
L91:
	sarw	%ax
	addl	$1, %ecx
	cmpl	-16(%ebp), %ecx
	je	L45
L92:
	movl	20(%ebp), %edx
	movzbl	(%edx,%edi), %edx
L48:
	testb	%al, %dl
	setne	%dl
	cmpw	$1, %ax
	movzbl	%dl, %edx
	leal	(%edx,%ebx,2), %ebx
	jne	L91
	addl	$1, %edi
	addl	$1, %ecx
	cmpl	-16(%ebp), %ecx
	movl	$128, %eax
	jne	L92
L45:
	movl	%esi, %ecx
	testb	%cl, -32(%ebp)
	jne	L49
	cmpw	$0, -28(%ebp)
	jle	L49
	movzbl	-16(%ebp), %ecx
	movl	$1, %edx
	sall	%cl, %edx
	subl	%edx, %ebx
	addl	$1, %ebx
L49:
	movl	8(%ebp), %esi
	testl	%esi, %esi
	jne	L50
	addl	_lcoef, %ebx
	movl	%ebx, _lcoef
L51:
	movl	-20(%ebp), %edx
	movswl	_zigzagx, %ecx
	movl	%ebx, -16(%ebp)
	fildl	-16(%ebp)
	sall	$4, %edx
	addl	8(%ebp), %edx
	sall	$8, %edx
	leal	_matrix(%edx), %esi
	movswl	_zigzagy, %edx
	movl	%esi, -32(%ebp)
	leal	(%edx,%ecx,8), %edx
	fstps	(%esi,%edx,4)
	movl	-24(%ebp), %edx
	movl	$1, -24(%ebp)
	andl	$15, %edx
	movl	_huffs+4(,%edx,8), %esi
	movl	%esi, -44(%ebp)
L68:
	movl	-44(%ebp), %edx
	movl	8(%edx), %ecx
	testl	%ecx, %ecx
	je	L93
L57:
	movl	20(%ebp), %esi
	testb	%al, (%esi,%edi)
	jne	L54
	movl	4(%edx), %ecx
L54:
	cmpw	$1, %ax
	je	L55
	sarw	%ax
	movl	%ecx, %edx
L98:
	movl	8(%edx), %ecx
	testl	%ecx, %ecx
	jne	L57
L93:
	movl	4(%edx), %ebx
	testl	%ebx, %ebx
	jne	L57
	movzwl	(%edx), %ecx
	testw	%cx, %cx
	je	L94
	movl	-24(%ebp), %esi
	cmpw	$15, %cx
	movl	%esi, -16(%ebp)
	jg	L61
	jmp	L60
L95:
	cmpl	$63, -16(%ebp)
	jg	L60
L61:
	movl	-16(%ebp), %ebx
	addl	$1, -16(%ebp)
	movswl	_zigzagx(%ebx,%ebx), %esi
	movswl	_zigzagy(%ebx,%ebx), %ecx
	movl	-32(%ebp), %ebx
	leal	(%ecx,%esi,8), %ecx
	movl	$0x00000000, (%ebx,%ecx,4)
	movzwl	(%edx), %ecx
	movl	-16(%ebp), %ebx
	subl	-24(%ebp), %ebx
	movl	%ecx, %esi
	sarw	$4, %si
	movswl	%si, %esi
	cmpl	%ebx, %esi
	jg	L95
L60:
	movl	20(%ebp), %ebx
	movswl	%ax, %esi
	movl	%esi, -36(%ebp)
	movzbl	(%ebx,%edi), %ebx
	movl	%ebx, -24(%ebp)
	andl	%esi, %ebx
	movl	%ebx, -40(%ebp)
	movl	%ecx, %ebx
	andl	$15, %ebx
	movl	%ebx, -28(%ebp)
	je	L73
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	jmp	L66
L96:
	sarw	%ax
	addl	$1, %ecx
	cmpl	%ecx, -28(%ebp)
	movswl	%ax, %esi
	movl	%esi, -36(%ebp)
	je	L63
L97:
	movl	20(%ebp), %ebx
	movswl	%ax, %esi
	movzbl	(%ebx,%edi), %ebx
	movl	%ebx, -24(%ebp)
L66:
	xorl	%ebx, %ebx
	testl	%esi, -24(%ebp)
	setne	%bl
	cmpw	$1, %ax
	movl	%ebx, %esi
	leal	(%esi,%edx,2), %edx
	jne	L96
	addl	$1, %edi
	addl	$1, %ecx
	cmpl	%ecx, -28(%ebp)
	movl	$128, -36(%ebp)
	movl	$128, %eax
	jne	L97
L63:
	movl	-40(%ebp), %ecx
	testl	%ecx, %ecx
	jne	L67
	movzbl	-28(%ebp), %ecx
	movl	$1, %esi
	sall	%cl, %esi
	subl	%esi, %edx
	addl	$1, %edx
L67:
	movl	-16(%ebp), %ebx
	cmpl	$64, %ebx
	je	L59
	movswl	_zigzagx(%ebx,%ebx), %esi
	movswl	_zigzagy(%ebx,%ebx), %ecx
	movl	%edx, -16(%ebp)
	fildl	-16(%ebp)
	leal	(%ecx,%esi,8), %ecx
	movl	-32(%ebp), %esi
	fstps	(%esi,%ecx,4)
	movl	%ebx, %esi
	addl	$1, %esi
	cmpl	$64, %esi
	movl	%esi, -24(%ebp)
	jne	L68
L59:
	movl	8(%ebp), %esi
	movl	-32(%ebp), %eax
	movzbl	_dct(%esi,%esi), %edx
	leal	32(%eax), %ebx
	addl	$_quant, %edx
L69:
	movzbl	(%edx), %ecx
	addl	$4, %eax
	addl	$16, %edx
	movl	%ecx, -16(%ebp)
	movzbl	240(%edx), %ecx
	fildl	-16(%ebp)
	fmuls	-4(%eax)
	movl	%ecx, -16(%ebp)
	movzbl	496(%edx), %ecx
	fstps	-4(%eax)
	fildl	-16(%ebp)
	movl	%ecx, -16(%ebp)
	movzbl	752(%edx), %ecx
	fmuls	28(%eax)
	fstps	28(%eax)
	fildl	-16(%ebp)
	movl	%ecx, -16(%ebp)
	movzbl	1008(%edx), %ecx
	fmuls	60(%eax)
	fstps	60(%eax)
	fildl	-16(%ebp)
	movl	%ecx, -16(%ebp)
	movzbl	1264(%edx), %ecx
	fmuls	92(%eax)
	fstps	92(%eax)
	fildl	-16(%ebp)
	movl	%ecx, -16(%ebp)
	movzbl	1520(%edx), %ecx
	fmuls	124(%eax)
	fstps	124(%eax)
	fildl	-16(%ebp)
	movl	%ecx, -16(%ebp)
	fmuls	156(%eax)
	fstps	156(%eax)
	fildl	-16(%ebp)
	movzbl	1776(%edx), %ecx
	fmuls	188(%eax)
	movl	%ecx, -16(%ebp)
	fstps	188(%eax)
	fildl	-16(%ebp)
	fmuls	220(%eax)
	fstps	220(%eax)
	cmpl	%ebx, %eax
	jne	L69
	movl	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_preo
	movl	8(%ebp), %eax
	movl	-36(%ebp), %esi
	addl	$1, _mcnt(,%eax,4)
	movl	16(%ebp), %eax
	movl	%esi, (%eax)
	movl	12(%ebp), %eax
	movl	%edi, (%eax)
	movl	8(%ebp), %eax
	movl	8(%ebp), %edi
	movzwl	_dct(%eax,%eax), %eax
	movl	%eax, %edx
	sarw	$8, %ax
	shrw	$12, %dx
	andl	$15, %eax
	movswl	%dx, %edx
	imull	%edx, %eax
	cmpl	_mcnt(,%edi,4), %eax
	sete	%al
	addl	$40, %esp
	popl	%ebx
	movzbl	%al, %eax
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L55:
	addl	$1, %edi
	movl	$128, %eax
	movl	%ecx, %edx
	jmp	L98
L73:
	xorl	%edx, %edx
	jmp	L63
L50:
	cmpl	$1, 8(%ebp)
	jne	L52
	addl	_lcoef1, %ebx
	movl	%ebx, _lcoef1
	jmp	L51
L94:
	cwtl
	movl	%eax, -36(%ebp)
	jmp	L59
L52:
	cmpl	$2, 8(%ebp)
	jne	L51
	addl	_lcoef2, %ebx
	movl	%ebx, _lcoef2
	jmp	L51
L71:
	movl	%esi, %eax
	xorl	%ebx, %ebx
	jmp	L45
	.def	___main;	.scl	2;	.type	32;	.endef
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	call	___main
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__zzk
	nop
	leave
	ret
	.section .rdata,"dr"
LC9:
	.ascii "rb\0"
LC10:
	.ascii "Can't find file %s!\12\0"
	.text
	.globl	__zzk
	.def	__zzk;	.scl	2;	.type	32;	.endef
__zzk:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$188, %esp
	movl	12(%ebp), %ebx
	movl	$LC9, 4(%esp)
	movl	4(%ebx), %eax
	movl	%eax, (%esp)
	call	_fopen
	testl	%eax, %eax
	movl	%eax, -168(%ebp)
	je	L252
	movl	%eax, %esi
	movl	$2, 8(%esp)
	movl	$0, 4(%esp)
	movl	%eax, (%esp)
	xorl	%edi, %edi
	call	_fseek
	movl	%esi, (%esp)
	call	_ftell
	movl	%esi, (%esp)
	movl	%eax, -184(%ebp)
	call	_rewind
	leal	-106(%ebp), %eax
	movl	%esi, 12(%esp)
	movl	$2, 8(%esp)
	movl	$1, 4(%esp)
	movw	%di, -106(%ebp)
	movl	%eax, (%esp)
	call	_fread
	cmpw	$-9985, -106(%ebp)
	je	L253
L102:
L100:
	addl	$188, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L253:
	movl	$_zigzag_table8, %ebx
	xorl	%edx, %edx
	xorl	%eax, %eax
	movl	%ebx, %ecx
	jmp	L125
L255:
	testl	%edx, %edx
	je	L106
	leal	-1(%edx), %esi
	cmpl	$7, %esi
	ja	L116
	addl	$1, %eax
	cmpl	$1, %edx
	movb	%al, -8(%ebx)
	je	L106
L116:
	leal	-2(%edx), %esi
	cmpl	$7, %esi
	ja	L118
	addl	$1, %eax
	cmpl	$2, %edx
	movb	%al, -15(%ebx)
	je	L106
L118:
	leal	-3(%edx), %esi
	cmpl	$7, %esi
	ja	L119
	addl	$1, %eax
	cmpl	$3, %edx
	movb	%al, -22(%ebx)
	je	L106
L119:
	leal	-4(%edx), %esi
	cmpl	$7, %esi
	ja	L120
	addl	$1, %eax
	cmpl	$4, %edx
	movb	%al, -29(%ebx)
	je	L106
L120:
	leal	-5(%edx), %esi
	cmpl	$7, %esi
	ja	L121
	addl	$1, %eax
	cmpl	$5, %edx
	movb	%al, -36(%ebx)
	je	L106
L121:
	leal	-6(%edx), %esi
	cmpl	$7, %esi
	ja	L122
	addl	$1, %eax
	cmpl	$6, %edx
	movb	%al, -43(%ebx)
	je	L106
L122:
	leal	-7(%edx), %esi
	cmpl	$7, %esi
	ja	L123
	addl	$1, %eax
	cmpl	$7, %edx
	movb	%al, -50(%ebx)
	je	L106
L123:
	leal	-8(%edx), %esi
	cmpl	$7, %esi
	ja	L106
	addl	$1, %eax
	movb	%al, -57(%ebx)
L106:
	addl	$1, %edx
	addl	$8, %ebx
	addl	$1, %ecx
	cmpl	$16, %edx
	je	L254
L125:
	testb	$1, %dl
	je	L255
	leal	-1(%edx), %esi
	cmpl	$7, %esi
	ja	L107
	addl	$1, %eax
	cmpl	$1, %edx
	movb	%al, -1(%ecx)
	je	L106
L107:
	leal	-2(%edx), %esi
	cmpl	$7, %esi
	ja	L109
	addl	$1, %eax
	cmpl	$2, %edx
	movb	%al, 6(%ecx)
	je	L106
L109:
	leal	-3(%edx), %esi
	cmpl	$7, %esi
	ja	L110
	addl	$1, %eax
	cmpl	$3, %edx
	movb	%al, 13(%ecx)
	je	L106
L110:
	leal	-4(%edx), %esi
	cmpl	$7, %esi
	ja	L111
	addl	$1, %eax
	cmpl	$4, %edx
	movb	%al, 20(%ecx)
	je	L106
L111:
	leal	-5(%edx), %esi
	cmpl	$7, %esi
	ja	L112
	addl	$1, %eax
	cmpl	$5, %edx
	movb	%al, 27(%ecx)
	je	L106
L112:
	leal	-6(%edx), %esi
	cmpl	$7, %esi
	ja	L113
	addl	$1, %eax
	cmpl	$6, %edx
	movb	%al, 34(%ecx)
	je	L106
L113:
	leal	-7(%edx), %esi
	cmpl	$7, %esi
	ja	L114
	addl	$1, %eax
	cmpl	$7, %edx
	movb	%al, 41(%ecx)
	je	L106
L114:
	leal	-8(%edx), %esi
	cmpl	$7, %esi
	ja	L106
	addl	$1, %eax
	addl	$1, %edx
	addl	$8, %ebx
	movb	%al, 48(%ecx)
	addl	$1, %ecx
	cmpl	$16, %edx
	jne	L125
L254:
	movzbl	_zigzag_table8, %eax
	xorl	%edx, %edx
	xorl	%ecx, %ecx
	xorl	%esi, %esi
	movl	$1, %ebx
	movl	$2, %edi
	subl	$1, %eax
	movw	%dx, _zigzagx(%eax,%eax)
	movw	%cx, _zigzagy(%eax,%eax)
	xorl	%edx, %edx
	movzbl	_zigzag_table8+8, %eax
	movl	$3, %ecx
	subl	$1, %eax
	movw	%bx, _zigzagx(%eax,%eax)
	movw	%si, _zigzagy(%eax,%eax)
	xorl	%ebx, %ebx
	movzbl	_zigzag_table8+16, %eax
	movl	$4, %esi
	subl	$1, %eax
	movw	%di, _zigzagx(%eax,%eax)
	movw	%dx, _zigzagy(%eax,%eax)
	xorl	%edi, %edi
	movzbl	_zigzag_table8+24, %eax
	movl	$5, %edx
	subl	$1, %eax
	movw	%cx, _zigzagx(%eax,%eax)
	movw	%bx, _zigzagy(%eax,%eax)
	xorl	%ecx, %ecx
	movzbl	_zigzag_table8+32, %eax
	movl	$6, %ebx
	subl	$1, %eax
	movw	%si, _zigzagx(%eax,%eax)
	movw	%di, _zigzagy(%eax,%eax)
	xorl	%esi, %esi
	movzbl	_zigzag_table8+40, %eax
	movl	$7, %edi
	subl	$1, %eax
	movw	%dx, _zigzagx(%eax,%eax)
	movw	%cx, _zigzagy(%eax,%eax)
	xorl	%edx, %edx
	movzbl	_zigzag_table8+48, %eax
	xorl	%ecx, %ecx
	subl	$1, %eax
	movw	%bx, _zigzagx(%eax,%eax)
	movw	%si, _zigzagy(%eax,%eax)
	movl	$1, %ebx
	movzbl	_zigzag_table8+56, %eax
	movl	$1, %esi
	subl	$1, %eax
	movw	%di, _zigzagx(%eax,%eax)
	movw	%dx, _zigzagy(%eax,%eax)
	movl	$1, %edi
	movzbl	_zigzag_table8+1, %eax
	movl	$2, %edx
	subl	$1, %eax
	movw	%cx, _zigzagx(%eax,%eax)
	movw	%bx, _zigzagy(%eax,%eax)
	movl	$1, %ecx
	movzbl	_zigzag_table8+9, %eax
	movl	$3, %ebx
	subl	$1, %eax
	movw	%si, _zigzagx(%eax,%eax)
	movw	%di, _zigzagy(%eax,%eax)
	movl	$1, %esi
	movzbl	_zigzag_table8+17, %eax
	movl	$4, %edi
	subl	$1, %eax
	movw	%dx, _zigzagx(%eax,%eax)
	movw	%cx, _zigzagy(%eax,%eax)
	movl	$1, %edx
	movzbl	_zigzag_table8+25, %eax
	movl	$5, %ecx
	subl	$1, %eax
	movw	%bx, _zigzagx(%eax,%eax)
	movw	%si, _zigzagy(%eax,%eax)
	movl	$1, %ebx
	movzbl	_zigzag_table8+33, %eax
	movl	$6, %esi
	subl	$1, %eax
	movw	%di, _zigzagx(%eax,%eax)
	movw	%dx, _zigzagy(%eax,%eax)
	movl	$1, %edi
	movzbl	_zigzag_table8+41, %eax
	movl	$7, %edx
	subl	$1, %eax
	movw	%cx, _zigzagx(%eax,%eax)
	movw	%bx, _zigzagy(%eax,%eax)
	movl	$1, %ecx
	movzbl	_zigzag_table8+49, %eax
	xorl	%ebx, %ebx
	subl	$1, %eax
	movw	%si, _zigzagx(%eax,%eax)
	movw	%di, _zigzagy(%eax,%eax)
	movl	$2, %esi
	movzbl	_zigzag_table8+57, %eax
	movl	$1, %edi
	subl	$1, %eax
	movw	%dx, _zigzagx(%eax,%eax)
	movw	%cx, _zigzagy(%eax,%eax)
	movl	$2, %edx
	movzbl	_zigzag_table8+2, %eax
	movl	$2, %ecx
	subl	$1, %eax
	movw	%bx, _zigzagx(%eax,%eax)
	movw	%si, _zigzagy(%eax,%eax)
	movl	$2, %ebx
	movzbl	_zigzag_table8+10, %eax
	movl	$3, %esi
	subl	$1, %eax
	movw	%di, _zigzagx(%eax,%eax)
	movw	%dx, _zigzagy(%eax,%eax)
	movl	$2, %edi
	movzbl	_zigzag_table8+18, %eax
	movl	$4, %edx
	subl	$1, %eax
	movw	%cx, _zigzagx(%eax,%eax)
	movw	%bx, _zigzagy(%eax,%eax)
	movl	$2, %ecx
	movzbl	_zigzag_table8+26, %eax
	movl	$5, %ebx
	subl	$1, %eax
	movw	%si, _zigzagx(%eax,%eax)
	movw	%di, _zigzagy(%eax,%eax)
	movl	$2, %esi
	movzbl	_zigzag_table8+34, %eax
	movl	$6, %edi
	subl	$1, %eax
	movw	%dx, _zigzagx(%eax,%eax)
	movw	%cx, _zigzagy(%eax,%eax)
	movl	$2, %edx
	movzbl	_zigzag_table8+42, %eax
	movl	$7, %ecx
	subl	$1, %eax
	movw	%bx, _zigzagx(%eax,%eax)
	movw	%si, _zigzagy(%eax,%eax)
	movl	$2, %ebx
	movzbl	_zigzag_table8+50, %eax
	xorl	%esi, %esi
	subl	$1, %eax
	movw	%di, _zigzagx(%eax,%eax)
	movw	%dx, _zigzagy(%eax,%eax)
	movl	$3, %edi
	movzbl	_zigzag_table8+58, %eax
	movl	$1, %edx
	subl	$1, %eax
	movw	%cx, _zigzagx(%eax,%eax)
	movw	%bx, _zigzagy(%eax,%eax)
	movl	$3, %ecx
	movzbl	_zigzag_table8+3, %eax
	movl	$2, %ebx
	subl	$1, %eax
	movw	%si, _zigzagx(%eax,%eax)
	movw	%di, _zigzagy(%eax,%eax)
	movl	$3, %esi
	movzbl	_zigzag_table8+11, %eax
	movl	$3, %edi
	subl	$1, %eax
	movw	%dx, _zigzagx(%eax,%eax)
	movw	%cx, _zigzagy(%eax,%eax)
	movl	$3, %edx
	movzbl	_zigzag_table8+19, %eax
	movl	$4, %ecx
	subl	$1, %eax
	movw	%bx, _zigzagx(%eax,%eax)
	movw	%si, _zigzagy(%eax,%eax)
	movl	$3, %ebx
	movzbl	_zigzag_table8+27, %eax
	movl	$5, %esi
	subl	$1, %eax
	movw	%di, _zigzagx(%eax,%eax)
	movw	%dx, _zigzagy(%eax,%eax)
	movl	$3, %edi
	movzbl	_zigzag_table8+35, %eax
	movl	$6, %edx
	subl	$1, %eax
	movw	%cx, _zigzagx(%eax,%eax)
	movw	%bx, _zigzagy(%eax,%eax)
	movl	$3, %ecx
	movzbl	_zigzag_table8+43, %eax
	movl	$7, %ebx
	subl	$1, %eax
	movw	%si, _zigzagx(%eax,%eax)
	movw	%di, _zigzagy(%eax,%eax)
	movl	$3, %esi
	movzbl	_zigzag_table8+51, %eax
	xorl	%edi, %edi
	subl	$1, %eax
	movw	%dx, _zigzagx(%eax,%eax)
	movw	%cx, _zigzagy(%eax,%eax)
	movl	$4, %edx
	movzbl	_zigzag_table8+59, %eax
	movl	$1, %ecx
	subl	$1, %eax
	movw	%bx, _zigzagx(%eax,%eax)
	movw	%si, _zigzagy(%eax,%eax)
	movl	$4, %ebx
	movzbl	_zigzag_table8+4, %eax
	movl	$2, %esi
	subl	$1, %eax
	movw	%di, _zigzagx(%eax,%eax)
	movw	%dx, _zigzagy(%eax,%eax)
	movl	$4, %edi
	movzbl	_zigzag_table8+12, %eax
	movl	$3, %edx
	subl	$1, %eax
	movw	%cx, _zigzagx(%eax,%eax)
	movw	%bx, _zigzagy(%eax,%eax)
	movl	$4, %ecx
	movzbl	_zigzag_table8+20, %eax
	movl	$4, %ebx
	subl	$1, %eax
	movw	%si, _zigzagx(%eax,%eax)
	movw	%di, _zigzagy(%eax,%eax)
	movl	$4, %esi
	movzbl	_zigzag_table8+28, %eax
	movl	$5, %edi
	subl	$1, %eax
	movw	%dx, _zigzagx(%eax,%eax)
	movw	%cx, _zigzagy(%eax,%eax)
	movl	$4, %edx
	movzbl	_zigzag_table8+36, %eax
	movl	$6, %ecx
	subl	$1, %eax
	movw	%bx, _zigzagx(%eax,%eax)
	movw	%si, _zigzagy(%eax,%eax)
	movl	$4, %ebx
	movzbl	_zigzag_table8+44, %eax
	movl	$7, %esi
	subl	$1, %eax
	movw	%di, _zigzagx(%eax,%eax)
	movw	%dx, _zigzagy(%eax,%eax)
	movl	$4, %edi
	movzbl	_zigzag_table8+52, %eax
	xorl	%edx, %edx
	subl	$1, %eax
	movw	%cx, _zigzagx(%eax,%eax)
	movw	%bx, _zigzagy(%eax,%eax)
	movl	$5, %ecx
	movzbl	_zigzag_table8+60, %eax
	movl	$1, %ebx
	subl	$1, %eax
	movw	%si, _zigzagx(%eax,%eax)
	movw	%di, _zigzagy(%eax,%eax)
	movl	$5, %esi
	movzbl	_zigzag_table8+5, %eax
	movl	$2, %edi
	subl	$1, %eax
	movw	%dx, _zigzagx(%eax,%eax)
	movw	%cx, _zigzagy(%eax,%eax)
	movl	$5, %edx
	movzbl	_zigzag_table8+13, %eax
	movl	$3, %ecx
	subl	$1, %eax
	movw	%bx, _zigzagx(%eax,%eax)
	movw	%si, _zigzagy(%eax,%eax)
	movl	$5, %ebx
	movzbl	_zigzag_table8+21, %eax
	movl	$4, %esi
	subl	$1, %eax
	movw	%di, _zigzagx(%eax,%eax)
	movw	%dx, _zigzagy(%eax,%eax)
	movl	$5, %edi
	movzbl	_zigzag_table8+29, %eax
	movl	$5, %edx
	subl	$1, %eax
	movw	%cx, _zigzagx(%eax,%eax)
	movw	%bx, _zigzagy(%eax,%eax)
	movl	$5, %ecx
	movzbl	_zigzag_table8+37, %eax
	movl	$6, %ebx
	subl	$1, %eax
	movw	%si, _zigzagx(%eax,%eax)
	movw	%di, _zigzagy(%eax,%eax)
	movl	$5, %esi
	movzbl	_zigzag_table8+45, %eax
	movl	$7, %edi
	subl	$1, %eax
	movw	%dx, _zigzagx(%eax,%eax)
	movw	%cx, _zigzagy(%eax,%eax)
	movl	$5, %edx
	movzbl	_zigzag_table8+53, %eax
	xorl	%ecx, %ecx
	subl	$1, %eax
	movw	%bx, _zigzagx(%eax,%eax)
	movw	%si, _zigzagy(%eax,%eax)
	movl	$6, %ebx
	movzbl	_zigzag_table8+61, %eax
	movl	$1, %esi
	subl	$1, %eax
	movw	%di, _zigzagx(%eax,%eax)
	movw	%dx, _zigzagy(%eax,%eax)
	movl	$6, %edi
	movzbl	_zigzag_table8+6, %eax
	movl	$2, %edx
	subl	$1, %eax
	movw	%cx, _zigzagx(%eax,%eax)
	movw	%bx, _zigzagy(%eax,%eax)
	movl	$6, %ecx
	movzbl	_zigzag_table8+14, %eax
	movl	$3, %ebx
	subl	$1, %eax
	movw	%si, _zigzagx(%eax,%eax)
	movw	%di, _zigzagy(%eax,%eax)
	movl	$6, %esi
	movzbl	_zigzag_table8+22, %eax
	movl	$4, %edi
	subl	$1, %eax
	movw	%dx, _zigzagx(%eax,%eax)
	movw	%cx, _zigzagy(%eax,%eax)
	movl	$6, %edx
	movzbl	_zigzag_table8+30, %eax
	movl	$5, %ecx
	subl	$1, %eax
	movw	%bx, _zigzagx(%eax,%eax)
	movw	%si, _zigzagy(%eax,%eax)
	movl	$6, %ebx
	movzbl	_zigzag_table8+38, %eax
	movl	$6, %esi
	subl	$1, %eax
	movw	%di, _zigzagx(%eax,%eax)
	movw	%dx, _zigzagy(%eax,%eax)
	movl	$6, %edi
	movzbl	_zigzag_table8+46, %eax
	movl	$7, %edx
	subl	$1, %eax
	movw	%cx, _zigzagx(%eax,%eax)
	movw	%bx, _zigzagy(%eax,%eax)
	movl	$6, %ecx
	movzbl	_zigzag_table8+54, %eax
	xorl	%ebx, %ebx
	subl	$1, %eax
	movw	%si, _zigzagx(%eax,%eax)
	movw	%di, _zigzagy(%eax,%eax)
	movl	$7, %esi
	movzbl	_zigzag_table8+62, %eax
	movl	$1, %edi
	flds	LC11
	fstpl	(%esp)
	subl	$1, %eax
	movw	%dx, _zigzagx(%eax,%eax)
	movw	%cx, _zigzagy(%eax,%eax)
	movl	$7, %edx
	movzbl	_zigzag_table8+7, %eax
	movl	$2, %ecx
	subl	$1, %eax
	movw	%bx, _zigzagx(%eax,%eax)
	movw	%si, _zigzagy(%eax,%eax)
	movl	$7, %ebx
	movzbl	_zigzag_table8+15, %eax
	movl	$3, %esi
	subl	$1, %eax
	movw	%di, _zigzagx(%eax,%eax)
	movw	%dx, _zigzagy(%eax,%eax)
	movl	$7, %edi
	movzbl	_zigzag_table8+23, %eax
	movl	$4, %edx
	subl	$1, %eax
	movw	%cx, _zigzagx(%eax,%eax)
	movw	%bx, _zigzagy(%eax,%eax)
	movl	$7, %ecx
	movzbl	_zigzag_table8+31, %eax
	movl	$5, %ebx
	subl	$1, %eax
	movw	%si, _zigzagx(%eax,%eax)
	movw	%di, _zigzagy(%eax,%eax)
	movl	$7, %esi
	movzbl	_zigzag_table8+39, %eax
	movl	$6, %edi
	subl	$1, %eax
	movw	%dx, _zigzagx(%eax,%eax)
	movw	%cx, _zigzagy(%eax,%eax)
	movl	$7, %edx
	movzbl	_zigzag_table8+47, %eax
	movl	$7, %ecx
	subl	$1, %eax
	movw	%bx, _zigzagx(%eax,%eax)
	movw	%si, _zigzagy(%eax,%eax)
	movl	$7, %ebx
	movzbl	_zigzag_table8+55, %eax
	subl	$1, %eax
	movw	%di, _zigzagx(%eax,%eax)
	movw	%dx, _zigzagy(%eax,%eax)
	movzbl	_zigzag_table8+63, %eax
	subl	$1, %eax
	movw	%cx, _zigzagx(%eax,%eax)
	movw	%bx, _zigzagy(%eax,%eax)
	call	_sqrt
	fmuls	LC12
	movl	$1, -164(%ebp)
	movl	-164(%ebp), %eax
	fstpl	-176(%ebp)
L126:
	addl	$2097151, %eax
	movl	$1, -136(%ebp)
	sall	$11, %eax
	movl	%eax, -180(%ebp)
L133:
	movl	-180(%ebp), %esi
	movl	$0, -160(%ebp)
	movl	$0, -156(%ebp)
L131:
	fildl	-160(%ebp)
	movl	-156(%ebp), %edi
	fstpl	-144(%ebp)
	testl	%edi, %edi
	fld1
	fldl	-176(%ebp)
	fcmovne	%st(1), %st
	fstp	%st(1)
	xorl	%ebx, %ebx
	xorl	%edi, %edi
	fstpl	-152(%ebp)
L128:
	testl	%edi, %edi
	je	L173
	fld1
	fstpl	-128(%ebp)
L127:
	fldl	-144(%ebp)
	fmull	_pi
	fstpl	(%esp)
	call	_cos
	fmull	-128(%ebp)
	movl	%ebx, -132(%ebp)
	fstpl	-128(%ebp)
	fildl	-132(%ebp)
	fmull	_pi
	fstpl	(%esp)
	call	_cos
	fmull	-152(%ebp)
	addl	-136(%ebp), %ebx
	fmull	-128(%ebp)
	fstps	_sxx(%esi,%edi,4)
	addl	$1, %edi
	cmpl	$8, %edi
	jne	L128
	addl	$1, -156(%ebp)
	movl	-164(%ebp), %edx
	addl	$32, %esi
	movl	-156(%ebp), %eax
	addl	%edx, -160(%ebp)
	cmpl	$8, %eax
	jne	L131
	addl	$2, -136(%ebp)
	addl	$256, -180(%ebp)
	movl	-136(%ebp), %eax
	cmpl	$17, %eax
	jne	L133
	addl	$2, -164(%ebp)
	movl	-164(%ebp), %eax
	cmpl	$17, %eax
	jne	L126
L132:
	movl	-168(%ebp), %esi
	movl	%esi, (%esp)
	call	_ftell
	cmpl	%eax, -184(%ebp)
	jle	L100
	leal	-106(%ebp), %eax
	movl	%esi, 12(%esp)
	movl	$1, 8(%esp)
	movl	$2, 4(%esp)
	movl	%eax, (%esp)
	call	_fread
	movzwl	-106(%ebp), %eax
	movl	%eax, (%esp)
	call	_bswap16
	cmpw	$-2, %ax
	movw	%ax, -106(%ebp)
	je	L256
	cmpw	$-37, %ax
	je	L257
	cmpw	$-64, %ax
	je	L258
	cmpw	$-60, %ax
	je	L259
	cmpw	$-38, %ax
	jne	L132
	movl	-168(%ebp), %esi
	leal	-104(%ebp), %eax
	movl	$1, 8(%esp)
	movl	$2, 4(%esp)
	movl	$0, -104(%ebp)
	movl	%eax, (%esp)
	movl	%esi, 12(%esp)
	call	_fread
	movzwl	-104(%ebp), %eax
	movl	%eax, (%esp)
	call	_bswap16
	movzwl	%ax, %eax
	movl	%esi, 12(%esp)
	movl	$1, 8(%esp)
	movl	%eax, -104(%ebp)
	leal	-100(%ebp), %eax
	movl	$1, 4(%esp)
	movl	$0, -100(%ebp)
	movl	%eax, (%esp)
	call	_fread
	movl	$9, (%esp)
	call	_malloc
	movl	-100(%ebp), %eax
	testl	%eax, %eax
	jle	L260
	leal	-88(%ebp), %eax
	xorl	%ebx, %ebx
	movl	%eax, -144(%ebp)
L158:
	movl	-168(%ebp), %eax
	movl	$1, 8(%esp)
	movl	$2, 4(%esp)
	movl	%eax, 12(%esp)
	movl	-144(%ebp), %eax
	movl	%eax, (%esp)
	call	_fread
	movl	-88(%ebp), %eax
	sarl	$8, %eax
	movl	%eax, _comp(,%ebx,4)
	movl	-100(%ebp), %eax
	addl	$1, %ebx
	cmpl	%ebx, %eax
	jg	L158
L157:
	movl	-104(%ebp), %edx
	negl	%eax
	movl	-168(%ebp), %esi
	movl	$1, 8(%esp)
	xorl	%edi, %edi
	leal	-3(%edx,%eax,2), %eax
	movl	%esi, 12(%esp)
	movl	%eax, 4(%esp)
	movl	-144(%ebp), %eax
	movl	%eax, (%esp)
	call	_fread
	movl	%esi, (%esp)
	call	_ftell
	movl	$262144, (%esp)
	call	_malloc
	movl	%esi, 12(%esp)
	movl	$1, 8(%esp)
	xorl	%esi, %esi
	movl	$262144, 4(%esp)
	movl	%eax, (%esp)
	movl	%eax, -132(%ebp)
	call	_fread
	movl	$262144, (%esp)
	call	_malloc
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	%eax, %ebx
	movl	%eax, (%esp)
	call	_memcpy
	movl	$262144, -128(%ebp)
	movl	$0, -144(%ebp)
L159:
	movl	-144(%ebp), %ecx
	movl	-132(%ebp), %eax
	movl	$262144, 8(%esp)
	addl	%ebx, %ecx
	movl	%eax, 4(%esp)
	movl	%ecx, (%esp)
	call	_memcpy
	movl	-132(%ebp), %eax
	leal	262144(%edi), %edx
	subl	%edi, %eax
	jmp	L164
L162:
	addl	$1, %edi
	movzbl	%cl, %esi
	cmpl	%edx, %edi
	je	L261
L164:
	cmpl	$255, %esi
	movzbl	(%eax,%edi), %ecx
	jne	L162
	cmpb	$-39, %cl
	jne	L162
	leal	-1(%edi), %esi
	addl	$1, %edi
	movl	%edi, (%esp)
	call	_malloc
	testl	%esi, %esi
	movl	%eax, %edi
	movl	$0, -128(%ebp)
	jle	L166
	xorl	%eax, %eax
	jmp	L168
L167:
	addl	$1, %eax
	addl	$1, -128(%ebp)
	cmpl	%eax, %esi
	jle	L166
L168:
	leal	(%ebx,%eax), %ecx
	movl	-128(%ebp), %edx
	movl	%ecx, -132(%ebp)
	movzbl	(%ecx), %ecx
	movb	%cl, (%edi,%edx)
	movl	-132(%ebp), %ecx
	cmpb	$-1, (%ecx)
	jne	L167
	cmpb	$0, 1(%ebx,%eax)
	jne	L167
	cmpl	%eax, %esi
	setg	%dl
	cmpb	$1, %dl
	sbbl	$-1, %eax
	addl	$1, -128(%ebp)
	addl	$1, %eax
	cmpl	%eax, %esi
	jg	L168
L166:
	movl	%ebx, (%esp)
	leal	-96(%ebp), %esi
	call	_free
	movl	-100(%ebp), %eax
	movl	$128, -96(%ebp)
	xorl	%edx, %edx
	movl	$0, -92(%ebp)
L169:
	testl	%eax, %eax
	movl	$0, _mcnt
	movl	$0, _mcnt+4
	movl	$0, _mcnt+8
	movl	$0, _mcnt+12
	movl	$0, _mcnt+16
	movl	$0, _mcnt+20
	movl	$0, _mcnt+24
	movl	$0, _mcnt+28
	movl	$0, _mcnt+32
	movl	$0, _mcnt+36
	movl	$0, _mcnt+40
	movl	$0, _mcnt+44
	movl	$0, _mcnt+48
	movl	$0, _mcnt+52
	movl	$0, _mcnt+56
	movl	$0, _mcnt+60
	jle	L170
	xorl	%ebx, %ebx
L171:
	leal	-92(%ebp), %eax
	movl	%edi, 12(%esp)
	movl	%esi, 8(%esp)
	movl	%ebx, (%esp)
	movl	%eax, 4(%esp)
	call	_prep
	testl	%eax, %eax
	je	L171
	movl	-100(%ebp), %eax
	addl	$1, %ebx
	cmpl	%ebx, %eax
	jg	L171
	movl	-92(%ebp), %edx
L170:
	cmpl	%edx, -128(%ebp)
	jg	L169
	jmp	L132
L261:
	movl	-168(%ebp), %eax
	movl	$1, 8(%esp)
	movl	$262144, 4(%esp)
	movl	%edx, -136(%ebp)
	movl	%eax, 12(%esp)
	movl	-132(%ebp), %eax
	movl	%eax, (%esp)
	call	_fread
	addl	$262144, -128(%ebp)
	movl	-128(%ebp), %edi
	movl	%edi, (%esp)
	call	_malloc
	leal	-262144(%edi), %ecx
	movl	%eax, %edx
	movl	%ebx, 4(%esp)
	movl	%edx, (%esp)
	movl	%eax, -152(%ebp)
	movl	%ecx, 8(%esp)
	movl	%ecx, -144(%ebp)
	call	_memcpy
	testl	%ebx, %ebx
	movl	-136(%ebp), %edx
	je	L160
	movl	%ebx, (%esp)
	call	_free
	movl	-136(%ebp), %edx
L160:
	movl	%edx, %edi
	movl	-152(%ebp), %ebx
	jmp	L159
L173:
	fldl	-176(%ebp)
	fstpl	-128(%ebp)
	jmp	L127
L257:
	movl	-168(%ebp), %esi
	leal	-106(%ebp), %eax
	movl	$1, 8(%esp)
	movl	$2, 4(%esp)
	movl	%eax, (%esp)
	movl	%esi, 12(%esp)
	call	_fread
	movzwl	-106(%ebp), %eax
	movl	%eax, (%esp)
	call	_bswap16
	leal	-88(%ebp), %ecx
	subl	$3, %eax
	movl	%esi, 12(%esp)
	movl	$1, 8(%esp)
	movl	$1, 4(%esp)
	movl	%ecx, (%esp)
	movl	%esi, -168(%ebp)
	movw	%ax, -106(%ebp)
	movl	$0, -88(%ebp)
	call	_fread
	movzwl	-106(%ebp), %edi
	movl	-88(%ebp), %ecx
	andl	$15, %ecx
	movl	%edi, (%esp)
	movl	%ecx, %esi
	call	_malloc
	movl	%eax, %ebx
	movl	-168(%ebp), %eax
	movl	$1, 8(%esp)
	movl	%edi, 4(%esp)
	movl	%ebx, (%esp)
	movl	%eax, 12(%esp)
	call	_fread
	leal	_quant(%esi), %edx
	movl	$_zigzag_table8+8, %eax
	movl	$_zigzag_table8+16, %esi
L137:
	movzbl	-8(%eax), %ecx
	addl	$1, %eax
	addl	$16, %edx
	movzbl	-1(%ebx,%ecx), %ecx
	movb	%cl, -16(%edx)
	movzbl	-1(%eax), %ecx
	movzbl	-1(%ebx,%ecx), %ecx
	movb	%cl, 240(%edx)
	movzbl	7(%eax), %ecx
	movzbl	-1(%ebx,%ecx), %ecx
	movb	%cl, 496(%edx)
	movzbl	15(%eax), %ecx
	movzbl	-1(%ebx,%ecx), %ecx
	movb	%cl, 752(%edx)
	movzbl	23(%eax), %ecx
	movzbl	-1(%ebx,%ecx), %ecx
	movb	%cl, 1008(%edx)
	movzbl	31(%eax), %ecx
	movzbl	-1(%ebx,%ecx), %ecx
	movb	%cl, 1264(%edx)
	movzbl	39(%eax), %ecx
	movzbl	-1(%ebx,%ecx), %ecx
	movb	%cl, 1520(%edx)
	movzbl	47(%eax), %ecx
	movzbl	-1(%ebx,%ecx), %ecx
	movb	%cl, 1776(%edx)
	cmpl	%eax, %esi
	jne	L137
	movl	%ebx, (%esp)
	call	_free
	jmp	L132
L256:
	movl	-168(%ebp), %esi
	leal	-106(%ebp), %eax
	movl	$1, 8(%esp)
	movl	$2, 4(%esp)
	movl	%eax, (%esp)
	movl	%esi, 12(%esp)
	call	_fread
	movzwl	-106(%ebp), %eax
	movl	%eax, (%esp)
	call	_bswap16
	subl	$2, %eax
	movl	$1, 8(%esp)
	movl	%esi, (%esp)
	movw	%ax, -106(%ebp)
	movzwl	%ax, %eax
	movl	%eax, 4(%esp)
	call	_fseek
	jmp	L132
L259:
	movl	-168(%ebp), %esi
	leal	-106(%ebp), %eax
	movl	$1, 8(%esp)
	movl	$2, 4(%esp)
	leal	-88(%ebp), %edi
	xorl	%ebx, %ebx
	movl	%eax, (%esp)
	movl	%esi, 12(%esp)
	call	_fread
	movzwl	-106(%ebp), %eax
	movl	%eax, (%esp)
	call	_bswap16
	movw	%ax, -106(%ebp)
	leal	-92(%ebp), %eax
	movl	%esi, 12(%esp)
	movl	$1, 8(%esp)
	movl	$1, 4(%esp)
	xorl	%esi, %esi
	movl	%eax, (%esp)
	movl	$0, -92(%ebp)
	call	_fread
	movl	$16, %ecx
	xorl	%eax, %eax
	movl	%edi, -144(%ebp)
	rep stosl
	leal	-96(%ebp), %edi
L143:
	movl	-168(%ebp), %eax
	movl	$1, 8(%esp)
	movl	$1, 4(%esp)
	movl	%edi, (%esp)
	movb	$0, -96(%ebp)
	movl	%eax, 12(%esp)
	call	_fread
	movzbl	-96(%ebp), %edx
	movl	-144(%ebp), %eax
	movl	%ebx, %ecx
	sall	$4, %ecx
	movl	%edx, (%eax,%ebx,4)
	movl	-92(%ebp), %eax
	addl	$1, %ebx
	addl	%edx, %esi
	andl	$15, %eax
	addl	%eax, %ecx
	movl	-92(%ebp), %eax
	sarl	$4, %eax
	cmpl	$16, %ebx
	leal	(%eax,%ecx,2), %ecx
	movzbl	-96(%ebp), %eax
	movw	%ax, _huf_len(%ecx,%ecx)
	jne	L143
	movl	$0, (%esp)
	call	_init_branches
	movl	%eax, %ebx
	movl	-92(%ebp), %eax
	xorl	%ecx, %ecx
	movl	%eax, %edx
	sarl	$4, %eax
	andl	$15, %edx
	leal	(%eax,%edx,2), %eax
	movl	%ebx, _huffs(,%eax,4)
	movl	$0, 4(%ebx)
	movl	_huffs(,%eax,4), %edx
	movl	$0, 8(%edx)
	movl	_huffs(,%eax,4), %edx
	movl	$0, 12(%edx)
	movl	_huffs(,%eax,4), %eax
	xorl	%edx, %edx
	movw	%dx, (%eax)
	movl	-92(%ebp), %eax
	movl	%eax, %edx
	sarl	$4, %eax
	andl	$15, %edx
	leal	(%eax,%edx,2), %eax
	movl	_huffs(,%eax,4), %eax
	movw	%cx, 2(%eax)
	leal	20(,%esi,4), %eax
	movl	%eax, (%esp)
	call	_malloc
	xorl	%edx, %edx
	testl	%esi, %esi
	movl	%eax, -152(%ebp)
	je	L147
L214:
	movl	-168(%ebp), %eax
	movl	$1, 8(%esp)
	movl	$1, 4(%esp)
	movl	%edi, (%esp)
	movl	%edx, -128(%ebp)
	movl	%eax, 12(%esp)
	call	_fread
	movzbl	-96(%ebp), %eax
	movl	-128(%ebp), %edx
	movl	-152(%ebp), %ecx
	movl	%eax, (%ecx,%edx,4)
	addl	$1, %edx
	cmpl	%edx, %esi
	jne	L214
L147:
	movl	$0, -156(%ebp)
	movl	-156(%ebp), %eax
	xorl	%edi, %edi
	movb	$0, -132(%ebp)
L145:
	movl	-144(%ebp), %ecx
	leal	1(%eax), %edx
	movzbl	-132(%ebp), %esi
	movl	(%ecx,%eax,4), %ecx
	movl	%edi, %eax
	subl	%eax, %edx
	testl	%ecx, %ecx
	movl	%ecx, -136(%ebp)
	je	L149
L212:
	testb	%dl, %dl
	je	L262
L213:
	movl	4(%ebx), %ecx
	testl	%ecx, %ecx
	je	L263
	movl	8(%ebx), %eax
	testl	%eax, %eax
	je	L264
	addl	$1, %edx
	subl	$1, %edi
	movl	12(%ebx), %ebx
	testb	%dl, %dl
	jne	L213
L262:
	movl	-152(%ebp), %ecx
	movl	%esi, %eax
	addl	$1, %esi
	movzbl	%al, %eax
	subl	$1, %edi
	movl	$1, %edx
	movl	(%ecx,%eax,4), %eax
	movw	%ax, (%ebx)
	movl	%esi, %eax
	subb	-132(%ebp), %al
	movl	12(%ebx), %ebx
	movzbl	%al, %eax
	cmpl	%eax, -136(%ebp)
	ja	L213
	movl	%esi, %eax
	movb	%al, -132(%ebp)
L149:
	addl	$1, -156(%ebp)
	movl	-156(%ebp), %eax
	cmpl	$16, %eax
	jne	L145
	jmp	L132
L263:
	movl	%ebx, (%esp)
	movb	%dl, -128(%ebp)
	addl	$1, %edi
	call	_init_branches
	movzbl	-128(%ebp), %edx
	movl	%eax, 4(%ebx)
	movl	%eax, %ebx
	subl	$1, %edx
	jmp	L212
L264:
	movl	%ebx, (%esp)
	movb	%dl, -128(%ebp)
	addl	$1, %edi
	call	_init_branches
	movzbl	-128(%ebp), %edx
	movl	%eax, 8(%ebx)
	movl	%eax, %ebx
	subl	$1, %edx
	jmp	L212
L258:
	movl	-168(%ebp), %esi
	leal	-106(%ebp), %eax
	movl	$1, 8(%esp)
	movl	$2, 4(%esp)
	leal	-96(%ebp), %edi
	movl	%eax, (%esp)
	movl	%esi, 12(%esp)
	call	_fread
	movzwl	-106(%ebp), %eax
	movl	%eax, (%esp)
	call	_bswap16
	movl	%esi, 12(%esp)
	movl	$1, 8(%esp)
	movl	$1, 4(%esp)
	movl	%edi, (%esp)
	movw	%ax, -106(%ebp)
	movl	$0, -96(%ebp)
	call	_fread
	movl	%esi, 12(%esp)
	movl	$1, 8(%esp)
	movl	$2, 4(%esp)
	movl	$_Imgsy, (%esp)
	call	_fread
	movzwl	_Imgsy, %eax
	movl	%eax, (%esp)
	call	_bswap16
	movl	%esi, 12(%esp)
	movzwl	%ax, %eax
	movl	$1, 8(%esp)
	movl	$2, 4(%esp)
	movl	$_Imgsx, (%esp)
	movl	%eax, _Imgsy
	call	_fread
	movzwl	_Imgsx, %eax
	movl	%eax, (%esp)
	call	_bswap16
	movzwl	%ax, %eax
	movl	%esi, 12(%esp)
	movl	$1, 8(%esp)
	movl	%eax, _Imgsx
	leal	-92(%ebp), %eax
	movl	$1, 4(%esp)
	movl	$0, -92(%ebp)
	movl	%eax, (%esp)
	call	_fread
	movl	-92(%ebp), %ebx
	testl	%ebx, %ebx
	jle	L132
	leal	-88(%ebp), %eax
	xorl	%ebx, %ebx
	movl	%eax, -144(%ebp)
L140:
	movl	-168(%ebp), %eax
	movl	$3, 8(%esp)
	movl	$1, 4(%esp)
	movl	%eax, 12(%esp)
	movl	-144(%ebp), %eax
	movl	%eax, (%esp)
	call	_fread
	movzwl	-87(%ebp), %eax
	movl	%eax, (%esp)
	call	_bswap16
	movw	%ax, _dct(%ebx,%ebx)
	addl	$1, %ebx
	cmpl	%ebx, -92(%ebp)
	jg	L140
	jmp	L132
L252:
	movl	4(%ebx), %eax
	movl	$LC10, (%esp)
	movl	%eax, 4(%esp)
	call	_printf
	addl	$188, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L260:
	leal	-88(%ebp), %ecx
	movl	%ecx, -144(%ebp)
	jmp	L157
	.section .rdata,"dr"
	.align 4
LC6:
	.long	1048576000
	.align 4
LC11:
	.long	1073741824
	.align 4
LC12:
	.long	1056964608
	.ident	"GCC: (tdm-1) 5.1.0"
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_malloc;	.scl	2;	.type	32;	.endef
	.def	_fopen;	.scl	2;	.type	32;	.endef
	.def	_fseek;	.scl	2;	.type	32;	.endef
	.def	_ftell;	.scl	2;	.type	32;	.endef
	.def	_rewind;	.scl	2;	.type	32;	.endef
	.def	_fread;	.scl	2;	.type	32;	.endef
	.def	_memcpy;	.scl	2;	.type	32;	.endef
	.def	_free;	.scl	2;	.type	32;	.endef
