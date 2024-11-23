	org 1024
	define stack 65535
	; FIRST PROGRAM TO USE NEW STACK POINTERS!! (s4 to z7)
	; yes, this cpu has 16 stack pointers/address registers...
	; PROGRAMMERS NOTE :
	; z0 is the text pos, dont mess with!
_start:
	; set up page
	ld s3, %stack
	push .#1, s3
	pop p1, s3
	ld s1, #2
	ld s0, %prompt
	call %puts

	ld z0, %keyboard
	call %gets
_inf:
	jmp %_inf

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
	inc z0
	ld s0, #2
	out
	cmp #13
	bnz %gets

	ld s0, %newl
	call %puts
	ld s0, %keyboard
	call %puts
	ret

prompt:
	ds ">"
	db 0
newl:
	db 13
	db 10
	db 0
run:
	ds "RUN"
	db 0
load:
	ds "LOAD"
	db 0
keyboard: