format ELF64

include 'string.inc'

public _start

	section '.code' executable
_start:
	mov	rdi, -17641562341
	mov	rsi, buffer
	call	strnum
	mov	rdi, buffer
	call	strprt

_exit:
	mov	rdi, 0
	mov	rax, 60
	syscall

	section '.data' writable
buffer	db	25 dup(0)

