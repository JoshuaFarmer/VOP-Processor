	; all data
cat:
	ds" ,_     _"
	db 10
	ds" |\\_,-~/"
	db 10
	ds" / _  _ |    ,--."
	db 10
	ds"(  @  @ )   / ,-'"
	db 10
	ds" \  _T_/-._( ("
	db 10
	ds" /         `. \"
	db 10
	ds"|         _  \ |"
	db 10
	ds" \ \ ,  /      |"
	db 10
	ds"  || |-_\__   /"
	db 10
	ds" ((_/`(____,-'"
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
cmd_is:
	ds "is"
	db 0
cmd_str:
	ds "str"
	db 0
cmd_getkey:
	ds "getkey"
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
cmd_at:
	ds "at"
	db 0
cmd_exit:
	ds "exit"
	db 0
cmd_call:
	ds "call"
	db 0
cmd_rts:
	ds "rts"
	db 0
cmd_less:
	ds "less"
	db 0
cmd_greater:
	ds "greater"
	db 0
list_msg:
	ds "Listing Program.."
	db 10
	db 0
run_msg:
	ds "Running Program.."
	db 10
	db 0
