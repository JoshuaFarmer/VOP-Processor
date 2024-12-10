 ;ARRAY.V
 ;DO NOT TOUCH Q
 ;Q HOLDS START OF ARRAYS
 ;FIRST WORD IS LEN
 ;REST IS DAT

$0 assign Q 0
$1 assign L 10
$2 call 32
$3 print $A
$4 call 32
$5 print $A
$6 exit

 ; CREATE_ARR
 ; $L=LENGTH
 ; $A=NEW_ARR
$32 assign at $Q $L
$33 assign A $Q
$34 assign Q add $Q add $L 1
$35 rts
 ; GET_ELEM
 ; $A=ARR_BASE
 ; $X=IDX
 ; $R=RETVALUE
