	.file	"plasma.c"
	.globl	_key
	.bss
	.align 4
_key:
	.space 4
	.text
	.globl	_handle
	.def	_handle;	.scl	2;	.type	32;	.endef
_handle:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	$11, %eax
	jne	L2
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movzwl	(%eax), %eax
	movzwl	%ax, %eax
	movl	%eax, _key
L2:
	nop
	popl	%ebp
	ret
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
	call	_omain
	nop
	leave
	ret
	.globl	_sqrt
	.def	_sqrt;	.scl	2;	.type	32;	.endef
_sqrt:
	pushl	%ebp
	movl	%esp, %ebp
	fldl	8(%ebp)
/APP
 # 22 "plasma.c" 1
	fsqrt
 # 0 "" 2
/NO_APP
	popl	%ebp
	ret
	.globl	_dist
	.def	_dist;	.scl	2;	.type	32;	.endef
_dist:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	fldl	24(%ebp)
	fsubrl	8(%ebp)
	fldl	32(%ebp)
	fsubrl	16(%ebp)
	fld	%st(0)
	fxch	%st(2)
	fmul	%st(0), %st
	fxch	%st(2)
	fmulp	%st, %st(1)
	faddp	%st, %st(1)
	fld	%st(0)
	fsqrt
	fucomi	%st(0), %st
	jp	L11
	fstp	%st(1)
	leave
	ret
L11:
	fstp	%st(0)
	fstpl	(%esp)
	call	_sqrt
	leave
	ret
	.globl	_fabs
	.def	_fabs;	.scl	2;	.type	32;	.endef
_fabs:
	pushl	%ebp
	movl	%esp, %ebp
	fldl	8(%ebp)
/APP
 # 34 "plasma.c" 1
	fabs
 # 0 "" 2
/NO_APP
	popl	%ebp
	ret
	.globl	_rgb
	.def	_rgb;	.scl	2;	.type	32;	.endef
_rgb:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	movl	16(%ebp), %edx
	sall	$8, %eax
	addl	8(%ebp), %eax
	sall	$16, %edx
	popl	%ebp
	addl	%edx, %eax
	ret
	.globl	_floor
	.def	_floor;	.scl	2;	.type	32;	.endef
_floor:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$32, %esp
	fnstcw	-10(%ebp)
	movzwl	-10(%ebp), %eax
	fldl	8(%ebp)
	movb	$12, %ah
	movw	%ax, -12(%ebp)
	fld	%st(0)
	fldcw	-12(%ebp)
	fistpq	-32(%ebp)
	fldcw	-10(%ebp)
	fildq	-32(%ebp)
	fxch	%st(1)
	fucomi	%st(1), %st
	jp	L21
	fld	%st(1)
	je	L25
	fstp	%st(0)
L21:
	fldz
	fxch	%st(1)
	fucomip	%st(1), %st
	fstp	%st(0)
	jb	L24
	jmp	L22
L25:
	fstp	%st(1)
	fstp	%st(1)
L22:
	leave
	ret
L24:
	fsubs	LC2
	leave
	ret
	.globl	_fmod
	.def	_fmod;	.scl	2;	.type	32;	.endef
_fmod:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	flds	8(%ebp)
	flds	12(%ebp)
	fld	%st(1)
	fstps	-12(%ebp)
	fdivr	%st, %st(1)
	fstps	-8(%ebp)
	fstpl	(%esp)
	call	_floor
	flds	-8(%ebp)
	fmulp	%st, %st(1)
	flds	-12(%ebp)
	fsubp	%st, %st(1)
	fstps	-4(%ebp)
	flds	-4(%ebp)
	leave
	ret
	.globl	_hsv_to_rgb
	.def	_hsv_to_rgb;	.scl	2;	.type	32;	.endef
