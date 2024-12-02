	org 1024
_start:
	mov a, [%_start]
	cmp [%_start]
	bz %yes
no:
	mov w0, #32
	out
yes:
	mov w1, #2
	out