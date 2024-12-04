 ; example string
$0 assign S 128
$1 str $S "Hello\K"
$2 jump 64

 ; printf
$64 assign P $S
$65 assign C at $P
$66 if is $C 0 exit
$67 put $C
$68 assign P add $P 2
$69 jump 65
