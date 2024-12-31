#!/bin/sh

# SCRIPT A32 - CST8152 - Fall 2021
#
# COMPILERS COURSE - SCRIPT ---------------------------------------------

clear

COMPILER=compiler

TEST_DIR="test"
FILE1=empty
FILE2=hello_world
FILE3=expression

# ---------------------------------------------------------------------
# - Begin of Tests (A32 - F21) ----------------------------------------
# ---------------------------------------------------------------------

#
# BASIC TESTS  ----------------------------------------------------------
#
# - Basic Tests (A32 - F21) - - - - - - - - - - - - - - - - - - - - - -

$COMPILER 3 ${TEST_DIR}/${FILE1}.phx > $FILE1.out 2> ${TEST_DIR}/${FILE1}.err
$COMPILER 3 ${TEST_DIR}/${FILE2}.phx > $FILE2.out 2> ${TEST_DIR}/${FILE2}.err
$COMPILER 3 ${TEST_DIR}/${FILE3}.phx > $FILE3.out 2> ${TEST_DIR}/${FILE3}.err

echo "Showing A32 Results..."

echo =========================
cat ${TEST_DIR}/${FILE1}.out
echo .........................
cat ${TEST_DIR}/${FILE2}.out
echo .........................
cat ${TEST_DIR}/${FILE3}.out
echo =========================

# ---------------------------------------------------------------------
# - End of Tests (A32 - F21) ------------------------------------------
# ---------------------------------------------------------------------
