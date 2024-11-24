	org 1024
	define stack 65535
	define variables 4096
	; FIRST PROGRAM TO USE NEW STACK POINTERS!! (s4 to z7)
	; yes, this cpu has 16 stack pointers/address registers...
	; PROGRAMMERS NOTE :
	; z0 is the text pos, dont mess with!
_start:
	ld s3, %stack
	ld a, #65
	call %print_hex
	push .#1, s3
	pop p1, s3
_inf:
	ld s1, #2
	ld s0, %prompt
	call %puts

	ld z0, %keyboard
	call %gets
	call %cmd
	jmp %_inf

	; A == name (A-Z)
	; returns address in a
_get_var:
	; (ord(name)-65) * 2 + 4096
	sub #65
	ld w0, #2
	ld w1, a
	call %mul
	add %variables
	ret

puts:
	xor w0, w0
_puts:
	peek a, .+w0
	and #255
	cmp #0
	retz
	inc w0
	xc s0, s1
	out
	xc s0, s1
	jmp %_puts

get_from_port:
	in
	cmp #0
	bz %get_from_port
	ret

gets:
	ld s0, #3
	call %get_from_port
	ld w0, a

	poke w0, .z0
	ld s0, #2

	cmp #8
	bz %back

	out

	inc z0
	cmp #13
	bnz %gets

	ld s0, %newl
	call %puts
	ld w0, #0
	poke w0, .z0
	inc z0
	ret
back:
	ld x7, z0
	cmp x7, %keyboard
	bz %gets
	dec z0
	out
	ld a, #32
	out
	ld a, #8
	out
	jmp %gets

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
cmd:
	ld s0, %keyboard
	ld s1, %echo
	call %strcmp
	cmp #1
	cz %echo_msg

	ld s0, %keyboard
	ld s1, %get
	call %strcmp
	cmp #1
	cz %get_var

	ld s0, %keyboard
	ld s1, %set
	call %strcmp
	cmp #1
	cz %set_var

	ld s0, %keyboard
	ld s1, %deref
	call %strcmp
	cmp #1
	cz %deref_var
	ret

	; inp = a
print_hex:
	ld s0, #2
	ld w2, #4
	ld w3, #12
	ld w0, a
__print_hex:
	ld a, w0
	shr w3
	sub w3, #4
	and #15
	cmp #10
	bc %__print_hex_alpha
	bz %__print_hex_alpha
	add #48
__print_hex_do:
	out
	dec w2
	bnz %__print_hex
	ret
__print_hex_alpha:
	add #55
	jmp %__print_hex_do

	; use s0 as address to string, output is A
string_to_hex:
	; init return value and bits to shift by
	ld a, #0
	ld w1, #4
	ld w2, #255
	ld w5, #15
	ld w7, #5
_char_to_nibble:
	; get char
	peek w0, .s0
	and w0, w2
	dec w7
	bz %_string_to_hex_exit
	cmp w0, #65
	bc %_char_to_nibble_alpha
	bz %_char_to_nibble_alpha

	; non alpha (0-9)
	sub w0, #48
_char_to_nibble_do:
	and w0, w5
	shl w1
	or w0
	inc s0
	jmp %_char_to_nibble
_string_to_hex_exit:
	ret
_char_to_nibble_alpha:
	sub w0, #55
	jmp %_char_to_nibble_do

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
	call %_get_var
	ld z0, a
	call %print_hex

	; print ": "
	ld s1, #2
	ld s0, %prompt2
	call %puts

	; get value
	peek w0, .z0
	ld a, w0
	call %print_hex

	; new line
	ld s1, #2
	ld s0, %newl
	call %puts
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
	call %_get_var
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
	call %_get_var
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
	peek w0, .s0
	ld w5, #255
	and w0, w5
	cmp w0, #36
	bz %deref_variable
deref_lit:
	call %string_to_hex
	ld w0, a
	jmp %deref_var_after
deref_variable:
	inc s0
	peek w0, .s0
	and w0, w5
	ld a, w0
	call %_get_var
	ld s0, a
	peek w0, .s0
deref_var_after:
	peek w0, .z1
	ld a, w0
	call %print_hex
deref_var_end:
	ret

echo_msg:
	ld s0, %keyboard
	xc a, s0
	add #5
	xc a, s0

	ld s1, #2
	call %puts

	ld s0, %newl
	ld s1, #2
	call %puts
	ret

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

__inf__:
	jmp %__inf__

prompt:
	ds "> "
	db 0
prompt2:
	ds ": "
	db 0
newl:
	db 13
	db 10
	db 0
run:
	ds "run"
	db 0
load:
	ds "load"
	db 0
echo:
	ds "echo"
	db 0
get:
	ds "get"
	db 0
set:
	ds "set"
	db 0
deref:
	ds "deref"
	db 0
keyboard:
	db 0