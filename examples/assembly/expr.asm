	org 1024
	define stack 65535
	define data 128
	define variables 0
	; FIRST PROGRAM TO USE NEW STACK POINTERS!! (s4 to z7)
	; yes, this cpu has 16 stack pointers/address registers...
_start:
	push .#2, s3
	pop p1, s3
	ld s3, %stack
	ld s0, %data
	call %_gets
_inf:
	jmp %_inf

_gets:
	ld w0, #3
	xc w0, s0
	ld x7, #2
_l0:
	in
	cmp #0
	bz %_l0
	cmp #13
	retz
	cmp #10
	retz
_put:
	xc x7, s0
	out
	xc x7, s0
	jmp %_l0
