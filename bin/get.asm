	org 1024
init:
	ld s0, #3
	ld x0, #0
getKey:
	in
	cmp x0
	bz %getKey
inf:
	jmp %inf