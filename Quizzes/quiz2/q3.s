	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	leaq	L_.str(%rip), %rax
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movl	$85, -20(%rbp)
	movl	$170, -24(%rbp)
	movl	-20(%rbp), %edi
	xorl	-24(%rbp), %edi
	xorl	-24(%rbp), %edi
	movl	%edi, -28(%rbp)         ## 4-byte Spill
	movq	%rax, %rdi
	movl	-28(%rbp), %esi         ## 4-byte Reload
	movb	$0, %al
	callq	_printf
	xorl	%esi, %esi
	movl	%eax, -32(%rbp)         ## 4-byte Spill
	movl	%esi, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"Result = %u"


.subsections_via_symbols