_hsv_to_rgb:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$32, %esp
	flds	16(%ebp)
	movl	$0x40000000, 4(%esp)
	fld	%st(0)
	fstps	-20(%ebp)
	fmuls	12(%ebp)
	fstps	-16(%ebp)
	fildl	8(%ebp)
	fdivs	LC3
	fsts	(%esp)
	fstps	-12(%ebp)
	call	_fmod
	fld1
	fld	%st(0)
	fsubr	%st, %st(2)
	fxch	%st(2)
	fabs
	fsubrp	%st, %st(2)
	flds	-16(%ebp)
	fmul	%st, %st(2)
	fxch	%st(2)
	fstps	-4(%ebp)
	flds	-4(%ebp)
	flds	-20(%ebp)
	fsub	%st(3), %st
	flds	-12(%ebp)
	fxch	%st(3)
	fucomip	%st(3), %st
	ja	L31
	fldz
	flds	LC4
	fucomip	%st(4), %st
	ja	L40
	flds	LC5
	fucomip	%st(4), %st
	ja	L33
	flds	LC6
	fucomip	%st(4), %st
	ja	L34
	flds	LC7
	fucomip	%st(4), %st
	ja	L35
	flds	LC8
	fucomip	%st(4), %st
	fstp	%st(3)
	jbe	L38
	fstp	%st(2)
	fxch	%st(1)
	fldz
	fxch	%st(3)
	fxch	%st(2)
	jmp	L29
L40:
	fstp	%st(3)
	fxch	%st(1)
	fxch	%st(2)
L29:
	fadd	%st(1), %st
	fnstcw	-6(%ebp)
	movzwl	-6(%ebp), %eax
	flds	LC9
	movb	$12, %ah
	movw	%ax, -8(%ebp)
	fmul	%st, %st(1)
	fxch	%st(1)
	fldcw	-8(%ebp)
	fistpl	16(%ebp)
	fldcw	-6(%ebp)
	fxch	%st(3)
	fadd	%st(1), %st
	fmul	%st(3), %st
	fldcw	-8(%ebp)
	fistpl	12(%ebp)
	fldcw	-6(%ebp)
	faddp	%st, %st(1)
	fmulp	%st, %st(1)
	fldcw	-8(%ebp)
	fistpl	8(%ebp)
	fldcw	-6(%ebp)
	leave
	jmp	_rgb
L34:
	fstp	%st(0)
	fstp	%st(2)
	fxch	%st(1)
	fldz
	fxch	%st(2)
	fxch	%st(3)
	jmp	L29
L33:
	fstp	%st(0)
	fstp	%st(2)
	fxch	%st(1)
	fldz
	fxch	%st(2)
	jmp	L29
L31:
	fstp	%st(2)
	fxch	%st(1)
	fldz
	fxch	%st(2)
	fxch	%st(3)
	fxch	%st(2)
	jmp	L29
L35:
	fstp	%st(0)
	fstp	%st(2)
	fxch	%st(1)
	fldz
	fxch	%st(3)
	jmp	L29
L38:
	fstp	%st(3)
	fstp	%st(0)
	fxch	%st(1)
	fld	%st(1)
	fld	%st(2)
	fxch	%st(2)
	fxch	%st(1)
	fxch	%st(3)
	jmp	L29
	.globl	_CONST_1
	.data
	.align 4
_CONST_1:
	.long	1067645315
	.globl	_CONST_2
	.align 4
_CONST_2:
	.long	1053786491
	.text
	.globl	_sins
	.def	_sins;	.scl	2;	.type	32;	.endef
_sins:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	flds	8(%ebp)
	fld	%st(0)
	fldl	LC10
	fucomip	%st(1), %st
	jbe	L52
	fstp	%st(1)
	faddl	LC11
	fstps	-4(%ebp)
	flds	-4(%ebp)
	jmp	L44
L56:
	fstp	%st(0)
L44:
	fldz
	fucomip	%st(1), %st
	ja	L55
L53:
	flds	_CONST_1
	fmul	%st(1), %st
	flds	_CONST_2
	leave
	fmul	%st(2), %st
	fmulp	%st, %st(2)
	fsubp	%st, %st(1)
	ret
