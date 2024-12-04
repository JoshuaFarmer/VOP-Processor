	org 1024
	define stack 65535
	define call_stack 61440
	define lang_call_stack 59392
	define variables 16000
	define keyboard 16100
	define lines 16384
	define line_len 32
	define max_line 512

	; for registers that you
	; cant use "ADD",
	; (address registers)
	; e.g. advn S0, #32
	macro advn x n
		xc a, $x
		add $n
		xc a, $x
	end

	macro pusha
		push a, s4
		push w0, s4
		push w1, s4
		push w2, s4
		push w3, s4
		push w4, s4
		push w5, s4
		push w6, s4
		push w7, s4
	end

	macro popa
		pop w7, s4
		pop w6, s4
		pop w5, s4
		pop w4, s4
		pop w3, s4
		pop w2, s4
		pop w1, s4
		pop w0, s4
		pop a, s4
	end

	macro pushw
		push w0, s4
		push w1, s4
		push w2, s4
		push w3, s4
		push w4, s4
		push w5, s4
		push w6, s4
		push w7, s4
	end

	macro popw
		pop w7, s4
		pop w6, s4
		pop w5, s4
		pop w4, s4
		pop w3, s4
		pop w2, s4
		pop w1, s4
		pop w0, s4
	end

	macro pushx
		push x0, s4
		push x1, s4
		push x2, s4
		push x3, s4
		push x4, s4
		push x5, s4
		push x6, s4
		push x7, s4
	end

	macro popx
		pop x7, s4
		pop x6, s4
		pop x5, s4
		pop x4, s4
		pop x3, s4
		pop x2, s4
		pop x1, s4
		pop x0, s4
	end

	macro outx port value
		ld z7, s0
		ld s0, $port
		ld a, $value
		out
		ld s0, z7
	end

	; FIRST PROGRAM TO USE NEW STACK POINTERS!! (s4 to z7)
	; yes, this cpu has 16 stack pointers/address registers...
_start:
	ld s3, %call_stack
	ld s4, %stack
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
	ld x1, #65535
	ld s1, %keyboard
	ld s0, %cmd_echo
	call %strcmp
	cmp #1
	bz %proc_echo

	ld s1, %keyboard
	ld s0, %cmd_get
	call %strcmp
	cmp #1
	bz %proc_get

	ld s1, %keyboard
	ld s0, %cmd_set
	call %strcmp
	cmp #1
	bz %proc_set

	;ld s0, %keyboard
	;ld s1, %cmd_deref
	;call %strcmp
	;cmp #1
	;bz %proc_deref

	ld s1, %keyboard
	ld s0, %cmd_list
	call %strcmp
	cmp #1
	bz %proc_list

	ld s1, %keyboard
	ld s0, %cmd_run
	call %strcmp
	cmp #1
	bz %proc_run

	ld s1, %keyboard
	peek a, s1
	and #255
	cmp #36
	ld s0, %keyboard
	bz %proc_expr

	ld s0, %keyboard
	call %EXPR
	ret

proc_expr:
	ld s0, %keyboard
	inc s0
	call %string_to_hex
	inc s0
	call %copy_to_line
	ret
	; CMDS
proc_run:
	ld x1, #0
_proc_run:
	ld z4, %lang_call_stack
	ld s1, #2
	ld s0, %run_msg
	call %PRINT

	; line counter
	ld x2, %max_line
proc_run_w0:
	ld a, x1
	call %get_line
	ld s0, a
	peek a, s0
	cmp #0
	bnz %run_line
run_after_1:
	inc x1
	cmp x1, x2
	bnz %proc_run_w0
	ret
run_line:
	pushw
	pushx
	call %EXPR
	popx
	popw
	jmp %run_after_1

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

; proc_deref:
; 	; you cannot add values to
; 	; address registers,
; 	; so with swap with a
; 	; and do it that way
; 	ld s0, %keyboard
; 	xc a, s0
; 	add #6
; 	xc a, s0

; 	; and you cant load into
; 	; a from local page
; 	peek w0, .s0
; 	ld a, w0

; 	; i can't count the amount of times
; 	; i have forgot that it loads
; 	; 16 bits, not 8 bits
; 	; this has caused so much
; 	; headache that i wanna break
; 	; something
; 	and #255
; 	cmp #91
; 	bc %set_var_end

; 	; if its prefixed with "$"
; 	; assume its a variable
; 	; not a literal
; 	cmp #36
; 	bz %deref_variable
; deref_lit:
; 	call %string_to_hex
; 	ld z1, a
; 	peek w0, .z1
; 	jmp %deref_var_after
; deref_variable:
; 	; get variable address
; 	inc s0
; 	peek w0, .s0
; 	ld a, w0
; 	and #255
; 	call %GetVariableAddress

; 	; get value
; 	ld z1, a
; 	peek w0, .z1
; 	ld a, w0
; 	ld z1, a
; 	peek w0, .z1
; deref_var_after:
; 	ld a, w0
; 	call %print_hex
; 	ld s1, #2
; 	ld s0, %newl
; 	call %PRINT
; deref_var_end:
; 	ret

__inf__:
	jmp %__inf__
shutdown:
	ld s0, #0
	out
	jmp %__inf__

	include "io.asm"
	include "video.asm"
	include "hex.asm"
	include "expr.asm"
	include "math.asm"
	include "vars.asm"
	include "data.asm"