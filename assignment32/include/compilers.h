/*************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2020
* Author: Paulo Sousa - Sep, 2021.
*************************************************************
* File name: compilers.h
* Compiler: MS Visual Studio 2019
* Author: Paulo Sousa
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A1, A2, A3.
* Date: Sep 01 2020
* Professor: Paulo Sousa / Haider Miraj
* Purpose: This file defines the functions called by main function.
* Function list: mainBuffer(), mainScanner(), mainParser().
*************************************************************/

#ifndef COMPILERS_H_
#define COMPILERS_H_

#define DEBUG 0
#define PHEONIX_TRUE	1
#define PHEONIX_FALSE 0

/*
------------------------------------------------------------
Programs:
1: Buffer - invokes MainBuffer code
2: Scanner - invokes MainScanner code
3: Parser - invokes MainParser code
------------------------------------------------------------
*/
enum PROGRAMS {
	PGM_BUFFER = '1',
	PGM_SCANNER,
	PGM_PARSER
};

/* Function Prototypes */
int mainBuffer(int argc, char* argv[]);
int mainScanner(int argc, char* argv[]);
int mainParser(int argc, char* argv[]);

/* Required Typedefs */
typedef int 		   	pheonix_int;
typedef long				pheonix_long;
typedef char			   pheonix_char;
typedef unsigned char	pheonix_byte;
typedef unsigned char   pheonix_bool;
typedef float				pheonix_float;
typedef double				pheonix_double;
typedef void				pheonix_void;

#endif
