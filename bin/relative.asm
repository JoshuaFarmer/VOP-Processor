	org 1024
start:
	ld s1, #2
	ld s0, %msg
	ld w0, #0
puts:
	peek a, .+w0
	and #255
	cmp #0
	bz %inf
	inc w0
	xc s0, s1
	out
	xc s0, s1
	jmp %puts
inf:
	jmp %inf
msg:
	ds "hello, world!, this is a test of the relative memory offset instruction"
	db 10
	ds "peek a, .+w0"
	db 10
	ds "which loads the value at s0 + w0 (at code page)"
	db 10
	ds "as you can see, i think its faster, idk"
	db 0