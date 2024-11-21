; w0 == A, w1 == B, a == res
	org 1024
main:
	ld w0, #8
	ld w1, #2
	call %_mul
	jmp %_inf
_mul:
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