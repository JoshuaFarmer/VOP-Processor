	; expressions
	; return value of literal or var in A
	; ptr == s0
FETCH_VALUE:
	peek a, s0
	cmp #36
	bnz %string_to_hex
	call %GetVariable
	inc s0
	inc s0
	ret

	; if equal, return 1
	; else, return 0
	; S0 as ptr
IS:
	inc s0
	inc s0
	inc s0
	call %FETCH_VALUE
	ld w0, a
	call %FETCH_VALUE
	cmp w0
	bz %IS_EQ
	ld a, #0
	ret
IS_EQ:
	ld a, #1
	ret

echo_msg:
	ld s0, %keyboard
	xc a, s0
	add #5
	xc a, s0

	ld s1, #2
	call %PRINT

	ld s0, %newl
	ld s1, #2
	call %PRINT
	ret

get_var:
	ld s0, %keyboard
	xc a, s0
	add #4
	xc a, s0
	peek w0, .s0
	ld a, w0
	and #255
	cmp #91
	bc %get_var_end

	; get the address
	call %GetVariableAddress
	ld z0, a
	call %print_hex

	; print ": "
	ld s1, #2
	ld s0, %prompt2
	call %PRINT

	; get value
	peek w0, .z0
	ld a, w0
	call %print_hex

	; new line
	ld s1, #2
	ld s0, %newl
	call %PRINT
get_var_end:
	ret

set_var:
	ld s0, %keyboard
	xc a, s0
	add #4
	xc a, s0
	peek w0, .s0
	ld a, w0
	and #255
	cmp #91
	bc %set_var_end

	; get the address
	call %GetVariableAddress
	ld z1, a

	; get value
	ld a, %keyboard
	add #6
	ld s0, a

	; "$"
	peek w0, .s0
	ld w5, #255
	and w0, w5
	cmp w0, #36
	bz %set_var_var
set_var_literal:
	call %string_to_hex
	ld w0, a
	jmp %set_var_after
set_var_var:
	inc s0
	peek w0, .s0
	and w0, w5
	ld a, w0
	call %GetVariableAddress
	ld s0, a
	peek w0, .s0
set_var_after:
	poke w0, .z1
	call %get_var
set_var_end:
	ret

deref_var:
	; you cannot add values to
	; address registers,
	; so with swap with a
	; and do it that way
	ld s0, %keyboard
	xc a, s0
	add #6
	xc a, s0

	; and you cant load into
	; a from local page
	peek w0, .s0
	ld a, w0

	; i can't count the amount of times
	; i have forgot that it loads
	; 16 bits, not 8 bits
	; this has caused so much
	; headache that i wanna break
	; something
	and #255
	cmp #91
	bc %set_var_end

	; if its prefixed with "$"
	; assume its a variable
	; not a literal
	cmp #36
	bz %deref_variable
deref_lit:
	call %string_to_hex
	ld z1, a
	peek w0, .z1
	jmp %deref_var_after
deref_variable:
	; get variable address
	inc s0
	peek w0, .s0
	ld a, w0
	and #255
	call %GetVariableAddress

	; get value
	ld z1, a
	peek w0, .z1
	ld a, w0
	ld z1, a
	peek w0, .z1
deref_var_after:
	ld a, w0
	call %print_hex
	ld s1, #2
	ld s0, %newl
	call %PRINT
deref_var_end:
	ret