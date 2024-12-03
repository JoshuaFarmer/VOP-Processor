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

	;
	; ascii 34 '"'
	; store in S1
	; from S0
	;
GET_STRING_LITERAL:
	ld w1, #255
	; assume first is '"'
	inc s0
	ld a, s1
GET_STRING_LITERAL_LOOP:
	peek w0, .s0
	and w0, w1
	cmp w0, #34
	bz %GET_STRING_LITERAL_END
	cmp w0, #0
	bz %GET_STRING_LITERAL_END
	cmp w0, #92
	bz %GET_STRING_BACKSLASH
	peek w0, .s0
	and w0, w1
GET_STRING_STR:
	poke w0, .s1
	advn s0, #1
	advn s1, #2
	jmp %GET_STRING_LITERAL_LOOP
GET_STRING_LITERAL_END:
	ret
GET_STRING_BACKSLASH:
	advn s0, #1
	peek w0, .s0
	; so, \K for newline (don't ask).
	sub w0, #65
	jmp %GET_STRING_STR


	;
	;	STORE STRING AT GIVEN VALUE
	;
_EXPR_STR:
	ld s0, x5
EXPR_STR:
	advn s0, #4
	call %FETCH_VALUE
	ld s1, a
	call %GET_STRING_LITERAL
	ret

	;
	; S0 as ptr
	; so, IS $A 32
	;
_EXPR_IS:
	ld s0, x5
EXPR_IS:
	advn s0, #3
	call %EXPR_TWO_ARGS

	cmp w7, x3
	bz %EXPR_IS_EQUAL
	ld a, #0
	ret
EXPR_IS_EQUAL:
	ld a, #1
	ret

EXPR_TWO_ARGS:
	call %FETCH_VALUE
	ld z6, a
	call %FETCH_VALUE
	ld w7, z6
	ld x3, a
	ret

_EXPR_AT:
	ld s0, x5
EXPR_AT:
	advn s0, #3
	call %FETCH_VALUE
	ld z6, a
	peek w0, .z6
	ld a, w0
	ret

_EXPR_AND:
	ld s0, x5
EXPR_AND:
	advn s0, #4
	call %EXPR_TWO_ARGS
	ld a, w7
	and x3
	ret

_EXPR_OR:
	ld s0, x5
EXPR_OR:
	advn s0, #3
	call %EXPR_TWO_ARGS
	ld a, w7
	or x3
	ret

_EXPR_XOR:
	ld s0, x5
EXPR_XOR:
	advn s0, #4
	call %EXPR_TWO_ARGS
	ld a, w7
	xor x3
	ret

_EXPR_ADD:
	ld s0, x5
EXPR_ADD:
	advn s0, #4
	call %EXPR_TWO_ARGS
	add w7, x3
	ld a, w7
	ret

_EXPR_SUB:
	ld s0, x5
EXPR_SUB:
	advn s0, #4
	call %EXPR_TWO_ARGS
	sub w7, x3
	ld a, w7
	ret

_EXPR_MUL:
	ld s0, x5
EXPR_MUL:
	advn s0, #4
	call %EXPR_TWO_ARGS
	ld w0, w7
	ld w1, x3
	call %mul
	ret

_EXPR_JUMP:
	ld s0, x5
EXPR_JUMP:
	advn s0, #5
	call %FETCH_VALUE
	popx
	popw
	ld x1, a
	sub x1, #1
	pushw
	pushx
	ret

_EXPR_IF:
	ld s0, x5
EXPR_IF:
	advn s0, #3
	; evaluate expression
	call %EXPR
	ld w7, a
	cmp #0
	bnz %EXPR
	ret

_EXPR_NOT:
	ld s0, x5
EXPR_NOT:
	advn s0, #4
	call %EXPR
	not
	ret

_EXPR_GET_KEY:
	ld s0, x5
EXPR_GET_KEY:
	call %GETKEY
	ld s0, x5
	advn s0, #7
	ret

_EXPR_INPUT:
	ld s0, x5
EXPR_INPUT:
	ld z0, %keyboard
	call %GETS
	ld s0, %keyboard
	call %FETCH_VALUE
	xor w7, w7
	ld s0, x5
	advn s0, #6
	ret

_EXPR_PUT:
	ld s0, x5
EXPR_PUT:
	advn s0, #4
	call %EXPR
	ld s1, #2
	call %PUTC
	ret

_EXPR_PRINT:
	ld s0, x5
EXPR_PRINT:
	advn s0, #6
	call %EXPR
	pushw
	call %print_hex
	popw
	ld s0, %newl
	ld s1, #2
	call %PRINT
	ret

_EXPR_ASSIGN:
	ld s0, x5
EXPR_ASSIGN:
	advn s0, #7

	ld w0, s0
	ld s1, w0
	ld s7, w0
	ld s0, %cmd_at
	call %strcmp
	cmp #1
	bz %EXPR_ASSIGN_AT 

	ld w0, s7
	ld s0, w0

	; get name
	peek w0, .s0
	ld a, w0
	and #255
	ld x7, a
	inc s0
	inc s0

EXPR_EVAL:
	; evaluate
	call %EXPR
	ld w7, a
	ld a, x7
	call %SetVariable
	ld a, w7
	ret
EXPR_ASSIGN_AT:
	ld w0, s7
	ld s0, w0
	advn s0, #3

	call %FETCH_VALUE
	ld s7, a

	call %EXPR
	poke a, s7
	ret

_EXPR_EXIT:
	ld s0, x5
EXPR_EXIT:
	popx
	popw
	ld x1, %max_line
	dec x1
	pushw
	pushx
	ret

	; a == line_num
get_line:
	ld w0, a
	ld w1, %line_len
	call %mul
	add %lines
	ld z7, a
	ret
	; s0 == src
	; a == line_num
copy_to_line:
	; save
	ld x6, s0
	call %get_line
	ld w7, %line_len
	dec w7
copy_to_line_l0:
	peek w1, .s0
	poke w1, .z7
	inc z7
	inc s0
	dec w7
	bnz %copy_to_line_l0
	; restore
	ld s0, x6
	ret

EXPR:
	ld x5, s0
	ld w7, #0

	ld s1, x5
	ld s0, %cmd_add
	call %strcmp
	cmp #1
	bz %_EXPR_ADD

	ld s1, x5
	ld s0, %cmd_sub
	call %strcmp
	cmp #1
	bz %_EXPR_SUB

	ld s1, x5
	ld s0, %cmd_mul
	call %strcmp
	cmp #1
	bz %_EXPR_MUL

	ld s1, x5
	ld s0, %cmd_and
	call %strcmp
	cmp #1
	bz %_EXPR_AND

	ld s1, x5
	ld s0, %cmd_str
	call %strcmp
	cmp #1
	bz %_EXPR_STR

	ld s1, x5
	ld s0, %cmd_or
	call %strcmp
	cmp #1
	bz %_EXPR_OR

	ld s1, x5
	ld s0, %cmd_xor
	call %strcmp
	cmp #1
	bz %_EXPR_XOR

	ld s1, x5
	ld s0, %cmd_not
	call %strcmp
	cmp #1
	bz %_EXPR_NOT

	ld s1, x5
	ld s0, %cmd_is
	call %strcmp
	cmp #1
	bz %_EXPR_IS

	ld s1, x5
	ld s0, %cmd_at
	call %strcmp
	cmp #1
	bz %_EXPR_AT

	ld s1, x5
	ld s0, %cmd_jump
	call %strcmp
	cmp #1
	bz %_EXPR_JUMP

	ld s1, x5
	ld s0, %cmd_if
	call %strcmp
	cmp #1
	bz %_EXPR_IF

	ld s1, x5
	ld s0, %cmd_print
	call %strcmp
	cmp #1
	bz %_EXPR_PRINT

	ld s1, x5
	ld s0, %cmd_assign
	call %strcmp
	cmp #1
	bz %_EXPR_ASSIGN

	ld s1, x5
	ld s0, %cmd_put
	call %strcmp
	cmp #1
	bz %_EXPR_PUT

	ld s1, x5
	ld s0, %cmd_input
	call %strcmp
	cmp #1
	bz %EXPR_INPUT

	ld s1, x5
	ld s0, %cmd_getkey
	call %strcmp
	cmp #1
	bz %_EXPR_GET_KEY

	ld s1, x5
	ld s0, %cmd_exit
	call %strcmp
	cmp #1
	bz %_EXPR_EXIT

	ld s0, x5
	jmp %FETCH_VALUE
	ret
