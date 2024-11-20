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
_loop:
	; peek into near memory (code page)
	peek w0, .s1

	; swap w0 & a, and extract lower eight bits.
	xc a, w0
	and #255

	; store and get ready for next.
	poke a, s0
	inc s0
	inc s1

	inc x6
	cmp x6, #32
	cz %incLine

	cmp #0
	bnz %_loop
_inf:
	jmp %_inf
	nop
incLine:
	ld x6, #0
	inc x7
	ret
msg:
;	ds "Hello, World!"
;	ds " the the the the the"
	ds "this is a test of my simple put_string function wow look at this!"
	ds "its like 256x160 with 8x8 font, (32x20 chars)"
	db 0