; MACRO NAME <ARGS>
macro jne x y addr
	ld a, $x
	cmp $y
	bnz $addr
end

macro inf
	__inf:
	jmp %__inf
end

	org 1024
start:
	inc w0
	jne w0, #1, %start
	inf