/*************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2021
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa / Daniel Cormier
*************************************************************/

/*************************************************************
* File name: Scanner.c
* Compiler: MS Visual Studio 2019
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A22.
* Date: May 01 2021
* Professor: Paulo Sousa
* Purpose: This file contains all functionalities from Scanner.
* Function list: (...).
*************************************************************/

 /* The #define _CRT_SECURE_NO_WARNINGS should be used in MS Visual Studio projects
  * to suppress the warnings about using "unsafe" functions like fopen()
  * and standard sting library functions defined in string.h.
  * The define does not have any effect in Borland compiler projects.
  */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>   /* standard input / output */
#include <ctype.h>   /* conversion functions */
#include <stdlib.h>  /* standard library functions and constants */
#include <string.h>  /* string functions */
#include <limits.h>  /* integer types constants */
#include <float.h>   /* floating-point types constants */
#include <math.h>

/* #define NDEBUG        to suppress assert() call */
#include <assert.h>  /* assert() prototype */

/* project header files */

#ifndef COMPILERS_H_
#include "../deps/Compilers.h"
#endif

#ifndef BUFFER_H_
#include "../deps/Buffer.h"
#endif

#ifndef SCANNER_H_
#include "../deps/Scanner.h"
#endif

/*
----------------------------------------------------------------
Define external variables from Scanner.h
----------------------------------------------------------------
*/

pheonix_int transitionTable[][TABLE_COLUMNS] = {
   /*       {0,1},[2-9],[A-Z],[a-z],     ',   ",       $,    .,    EOS,   SEOF   Other   */
   /*       B(0),  D(1), U(2),  L(3),  A(4),  Q(5),  R(6),  P(7)  E(8),  F(9)    O(10)   */
   /* S00 */   {6,    4,    17,    16,    9,     12,    14,    1,    ER,    ER,    ER},   /* NOAS */
   /* S01 */   {2,    2,    ER,    ER,    ER,    ER,    ER,    ER,   ER,    ER,    ER},   /* NOAS */
   /* S02 */   {2,    2,    IS,    3,     IS,    IS,    IS,    IS,   IS,    IS,    IS},   /* ASWR (FPL) */
   /* S03 */   {IS,   IS,   IS,    IS,    IS,    IS,    IS,    IS,   IS,    IS,    IS},   /* ASWR (FPL) */
   /* S04 */   {5,    4,    IS,    IS,    IS,    IS,    IS,    1,    IS,    IS,    IS},   /* ASWR (IL) */
   /* S05 */   {5,    4,    IS,    IS,    IS,    IS,    IS,    1,    IS,    IS,    IS},   /* ASWR (IL) */
   /* S06 */   {5,    4,    IS,    7,     IS,    IS,    IS,    1,    IS,    IS,    IS},   /* ASWR (IL) */
   /* S07 */   {8,    ER,   ER,    ER,    ER,    ER,    ER,    ER,   ER,    ER,    ER},   /* NOAS */
   /* S08 */   {8,    IS,   IS,    IS,    IS,    IS,    IS,    IS,   IS,    IS,    IS},   /* ASWR (BL) */
   /* S09 */   {10,   10,   10,    10,    11,    10,    10,    10,   10,    ER,    10},   /* NOAS */
   /* S10 */   {ER,   ER,   ER,    ER,    11,    ER,    ER,    ER,   ER,    ER,    ER},   /* NOAS */
   /* S11 */   {IS,   IS,   IS,    IS,    IS,    IS,    IS,    IS,   IS,    IS,    IS},   /* ASWR (CL) */
   /* S12 */   {12,   12,   12,    12,    12,    13,    12,    12,   12,    ER,    12},   /* NOAS */
   /* S13 */   {IS,   IS,   IS,    IS,    IS,    IS,    IS,    IS,   IS,    IS,    IS},   /* ASNR (SL) */
   /* S14 */   {15,   15,   ER,    ER,    ER,    ER,    ER,    ER,   ER,    ER,    ER},   /* NOAS */
   /* S15 */   {15,   15,   IS,    IS,    IS,    IS,    IS,    IS,   IS,    IS,    IS},   /* ASWR (LVID) */
   /* S16 */   {17,   17,   17,    16,    IS,    IS,    IS,    IS,   IS,    IS,    IS},   /* ASWR (KEY) */
   /* S17 */   {17,   17,   17,    17,    IS,    IS,    IS,    IS,   IS,    IS,    IS},   /* ASWR (VID) */
   /* S18 */   {IS,   IS,   IS,    IS,    IS,    IS,    IS,    IS,   IS,    IS,    IS},   /* ASWR (ES) */
   /* S19 */   {IS,   IS,   IS,    IS,    IS,    IS,    IS,    IS,   IS,    IS,    IS},   /* ASWR (ER) */
   };

