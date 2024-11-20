	org 512
init:
	; Page 1, Offset 0 (0x10000)
	push #1,s0
	pop p1,s0
	ld s0, #0

	; 'A'
	ld a, #65

	; letters to print
	ld w0, #26
_loop:
	poke a, s0
	inc a
	inc s0

	; loop condition
	dec w0
	bnz %_loop
_inf:
	jmp %_inf