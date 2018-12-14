	.file	"cmd.c"
	.comm	_w, 4, 2
	.globl	_kkey
	.bss
	.align 2
_kkey:
	.space 2
	.text
	.globl	_handle
	.def	_handle;	.scl	2;	.type	32;	.endef
_handle:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	$11, %eax
	jne	L3
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	movzwl	(%eax), %eax
	movw	%ax, _kkey
L3:
	nop
	popl	%ebp
	ret
	.globl	_RecieveKey
	.def	_RecieveKey;	.scl	2;	.type	32;	.endef
_RecieveKey:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movzwl	_kkey, %eax
	testw	%ax, %ax
	je	L5
	movzwl	_kkey, %eax
	movw	%ax, -2(%ebp)
	movw	$0, _kkey
	movzwl	-2(%ebp), %eax
	jmp	L4
L5:
L4:
	leave
	ret
	.globl	_min
	.def	_min;	.scl	2;	.type	32;	.endef
_min:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	cmpl	%eax, 12(%ebp)
	cmovle	12(%ebp), %eax
	popl	%ebp
	ret
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "Command Shell\0"
	.align 4
LC1:
	.ascii "\12Command line for ButterflyOS\12Written by @MrLolthe1st 2018(C)\12\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	call	___main
	movl	$LC0, 16(%esp)
	movl	$_handle, 12(%esp)
	movl	$0, 8(%esp)
	movl	$480, 4(%esp)
	movl	$720, (%esp)
	call	_openWindow
	movl	%eax, _w
	movl	$LC1, (%esp)
	call	_printf
	nop
	leave
	ret
	.ident	"GCC: (tdm-1) 5.1.0"
	.def	_openWindow;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
