/*************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2021
* Author: Svillen Ranev - Paulo Sousa.
*************************************************************
* File name: MainScanner.c
* Compiler: MS Visual Studio 2019
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A2.
* Date: May 01 2021
* Professor: Paulo Sousa
* Purpose: This file is the main code for Scanner (A2)
* Function list: (...).
*************************************************************/

/* The #define _CRT_SECURE_NO_WARNINGS should be used in MS Visual Studio projects
 * to suppress the warnings about using "unsafe" functions like fopen()
 * and standard sting library functions defined in string.h.
 * The define does not have any effect in other compiler projects.
 */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#include "Buffer.h"
#endif

#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/*check for ANSI C compliancy */
#define ANSI_C 0
#if defined(__STDC__)
#undef ANSI_C
#define ANSI_C 1
#endif

/*
 * -------------------------------------------------------------
 *  Global vars and External vars
 * -------------------------------------------------------------
 */

/* Global objects - variables (used in other codes as external) */
BufferPointer stringLiteralTable;	/* this buffer implements String Literal Table */
int errorNumber;			/* run-time error number = 0 by default (ANSI) */

/* External objects */
extern int line; /* source code line numbers - defined in scanner.c */
extern int startScanner(BufferPointer psc_buf);
extern Token tokenizer(void);
extern BufferPointer sourceBuffer;	  /* pointer to input (source) buffer */

/*
 * -------------------------------------------------------------
 *  Function declarations
 * -------------------------------------------------------------
 */
void printScannerError(char* fmt, ...);
void displayScanner(Buffer* ptrBuffer);
long getScannerFilesize(char* fname);
void printToken(Token t);

/*************************************************************
*  Scanner Main function 
* Parameters:
*   argc / argv = Parameters from command prompt
* Return value:
*	Success operation.
************************************************************/
int mainScanner(int argc, char** argv) {

	/*BufferPointer sourceBuffer;	  pointer to input (source) buffer */
	FILE* fileHandler;		/* input file handle */
	Token currentToken;		/* token produced by the scanner */
	int loadSize = 0;		/* the size of the file loaded in the buffer */
	int isAnsiC = !ANSI_C;	/* ANSI C compliancy flag */

	/* Check if the compiler option is set to compile ANSI C */
	/* __DATE__, __TIME__, __LINE__, __FILE__, __STDC__ are predefined preprocessor macros*/
	if (isAnsiC) {
		printScannerError("Date: %s  Time: %s", __DATE__, __TIME__);
		printScannerError("ERROR: Compiler is not ANSI C compliant!\n");
		exit(EXIT_FAILURE);
	}

	/*check for correct arrguments - source file name */
	if (argc <= 2) {
		/* __DATE__, __TIME__, __LINE__, __FILE__ are predefined preprocessor macros*/
		printScannerError("Date: %s  Time: %s", __DATE__, __TIME__);
		printScannerError("Runtime error at line %d in file %s", __LINE__, __FILE__);
		printScannerError("%s%s", argv[0], ": Missing source file name.");
		printScannerError("%s", "Usage: <Option=1> <SourceFile>");
		exit(EXIT_FAILURE);
	}

	/* Shows debug mode */
	printf("%s%d%s", "[Debug mode: ", DEBUG, "]\n");

	/* create a source code input buffer - multiplicative mode */
	sourceBuffer = create(BUFFER_DEFAULT_SIZE, BUFFER_DEFAULT_INCREMENT, MODE_MULTI);
	if (sourceBuffer == NULL) {
		printScannerError("%s%s", argv[1], ": Could not create source buffer");
		exit(EXIT_FAILURE);
	}

	/* open source file */
	if ((fileHandler = fopen(argv[2], "r")) == NULL) {
		printScannerError("%s%s%s", argv[0], ": Cannot open file: ", argv[2]);
		exit(EXIT_FAILURE);
	}

	/* load source file into input buffer  */
	printf("Reading file %s ....Please wait\n", argv[2]);
	loadSize = load(sourceBuffer, fileHandler);
	if (loadSize == BUFFER_ERROR)
		printScannerError("%s%s", argv[0], ": Error in loading buffer.");

	/* close source file */
	fclose(fileHandler);
	/* find the size of the file */
	if (loadSize == BUFFER_ERROR) {
		printf("The input file %s %s\n", argv[2], "is not completely loaded.");
		printf("Input file size: %ld\n", getScannerFilesize(argv[2]));
	}

	/* compact and display the source buffer */
	/* add SEOF to input program buffer*/
	if ((loadSize != BUFFER_ERROR) && (loadSize != 0)) {
		if (addChar(sourceBuffer, BUFFER_EOF)) {
			displayScanner(sourceBuffer);
		}
	}

	/* create string Literal Table */
	stringLiteralTable = create(BUFFER_DEFAULT_SIZE, BUFFER_DEFAULT_INCREMENT, MODE_ADDIT);
	if (stringLiteralTable == NULL) {
		printScannerError("%s%s", argv[0], ": Could not create string literals buffer");
		exit(EXIT_FAILURE);
	}

	/* Testbed for the scanner */
    /* add SEOF to input program buffer*/
	/* Initialize scanner input buffer */
	if (startScanner(sourceBuffer)) {
		printScannerError("%s%s", argv[0], ": Empty program buffer - scanning canceled");
		exit(EXIT_FAILURE);
	}

	printf("\nScanning source file...\n\n");
	printf("Token\t\tAttribute\n");
	printf("----------------------------------\n");
	do {
		currentToken = tokenizer();
		printToken(currentToken);
	} while (currentToken.code != SEOF_T);

	/* print String Literal Table if not empty */
	printf("\nPrinting string table...\n");
	printf("----------------------------------\n");
	if (getWritePos(stringLiteralTable)) print(stringLiteralTable);
	printf("\n----------------------------------\n");
	destroy(sourceBuffer);
	destroy(stringLiteralTable);
	sourceBuffer = stringLiteralTable = NULL;
	
	/* Ass2 evaluation only */
	if (argv[3] != NULL && *argv[3] == 'l')
		printf("The number of lines is: %d\n", line);

	return (EXIT_SUCCESS);
}

/*************************************************************
*  Error printing function with variable number of arguments
*  Params: Variable arguments, using formats from C language.
*	 - Internal vars use list of arguments and types from stdarg.h
*   - NOTE: The format is using signature from C Language
************************************************************/
void printScannerError(char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
		(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	/* Move to new line */
	if (strchr(fmt, '\n') == NULL)
		fprintf(stderr, "\n");
}

/*************************************************************
* The function displays buffer contents
* Param:
*		- Scanner to be displayed.
************************************************************/
void displayScanner(Buffer* ptrBuffer) {
	printf("\nPrinting buffer parameters:\n\n");
	printf("The capacity of the buffer is:  %d\n", getSize(ptrBuffer));
	printf("The current size of the buffer is:  %d\n", getWritePos(ptrBuffer));
	printf("\nPrinting buffer contents:\n\n");
	recover(ptrBuffer);
	print(ptrBuffer);
}

/*************************************************************
* The function gets size of scanner file
* Param:
*	- Filename
* Return:
*	- Size of the file
************************************************************/
long getScannerFilesize(char* fname) {
	FILE* fileInput;
	long fileLength;
	fileInput = fopen(fname, "r");
	if (fileInput == NULL) {
		printScannerError("%s%s", "Cannot open file: ", fname);
		return 0L;
	}
	fseek(fileInput, 0L, SEEK_END);
	fileLength = ftell(fileInput);
	fclose(fileInput);
	return fileLength;
}
