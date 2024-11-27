	org 1024
	define stack 65535
	define variables 4096
	define keyboard 8192
	; FIRST PROGRAM TO USE NEW STACK POINTERS!! (s4 to z7)
	; yes, this cpu has 16 stack pointers/address registers...
_start:
	ld s3, %stack
	push .#1, s3
	pop p1, s3
	ld s1, #2
	ld s0, %cat
	call %PRINT
_inf:
	ld s1, #2
	ld s0, %prompt
	call %PRINT

	ld z0, %keyboard
	call %GETS
	call %CMD
	jmp %_inf

CMD:
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

__inf__:
	jmp %__inf__

	include "io.asm"
	include "hex.asm"
	include "expr.asm"
	include "math.asm"
	include "vars.asm"
	include "data.asm"