L52:
	fldl	LC12
	fxch	%st(1)
	fucomi	%st(1), %st
	fstp	%st(1)
	jbe	L56
	fstp	%st(1)
	fldl	LC11
	fsubrp	%st, %st(1)
	fstps	-4(%ebp)
	flds	-4(%ebp)
	fldz
	fucomip	%st(1), %st
	jbe	L53
L55:
	flds	_CONST_2
	fmul	%st(1), %st
	fmul	%st(1), %st
	fxch	%st(1)
	fmuls	_CONST_1
	leave
	faddp	%st, %st(1)
	ret
	.globl	_sin
	.def	_sin;	.scl	2;	.type	32;	.endef
_sin:
	pushl	%ebp
	movl	%esp, %ebp
	fldl	8(%ebp)
/APP
 # 89 "plasma.c" 1
	fsin
 # 0 "" 2
/NO_APP
	popl	%ebp
	ret
	.globl	_cos
	.def	_cos;	.scl	2;	.type	32;	.endef
_cos:
	pushl	%ebp
	movl	%esp, %ebp
	fldl	8(%ebp)
/APP
 # 94 "plasma.c" 1
	fcos
 # 0 "" 2
/NO_APP
	popl	%ebp
	ret
	.globl	_t
	.bss
	.align 32
_t:
	.space 1000000
	.text
	.globl	_bswap24
	.def	_bswap24;	.scl	2;	.type	32;	.endef
_bswap24:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	popl	%ebp
	movl	%edx, %ecx
	movzbl	%dl, %eax
	sarl	$16, %edx
	andl	$65280, %ecx
	sall	$16, %eax
	leal	255(%ecx,%eax), %eax
	andl	%edx, %eax
	ret
	.section .rdata,"dr"
LC14:
	.ascii "Graphics Test\0"
	.text
	.globl	_omain
	.def	_omain;	.scl	2;	.type	32;	.endef
_omain:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$1148, %esp
	movl	8(%ebp), %esi
	movl	12(%ebp), %ebx
	movl	$LC14, 16(%esp)
	movl	$_handle, 12(%esp)
	movl	$1, 8(%esp)
	movl	$500, 4(%esp)
	movl	$500, (%esp)
	call	_openWindow
	cmpl	$2, %esi
	movl	%eax, -1064(%ebp)
	je	L99
L65:
	movl	-1064(%ebp), %eax
	movl	%eax, 8(%ebp)
	addl	$1148, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	jmp	_closeWindow
L99:
	movl	4(%ebx), %eax
	movzbl	(%eax), %eax
	cmpb	$112, %al
	je	L100
	cmpb	$51, %al
	jne	L65
	flds	LC13
	fstpl	-1080(%ebp)
L82:
	movl	_key, %eax
	andl	$-33, %eax
	cmpl	$81, %eax
	je	L65
	fldl	LC21
	xorl	%ebx, %ebx
	faddl	-1080(%ebp)
	fstl	-1080(%ebp)
	fdivs	LC22
	fstl	(%esp)
	fstpl	-1088(%ebp)
	call	_sin
	fstpl	-1072(%ebp)
	fldl	-1088(%ebp)
	fstpl	(%esp)
	call	_cos
	fldl	-1072(%ebp)
	xorl	%ecx, %ecx
L81:
	movl	%ebx, -1072(%ebp)
	fildl	-1072(%ebp)
	fsubl	LC27
	fdivs	LC24
	fldz
	fucomip	%st(1), %st
	ja	L101
L78:
	fldl	LC25
	fxch	%st(1)
	fucomi	%st(1), %st
	fstp	%st(1)
	jbe	L102
	fdivrs	LC26
	flds	LC13
	fucomip	%st(1), %st
	jbe	L103
	fld	%st(1)
	fnstcw	-1054(%ebp)
	movzwl	-1054(%ebp), %eax
	movl	-1064(%ebp), %edi
	xorl	%edx, %edx
	fmul	%st(1), %st
	movb	$12, %ah
	movw	%ax, -1056(%ebp)
	fld	%st(3)
	fmul	%st(2), %st
	flds	LC23
