	org 1024
	; s0 as ptr
	; a as ret value
	ld s0, %msgstr
atoi:
	ld a, #0
	ld w6, #255
atoi_loop:
	peek w7, .s0
	and w7, w6
	cmp w7, #0
	bz %atoi_break
	sub w7, #48
	ld w0, a
	ld w1, #10
	call %mul
	add w7
	inc s0
	jmp %atoi_loop
atoi_break:
	jmp %atoi_break

msgstr:
	ds "12"
	db 0
mul:
	xor w2, w2
	ld w3, #1
_mul_loop:
	ld a, w1
	and #1
	cmp #1
	bnz %_mul_endif
	add w2, w0
_mul_endif:
	ld a, w0
	shl w3
	ld w0, a

	ld a, w1
	shr w3
	ld w1, a

	cmp w1, #0
	bnz %_mul_loop
	ld a, w2
	ret
_inf:
	jmp %_inf