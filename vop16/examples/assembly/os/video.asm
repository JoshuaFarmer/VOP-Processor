puts_vid:
	ld s0, %pos_x
	peek x6, .s0
	ld s0, %pos_y
	peek x7, .s0

	; Page 1, Offset 0 (0x10000) (terminal buffer)
	push #1,s3
	pop p1,s3
	call %calculate_offset
_loop:
	ld w3, #255
	xor w1, w1

	; peek into near memory (code page)
	peek w0, .s1
	and w0, w3

	; set a to w0
	ld a, w0
	cmp #10
	cz %next_line

	; blue bg and yellow fg (0x1E00)
	or #7680

	; store and get ready for next.
	poke a, s0
	inc s0
	inc s0
	inc s1

	inc x6
	ld a, w0
	sub #0
	bnz %_loop
	push p0,s3
	pop p1,s3
	ld s0, %pos_x
	poke x6, .s0
	ld s0, %pos_y
	poke x7, .s0
	ret
next_line:
	inc x7
	ld x6, #0
	call %calculate_offset

	ld s0, a
	ret
calculate_offset:
	; Y
	ld w0, x7
	ld w1, #64
	call %mul
	; X
	add x6

	ld s0, a
	ret

pos_x:
	db 0
	db 0
pos_y:
	db 1
	db 0