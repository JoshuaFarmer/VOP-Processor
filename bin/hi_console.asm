	; ARCHITECTURE:
	; PC		program counter (16 b)
	; A		accumulator (16 b)
	; Rn		register bank (W0-W7, X0-X7) (16 b)
	; Sn		stack ptr bank (S0-S3) (16 b)
	; Pn		pages (P0, P1) (8 b)
	; Te&Re	Temp&Res (internal) (16 b)

	org 512
	; call stack is hard coded as S3 (0x8000 on boot)
init:
	push p0,s0
	pop p1,s0

	; terminal port num
	ld s0, #2

	; get address of message
	ld s1, %msg

	; xor is one byte less, than ld w1, #0000. worth it.
	xor w1, w1

	; constant for lower byte
	ld w3, #255
_loop:
	; peek into near memory (code page)
	peek w0, .s1
	and w0, w3

	ld a, w0
	out
	inc s1
	sub #0
	bnz %_loop
_inf:
	jmp %_inf
msg:
	ds "Hello, World!"
	db 10
	ds "the the the the the"
	db 10
	ds "this is a test of my simple put_string function wow look at this!"
	db 10
	ds "its like 256x160 with 8x8 font, (32x20 chars)"
	db 10
	db 0