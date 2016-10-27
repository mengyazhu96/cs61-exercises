	.file	"switch.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"It's an a"
.LC1:
	.string	"It's an b"
.LC2:
	.string	"It's an c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC3:
	.string	"It is neither an a nor a b nor a c"
	.text
	.globl	doswitch
	.type	doswitch, @function
doswitch:
.LFB38:
	subq	$8, %rsp
	subl	$65, %edi
	cmpb	$34, %dil
	ja	.L2
	movzbl	%dil, %edi
	jmp	*.L4(,%rdi,8)
	.section	.rodata
	.align 8
	.align 4
.L4:
	.quad	.L3
	.quad	.L5
	.quad	.L6
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L2
	.quad	.L3
	.quad	.L5
	.quad	.L6
	.text
.L3:
	movl	$.LC0, %edi
	call	puts
	jmp	.L1
.L5:
	movl	$.LC1, %edi
	call	puts
	jmp	.L1
.L6:
	movl	$.LC2, %edi
	call	puts
	jmp	.L1
.L2:
	movl	$.LC3, %edi
	call	puts
.L1:
	addq	$8, %rsp
	ret
.LFE38:
	.size	doswitch, .-doswitch
	.section	.rodata.str1.1
.LC4:
	.string	"Usage: switch A\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB39:
	subq	$8, %rsp
	cmpl	$1, %edi
	jg	.L10
	movq	stderr(%rip), %rcx
	movl	$16, %edx
	movl	$1, %esi
	movl	$.LC4, %edi
	call	fwrite
	movl	$1, %edi
	call	exit
.L10:
	movq	8(%rsi), %rax
	movsbl	(%rax), %edi
	call	doswitch
	movl	$0, %eax
	addq	$8, %rsp
	ret
.LFE39:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