L85:
	movl	%edx, -1072(%ebp)
	fildl	-1072(%ebp)
	fsub	%st(1), %st
	fdivs	LC24
	fmul	%st(4), %st
	fld	%st(6)
	fmul	%st(1), %st
	fadd	%st(4), %st
	fldcw	-1056(%ebp)
	fistpl	-1060(%ebp)
	fldcw	-1054(%ebp)
	movl	-1060(%ebp), %eax
	fmul	%st(5), %st
	andl	$15, %eax
	sall	$4, %eax
	movl	%eax, %esi
	fsubr	%st(2), %st
	fldcw	-1056(%ebp)
	fistpl	-1060(%ebp)
	fldcw	-1054(%ebp)
	movl	-1060(%ebp), %eax
	andl	$15, %eax
	sall	$12, %eax
	orl	%esi, %eax
	leal	(%edx,%edx,2), %esi
	addl	56(%edi), %esi
	addl	$1, %edx
	movl	%eax, -1048(%ebp)
	addl	%ecx, %esi
	cmpl	$500, %edx
	movw	%ax, (%esi)
	movb	$0, 2(%esi)
	jne	L85
	fstp	%st(0)
	fstp	%st(0)
	fstp	%st(0)
	fstp	%st(0)
	jmp	L83
L102:
	fstp	%st(0)
	jmp	L83
L103:
	fstp	%st(0)
L83:
	addl	$1, %ebx
	addl	$1500, %ecx
	cmpl	$500, %ebx
	jne	L81
	fstp	%st(0)
	fstp	%st(0)
	jmp	L82
L100:
	xorl	%ecx, %ecx
L67:
	movl	%ecx, (%esp)
	movl	$0x3f800000, 8(%esp)
	movl	$0x3f800000, 4(%esp)
	call	_hsv_to_rgb
	movl	%eax, -1048(%ebp,%ecx,4)
	addl	$1, %ecx
	cmpl	$256, %ecx
	jne	L67
	xorl	%ebx, %ebx
L70:
	movl	%ebx, -1072(%ebp)
	xorl	%eax, %eax
	fildl	-1072(%ebp)
	imull	$500, %ebx, %ecx
	fstpl	-1072(%ebp)
L69:
	movl	%eax, -1080(%ebp)
	fildl	-1080(%ebp)
	flds	LC15
	fstl	24(%esp)
	fstpl	16(%esp)
	fstl	8(%esp)
	fstpl	-1104(%ebp)
	fldl	-1072(%ebp)
	fstpl	(%esp)
	call	_dist
	flds	LC16
	fmul	%st, %st(1)
	fstpl	-1088(%ebp)
	fstpl	(%esp)
	call	_sin
	fstpl	-1080(%ebp)
	flds	LC13
	fstpl	24(%esp)
	flds	LC17
	fstpl	16(%esp)
	fldl	-1104(%ebp)
	fstpl	8(%esp)
	fldl	-1072(%ebp)
	fstpl	(%esp)
	call	_dist
	fldl	-1088(%ebp)
	fmulp	%st, %st(1)
	fstpl	(%esp)
	call	_sin
	faddl	-1080(%ebp)
	leal	(%eax,%ecx), %edx
	addl	$1, %eax
	cmpl	$500, %eax
	fstps	_t(,%edx,4)
	jne	L69
	addl	$1, %ebx
	cmpl	$500, %ebx
	jne	L70
L74:
	movl	_key, %eax
	andl	$-33, %eax
	cmpl	$81, %eax
	je	L65
	fldl	-1096(%ebp)
	movl	-1064(%ebp), %eax
	xorl	%esi, %esi
	movl	$0, -1116(%ebp)
	fadds	LC2
	movl	56(%eax), %eax
	movl	%eax, -1120(%ebp)
	fstpl	-1096(%ebp)
L72:
	fildl	-1116(%ebp)
	movl	-1120(%ebp), %edi
	xorl	%ebx, %ebx
	fstl	-1104(%ebp)
	fldl	-1096(%ebp)
	faddp	%st, %st(1)
	fstpl	-1112(%ebp)
