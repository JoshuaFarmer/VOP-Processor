	org 512
init:
	; Page 1, Offset 0 (0x10000)
	push #1,s0
	pop p1,s0
	ld s0, #0

	ld s1, %msg
	ld x0, #0

	; pos
	ld x1, #0
_loop:
	; peek into NEAR memory (current page)
	peek w1, .s1

	; swap w1 & a
	xc a, w1
	poke a, s0
	inc s0
	inc s1
	inc x1

	cmp x0
	bz %_loop
	jmp %_loop
_inf:
	jmp %_inf
	nop
msg:
	ds "Hello, World!"
	db 0