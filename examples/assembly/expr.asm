	org 1024
	define stack 65535
	define data 128
	define variables 0
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
	bz %getKey
_put:
	xc x7, s0
	out
	xc x7, s0
	cmp #13
	retz
	jmp %_l0
