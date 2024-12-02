	; all data
cat:
	ds " /\_/\ "
	db 10
	ds "( o.o )"
	db 10
 	ds " > ^ <"
	db 10
	db 0
prompt:
	ds ":3 $ > "
	db 0
prompt2:
	ds ": "
	db 0
newl:
	db 10
	db 13
	db 0
cmd_run:
	ds "run"
	db 0
cmd_list:
	ds "list"
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
cmd_or:
	ds "or"
	db 0
cmd_and:
	ds "and"
	db 0
cmd_xor:
	ds "xor"
	db 0
cmd_sub:
	ds "sub"
	db 0
cmd_add:
	ds "add"
	db 0
cmd_sub:
	ds "sub"
	db 0
cmd_mul:
	ds "mul"
	db 0
cmd_jump:
	ds "jump"
	db 0
cmd_if:
	ds "if"
	db 0
cmd_print:
	ds "print"
	db 0
cmd_put:
	ds "put"
	db 0
cmd_input:
	ds "input"
	db 0
cmd_assign:
	ds "assign"
	db 0
cmd_not:
	ds "not"
	db 0
cmd_exit:
	ds "exit"
	db 0
list_msg:
	ds "Listing Program.."
	db 10
	db 0
run_msg:
	ds "Running Program.."
	db 10
	db 0