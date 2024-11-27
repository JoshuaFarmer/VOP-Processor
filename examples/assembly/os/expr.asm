	; expressions

	; return value of literal or var in A
	; ptr == s0
FETCH_VALUE:
	peek a, s0
	and #255
	cmp #36
	bz %FETCH_VALUE_VAR
	call %string_to_hex
	inc s0
	jmp %FETCH_VALUE_END
FETCH_VALUE_VAR:
	inc s0
	peek a, s0
	and #255
	call %GetVariable
	inc s0
	inc s0
FETCH_VALUE_END:
	ret

	; S0 as ptr
EXPR_IS:
	xc a, s0
	add #3
	xc a, s0
	call %EXPR_TWO_ARGS

	cmp w7, x3
	ret

EXPR_TWO_ARGS:
	call %FETCH_VALUE
	ld z6, a
	call %FETCH_VALUE
	ld w7, z6
	ld x3, a
	ret

EXPR_ADD:
	xc a, s0
	add #4
	xc a, s0
	call %EXPR_TWO_ARGS
	add w7, x3
	ld a, w7
	ret

EXPR_SUB:
	xc a, s0
	add #4
	xc a, s0
	call %EXPR_TWO_ARGS
	sub w7, x3
	ld a, w7
	ret
