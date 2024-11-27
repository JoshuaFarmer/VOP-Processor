	; all data
true:
	ds "true"
	db 10
	db 13
	db 0
false:
	ds "false"
	db 10
	db 13
	db 0
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
cmd_run:
	ds "run"
	db 0
cmd_load:
	ds "load"
	db 0
cmd_echo:
	ds "echo"
	db 0
cmd_get:
	ds "get"
	db 0
cmd_set:
	ds "set"
	db 0
cmd_deref:
	ds "deref"
	db 0
cmd_is:
	ds "is"
	db 0
cmd_add:
	ds "add"
	db 0