pheonix_int stateType[] = {
	  NOAS, /* 00 NOAS */
     NOAS, /* 01 NOAS */ 
     ASWR, /* 02 ASWR (FPL) */
     ASWR, /* 03 ASWR (FPL) */
     ASWR, /* 04 ASWR (IL) */
     ASWR, /* 05 ASWR (IL) */
     ASWR, /* 06 ASWR (IL) */
     NOAS, /* 07 NOAS */
     ASWR, /* 08 ASWR (BL) */
     NOAS, /* 09 NOAS */
     NOAS, /* 10 NOAS */
     ASWR, /* 11 ASWR (CL) */
     NOAS, /* 12 NOAS */
     ASNR, /* 13 ASNR (SL) */
     NOAS, /* 14 NOAS */      
     ASWR, /* 15 ASWR (LVID) */
     ASWR, /* 16 ASWR (KEY) */
     ASWR, /* 17 ASWR (VID) */
     ASNR, /* 18 ASWR (ES) */
     ASWR  /* 19 ASWR (ER) */
};            

PTR_ACCFUN finalStateTable[] = {
    NULL,    /*00 */
    NULL,    /* 01 */
    funcFL,  /* 02 */
    funcFL,  /* 03 */
    funcIL,  /* 04 */
    funcIL,  /* 05 */
    funcIL,  /* 06 */
    NULL,    /* 07 */
    funcBL,  /* 08 */
    NULL,    /* 09 */
    NULL,    /* 10 */
    funcCL,  /* 11 */
    NULL,    /* 12 */
    funcSL,  /* 13 */
    NULL,    /* 14 */
    funcLVID,/* 15 */
    funcKEY, /* 16 */
	 funcVID, /* 17 */
    funcErr, /* 18 */
    funcErr  /* 19 */
};

pheonix_char* keywordTable[] = {
   "int",
   "float",
   "char",
   "string",
	"byte",
   "bool",
   "void",
   "null",
   "if",
   "else",
   "while",
   "for",
   "function",
   "return",
   "print",
   "read",
   "true",
   "false",
   "import"
};

/*
----------------------------------------------------------------
TO_DO 12: Global vars definitions
----------------------------------------------------------------
*/

/* Global objects - variables */
/* This buffer is used as a repository for string literals. */
pheonix_int line;									/* Current line number of the source code */
extern pheonix_int errorNumber;					/* Defined in platy_st.c - run-time error number */
extern BufferPointer stringLiteralTable;		/* String literal table */

/* Local(file) global objects - variables */
static BufferPointer lexemeBuffer;			/* pointer to temporary lexeme buffer */
/*static BufferPointer sourceBuffer;			 pointer to input source buffer */
BufferPointer sourceBuffer;			 /* pointer to input source buffer */

/*************************************************************
 * Intitializes scanner
 *		This function initializes the scanner using defensive programming.
 ************************************************************/

/* ---- Finished ---- */

