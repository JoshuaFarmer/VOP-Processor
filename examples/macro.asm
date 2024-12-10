; theoretically you can use macros to retarget the assembler (lmao) as they are resolved before instructions;

; MACRO NAME <ARGS>
macro jne x y addr
	ld a, $x
	cmp $y
	bnz $addr
end

macro inf x
	__inf$x:
	jmp %__inf$x
end

	org 1024
init:
	inc w0
	jne w0, #1, %init
	inf 0
