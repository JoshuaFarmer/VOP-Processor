; theoretically you can use macros to retarget the assembler (lmao) as they are resolved before instructions;

; MACRO NAME <ARGS>
macro jne x y addr
	ld a, $x
	cmp $y
	bnz $addr
endmacro

macro inf
	__inf:
	jmp %__inf
endmacro

macro test x
	if($x==1)
		ld a,#10
	endif
endmacro

	org 1024
init:
	inc w0
	jne w0, #1, %init
	inf
	test 0