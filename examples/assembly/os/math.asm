	; simple Math library
	; res is a
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

	; w0 == L0, w1 == H0
	; w2 == L1, w3 == H1
add32:
	add w0, w2
	cc %add32_carry_l
	add w1, w3
	ret
add32_carry_l:
	add w1, #1
	ret

sub32:
	sub w0, w2
	cc %sub32_carry_l
	sub w1, w3
	ret
sub32_carry_l:
	sub w1, #1
	ret


	; A = value
	; A = ret value
div10:
	ld w0, #0
	ld w1, #10
	ld w2, a
div10_w0:
	jl w2, w1, %div_10_end
	sub w2, w1
	inc w0
	jmp %div10_w0
div_10_end:
	ld a, w0
	ret

mod10:
	; A = value
	; A = ret value (remainder)
mod10_start:
	ld w1, #10
	ld w2, a
mod10_loop:
	jl w2, w1, %mod10_end
	sub w2, w1
	jmp %mod10_loop
mod10_end:
	ld a, w2
	ret
