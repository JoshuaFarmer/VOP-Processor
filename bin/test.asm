	org 512
_start:
	; 0 - 3
	push #1,s0
	; 4 - 5
	pop p1,s0
	; 6 - 9
	ld s0, #0
	; A - C
	ld a, #65
	; D - E
	poke a, s0
inf:
	; F - 11
	jmp %inf