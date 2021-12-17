#!/bin/sh

# SCRIPT A32 - CST8152 - Fall 2021
#
# COMPILERS COURSE - SCRIPT ---------------------------------------------

clear

COMPILER=Compilers.exe

FILE1=A32A_Empty
FILE2=A32B_Hello
FILE3=A32C_Expression

# ---------------------------------------------------------------------
# - Begin of Tests (A32 - F21) ----------------------------------------
# ---------------------------------------------------------------------

#
# BASIC TESTS  ----------------------------------------------------------
#
# - Basic Tests (A32 - F21) - - - - - - - - - - - - - - - - - - - - - -

$COMPILER 3 $FILE1.phx > $FILE1.out	2> $FILE1.err
$COMPILER 3 $FILE2.phx > $FILE2.out	2> $FILE2.err
$COMPILER 3 $FILE3.phx > $FILE3.out	2> $FILE3.err

echo "Showing A32 Results..."

echo =========================
cat $FILE1.out
echo .........................
cat $FILE2.out
echo .........................
cat $FILE3.out
echo =========================
ls *.out
ls *.err

# ---------------------------------------------------------------------
# - End of Tests (A32 - F21) ------------------------------------------
# ---------------------------------------------------------------------
