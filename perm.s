	.file	"perm.c"
	.text
	.type	get_file_type, @function
get_file_type:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movl	%eax, %edx
	andl	$61440, %edx
	cmpl	$24576, %edx
	jne	.L2
	movl	$98, %eax
	jmp	.L3
.L2:
	movl	%eax, %edx
	andl	$61440, %edx
	cmpl	$8192, %edx
	jne	.L4
	movl	$99, %eax
	jmp	.L3
.L4:
	movl	%eax, %edx
	andl	$61440, %edx
	cmpl	$16384, %edx
	jne	.L5
	movl	$100, %eax
	jmp	.L3
.L5:
	movl	%eax, %edx
	andl	$61440, %edx
	cmpl	$4096, %edx
	jne	.L6
	movl	$112, %eax
	jmp	.L3
.L6:
	movl	%eax, %edx
	andl	$61440, %edx
	cmpl	$40960, %edx
	jne	.L7
	movl	$108, %eax
	jmp	.L3
.L7:
	andl	$61440, %eax
	cmpl	$49152, %eax
	jne	.L8
	movl	$115, %eax
	jmp	.L3
.L8:
	movl	$45, %eax
.L3:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	get_file_type, .-get_file_type
	.type	get_xattr, @function
get_xattr:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	$32, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	get_xattr, .-get_xattr
	.globl	perm_format
	.type	perm_format, @function
perm_format:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$8, %rsp
	.cfi_offset 3, -24
	movl	%edi, %ebx
	movq	%rsi, -16(%rbp)
	movl	%ebx, %edi
	call	get_file_type
	movb	%al, perm.4216(%rip)
	movl	%ebx, %eax
	andl	$256, %eax
	testl	%eax, %eax
	je	.L12
	movl	$114, %eax
	jmp	.L13
.L12:
	movl	$45, %eax
.L13:
	movb	%al, perm.4216+1(%rip)
	movl	%ebx, %eax
	andl	$128, %eax
	testl	%eax, %eax
	je	.L14
	movl	$119, %eax
	jmp	.L15
.L14:
	movl	$45, %eax
.L15:
	movb	%al, perm.4216+2(%rip)
	movl	%ebx, %eax
	andl	$2048, %eax
	testl	%eax, %eax
	je	.L16
	movl	%ebx, %eax
	andl	$64, %eax
	testl	%eax, %eax
	je	.L17
	movl	$115, %eax
	jmp	.L18
.L17:
	movl	$83, %eax
.L18:
	movb	%al, perm.4216+3(%rip)
	jmp	.L19
.L16:
	movl	%ebx, %eax
	andl	$64, %eax
	testl	%eax, %eax
	je	.L20
	movl	$120, %eax
	jmp	.L21
.L20:
	movl	$45, %eax
.L21:
	movb	%al, perm.4216+3(%rip)
.L19:
	movl	%ebx, %eax
	andl	$32, %eax
	testl	%eax, %eax
	je	.L22
	movl	$114, %eax
	jmp	.L23
.L22:
	movl	$45, %eax
.L23:
	movb	%al, perm.4216+4(%rip)
	movl	%ebx, %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L24
	movl	$119, %eax
	jmp	.L25
.L24:
	movl	$45, %eax
.L25:
	movb	%al, perm.4216+5(%rip)
	movl	%ebx, %eax
	andl	$1024, %eax
	testl	%eax, %eax
	je	.L26
	movl	%ebx, %eax
	andl	$8, %eax
	testl	%eax, %eax
	je	.L27
	movl	$115, %eax
	jmp	.L28
.L27:
	movl	$83, %eax
.L28:
	movb	%al, perm.4216+6(%rip)
	jmp	.L29
.L26:
	movl	%ebx, %eax
	andl	$8, %eax
	testl	%eax, %eax
	je	.L30
	movl	$120, %eax
	jmp	.L31
.L30:
	movl	$45, %eax
.L31:
	movb	%al, perm.4216+6(%rip)
.L29:
	movl	%ebx, %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L32
	movl	$114, %eax
	jmp	.L33
.L32:
	movl	$45, %eax
.L33:
	movb	%al, perm.4216+7(%rip)
	movl	%ebx, %eax
	andl	$2, %eax
	testl	%eax, %eax
	je	.L34
	movl	$119, %eax
	jmp	.L35
.L34:
	movl	$45, %eax
.L35:
	movb	%al, perm.4216+8(%rip)
	movl	%ebx, %eax
	andl	$512, %eax
	testl	%eax, %eax
	je	.L36
	movl	%ebx, %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L37
	movl	$116, %eax
	jmp	.L38
.L37:
	movl	$84, %eax
.L38:
	movb	%al, perm.4216+9(%rip)
	jmp	.L39
.L36:
	movl	%ebx, %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L40
	movl	$120, %eax
	jmp	.L41
.L40:
	movl	$45, %eax
.L41:
	movb	%al, perm.4216+9(%rip)
.L39:
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	get_xattr
	movb	%al, perm.4216+10(%rip)
	movl	$perm.4216, %eax
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	perm_format, .-perm_format
	.local	perm.4216
	.comm	perm.4216,12,8
	.ident	"GCC: (GNU) 6.3.1 20170306"
	.section	.note.GNU-stack,"",@progbits
