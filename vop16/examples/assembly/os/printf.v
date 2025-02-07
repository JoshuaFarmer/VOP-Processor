$1 assign B 10
$2 str $B "Hello\K"
$3 assign B 10
$4 call 64
$5 exit
$64 assign P $B
$65 assign C at $P
$66 if is $C 0 exit
$67 put $C
$68 assign P add $P 2
$69 jump 65
$6A rts
