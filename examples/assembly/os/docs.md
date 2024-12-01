the docs of the language (WIP, BARELY WORKS):

we have a few simple commands that make it "usable",
but it lacks strings or arrays, anyway here it is!
note: most operands can also be expressions e.g. print add $T 1
or is $A add $B $C

# run
shell command, run the program

# list
shell command, list the code (without line numbers...)

# is
test whether the two operands are equal (return one on true)

# or
logical bitwise or the two operands

# and
logical bitwise and the two operands

# xor
logical bitwise xor the two operands

# add
add the two operands

# sub
subtract the two operands

# mul
multiply the two operands

# jump
like goto in basic, jump to line number, e.g. jump 0 (or jump $A (hmmm))

# if
if the first expression is true (not zero) it executes the next expression
e.g.
$(line number) if is $A 8 jump (other line number)

# print
print the expressions result
e.g. print add 2 2

# input
get hex integer from the user.
e.g. assign I input

# assign
assign the given variable (no $ needed).
to the result of the expression.
e.g. assign A add $A $B

# put
print the expression as a char.

please note that EVERY number is in hex,
decimal is soon to be implemented

# COMING SOON:
arrays so i can make strings
merging put&print by keeping track
of types.
poking/peeking in ram.
less/greater than
arrays will probably be like:
$N assign $V array 1 2 3 4 5 6 7 8 9
$N print getn $V 2
it would work by overhauling the var system
instead of the ptr containing the value,
the value would point to the data,
which is prefixed with the type and length.