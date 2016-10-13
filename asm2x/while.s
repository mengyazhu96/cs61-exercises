	.file	"while.c"
	.text
	.globl	dowhile
	.type	dowhile, @function
dowhile:
.LFB38:
	pushq	%rbp
	pushq	%rbx
	subq	$8, %rsp
	cmpl	%esi, %edi
	jge	.L2
	subl	$1, %esi
	subl	%edi, %esi
	leaq	1(%rsi), %rbp
	movl	$0, %ebx
.L3:
	movl	$120, %edi
	call	putchar
	addq	$1, %rbx
	cmpq	%rbp, %rbx
	jne	.L3
.L2:
	movl	$10, %edi
	call	putchar
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	ret
.LFE38:
	.size	dowhile, .-dowhile
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Usage: while A B\n"
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
	movl	$17, %edx
	movl	$1, %esi
	movl	$.LC0, %edi
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
	call	dowhile
	movl	$0, %eax
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	ret
.LFE39:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
