	org 1024
	define stack 65535
	define data 128
	define variables 0
	; FIRST PROGRAM TO USE NEW STACK POINTERS!! (s4 to z7)
	; yes, this cpu has 16 stack pointers/address registers...
	; PROGRAMMERS NOTE :
	; DONT USE S0 FOR ADDRESSES,
	; IT IS OVEWRITTEN ALOT WITHOUT SAVING
	; IN THIS CODE
_start:
	push .#2, s3
	pop p1, s3
	ld s3, %stack
	ld s1, %data
	call %_gets
_inf:
	jmp %_inf

	; s1 is the input address
	; x6 is the length
_gets:
	ld s0, #3
	ld x7, #2
	ld x6, #0
_f0:
	in
	cmp #0
	bz %_f0
	cmp #10
	bz %_f2
_f1:
	xc x7, s0
	out
	xc x7, s0
	poke a, s1
	inc s1
	inc x6
	jmp %_l0
_f2:
	ld x5, s1
	sub x5, x6
	ld s1, x5
	ret
