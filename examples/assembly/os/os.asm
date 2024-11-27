	org 1024
	define stack 65535
	define variables 4096
	define keyboard 8192
	define lines 16384
	define line_len 32
	define max_line 100

	; FIRST PROGRAM TO USE NEW STACK POINTERS!! (s4 to z7)
	; yes, this cpu has 16 stack pointers/address registers...
_start:
	format .#0
	ld s3, %stack
	push .#0, s3
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
	ld s1, %cmd_assign
	call %strcmp
	cmp #1
	bz %proc_assign

	ld s0, %keyboard
	ld s1, %cmd_echo
	call %strcmp
	cmp #1
	bz %proc_echo

	ld s0, %keyboard
	ld s1, %cmd_get
	call %strcmp
	cmp #1
	bz %proc_get

	ld s0, %keyboard
	ld s1, %cmd_set
	call %strcmp
	cmp #1
	bz %proc_set

	ld s0, %keyboard
	ld s1, %cmd_deref
	call %strcmp
	cmp #1
	bz %proc_deref

	ld s0, %keyboard
	ld s1, %cmd_is
	call %strcmp
	cmp #1
	bz %proc_is

	ld s0, %keyboard
	ld s1, %cmd_add
	call %strcmp
	cmp #1
	bz %proc_add

	ld s0, %keyboard
	ld s1, %cmd_sub
	call %strcmp
	cmp #1
	bz %proc_sub

	ld s0, %keyboard
	ld s1, %cmd_mul
	call %strcmp
	cmp #1
	bz %proc_mul

	ld s0, %keyboard
	ld s1, %cmd_assign
	call %strcmp
	cmp #1
	bz %proc_assign

	ld s0, %keyboard
	ld s1, %cmd_list
	call %strcmp
	cmp #1
	bz %proc_list

	ld s0, %keyboard
	ld s1, %cmd_run
	call %strcmp
	cmp #1
	bz %proc_run

	; line num
	ld s0, %keyboard
	call %string_to_hex
	ld s0, %keyboard
	xc a, s0
	add #5
	xc a, s0
	call %copy_to_line
	ret

	; CMDS
proc_run:
	ld s1, #2
	ld s0, %run_msg
	call %PRINT

	ld x1, #0
	ld x2, %max_line
proc_run_w0:
	ld a, x1
	call %get_line
	ld s0, a
	peek a, s0
	cmp #0
	bnz %run_line
run_after:
	inc x1
	cmp x1, x2
	bnz %proc_run_w0
	ret
run_line:
	call %EXPR
	jmp %run_after

proc_list:
	ld s1, #2
	ld s0, %list_msg
	call %PRINT

	ld x1, #0
	ld x2, %max_line
proc_list_w0:
	ld a, x1
	call %get_line
	ld s0, a
	peek a, s0
	cmp #0
	bnz %print_list
list_after:
	inc x1
	cmp x1, x2
	bnz %proc_list_w0
	ret
print_list:
	ld s1, #2
	call %PRINT
	ld s0, %newl
	call %PRINT
	jmp %list_after

proc_sub:
	ld s0, %keyboard
	call %EXPR_SUB
	call %print_hex
	ld s0, %newl
	ld s1, #2
	call %print
	ret

proc_mul:
	ld s0, %keyboard
	call %EXPR_MUL
	call %print_hex
	ld s0, %newl
	ld s1, #2
	call %print
	ret

proc_add:
	ld s0, %keyboard
	call %EXPR_ADD
	call %print_hex
	ld s0, %newl
	ld s1, #2
	call %print
	ret

proc_is:
	ld s0, %keyboard
	call %EXPR_IS
	bz %is_equal
	ld s1, #2
	ld s0, %false
	call %PRINT
	ret
is_equal:
	ld s1, #2
	ld s0, %true
	call %PRINT
	ret

proc_echo:
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

proc_get:
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

proc_set:
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
	call %proc_get
set_var_end:
	ret

proc_deref:
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

__inf__:
	jmp %__inf__

	include "io.asm"
	include "hex.asm"
	include "expr.asm"
	include "math.asm"
	include "vars.asm"
	include "data.asm"