:: SCRIPT A12 - CST8152 - Fall 2021
::
:: COMPILERS COURSE - SCRIPT ---------------------------------------------

SET COMPILER=Buffer.exe

SET FILE1=A12A_Empty
SET FILE2=A12B_Hello
SET FILE3=A12C_Basic
SET FILE4=A12D_Big

REM ---------------------------------------------------------------------
REM - Begin of Tests (A12 - F21) ----------------------------------------
REM ---------------------------------------------------------------------

ren *.exe %COMPILER%

::
:: BASIC TESTS  ----------------------------------------------------------
::
REM - Basic Tests (A12 - F21) - - - - - - - - - - - - - - - - - - - - - -

%COMPILER% 1 %FILE1%.sof	> %FILE1%.out	2> %FILE1%.err
%COMPILER% 1 %FILE2%.sof	> %FILE2%.out	2> %FILE2%.err
%COMPILER% 1 %FILE3%.sof	> %FILE3%.out	2> %FILE3%.err

::
:: ADVANCED TESTS  -------------------------------------------------------
::
REM - Advanced Tests (A12 - F21) - - - - - - - - -- - - - - - - - - - - -

%COMPILER% 1 %FILE4%.sof	f 100 10	> %FILE4%-f-100-10.out	2> %FILE4%-f-100-10.err
%COMPILER% 1 %FILE4%.sof	a 100 10	> %FILE4%-a-100-10.out	2> %FILE4%-a-100-10.err
%COMPILER% 1 %FILE4%.sof	m 100 10	> %FILE4%-m-100-10.out	2> %FILE4%-m-100-10.err

REM ---------------------------------------------------------------------
REM - End of Tests (A12 - F21) ------------------------------------------
REM ---------------------------------------------------------------------
