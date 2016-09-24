	.file	"4a.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%c\n"
.LC1:
	.string	"%d\n"
	.text
	.globl	output_func
	.type	output_func, @function
output_func:
.LFB23:
	pushq	%rbx
	movq	%rdi, %rbx
	movsbl	(%rdi), %edx
	movl	$.LC0, %esi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
	movl	(%rbx), %edx
	movl	$.LC1, %esi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
	movl	(%rbx), %edx
	movl	$.LC1, %esi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk
	popq	%rbx
	ret
.LFE23:
	.size	output_func, .-output_func
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
