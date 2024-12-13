	; A is num
	; we need to isolate the digit; print and then /10
print_decimal:
	ld s0, #2
	ld w0, s4
	ld z7, w0
print_decimal_loop:
	ld w7, a
	call %mod10
	add #48
	; now, digit is in a
	push a, z7
	ld a, w7
	call %div10
	cmp #0
	bz %print_decimal_print_stck
	jmp %print_decimal_loop
print_decimal_print_stck:
	inc z7
	inc z7
print_decimal_print_stck_w0:
	peek w0, .z7
	ld a, w0
	and #255
	cmp #0
	retz
	out
	inc z7
	inc z7
	jmp %print_decimal_print_stck_w0

	; s0 as ptr
	; a as ret value
atoi:
	ld a, #0
	ld w6, #255
atoi_loop:
	peek w7, .s0
	and w7, w6
	cmp w7, #0
	ld w5, #48
	jl w7, w5, %atoi_break
	ld w5, #57
	jg w7, w5, %atoi_break
	ld w0, a
	ld w1, #10
	call %mul
	add w7
	inc s0
	jmp %atoi_loop
atoi_break:
	ret
