	org 1024
init:
	ld s0, #3
	ld x7, #2
	ld x0, #0
getKey:
	in
	cmp x0
	bz %getKey
put:
	xc x7, s0
	out
	xc x7, s0
inf:
	jmp %getKey