L73:
	movl	%ebx, -1072(%ebp)
	addl	$3, %edi
	fildl	-1072(%ebp)
	flds	LC18
	fstl	24(%esp)
	fstpl	16(%esp)
	fstl	8(%esp)
	fstpl	-1088(%ebp)
	fldl	-1112(%ebp)
	fstpl	(%esp)
	call	_dist
	fmuls	LC16
	fstpl	(%esp)
	call	_sin_ps
	movl	%eax, -1072(%ebp)
	leal	(%ebx,%esi), %eax
	addl	$1, %ebx
	fildl	-1072(%ebp)
	fadds	_t(,%eax,4)
	fstps	-1072(%ebp)
	flds	LC15
	fstpl	24(%esp)
	flds	LC17
	fstpl	16(%esp)
	flds	LC19
	fldl	-1096(%ebp)
	fdiv	%st(1), %st
	fxch	%st(1)
	fstpl	-1080(%ebp)
	fldl	-1088(%ebp)
	faddp	%st, %st(1)
	fstpl	8(%esp)
	fldl	-1104(%ebp)
	fstpl	(%esp)
	call	_dist
	fldl	-1080(%ebp)
	fdivrp	%st, %st(1)
	fstpl	(%esp)
	call	_sin_ps
	fnstcw	-1054(%ebp)
	movl	%eax, -1080(%ebp)
	movzwl	-1054(%ebp), %eax
	cmpl	$500, %ebx
	fildl	-1080(%ebp)
	fadds	-1072(%ebp)
	movb	$12, %ah
	movw	%ax, -1056(%ebp)
	fadds	LC6
	fmuls	LC20
	fldcw	-1056(%ebp)
	fistpl	-1060(%ebp)
	fldcw	-1054(%ebp)
	movl	-1060(%ebp), %eax
	movzwl	-1048(%ebp,%eax,4), %ecx
	movzbl	-1046(%ebp,%eax,4), %eax
	movw	%cx, -3(%edi)
	movb	%al, -1(%edi)
	jne	L73
	addl	$500, %esi
	addl	$1500, -1120(%ebp)
	addl	$1, -1116(%ebp)
	cmpl	$250000, %esi
	jne	L72
	jmp	L74
L101:
	fchs
	jmp	L78
	.section .rdata,"dr"
	.align 4
LC2:
	.long	1065353216
	.align 4
LC3:
	.long	1110092459
	.align 4
LC4:
	.long	1073741824
	.align 4
LC5:
	.long	1077936128
	.align 4
LC6:
	.long	1082130432
	.align 4
LC7:
	.long	1084227584
	.align 4
LC8:
	.long	1086324736
	.align 4
LC9:
	.long	1132396544
	.align 8
LC10:
	.long	1518260631
	.long	-1073143301
	.align 8
LC11:
	.long	1518260631
	.long	1075388923
	.align 8
LC12:
	.long	1518260631
	.long	1074340347
	.align 4
LC13:
	.long	1120403456
	.align 4
LC15:
	.long	1115684864
	.align 4
LC16:
	.long	1040187392
	.align 4
LC17:
	.long	1128267776
	.align 4
LC18:
	.long	1124073472
	.align 4
LC19:
	.long	1088421888
	.align 4
LC20:
	.long	1107296256
	.align 8
LC21:
	.long	-1717986918
	.long	1069128089
	.align 4
LC22:
	.long	1092616192
	.align 4
LC23:
	.long	1132068864
	.align 4
LC24:
	.long	1140457472
	.align 8
LC25:
	.long	1202590843
	.long	1065646817
	.align 4
LC26:
	.long	1090519040
	.align 8
LC27:
	.long	0
	.long	1081032704
	.ident	"GCC: (tdm-1) 5.1.0"
	.def	_openWindow;	.scl	2;	.type	32;	.endef
	.def	_closeWindow;	.scl	2;	.type	32;	.endef
	.def	_sin_ps;	.scl	2;	.type	32;	.endef
