; MACRO NAME <ARGS>
macro test x y
	sub $x
	add $y
end

macro je x y addr
	ld a, $x
	cmp $y
	bz $addr
end

macro jne x y addr
	ld a, $x
	cmp $y
	bnz $addr
end

macro inf
	__inf:
	jmp %__inf
end

start:
	inc w0
	jne w0, #1, %start
	inf