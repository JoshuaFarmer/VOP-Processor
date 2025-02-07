	org 1024
start:
	push #1, s3
	pop p1, s3
	ld a, #65
	or #7680
	ld s0, #0
	poke a, s0
	ld s2, #0
inf:
	jmp %inf