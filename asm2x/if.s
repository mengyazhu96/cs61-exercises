	.file	"if.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Equal!"
.LC1:
	.string	"Not equal!"
	.text
	.globl	doif
	.type	doif, @function
doif:
.LFB38:
	subq	$8, %rsp
	cmpl	%esi, %edi
	jne	.L2
	movl	$.LC0, %edi
	call	puts
	jmp	.L1
.L2:
	movl	$.LC1, %edi
	call	puts
.L1:
	addq	$8, %rsp
	ret
.LFE38:
	.size	doif, .-doif
	.section	.rodata.str1.1
.LC2:
	.string	"Usage: if A B\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB39:
	pushq	%rbp
	pushq	%rbx
	subq	$8, %rsp
	cmpl	$2, %edi
	jg	.L6
	movq	stderr(%rip), %rcx
	movl	$14, %edx
	movl	$1, %esi
	movl	$.LC2, %edi
	call	fwrite
	movl	$1, %edi
	call	exit
.L6:
	movq	%rsi, %rbx
	movq	8(%rsi), %rdi
	movl	$0, %edx
	movl	$0, %esi
	call	strtol
	movq	%rax, %rbp
	movq	16(%rbx), %rdi
	movl	$0, %edx
	movl	$0, %esi
	call	strtol
	movl	%eax, %esi
	movl	%ebp, %edi
	call	doif
	movl	$0, %eax
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	ret
.LFE39:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
