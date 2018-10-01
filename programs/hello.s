	.file	"hello.c"
	.text
	.globl	__main
	.def	__main;	.scl	2;	.type	32;	.endef
__main:
	pushl	%ebp
	movl	%esp, %ebp
	nop
	popl	%ebp
	ret
	.ident	"GCC: (tdm-1) 5.1.0"
