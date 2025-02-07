$1 assign A 0
$2 assign B 1
$3 assign C 0
$4 assign N 8
$5 print $C
$6 assign A $B
$7 assign B $C
$8 assign C add $A $B
$9 assign N sub $N 1
$A if greater $N 0 jump 5
$B exit