pheonix_int startScanner(BufferPointer psc_buf) {
	if (isEmpty(psc_buf)==PHEONIX_TRUE)
		return EXIT_FAILURE; /*1*/
	/* in case the buffer has been read previously  */
	recover(psc_buf);
	clear(stringLiteralTable);
	line = 1;
	sourceBuffer = psc_buf;
	return EXIT_SUCCESS; /*0*/
}

/*************************************************************
 * Process Token
 *		Main function of buffer, responsible to classify a char (or sequence
 *		of chars). In the first part, a specific sequence is detected (reading
 *		from buffer). In the second part, a pattern (defined by Regular Expression)
 *		is recognized and the appropriate function is called (related to final states 
 *		in the Transition Diagram).
 ************************************************************/
Token tokenizer(void) {

	/* TO_DO 14: Follow the standard and adjust datatypes */

	Token currentToken = { 0 }; /* token to return after pattern recognition. Set all structure members to 0 */
	pheonix_char c;             /* input symbol */
	pheonix_char newc;			 /* new char */
	pheonix_int i;				    /* counter */
	pheonix_int state = 0;		 /* initial state of the FSM */
	pheonix_int prevState = 0;
	pheonix_int copyState = 0;

	pheonix_int lexStart = 0;		 /* start offset of a lexeme in the input char buffer (array) */
	pheonix_int lexEnd = 0;		    /* end offset of a lexeme in the input char buffer (array)*/
	pheonix_int lexLength = 0;		 /* token length */

	while (1) { /* endless loop broken by token returns it will generate a warning */
		c = getChar(sourceBuffer);

		/* ------------------------------------------------------------------------
			Part 1: Implementation of token driven scanner.
			Every token is possessed by its own dedicated code
			-----------------------------------------------------------------------
		*/

		/* TO_DO 15: All patterns that do not require accepting functions */
		switch (c) {

		/* ------- Whitespace -------- */

		case ' ':
		case '\t':
		case '\f':
			break;
		case '\r':
		case '\n':
			line++;
			break;

		/* ------- Symbols -------- */

		case ';':
			currentToken.code = EOS_T;
			return currentToken;
		case '(':
			currentToken.code = LPR_T;
			return currentToken;
		case ')':
			currentToken.code = RPR_T;
			return currentToken;
		case '{':
			currentToken.code = LBR_T;
			return currentToken;
		case '}':
			currentToken.code = RBR_T;
			return currentToken;
		case ',':
			currentToken.code = COM_T;
			return currentToken;

		/* ------- Arithmetic Operators -------- */

		case '+':
			newc = getChar(sourceBuffer);
			if (newc == '+') {
				currentToken.code = ART_OP_T;
				currentToken.attribute.codeType = OP_INC;
				return currentToken;
			}
			retract(sourceBuffer);
			currentToken.code = ART_OP_T;
			currentToken.attribute.codeType = OP_ADD;
			return currentToken;
		case '-':
			newc = getChar(sourceBuffer);
			if (newc == '-') {
				currentToken.code = ART_OP_T;
				currentToken.attribute.codeType = OP_DEC;
				return currentToken;
			}
			retract(sourceBuffer);
			currentToken.code = ART_OP_T;
			currentToken.attribute.codeType = OP_SUB;
			return currentToken;
		case '*':
			currentToken.code = ART_OP_T;
			currentToken.attribute.codeType = OP_MUL;
			return currentToken;
		case '/':
			currentToken.code = ART_OP_T;
			currentToken.attribute.codeType = OP_DIV;
			return currentToken;

		/* ------- Relational Operators -------- */

		case '>':
			newc = getChar(sourceBuffer);
			if(newc == '=') {
				currentToken.code = REL_OP_T;
				currentToken.attribute.codeType = OP_GTE;
				return currentToken;
			}
			retract(sourceBuffer);
			currentToken.code = REL_OP_T;
			currentToken.attribute.codeType = OP_GT;
			return currentToken;
		case '<':
			newc = getChar(sourceBuffer);
			if (newc == '=') {
				currentToken.code = REL_OP_T;
				currentToken.attribute.codeType = OP_LTE;
				return currentToken;
			}
			retract(sourceBuffer);
			currentToken.code = REL_OP_T;
			currentToken.attribute.codeType = OP_LT;
			return currentToken;
		case '=':
			newc = getChar(sourceBuffer);
			if (newc == '=') {
				currentToken.code = REL_OP_T;
				currentToken.attribute.codeType = OP_EQ;
				return currentToken;
			}
			retract(sourceBuffer);
			currentToken.code = ASS_OP_T;
			return currentToken;

		/* ------- Logical Operators -------- */

		case '&':
			/*setMark(sourceBuffer, getReadPos(sourceBuffer));*/
			newc = getChar(sourceBuffer);
			if (newc == '&') {
				currentToken.code = LOG_OP_T;
				currentToken.attribute.codeType = OP_AND;
				return currentToken;
			}
			retract(sourceBuffer);
			currentToken.code = ERR_T;
			return currentToken;
		case '|':
				/*restore(sourceBuffer);*/
			newc = getChar(sourceBuffer);
			if (newc == '|') {
				currentToken.code = LOG_OP_T;
				currentToken.attribute.codeType = OP_OR;
				return currentToken;
			}
			retract(sourceBuffer);
			currentToken.code = ERR_T;
			return currentToken;
		case '!':
				/*restore(sourceBuffer);*/
				newc = getChar(sourceBuffer);
				if(newc == '=') {
					currentToken.code = REL_OP_T;
					currentToken.attribute.codeType = OP_NE;
					return currentToken;
				}
				retract(sourceBuffer);
				currentToken.code = LOG_OP_T;
				currentToken.attribute.codeType = OP_NOT;
				return currentToken;

		/* ------- Other -------- */
		
		/* Comments */
		case '#':
			newc = getChar(sourceBuffer);
			do {
				c = getChar(sourceBuffer);
				if (c == CHARSEOF0 || c == CHARSEOF255) {
					retract(sourceBuffer);
					/*return currentToken;*/
				} else if (c == '\n') {
					line++;
				}
			} while (c != ';' && c != CHARSEOF0 && c != CHARSEOF255);
			break;		
		/* Cases for END OF FILE */
		case CHARSEOF0:
			currentToken.code = SEOF_T;
			currentToken.attribute.seofType = SEOF_0;
			return currentToken;
		case CHARSEOF255:
			currentToken.code = SEOF_T;
			currentToken.attribute.seofType = SEOF_255;
			return currentToken;

		/* ------------------------------------------------------------------------
			Part 2: Implementation of Finite State Machine (DFA) or Transition Table driven Scanner
			Note: Part 2 must follow Part 1 to catch the illegal symbols
			-----------------------------------------------------------------------
		*/

		/* TO_DO_16: Adjust / check the logic for your language */
		default: 
			/* !Important to retrieve state 0! */
			state = nextState(state, c);

			lexStart = getReadPos(sourceBuffer) -1;
			setMark(sourceBuffer, lexStart);
			/*printf("lexStart (read-1): %d\n", lexStart);*/
			/*printf("Mark pos: %d\n", getMarkPos(sourceBuffer));*/
			/*printf("Source Buffer contents: %s", getContent(sourceBuffer, lexStart));*/

			/* Advance to next state while we haven't reached a final state */
			/* Need to do it this way because final states can still read characters. getChar advances readPos which determines lexEnd */
			/*while (stateType[state] == NOAS) {*/
			while(1) {
				if(copyState != state)
					prevState = copyState;
				if(stateType[prevState] != NOAS && (state == IS || state == ES || state == ER))
					break;

				copyState = state;
				c = getChar(sourceBuffer);
				state = nextState(state, c);
			}

			/* Final state reached - we now have lexStart and lexEnd */
			if (stateType[prevState] == ASWR)
				retract(sourceBuffer);
			lexEnd = getReadPos(sourceBuffer);
			lexLength = lexEnd - lexStart;

			/* Initialize lexemeBuffer */
			lexemeBuffer = create((short)lexLength + 2, 0, MODE_FIXED);
			if (!lexemeBuffer) {
				fprintf(stderr, "Scanner error: Can not create buffer\n");
				exit(1);
			}
			/* Set read pos back to markPos */
			restore(sourceBuffer);
			
			/*printf("Source Contents from readPos\n");
			for(i = 0; i < lexLength; i++) {
				printf("%c", getChar(sourceBuffer));
				printf("\n");
			}*/

			/* Writes characters from pos lexStart to lexEnd into lexemeBuffer */
			for (i = 0; i < lexLength; i++)
				addChar(lexemeBuffer, getChar(sourceBuffer));
			addChar(lexemeBuffer, BUFFER_EOF);
			currentToken = (*finalStateTable[prevState])(getContent(lexemeBuffer, 0));

			destroy(lexemeBuffer);
			return currentToken;
		} 
	} 
} 


