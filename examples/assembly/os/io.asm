PRINT:
	xor w0, w0
_PRINT:
	peek a, .+w0
	and #255
	cmp #0
	retz
	inc w0
	xc s0, s1
	out
	xc s0, s1
	jmp %_PRINT

PUTC:
	xc s0, s1
	out
	xc s0, s1
	ret

GETKEY:
	ld s0, #4
	ld a, #1
	out
	ld s0, #3
get_from_port:
	in
	cmp #0
	bz %get_from_port
	ret

GETS:
	call %GETKEY
	ld w0, a

	cmp #13
	bz %GETS_END

	poke w0, .z0
	ld s0, #2

	cmp #8
	bz %back

	out
	inc z0
	jmp %GETS

GETS_END:
	ld s0, %newl
	call %PRINT
	ld w0, #0
	poke w0, .z0
	inc z0
	ret
back:
	ld x7, z0
	cmp x7, %keyboard
	bz %GETS
	dec z0
	out
	ld a, #32
	out
	ld a, #8
	out
	jmp %GETS

; s0 == 1, s1 == b
; call %strcmp
; cmp #1
; bz %true
strcmp:
	ld w3, #255
__strcmp:
	peek w0, .s0
	peek w1, .s1
	and w0, w3
	and w1, w3
	inc s0
	inc s1

	cmp w0, #0
	bz %__strcmp_ys

	cmp w0, #32
	bz %__strcmp_ys

	cmp w0, w1
	bz %__strcmp
__strcmp_no:
	ld a, #0
	ret
__strcmp_ys:
	ld a, #1
	ret