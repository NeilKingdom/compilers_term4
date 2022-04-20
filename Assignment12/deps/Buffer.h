/*************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2021
*************************************************************
* File name: Buffer.h
* Compiler: MS Visual Studio 2019
* Author: Paulo Sousa (based on prof. Svillen Ranev work)
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A12.
* Date: Sep 01 2021
* Purpose: This file is the main header for Parser (.h)
*************************************************************/


#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#define BUFFER_H_

/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer) */
enum BUFFERMODES {
	MODE_FIXED = 'f',
	MODE_ADDIT = 'a',
	MODE_MULTI = 'm'
};

/* TO_DO: Adjust all constants to your Language */

#define BUFFER_ERROR (-1)						/* General error message */
#define BUFFER_EOF '\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA) .................................. */

#define BUFFER_DEFAULT_SIZE			200			/* default initial buffer capacity */
#define BUFFER_DEFAULT_INCREMENT	100			/* default increment factor */

/* You should add your own constant definitions here */
#define SOFIA_MAX_SIZE				SHRT_MAX-1	/*maximum capacity*/

/* Add your bit-masks constant definitions here - Defined for SOFIA */
/* BITS                                7654.3210 */
#define SOFIA_DEFAULT_FLAG 0xF0 	/* 1111.0000 = 240 */
/* TO_DO: BIT 0: EMP: Empty */
/* TO_DO: BIT 1: FUL = Full */
/* TO_DO: BIT 2: EOB = EndOfBuffer */
/* TO_DO: BIT 3: REL = Relocation */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* TO_DO: Adjust datatypes */

/* Offset declaration */
typedef struct position {
	sofia_int writePos;				/* the offset (in chars) to the add-character location */
	sofia_int readPos;				/* the offset (in chars) to the get-character location */
	sofia_int markPos;				/* the offset (in chars) to the mark location */
} Position;

/* Buffer structure */
typedef struct buffer {
	sofia_chr*	content;		/* pointer to the beginning of character array (character buffer) */
	sofia_int	size;		    /* current dynamic memory size (in bytes) allocated to character buffer */
	sofia_int	increment;		/* character array increment factor */
	sofia_int	mode;			/* operational mode indicator */
	sofia_flg	flags;			/* contains character array reallocation flag and end-of-buffer flag */
	Position	position;		/* Offset / position field */
} Buffer, * BufferPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
BufferPointer create(sofia_int, sofia_int, sofia_int);
BufferPointer addChar(BufferPointer const, sofia_chr);
sofia_bol retract(BufferPointer const);
sofia_bol restore(BufferPointer const);
sofia_bol recover(BufferPointer const);
sofia_bol clear(BufferPointer const);
sofia_bol destroy(BufferPointer const);
sofia_bol setMark(BufferPointer const, sofia_int);
sofia_bol isEmpty(BufferPointer const);
sofia_bol isFull(BufferPointer const);
sofia_bol isRealocated(BufferPointer const);
sofia_int print(BufferPointer const);
sofia_int load(BufferPointer const, FILE* const);
/* Getters */
sofia_int getSize(BufferPointer const);
sofia_int getWritePos(BufferPointer const);
sofia_int getMarkPos(BufferPointer const);
sofia_int getReadPos(BufferPointer const);
sofia_int getIncrement(BufferPointer const);
sofia_int getMode(BufferPointer const);
sofia_chr getChar(BufferPointer const);
sofia_chr* getContent(BufferPointer const, sofia_int);
sofia_flg getFlags(BufferPointer const);

#endif