/*************************************************************
 * Get Next State
	The assert(int test) macro can be used to add run-time diagnostic to programs
	and to "defend" from producing unexpected results.
 ************************************************************/

/* ---- Finished ---- */

/* Debug function for catching Illegal states */
pheonix_int nextState(pheonix_int state, pheonix_char c) {
	pheonix_int col;
	pheonix_int next;
	col = nextClass(c);
	next = transitionTable[state][col];

	if (DEBUG) {
		printf("Input symbol: %c Row: %d Column: %d Next: %d \n", c, state, col, next);
		assert(next != IS);
		if (next == IS) {
			printf("Scanner Error: Illegal state:\n");
			printf("Input symbol: %c Row: %d Column: %d\n", c, state, col);
			exit(1);
		}
	}
	return next;
}

/*************************************************************
 * Get Next Token Class
	* Create a function to return the column number in the transition table:
	* Considering an input char c, you can identify the "class".
	* For instance, a letter should return the column for letters, etc.
************************************************************/

pheonix_int nextClass(pheonix_char c) {
	pheonix_int val = -1; /* Set to IS by default */
	/* Adjust the logic to return next column in TT */
	/*	{0,1}(0), [2-9](1), [A-Z](2), [a-z](3), '(4), "(5), $(6), .(7), EOS(8), EOF(9), Other(10) */
	pheonix_int asciiVal = (int)(c - '0');
		
	switch (c) {
		case CHRCOL4:
			val = 4;
			break;
		case CHRCOL5:
			val = 5;
			break;
		case CHRCOL6:
			val = 6;
			break;
		case CHRCOL7:
			val = 7;
			break;
		case CHRCOL8:
			val = 8;
			break;
		case CHARSEOF0:
		case CHARSEOF255:
			val = 9;
			break;
		default:
			/* Lower-case */
			if (isalpha(c) && islower(c)) {
				val = 3;	
			}
			/* Upper-case */
			else if (isalpha(c) && isupper(c)) {
				val = 2;	
			}
			/* Binary digit */
			else if(isdigit(c) && asciiVal < 2) {
				val = 0;
			}
			/* 2 - 9 digit */
			else if(isdigit(c)) {
				val = 1;
			} 
			/* Other */
			else {
				val = 10;	
			}
	}
	return val;
}

