	; all data
cat:
	ds " /\_/\"
	db 13
	db 10
	ds "( o.o )"
	db 13
	db 10
 	ds " > ^ <"
	db 13
	db 10
	db 0
prompt:
	ds ":3 $ > "
	db 0
prompt2:
	ds ": "
	db 0
newl:
	db 13
	db 10
	db 0
run:
	ds "run"
	db 0
load:
	ds "load"
	db 0
echo:
	ds "echo"
	db 0
get:
	ds "get"
	db 0
set:
	ds "set"
	db 0
deref:
	ds "deref"
	db 0
data_is:
	ds "IS"
	db 0