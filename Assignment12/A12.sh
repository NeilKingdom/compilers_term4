# SCRIPT A12 - CST8152 - Fall 2021
#
# COMPILERS COURSE - SCRIPT ---------------------------------------------

COMPILER="Buffer.exe"

FILE1="A12A_Empty"
FILE2="A12B_Hello"
FILE3="A12C_Basic"
FILE4="A12D_Big"

# ---------------------------------------------------------------------
# - Begin of Tests (A12 - F21) ----------------------------------------
# ---------------------------------------------------------------------

#
# BASIC TESTS  ----------------------------------------------------------
#
# - Basic Tests (A12 - F21) - - - - - - - - - - - - - - - - - - - - - -

$COMPILER 1 "$FILE1.phx" > "$FILE1.phx" 2> "$FILE1.err"
$COMPILER 1 "$FILE2.phx" > "$FILE2.phx" 2> "$FILE2.err"
$COMPILER 1 "$FILE3.phx" > "$FILE3.phx" 2> "$FILE3.err"

#
# ADVANCED TESTS  -------------------------------------------------------
#
# - Advanced Tests (A12 - F21) - - - - - - - - -- - - - - - - - - - - -

$COMPILER 1 "$FILE4.phx" f 100 10 > "$FILE4-f-100-10.out" 2> "$FILE4%-f-100-10.err"
$COMPILER 1 "$FILE4.phx" a 100 10 > "$FILE4-a-100-10.out" 2> "$FILE4%-a-100-10.err"
$COMPILER 1 "$FILE4.phx" m 100 10 > "$FILE4-m-100-10.out" 2> "$FILE4%-m-100-10.err"

# ---------------------------------------------------------------------
# - End of Tests (A12 - F21) ------------------------------------------
# ---------------------------------------------------------------------
