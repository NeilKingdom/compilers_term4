/*************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2021
*************************************************************
* File name: Scanner.h
* Compiler: MS Visual Studio 2019
* Author: Paulo Sousa (from original work of Svillen Ranev)
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A2.
* Date: May 01 2021
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/* Constants */
#define VID_LEN 15	/* variable identifier length */
#define ERR_LEN 20	/* error message length */
#define BYTE_LEN 8   /* Maximim number of digits for BL */
#define NUM_LEN 5	   /* maximum number of digits for IL */

#define RTE_CODE 1	 /* Value for run-time error */

/* EOF definitions */
#define CHARSEOF0 ('\0')
#define CHARSEOF255 (0xFF)

/* Lexeme classes */
#define CHRCOL4 '\''
#define CHRCOL5 '\"'
#define CHRCOL6 '$'
#define CHRCOL7 '.'
#define CHRCOL8 ';'

#define ES	18	  /* Error state with no retract */
#define ER	19	  /* Error state with retract */
#define IS  -1   /* Illegal state */

#define NOAS 0	  /* no acceptable state */
#define ASNR 1	  /* accepting state with no retract */
#define ASWR 2	  /* accepting state with retract */

#define TABLE_COLUMNS 11
#define KWT_SIZE 20


enum TOKENS {
   ERR_T,	   /* Error token */
   VID_T,	   /* General variable identifier */ 
	LVID_T,     /* Local variable identifier */
   INL_T,	   /* Integer literal token */
   FPL_T,	   /* Floating point literal token */
   BYL_T,	   /* Byte literal token */
   CHL_T,	   /* Character literal token */
   STR_T,	   /* String literal token */
   ASS_OP_T,   /* Assignment operator token */
   ART_OP_T,   /* Arithmetic operator token */
   REL_OP_T,   /* Relational operator token */
   LOG_OP_T,   /* Logical operator token */
	BIT_OP_T,	/* Bitwise operator token */
   LPR_T,	   /* Left parenthesis token */
   RPR_T,	   /* Right parenthesis token */
   LBR_T,	   /* Left brace token */
   RBR_T,	   /* Right brace token */
   KW_T,	      /* Keyword token */
   COM_T,	   /* Comma token */
	COL_T,		/* Colon token */
   EOS_T,	   /* End of statement (semicolon) */
   RTE_T,	   /* Run-time error token */
   SEOF_T	   /* Source end-of-file token */
};

typedef enum ArithmeticOperators { OP_ADD, OP_INC, OP_SUB, OP_DEC, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT, OP_GTE, OP_LTE } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum BitwiseOperators { OP_BWA, OP_BWO, OP_BSL, OP_BSR } BitOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

typedef union TokenAttribute {
   pheonix_int codeType;			       /* integer attributes accessor */
   AriOperator arithmeticOperator;	    /* arithmetic operator attribute code */
   RelOperator relationalOperator;	    /* relational operator attribute code */
   LogOperator logicalOperator;		    /* logical operator attribute code */
	BitOperator	bitwiseOperator;			 /* bitwise operator attribute code */
   EofOperator seofType;			       /* source-end-of-file attribute code */
   pheonix_int intValue;			       /* integer literal attribute (value) */
   pheonix_int keywordIndex;		       /* keyword index in the keyword table */
   pheonix_int contentString;		       /* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
   pheonix_float floatValue;			    /* floating-point literal attribute (value) */
   pheonix_char charValue;			       /* char literal attribute (value) */
   pheonix_byte byteValue;			       /* byte literal attribute (value) */
   pheonix_char idLexeme[VID_LEN + 1];	 /* variable identifier token attribute */
   pheonix_char errLexeme[ERR_LEN + 1]; /* error token attribite */
} TokenAttribute;

typedef struct idAttibutes {
   pheonix_byte flags;		             /* Flags information */
   union {
	  pheonix_int intValue;			       /* Integer value */
	  pheonix_float floatValue;		    /* Float value */
	  pheonix_void* stringContent;	    /* String value */
   } values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
   pheonix_int code;				 /* token code */
   TokenAttribute attribute;	 /* token attribute */
   IdAttibutes idAttribute;	 /* not used in this scanner implementation - for further use */
} Token;

/* Function prototypes */
pheonix_int startScanner(BufferPointer psc_buf);   /* initialize buffer and soforth */
pheonix_int nextClass(pheonix_char c);		         /* character class function */
pheonix_int nextState(pheonix_int, pheonix_char);	/* state machine function */

/* Declare accepting states functions */
typedef Token(*PTR_ACCFUN)(pheonix_char* lexeme);

Token funcVID(pheonix_char lexeme[]);
Token funcLVID(pheonix_char lexeme[]);
Token funcIL(pheonix_char lexeme[]);
Token funcCL(pheonix_char lexeme[]);
Token funcBL(pheonix_char lexeme[]);
Token funcFL(pheonix_char lexeme[]);
Token funcSL(pheonix_char lexeme[]);
Token funcKEY(pheonix_char lexeme[]);
Token funcErr(pheonix_char lexeme[]);

/* Global variables */
extern pheonix_int transitionTable[][TABLE_COLUMNS];
extern pheonix_int stateType[];
extern PTR_ACCFUN finalStateTable[];
extern pheonix_char* keywordTable[KWT_SIZE];

#endif
