	section '.strlen' executable
; input:
; | rdi - string
; output:
; | rax - length
public strlen
strlen:
	mov	rax, -1
.iteration:
	inc	rax
	cmp	[rdi + rax], byte 0
	jne	.iteration
	ret

	section '.strcmp' executable
; input:
; | rdi - first string
; | rsi - second string
; output:
; | rax:
;   | -n - n symbol of first string <
;   |  0 - equals
;   | +n - n symbol of first string >
public strcmp
strcmp:
	push	rbx
	xor	rbx, rbx
	mov	rax, -1
.iteration:
	inc	rax
	mov	bl, byte [rdi + rax]
	sub	bl, byte [rsi + rax]
	jz .iteration
	jns .return
	neg	rax
.return:
	pop	rbx
	ret

	section '.strnum' executable
; input:
; | rdi - number
; | rsi - string buffer
; output: void
public strnum
strnum:
	push	rdi
	push	rsi

	cmp	rdi, 0
	jns	.not_negative
	neg	rdi
	mov	[rsi], byte '-'
	inc	rsi
.not_negative:
	call	strposnum

.return:
	pop	rsi
	pop	rdi
	ret

; input:
; | rdi - number
; | rsi - buffer
; output: void
strposnum:
	push	rax
	push	rdx
	mov	rax, rdi
	mov	rdi, 10
	call	iteration
	pop	rdx
	pop	rax
	ret
iteration:
	xor	rdx, rdx
	div	rdi
	push	rdx
	cmp	rax, 0
	je	.return
	call	iteration
.return:
	pop	rdx
	add	rdx, '0'
	mov	[rsi], dl
	inc	rsi
	ret

	section '.strprt' executable
; input:
; | rdi - string
; output: void
public strprt
strprt:
	push	rax
	push	rdi
	push	rsi
	push	rdx

	call	strlen
	mov	rsi, rdi
	mov	rdi, 1
	mov	rdx, rax
	mov	rax, 1
	syscall

	pop	rdx
	pop	rsi
	pop	rdi
	pop	rax
	ret

