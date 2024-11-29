macro test: x y
	sub $x
	add $y
end

start:
	test: #2, #5
	jmp %start