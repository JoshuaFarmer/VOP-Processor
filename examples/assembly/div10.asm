	org 1024
	; A = ret value
	ld a, #20
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
inf:
	jmp %inf