/*************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2021
*************************************************************
* File name: Parser.h
* Compiler: MS Visual Studio 2019
* Author: Paulo Sousa (based on prof. Svillen Ranev work)
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A3.
* Date: Dec 11 2021
* Purpose: This file is the main header for Parser (.h)
*************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
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

/* Global vars */

static Token lookahead;
pheonix_int syntaxErrorNumber = 0;
extern Buffer* stringLiteralTable;
extern pheonix_int line;
extern Token tokenizer();
extern pheonix_char* keywordTable[];

#define STR_LANGNAME "Pheonix"

/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
   INT,
   FLOAT,
   CHAR,
   STRING,
   BYTE,
   BOOL,
   VOID,
   NUL,
   IF,
	ELIF,
   ELSE,
   WHILE,
   FOR,
   FUNCTION,
   RETURN,
   PRINT,
   READ,
   TRUE,
   FALSE,
   MAIN
};

/* Function definitions */
pheonix_void startParser();
pheonix_void matchToken(pheonix_int, pheonix_int);
pheonix_void syncErrorHandler(pheonix_int);
pheonix_void printError();

/* Unique Functions Describing Each Non-Terminal */

/* Pheonix Program*/
pheonix_void program();
/* Declarations */
pheonix_void opt_declarations();
pheonix_void function_decls();
pheonix_void function_decls_prime();
pheonix_void function_decl();
pheonix_void function_id();
pheonix_void return_type();
pheonix_void opt_param_list();
pheonix_void parameters();
pheonix_void parameters_prime();
pheonix_void parameter();
pheonix_void pheonix_main();
pheonix_void main_function_id();
pheonix_void variable_decls();
pheonix_void variable_decls_prime();
pheonix_void variable_decl();
pheonix_void opt_var_init();
/* Variable IDs */
pheonix_void variable_id();
pheonix_void integer_id();
pheonix_void float_id();
pheonix_void char_id();
pheonix_void byte_id();
pheonix_void bool_id();
pheonix_void string_id();
/* Code Blocks */
pheonix_void code_block();
pheonix_void opt_statements();
/* Statements */
pheonix_void statements();
pheonix_void statements_prime();
pheonix_void statement();
pheonix_void alpha_statement();
pheonix_void beta_statement();
/* Assignment */
pheonix_void assignment_statement();
pheonix_void assignment_expr();
/* Selection Statements (if clause) */
pheonix_void selection_statement();
pheonix_void primary_selection();
pheonix_void primary_selection_prime();
pheonix_void secondary_selection();
pheonix_void secondary_selection_prime();
pheonix_void tertiary_selection();
pheonix_void tertiary_selection_prime();
/* Iteration Statement (for loop) */
pheonix_void iteration_statement();
pheonix_void conditional_for_expr();
/* Loop Statement (while loop) */
pheonix_void loop_statement();
/* Input Statement (read) */
pheonix_void input_statement();
/* Output Statement (print) */
pheonix_void output_statement();
pheonix_void opt_arg_list();
pheonix_void argument_list();
pheonix_void argument_list_prime();
pheonix_void argument();
/* Function Call */
pheonix_void function_call();
/* Return Statement */
pheonix_void return_statement();
pheonix_void return_value();
/* Arithmetic Expressions */
pheonix_void arithmetic_expr();
pheonix_void unary_arithmetic_expr();
pheonix_void additive_arithmetic_expr();
pheonix_void additive_arithmetic_expr_prime();
pheonix_void multiplicative_arithmetic_expr();
pheonix_void multiplicative_arithmetic_expr_prime();
pheonix_void primary_arithmetic_expr();
pheonix_void numeric_arithmetic_expr();
pheonix_void numeric_value();
/* Bitwise Expressions */
pheonix_void bitwise_expr();
pheonix_void left_bitshift();
pheonix_void left_bitshift_prime();
pheonix_void right_bitshift();
pheonix_void right_bitshift_prime();
pheonix_void bitwise_or();
pheonix_void bitwise_and();
pheonix_void byte_value();
/* Logical Expressions */
pheonix_void conditional_expr();
pheonix_void logical_or_expr();
pheonix_void logical_or_expr_prime();
pheonix_void logical_and_expr();
pheonix_void logical_and_expr_prime();
pheonix_void logical_not_expr();
pheonix_void relational_expr();
pheonix_void relational_expr_prime();
pheonix_void inner_conditional_op();
pheonix_void bitwise_byte_expr();

#endif
