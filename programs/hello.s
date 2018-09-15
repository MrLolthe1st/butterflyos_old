	.file	"hello.c"
	.text
	.globl	_____start
	.def	_____start;	.scl	2;	.type	32;	.endef
_____start:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	call	__main
	nop
	leave
	ret
	.comm	_w, 4, 2
	.globl	_q
	.bss
	.align 4
_q:
	.space 4
	.globl	_ii
_ii:
	.space 1
	.section .rdata,"dr"
LC0:
	.ascii "Event!\0"
	.text
	.globl	_qq
	.def	_qq;	.scl	2;	.type	32;	.endef
_qq:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	_w, %eax
	movl	$LC0, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$6, (%esp)
	call	_printTextToWindow
	nop
	leave
	ret
	.section .rdata,"dr"
LC1:
	.ascii "abcde\0"
	.text
	.globl	__main
	.def	__main;	.scl	2;	.type	32;	.endef
__main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	movl	$10, (%esp)
	call	_malloc
	movl	%eax, _q
	movl	_q, %eax
	movb	$32, (%eax)
	movl	_q, %eax
	addl	$1, %eax
	movb	$37, (%eax)
	movl	_q, %eax
	addl	$2, %eax
	movb	$120, (%eax)
	movl	_q, %eax
	addl	$3, %eax
	movb	$10, (%eax)
	movl	_q, %eax
	addl	$4, %eax
	movb	$0, (%eax)
	movl	$LC1, 16(%esp)
	movl	$_qq, 12(%esp)
	movl	$0, 8(%esp)
	movl	$100, 4(%esp)
	movl	$300, (%esp)
	call	_openWindow
	movl	%eax, _w
	movl	_q, %edx
	movl	_w, %eax
	movl	$_qq, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$6, (%esp)
	call	_printTextToWindow
	movl	$0, -12(%ebp)
	nop
	leave
	ret
	.ident	"GCC: (tdm-1) 5.1.0"
	.def	_printTextToWindow;	.scl	2;	.type	32;	.endef
	.def	_malloc;	.scl	2;	.type	32;	.endef
	.def	_openWindow;	.scl	2;	.type	32;	.endef