/*************************************************************
 * Acceptance State Function VID
 *		In this function, the pattern for IVID must be recognized.
 *		Since keywords obey the same pattern, is required to test if 
 *		the current lexeme matches with KW from language.
 *	- Remember to respect the limit defined for lexemes (VID_LEN) and 
 *	  set the lexeme to the corresponding attribute (vidLexeme).
 *    Remember to end each token with the \0.
 *  - Suggestion: Use "strncpy" function.
 *
 * Parameters: lexeme[] - The lexeme retrieved from TT
 ************************************************************/
 /* TO_DO_19A: Adjust the function for VID */
Token funcVID(pheonix_char lexeme[]) {
	Token currentToken = { 0 };
	
	/* Can't have digit as first character in VID lexeme */
	if(isdigit(lexeme[0]))
		currentToken.code = ERR_T;
	else
		currentToken.code = VID_T;

	strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
	currentToken.attribute.idLexeme[VID_LEN] = CHARSEOF0; 
	return currentToken;
}

/*************************************************************
 * Acceptance State Function LVID
 *		In this function, the pattern for LVID must be recognized.
 *		Since keywords obey the same pattern, is required to test if 
 *		the current lexeme matches with KW from language.
 *	- Remember to respect the limit defined for lexemes (VID_LEN) and 
 *	  set the lexeme to the corresponding attribute (vidLexeme).
 *    Remember to end each token with the \0.
 *  - Suggestion: Use "strncpy" function.
 *
 * Parameters: lexeme[] - The lexeme retrieved from TT
 ************************************************************/
 /* TO_DO_19A: Adjust the function for VID */
