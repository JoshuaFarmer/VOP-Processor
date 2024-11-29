	; yes.
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
_char_to_nibble:
	; get char
	peek w0, .s0
	and w0, w2

	; exit
	cmp w0, #32
	bz %_string_to_hex_exit
	cmp w0, #0
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