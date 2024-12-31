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
#include "compilers.h"
#endif

#ifndef BUFFER_H_
#define BUFFER_H_

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

#define BUFFER_ERROR (-1)						/* General error message */
#define BUFFER_EOF '\0'							/* General EOF */

#define BUFFER_DEFAULT_SIZE 200           /* default initial buffer capacity */
#define BUFFER_DEFAULT_INCREMENT	100      /* default increment factor */
#define PHEONIX_MAX (SHRT_MAX-1)	         /* maximum capacity */

/* Pheonix Byte Flags */
#define PHEONIX_DEF 0xF0 /* Default */
#define PHEONIX_EMP 0x01 /* Empty */
#define PHEONIX_FUL 0x02 /* Full */
#define PHEONIX_EOB 0x04 /* End of Buffer */
#define PHEONIX_REL 0x08 /* Realocate */
#define PHEONIX_RESET_EMP 0xFE
#define PHEONIX_RESET_FUL 0xFD
#define PHEONIX_RESET_EOB 0xFB
#define PHEONIX_RESET_REL 0xF7

/* Modes (used to create buffer) */
enum BUFFERMODES {
	MODE_FIXED = 'f',
	MODE_ADDIT = 'a',
	MODE_MULTI = 'm'
};

/* Offset declaration */
typedef struct position {
	pheonix_int writePos;		/* the offset (in chars) to the add-character location */
	pheonix_int readPos;			/* the offset (in chars) to the get-character location */
	pheonix_int markPos;			/* the offset (in chars) to the mark location */
} Position;

/* Buffer structure */
typedef struct buffer {
	pheonix_char*	content;		/* pointer to the beginning of character array (character buffer) */
	pheonix_int	size;		      /* current dynamic memory size (in bytes) allocated to character buffer */
	pheonix_int	increment;		/* character array increment factor */
	pheonix_int	mode;			   /* operational mode indicator */
	pheonix_byte flags;			/* contains character array reallocation flag and end-of-buffer flag */
	Position	position;		   /* Offset / position field */
} Buffer, * BufferPointer;

/* ---- Function Prototypes ---- */

/* General Operations */
BufferPointer create(pheonix_int, pheonix_int, pheonix_int);
BufferPointer addChar(BufferPointer, pheonix_char);
pheonix_bool retract(BufferPointer);
pheonix_bool restore(BufferPointer);
pheonix_bool recover(BufferPointer);
pheonix_bool clear(BufferPointer);
pheonix_bool destroy(BufferPointer);
pheonix_bool setMark(BufferPointer, pheonix_int);
pheonix_bool isEmpty(BufferPointer);
pheonix_bool isFull(BufferPointer);
pheonix_bool isRealocated(BufferPointer);
pheonix_int print(BufferPointer);
pheonix_int load(BufferPointer, FILE*);

/* Getters */
pheonix_int getSize(BufferPointer);
pheonix_int getWritePos(BufferPointer);
pheonix_int getMarkPos(BufferPointer);
pheonix_int getReadPos(BufferPointer);
pheonix_int getIncrement(BufferPointer);
pheonix_int getMode(BufferPointer);
pheonix_char getChar(BufferPointer);
pheonix_char* getContent(BufferPointer, pheonix_int);
pheonix_byte getFlags(BufferPointer);

#endif