Token funcLVID(pheonix_char lexeme[]) {
	Token currentToken = { 0 };

	if(lexeme[0] != '$')
		currentToken.code = ERR_T;
	else
		currentToken.code = LVID_T;

	strncpy(currentToken.attribute.idLexeme, lexeme, NUM_LEN);
	currentToken.attribute.idLexeme[NUM_LEN] = CHARSEOF0;
	return currentToken;
}

/*************************************************************
 * Acceptance State Function IL
 *		Function responsible to identify IL (integer literals).
 * - It is necessary respect the limit (ex: 2-byte integer in C).
 * - In the case of larger lexemes, error shoul be returned.
 * - Only first ERR_LEN characters are accepted and eventually, 
 *   additional three dots (...) should be put in the output.
 *
 * Parameters: lexeme[] - The lexeme retrieved from TT
 ************************************************************/
/* TO_DO_19B: Adjust the function for IL */

Token funcIL(pheonix_char lexeme[]) {
	Token currentToken = { 0 };

	pheonix_long tlong;
	/* Not a valid lexeme */
	if (lexeme[0] != '\0' && strlen(lexeme) > NUM_LEN) {
		currentToken = (*finalStateTable[ES])(lexeme);
	}
	else {
		tlong = atol(lexeme);
		if (tlong >= 0 && tlong <= SHRT_MAX) {
			currentToken.code = INL_T;
			currentToken.attribute.intValue = (pheonix_int)tlong;
		}
		else {
			currentToken = (*finalStateTable[ES])(lexeme);
		}
	}
	return currentToken;
}

/*************************************************************
 * Acceptance State Function CL
 *		Function responsible to identify CL (integer literals).
 * - It is necessary respect the limit (ex: 2-byte integer in C).
 * - In the case of larger lexemes, error shoul be returned.
 * - Only first ERR_LEN characters are accepted and eventually, 
 *   additional three dots (...) should be put in the output.
 *
 * Parameters: lexeme[] - The lexeme retrieved from TT
 ************************************************************/
/* TO_DO_19B: Adjust the function for CL */

Token funcCL(pheonix_char lexeme[]) {
	Token currentToken = { 0 };

	if(strlen(lexeme) == 3 && lexeme[0] == '\'' && lexeme[2] == '\'') {
		currentToken.code = CHL_T;
		currentToken.attribute.charValue = lexeme[1];
	}
	else {
		currentToken = (*finalStateTable[ES])(lexeme);
	}

	return currentToken;
}

/*************************************************************
 * Acceptance State Function BL
 *		Function responsible to identify BL (integer literals).
 * - It is necessary respect the limit (ex: 2-byte integer in C).
 * - In the case of larger lexemes, error shoul be returned.
 * - Only first ERR_LEN characters are accepted and eventually, 
 *   additional three dots (...) should be put in the output.
 *
 * Parameters: lexeme[] - The lexeme retrieved from TT
 ************************************************************/
/* TO_DO_19B: Adjust the function for BL */

