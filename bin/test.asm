	org 512
_start:
	push #1,s0
	pop p1,s0
	ld s0, #0
	ld a, #65
	poke a, s0
inf:
	jmp %inf