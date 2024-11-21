	; ARCHITECTURE:
	; PC		program counter (16 b)
	; A		accumulator (16 b)
	; Rn		register bank (W0-W7, X0-X7) (16 b)
	; Sn		stack ptr bank (S0-S3) (16 b)
	; Pn		pages (P0, P1) (8 b)
	; Te&Re	Temp&Res (internal) (16 b)

	org 1024
	; call stack is hard coded as S3 (0x8000 on boot)
init:
	; Page 1, Offset 0 (0x10000) (terminal buffer)
	push #1,s0
	pop p1,s0
	ld s0, #0

	; get address of message
	ld s1, %msg

	; xor is one byte less, worth it.
	xor w1, w1

	; X,Y
	ld x6, #0
	ld x7, #0

	; constant for and
	ld w3, #255
_loop:
	; peek into near memory (code page)
	peek w0, .s1
	and w0, w3

	; set a to w0
	ld a, w0

	; blue bg and yellow fg (0x1E00)
	or #7680

	; store and get ready for next.
	poke a, s0
	inc s0
	inc s0
	inc s1

	inc x6
	cmp x6, #32
	cz %next_line
	ld a, w0
	sub #0
	bnz %_loop
_inf:
	ld a, #65
	jmp %_inf
next_line:
	ld x6, #0
	inc x7
	ret
msg:
	ds "Hello, World! "
	ds "the the the the the "
	ds "this is a test of my simple put_string function wow look at this! "
	ds "its like 256x160 with 8x8 font, (32x20 chars) "
	db 0