Token funcBL(pheonix_char lexeme[]) {
	Token currentToken = { 0 };

	pheonix_int i, lexLength, newLexLen;
	pheonix_byte tbyte;
	pheonix_char* newlexeme = malloc(sizeof(lexeme));

	lexLength = strlen(lexeme);
	if (lexLength > BYTE_LEN+2) {
		currentToken.code = ERR_T;
		return currentToken;
	}

	for(i = 2; i < lexLength; i++)
		(*(newlexeme + (i-2))) = lexeme[i]; 

	newLexLen = strlen(newlexeme);
	/* Place bits in tbyte */
	tbyte = 0;
	for(i = (newLexLen-1); i > 0; i--) {
		if(newlexeme[i] == '1') {
			tbyte += pow(2, (newLexLen-i-1));
		}
	}

	currentToken.code = BYL_T;
	currentToken.attribute.byteValue = tbyte;

	return currentToken;
}

/*************************************************************
 * Acceptance State Function FPL
 *		Function responsible to identify FPL (float point literals).
 * - It is necessary respect the limit (ex: 4-byte integer in C).
 * - In the case of larger lexemes, error should be returned.
 * - Only first ERR_LEN characters are accepted and eventually, 
 *   additional three dots (...) should be put in the output.
 *
 * Parameters: lexeme[] - The lexeme retrieved from TT
 ************************************************************/
/* TO_DO_19C: Adjust the function for FPL */

Token funcFL(pheonix_char lexeme[]) {
	Token currentToken = { 0 };

	if(isalpha(lexeme[strlen(lexeme)-1]))
		lexeme[strlen(lexeme)-1] = '\0';

	pheonix_float tfloat = atof(lexeme);
	if ((tfloat == 0.0) || ((tfloat >= FLT_MIN) && (tfloat <= FLT_MAX))) {
		currentToken.code = FPL_T;
		currentToken.attribute.floatValue = tfloat;
	}
	else {
		currentToken = (*finalStateTable[ES])(lexeme);
	}
	return currentToken;
}

/*************************************************************
 * Acceptance State Function SL
 *		Function responsible to identify SL (string literals).
 * - The lexeme must be stored in the String Literal Table 
 *   (stringLiteralTable). You need to include the literals in 
 *   this structure, using offsets. Remember to include \0 to
 *   separate the lexemes. Remember also to incremente the line.
 *
 * Parameters: lexeme[] - The lexeme retrieved from TT
 ************************************************************/
/* TO_DO_19D: Adjust the function for SL */

Token funcSL(pheonix_char lexeme[]) {
	Token currentToken = { 0 };

	pheonix_int i = 0, len = (pheonix_int)strlen(lexeme);
	currentToken.attribute.contentString = getWritePos(stringLiteralTable);
	for (i = 1; i < len - 2; i++) {
		if (lexeme[i] == '\n' || lexeme[i] == '\r')
			line++;
		if (!addChar(stringLiteralTable, lexeme[i])) {
			currentToken.code = RTE_T;
			strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
			errorNumber = RTE_CODE;
			return currentToken;
		}
	}
	if (!addChar(stringLiteralTable, CHARSEOF0)) {
		currentToken.code = RTE_T;
		strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
		errorNumber = RTE_CODE;
		return currentToken;
	}
	currentToken.code = STR_T;
	return currentToken;
}


/*************************************************************
 * This function checks if one specific lexeme is a keyword.
 * - Tip: Remember to use the keywordTable to check the keywords.
 *
 * Parameters: lexeme[] - The lexeme retrieved from TT
 ************************************************************/
 /* TO_DO_19E: Adjust the function for Keywords */

Token funcKEY(pheonix_char lexeme[]) {
	Token currentToken = { 0 };

	pheonix_int kwindex = -1, j = 0;
	for (j = 0; j < KWT_SIZE; j++)
		if (!strcmp(lexeme, &keywordTable[j][0]))
			kwindex = j;
	if (kwindex != -1) {
		currentToken.code = KW_T;
		currentToken.attribute.keywordIndex = kwindex;
	}
	else {
		currentToken = funcVID(lexeme);
	}
	return currentToken;
}


