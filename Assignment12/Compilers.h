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

/* Logical constants - adapt for your language */
#define SOFIA_TRUE	1
#define SOFIA_FALSE 0

/*
------------------------------------------------------------
Programs:
1: Buffer - invokes MainBuffer code
2: Scanner - invokes MainScanner code
3: Parser - invokes MainParser code
------------------------------------------------------------
*/
enum PROGRAMS {
	PGM_BUFFER	= '1',
	PGM_SCANNER = '2',
	PGM_PARSER	= '3'
};

/*
------------------------------------------------------------
Main functions signatures
(Codes will be updated during next assignments)
------------------------------------------------------------
*/
int mainBuffer	(int argc, char** argv);
int mainScanner	(int argc, char** argv);
int mainParser	(int argc, char** argv);

/*
------------------------------------------------------------
Data types definitions
------------------------------------------------------------
*/

/* TO_DO: Define your typedefs */

typedef short			sofia_int;
typedef long			sofia_lng;
typedef char			sofia_chr;
typedef unsigned char	sofia_flg;
typedef char			sofia_bol;
typedef float			sofia_flt;
typedef double			sofia_dbl;
typedef void			sofia_nul;

#endif