/*************************************************************
 * Acceptance State Function Error
 *		Function responsible to deal with ERR token.
 * - This function uses the errLexeme, respecting the limit given
 *   by ERR_LEN. If necessary, use three dots (...) to use the
 *   limit defined. The error lexeme contains line terminators,
 *   so remember to increment line.
 *
 * Parameters: lexeme[] - The lexeme retrieved from TT
 ************************************************************/

/* ---- Finished ---- */

Token funcErr(pheonix_char lexeme[]) {
	Token currentToken = { 0 };

	pheonix_int i = 0, len = (pheonix_int)strlen(lexeme);
	if (len > ERR_LEN) {
		strncpy(currentToken.attribute.errLexeme, lexeme, ERR_LEN - 3);
		currentToken.attribute.errLexeme[ERR_LEN - 3] = CHARSEOF0;
		strcat(currentToken.attribute.errLexeme, "...");
	}
	else {
		strcpy(currentToken.attribute.errLexeme, lexeme);
	}
	for (i = 0; i < len; i++)
		if (lexeme[i] == '\n')
			line++;
	currentToken.code = ERR_T;
	return currentToken;
}


/*************************************************************
 * The function prints the token returned by the scanner
 ************************************************************/

void printToken(Token t) {
	extern pheonix_char* keywordTable[]; /* link to keyword table in */
	switch (t.code) {
		case RTE_T:
			printf("RTE_T\t\t%s", t.attribute.errLexeme);
			/* Call here run-time error handling component */
			if (errorNumber) {
				printf("%d", errorNumber);
				exit(errorNumber);
			}
			printf("\n");
			break;
		case ERR_T:
			printf("ERR_T\t\t%s\n", t.attribute.errLexeme);
			break;
		case SEOF_T:
			printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
			break;
		case VID_T:
			printf("VID_T\t\t%s\n", t.attribute.idLexeme);
			break;
		case LVID_T:
			printf("LVID_T\t\t%s\n", t.attribute.idLexeme);
			break;
		case FPL_T:
			printf("FL_T\t\t%f\n", t.attribute.floatValue);
			break;
		case INL_T:
			/*printf("INL_T\t\t%d\n", t.attribute.codeType);*/
			printf("INL_T\t\t%d\n", t.attribute.intValue);
			break;
		case CHL_T:
			printf("CHL_T\t\t%c\n", t.attribute.charValue);
			break;
		case BYL_T:
			printf("BYL_T\t\t0x%02x\n", t.attribute.byteValue);
			break;
		case STR_T:
			printf("STR_T\t\t%d\t ", (short)t.attribute.codeType);
			printf("%s\n", getContent(stringLiteralTable, (short)t.attribute.codeType));
			break;
		case ASS_OP_T:
			printf("ASS_OP_T\n");
			break;
		case ART_OP_T:
			printf("ART_OP_T\t%d\n", t.attribute.codeType);
			break;
		case REL_OP_T:
			printf("REL_OP_T\t%d\n", t.attribute.codeType);
			break;
		case LOG_OP_T:
			printf("LOG_OP_T\t%d\n", t.attribute.codeType);
			break;
		case LPR_T:
			printf("LPR_T\n");
			break;
		case RPR_T:
			printf("RPR_T\n");
			break;
		case LBR_T:
			printf("LBR_T\n");
			break;
		case RBR_T:
			printf("RBR_T\n");
			break;
		case KW_T:
			printf("KW_T\t\t%s\n", keywordTable[t.attribute.keywordIndex]);
			break;
		case COM_T:
			printf("COM_T\n");
			break;
		case EOS_T:
			printf("EOS_T\n");
			break;
		default:
			printf("Scanner error: invalid token code: %d\n", t.code);
	}
}
