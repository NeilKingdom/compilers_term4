/*************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2021
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa / Daniel Cormier
*************************************************************/

/*************************************************************
* File name: Parser.c
* Compiler: MS Visual Studio 2019
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A32.
* Date: Sep 01 2021
* Professor: Paulo Sousa
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/*************************************************************
 * Process Parser
 ************************************************************/
pheonix_void startParser() {
	lookahead = tokenizer();
	if (lookahead.code != SEOF_T) {
		program();
	}
	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}


/*************************************************************
 * Match Token
 ************************************************************/
pheonix_void matchToken(pheonix_int tokenCode, pheonix_int tokenAttribute) {
	pheonix_int matchFlag = 1;
	switch (lookahead.code) {
		case KW_T:
				if (lookahead.attribute.codeType != tokenAttribute)
					matchFlag = 0;
			break;
		default:
				if (lookahead.code != tokenCode)
					matchFlag = 0;
				break;
	}

	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		lookahead = tokenizer();
		if (lookahead.code == ERR_T) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
}

/*************************************************************
 * Syncronize Error Handler
 ************************************************************/
pheonix_void syncErrorHandler(pheonix_int syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*************************************************************
 * Print Error
 ************************************************************/
pheonix_void printError() {
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
		case ERR_T:
			printf("%s\n", t.attribute.errLexeme);
			break;
		case SEOF_T:
			printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
			break;
		case VID_T:
			printf("%s\n", t.attribute.idLexeme);
			break;
		case LVID_T:
			printf("%s\n", t.attribute.idLexeme);
			break;
		case STR_T:
			printf("%s\n", getContent(stringLiteralTable, t.attribute.contentString));
			break;
		case KW_T:
			printf("%s\n", keywordTable[t.attribute.keywordIndex]);
			break;
		case LPR_T:
		case RPR_T:
		case LBR_T:
		case RBR_T:
		case COM_T:
		case EOS_T:
		case COL_T:
			printf("NA\n");
			break;
		default:
			printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
			break;
	}
}


/* Pheonix Program*/

/*************************************************************
 * Program statement
 * BNF: <program> -> <declarations><main>
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void program() {

	/* TODO: Reincorporate opt_declarations*/
	/*opt_declarations();*/ 
	pheonix_main();		
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}

/* Declarations */

/*************************************************************
 * Optional declarations
 * BNF: <opt_declarations> -> <function_decls> | <variable_decls> | e
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void opt_declarations() {

	switch(lookahead.code) {
		case VID_T: 
			variable_decls();	
			break;
		case KW_T: 
			function_decls(); 
			break;
		default:
			; /* Empty */
			break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Declarations parsed");
}

/*************************************************************
 * Function declarations
 * BNF: <function_decls> -> <function_decl><function_decls_prime>
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void function_decls() {

	function_decl();
	function_decls_prime();
	printf("%s%s\n", STR_LANGNAME, ": Function declarations parsed");
}

/*************************************************************
 * Function declarations prime
 * BNF: <function_decls_prime> -> <function_decl><function_decls_prime> | e
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void function_decls_prime() {

	switch(lookahead.code) {
		case KW_T:
			function_decl();
			function_decls_prime();
			break;
		default:
			; /* Empty */
			break;
	}
}

/*************************************************************
 * Function declaration
 * BNF: <function_decl> -> <function_id><opt_param_list><code_block>
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void function_decl() {

	function_id();
	opt_param_list();
	code_block();
	printf("%s%s\n", STR_LANGNAME, ": Function declaration parsed");
}

/*************************************************************
 * Function id
 * BNF: <function_id> -> KW_T {function}<return_type>VID_T
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void function_id() {

	switch(lookahead.code) {
		case KW_T:
			matchToken(KW_T, FUNCTION);
			return_type();
			matchToken(VID_T, NO_ATTR);
			break;
		default:
			printError();
			break;
	}	
	printf("%s%s\n", STR_LANGNAME, ": Function ID parsed");
}

/*************************************************************
 * Return type
 * BNF: <return_type> -> KW_T {void, int, float, char, byte, bool, string}
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void return_type() {

	switch(lookahead.code) {
		case KW_T:
			if(lookahead.attribute.codeType == VOID) {
				matchToken(KW_T, VOID);
			}
			else if(lookahead.attribute.codeType == INT) {
				matchToken(KW_T, INT);
			}
			else if(lookahead.attribute.codeType == FLOAT) {
				matchToken(KW_T, FLOAT);
			}
			else if(lookahead.attribute.codeType == CHAR) {
				matchToken(KW_T, CHAR);
			}
			else if(lookahead.attribute.codeType == BYTE) {
				matchToken(KW_T, BYTE);
			}
			else if(lookahead.attribute.codeType == BOOL) {
				matchToken(KW_T, BOOL);
			}
			else if(lookahead.attribute.codeType == STRING) {
				matchToken(KW_T, STRING);
			}
			else {
				printError();
			}
			break;
		default:
			printError();
			break;
	}	
	printf("%s%s\n", STR_LANGNAME, ": Return type parsed");
}

/*************************************************************
 * Optional parameter list
 * BNF: <opt_param_list> -> <parameters>|e 
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void opt_param_list() {

	switch(lookahead.code) {
		case KW_T:
			parameters();
			break;
		default:
			; /* Empty */
			break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional parameters list parsed");
}

/*************************************************************
 * Parameters
 * BNF: <parameters> -> <parameter><parameters_prime>
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void parameters() {

	parameter();
	parameters_prime();
	printf("%s%s\n", STR_LANGNAME, ": Parameters parsed");
}

/*************************************************************
 * Parameters prime
 * BNF: <parameters_prime> -> <parameter><parameters_prime>|e
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void parameters_prime() {

	switch(lookahead.code) {
		case KW_T:
			parameter();
			parameters_prime();
			break;
		default:
			; /* Empty */
			break;
	}
}

/*************************************************************
 * Parameter
 * BNF: <parameter> -> KW_T {void, int, float, char, byte, bool, string} 
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void parameter() {

	switch(lookahead.code) {
		case KW_T:
			if(lookahead.attribute.codeType == VOID) {
				matchToken(KW_T, VOID);
			}
			else if(lookahead.attribute.codeType == INT) {
				matchToken(KW_T, INT);
			}
			else if(lookahead.attribute.codeType == FLOAT) {
				matchToken(KW_T, FLOAT);
			}
			else if(lookahead.attribute.codeType == CHAR) {
				matchToken(KW_T, CHAR);
			}
			else if(lookahead.attribute.codeType == BYTE) {
				matchToken(KW_T, BYTE);
			}
			else if(lookahead.attribute.codeType == BOOL) {
				matchToken(KW_T, BOOL);
			}
			else if(lookahead.attribute.codeType == STRING) {
				matchToken(KW_T, STRING);
			}
			else {
				printError();
			}
			break;
		default:
			printError();
			break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Parameter parsed");	
}

/*************************************************************
 * Pheonix main
 * BNF: <pheonix_main> -> <main_function_id><opt_param_list><code_block> 
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void pheonix_main() {

	main_function_id();
	opt_param_list();
	code_block();	
	printf("%s%s\n", STR_LANGNAME, ": Main parsed");	
}

/*************************************************************
 * Main function ID
 * BNF: <main_function_id> -> KW_T {function}<return_type>KW_T {main}
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void main_function_id() {

	switch(lookahead.code) {
		case KW_T:
			matchToken(KW_T, FUNCTION);
			return_type();
			matchToken(KW_T, MAIN);
			break;
		default:
			printError();
			break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Main function ID parsed");	
}

/*************************************************************
 * Variable declarations
 * BNF: <variable_decls> -> <variable_decl><variable_decls_prime>
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void variable_decls() {

	variable_decl();
	variable_decls_prime();
	printf("%s%s\n", STR_LANGNAME, ": Variable declaration parsed");	
}

/*************************************************************
 * Variable declarations prime
 * BNF: <variable_decls_prime> -> <variable_decl><variable_decls_prime>|e 
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void variable_decls_prime() {

	switch(lookahead.code) {
		case KW_T:
			variable_decl();
			variable_decls_prime();	
			break;
		default:
			; /* Empty */
			break;
	}
}

/*************************************************************
 * Variable declaration
 * BNF: <variable_decl> -> <variable_identifier><opt_var_init>
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void variable_decl() {

	variable_id();
	opt_var_init();
	printf("%s%s\n", STR_LANGNAME, ": Variable declaration parsed");
}

/*************************************************************
 * Optional variable initialization
 * BNF: <opt_var_init> -> <assignment_statement>|e
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void opt_var_init() {

	switch(lookahead.code) {
		case ASS_OP_T:
			assignment_statement();
			break;
		default:
			matchToken(EOS_T, NO_ATTR); 
			; /* Empty */
			break;
	}	
	printf("%s%s\n", STR_LANGNAME, ": Optional variable initialization parsed");
}

/* Variable Identifiers */
/*************************************************************
 * Variable identifer
 * BNF: <variable_id> -> <integer_id>|<float_id>|<char_id>
|<byte_id>|<bool_id>|<string_id> 
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void variable_id() {

	switch(lookahead.attribute.codeType) {
		case INT:
			integer_id();
			break;
		case FLOAT:
			float_id();
			break;
		case CHAR:
			char_id();
			break;
		case BYTE:
			byte_id();
			break;
		case BOOL:
			bool_id();
			break;
		case STRING:
			string_id();
			break;
		default:
			printError();
	}	
	printf("%s%s\n", STR_LANGNAME, ": Variable identifer parsed");
}

/*************************************************************
 * Integer identifier
 * BNF: <integer_id> -> KW_T{int} VID_T 
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void integer_id() {

	matchToken(KW_T, INT);
	matchToken(VID_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Integer ID parsed");
}

/*************************************************************
 * Float identifier
 * BNF: <float_id> -> KW_T{float} VID_T 
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void float_id() {

	matchToken(KW_T, FLOAT);
	matchToken(VID_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Float ID parsed");
}

/*************************************************************
 * Char identifier
 * BNF: <char_id> -> KW_T{char} VID_T 
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void char_id() {

	matchToken(KW_T, CHAR);
	matchToken(VID_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Char ID parsed");
}

/*************************************************************
 * Byte identifier
 * BNF: <byte_id> -> KW_T{byte} VID_T 
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void byte_id() {

	matchToken(KW_T, BYTE);
	matchToken(VID_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Byte ID parsed");
}

/*************************************************************
 * Bool identifier
 * BNF: <bool_id> -> KW_T{bool} VID_T 
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void bool_id() {

	matchToken(KW_T, BOOL);
	matchToken(VID_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Bool ID parsed");
}

/*************************************************************
 * String identifier
 * BNF: <string_id> -> KW_T{string} VID_T 
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void string_id() {

	matchToken(KW_T, STRING);
	matchToken(VID_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": String ID parsed");
}

/* Code Blocks */

/*************************************************************
 * Code block
 * BNF: <code_block> -> LBR_T<opt_statements>RBR_T
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void code_block() {

	matchToken(LBR_T, NO_ATTR);
	opt_statements(); 
	matchToken(RBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Code block parsed");
}

/*************************************************************
 * Optional statements
 * BNF: <opt_statements> -> <statements>|e
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void opt_statements() {
	
	switch(lookahead.code) {
		case KW_T:
		case VID_T:
		case LVID_T:
			statements();
			break;
		default:
			; /* Empty */
			break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/* Statements */
/*************************************************************
 * Statements
 * BNF: <statements> -> <statement>|<statements_prime>
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void statements() {

	statement();
	statements_prime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");	
}

/*************************************************************
 * Statements prime
 * BNF: <statements_prime> -> <statement><statements_prime>|e
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void statements_prime() {

	switch(lookahead.code) {
		case KW_T:
		case VID_T:
		case LVID_T:
			statement();
			statements_prime();
			break;
		default:
			; /* Empty */
			break;	
	}	
}

/*************************************************************
 * Statement
 * BNF: <statement> -> <alpha_statement>|<beta_statement>
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void statement() {

	switch(lookahead.code) {
		case VID_T:
		case LVID_T:
			alpha_statement();
			break;
		case KW_T:
			beta_statement();
			break;
		default:
			printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

pheonix_void alpha_statement() {

	switch(lookahead.code) {
		case LVID_T:
			matchToken(LVID_T, NO_ATTR);
			assignment_statement();
			break;
		case VID_T:
			matchToken(VID_T, NO_ATTR);
			if(lookahead.code == ASS_OP_T) {
				assignment_statement();
			}
			else {
				function_call();
			}
			break;
		default:
			printError();
	}	
	printf("%s%s\n", STR_LANGNAME, ": Alpha statement parsed");
}

/*************************************************************
 * Beta statement 
 * BNF: <beta_statement> -> <selection_statement>
|<iteration_statement>|<loop_statement>|<input_statement>
|<output_statement>|<return_statement>|<variable_decl>
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void beta_statement() {

	switch(lookahead.code) {
		case KW_T:
			/* If statement */
			if(lookahead.attribute.codeType == IF) {
				selection_statement();	
			}
			/* While loop */
			else if(lookahead.attribute.codeType == WHILE) {
				loop_statement();
			}
			/* For loop */
			else if(lookahead.attribute.codeType == FOR) {
				iteration_statement();
			}
			/* Read function */
			else if(lookahead.attribute.codeType == READ) {
				input_statement();
			}
			/* Write function */
			else if(lookahead.attribute.codeType == PRINT) {
				output_statement();
			}
			else if(lookahead.attribute.codeType == RETURN) {
				return_statement();
			}
			else {
				variable_decl();
			}
			break;
		default:
			printError();
			break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Beta statement parsed");
}

/* Assignment */
/*************************************************************
 * Assignment statement
 * BNF: <assignment_statement> -> ASS_OP_T<assignment_expr>
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void assignment_statement() {

	matchToken(ASS_OP_T, NO_ATTR);
	assignment_expr();
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Assignment statement parsed");
}

/*************************************************************
 * Assignment expression
 * BNF: <assignment_expr> -> <???> 
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void assignment_expr() {

	/* TODO: Haven't implemented any assignment expressions other than
	numeric_arithmetic_expr and input_expr. The grammar need to be revised 
	before implementing the others */
	switch(lookahead.code) {
		case KW_T:
			if(lookahead.attribute.codeType == READ) {
				input_statement();
			}
			else {
				printError();
			}
			break;
		default:
			numeric_arithmetic_expr(); 
			break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Assignment expression parsed");
}

/* Selection Statements (if clause) */
/*************************************************************
 * Selection statement
 * BNF: <selection_statment> -> <primary_selection><selection_statment_prime>
|<primary_selection> 
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void selection_statement() {

	switch(lookahead.code) {
		case KW_T:
			if(lookahead.attribute.codeType == IF) {
				primary_selection();
				primary_selection_prime();
			}
			else {
				printError();
			}
			break;
		default:
			printError();
			break;
	}	
	printf("%s%s\n", STR_LANGNAME, ": Selection statement parsed");
}

/*************************************************************
 * Primary selection
 * BNF: <primary_selection> -> KW_T {if} LBR_T <opt_statements> RBR_T 
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void primary_selection() {

	matchToken(KW_T, IF);
	/*TODO: Add conditional expr*/
	matchToken(LBR_T, NO_ATTR);
	opt_statements();
	matchToken(RBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Primary selection parsed");
}

/*************************************************************
 * Primary selection prime
 * BNF: <primary_selection_prime> -> <secondary_selection><secondary_selection_prime>|e 
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void primary_selection_prime() {

	switch(lookahead.code) {
		case KW_T:
			if(lookahead.attribute.codeType == ELIF) {
				secondary_selection();
				secondary_selection_prime();
			}
			else {
				printError();
			}
			break;
		default:
			; /* Empty */
			break;
	}	
}

/*************************************************************
 * Secondary selection
 * BNF: <secondary_selection> -> KW_T {elif} LBR_T <opt_statements> RBR_T 
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void secondary_selection() {

	matchToken(KW_T, ELIF);
	/*TODO: Add conditional expr*/
	matchToken(LBR_T, NO_ATTR);
	opt_statements();
	matchToken(RBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Secondary selection parsed");
}

/*************************************************************
 * Secondary selection prime
 * BNF: <secondary_selection_prime> -> <tertiary_selection><tertiary_selection_prime>|e 
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void secondary_selection_prime() {

	switch(lookahead.code) {
		case KW_T:
			if(lookahead.attribute.codeType == ELSE) {
				tertiary_selection();
				tertiary_selection_prime();
			}
			else {
				printError();
			}
			break;
		default:
			; /* Empty */
			break;
	}	
}

/*************************************************************
 * Tertiary selection
 * BNF: <tertiary_selection> -> KW_T {else} LBR_T <opt_statements> RBR_T 
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void tertiary_selection() {

	matchToken(KW_T, IF);
	matchToken(LBR_T, NO_ATTR);
	opt_statements();
	matchToken(RBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Primary selection parsed");
}

/*************************************************************
 * Tertiary selection prime
 * BNF: <tertiary_selection> -> <tertiary_selection>|e 
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void tertiary_selection_prime() {

	switch(lookahead.code) {
		case KW_T:
			if(lookahead.attribute.codeType == ELSE) {
				tertiary_selection();
			}
			else {
				printError();
			}
			break;
		default:
			; /* Empty */
			break;
	}	
}

/* Loop Statement (while loop) */
pheonix_void loop_statement() {


}


/* Iteration Statement (for loop) */
pheonix_void iteration_statement() {


}

pheonix_void conditional_for_expr() {


}

/* Input Statement (read) */
/*************************************************************
 * Input statement
 * BNF: <input_statement> -> KW_T {read} 
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void input_statement() {

	matchToken(KW_T, READ);	
	/* Doesnt require EOF since it is only used in assignment_expr */
	printf("%s%s\n", STR_LANGNAME, ": Input statement parsed");
}


/* Output Statement (print) */
/*************************************************************
 * Output statement
 * BNF: <output_statement> -> KW_T {print} <opt_arg_list> EOS_T 
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void output_statement() {

	matchToken(KW_T, PRINT);
	opt_arg_list();
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

/*************************************************************
 * Optional argument list
 * BNF: <opt_arg_list> -> <argument_list>|e 
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void opt_arg_list() {

	switch(lookahead.code) {
		case KW_T:
		case LVID_T:
		case VID_T:
		case INL_T:
		case FPL_T:
		case CHL_T:
		case BYL_T:
		case STR_T:
			argument_list();
			break;
		default:
			; /* Empty */
			break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional argument list parsed");
}

/*************************************************************
 * Argument list
 * BNF: <argument_list> -> <argument><argument_list_prime>
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void argument_list() {

	argument();
	argument_list_prime();
	printf("%s%s\n", STR_LANGNAME, ": Argument list parsed");
}

/*************************************************************
 * Argument list prime
 * BNF: <argument_list_prime> -> <argument_list><argument_list_prime>|e
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void argument_list_prime() {

	switch(lookahead.code) {
		case KW_T:
		case LVID_T:
		case VID_T:
		case INL_T:
		case FPL_T:
		case CHL_T:
		case BYL_T:
		case STR_T:
			argument_list();
			argument_list_prime();
			break;
		default:
			; /* Empty */
			break;
	} 
}

/*************************************************************
 * Argument 
 * BNF: <argument> -> LVID_T | VID_T | INL_T | FPL_T | CHL_T |
BYL_T | STR_T 
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void argument() {

	switch(lookahead.code) {
		case VID_T:
			matchToken(VID_T, NO_ATTR);
			break;
		case LVID_T:
			matchToken(LVID_T, NO_ATTR);
			break;
		case INL_T:
			matchToken(INL_T, NO_ATTR);
			break;
		case FPL_T:
			matchToken(FPL_T, NO_ATTR);
			break;
		case CHL_T:
			matchToken(CHL_T, NO_ATTR);
			break;
		case BYL_T:
			matchToken(BYL_T, NO_ATTR);
			break;
		case STR_T:
			matchToken(STR_T, NO_ATTR);
			break;
			/* TODO: Could add support for keywords like true, false */
		case EOS_T:
			;
			break;
		default:
			printError();
			break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Argument parsed");
}

/* Function call */
/*************************************************************
 * Function call
 * BNF: <function_call> -> VID_T <opt_arg_list> EOS_T
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void function_call() {

	matchToken(VID_T, NO_ATTR);
	opt_arg_list();
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Function call parsed");
}

/* Return Statement */
/*************************************************************
 * Return statement
 * BNF: <return_statement> -> VID_T <opt_arg_list> EOS_T
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void return_statement() {

	matchToken(KW_T, RETURN);
	return_value();
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Return statement parsed");
}

/*************************************************************
 * Return value
 * BNF: <return_value> -> INL_T | FPL_T | CHL_T | BYL_T | STR_T
| VID_T | LVID_T | e
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void return_value() {

	switch(lookahead.code) {
		case INL_T:
			matchToken(INL_T, NO_ATTR);
			break;
		case FPL_T:
			matchToken(FPL_T, NO_ATTR); 
			break;
		case CHL_T:
			matchToken(CHL_T, NO_ATTR);
			break;
		case BYL_T:
			matchToken(BYL_T, NO_ATTR);
			break;
		case STR_T:
			matchToken(STR_T, NO_ATTR);
			break;
		case VID_T:
			matchToken(VID_T, NO_ATTR);
			break;
		case LVID_T:
			matchToken(LVID_T, NO_ATTR);
			break;
		default:
			; /* Empty */
			break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Return value parsed");
}

/* Arithmetic Expressions */
/*************************************************************
 * Arithmetic expression
 * BNF: <arithmetic_expr> -> <unary_arithmetic_expr>|<additive_arithmetic_expr>|e
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void arithmetic_expr() {

	switch(lookahead.code) {
		case ART_OP_T:
			if(lookahead.attribute.codeType == OP_ADD
			|| lookahead.attribute.codeType == OP_SUB) {
				unary_arithmetic_expr();
			}	
			else {
				additive_arithmetic_expr();
			}
			break;
		default:
			; /* Empty */
			break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Arithmetic expression parsed");
}

/*************************************************************
 * Unary arithmetic expression
 * BNF: <unary_arithmetic_expr> -> OP_SUB <primary_arithmetic_expr> 
| OP_ADD <primary_arithmetic_expr>
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void unary_arithmetic_expr() {

	switch(lookahead.code) {
		case ART_OP_T:
			if(lookahead.attribute.codeType == OP_ADD) {
				matchToken(ART_OP_T, OP_ADD); /* Right param doesn't actually matter */
				primary_arithmetic_expr();
			}
			else if(lookahead.attribute.codeType == OP_SUB) {
				matchToken(ART_OP_T, OP_SUB); /* Same thing as above */
				primary_arithmetic_expr();
			}
			else {
				printError();
			}
			break;
		default:
			printError();
			break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Unary arithmetic expression parsed");
}

/*************************************************************
 * Additive arithmetic expression
 * BNF: <additive_arithmetic_expr> -> 
	<multiplicative_arithmetic_expr><additive_arithmetic_expr_prime>
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void additive_arithmetic_expr() {

	multiplicative_arithmetic_expr();
	additive_arithmetic_expr_prime();
	printf("%s%s\n", STR_LANGNAME, ": Additive arithmetic expression parsed");	
}

/*************************************************************
 * Additive arithmetic expression prime
 * BNF: <additive_arithmetic_expr_prime> -> OP_ADD <additive_arithmetic_expr> 
| OP_SUB <additive_arithmetic_expr>|e
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void additive_arithmetic_expr_prime() {

	switch(lookahead.code) {
		case ART_OP_T:
			if(lookahead.attribute.codeType == OP_ADD) {
				matchToken(ART_OP_T, OP_ADD); /* Right param doesn't actually matter */
				additive_arithmetic_expr();
				additive_arithmetic_expr_prime();
			}
			else if(lookahead.attribute.codeType == OP_SUB) {
				matchToken(ART_OP_T, OP_SUB); /* Same thing as above */
				additive_arithmetic_expr();
				additive_arithmetic_expr_prime();
			}
			else {
				printError();
			}
			break;
		default:
			; /* Empty */
			break;
	}
}

/*************************************************************
 * Multiplicative arithmetic expression
 * BNF: <multiplicative_arithmetic_expr> ->
	<multiplicative_arithmetic_expr><additive_arithmetic_expr_prime> 
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void multiplicative_arithmetic_expr() {

	primary_arithmetic_expr();
	multiplicative_arithmetic_expr_prime();
	printf("%s%s\n", STR_LANGNAME, ": Multiplicative arithmetic expression parsed");
}

/*************************************************************
 * Multiplicative arithmetic expression prime
 * BNF: <multiplicative_arithmetic_expr_prime> ->
	OP_MUL <primary_arithmetic_expr>|OP_DIV <primary_arithmetic_expr>|e
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void multiplicative_arithmetic_expr_prime() {

	switch(lookahead.code) {
		case ART_OP_T:
			if(lookahead.attribute.codeType == OP_MUL) {
				matchToken(ART_OP_T, OP_MUL); /* Right param doesn't actually matter */
				primary_arithmetic_expr();
				multiplicative_arithmetic_expr_prime();
			}
			else if(lookahead.attribute.codeType == OP_DIV) {
				matchToken(ART_OP_T, OP_DIV); /* Same thing as above */
				primary_arithmetic_expr();
				multiplicative_arithmetic_expr_prime();
			}
			else {
				printError();
			}
			break;
		default:
			; /* Empty */
			break;
	}
}

/*************************************************************
 * Primary arithmetic expression 
 * BNF: <primary_arithmetic_expr> -> <numeric_value>|(<arithmetic_expr>)
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void primary_arithmetic_expr() {

	switch(lookahead.code) {
		/* (<arithmetic_expr>) */
		case LPR_T:
			matchToken(LPR_T, NO_ATTR);
			numeric_arithmetic_expr();
			matchToken(RPR_T, NO_ATTR);
			break;
		default:
			numeric_value();
			break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Primary arithmetic expression parsed");
}

/*************************************************************
 * Numeric arithmetic expression 
 * BNF: <numeric_arithmetic_expr> -> <numeric_value><arithmetic_expr>
| (<numeric_value>|<arithmetic_expr>)
| (<arithmetic_expr>)
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void numeric_arithmetic_expr() {

	switch(lookahead.code) {
		case LPR_T:
			matchToken(LPR_T, NO_ATTR);
			numeric_value();
			arithmetic_expr();
			matchToken(RPR_T, NO_ATTR);
			break;
		default:
			numeric_value();
			arithmetic_expr();
			break;
	}
	printf("%s%s\n", STR_LANGNAME, ": Numeric arithmetic expression parsed");
}

/*************************************************************
 * Numeric value
 * BNF: <numeric_value> -> FPL_T | INL_T | CHL_T | VID_T | LVID_T
 * FIRST(<program>)= 
 ************************************************************/
pheonix_void numeric_value() {

	switch(lookahead.code) {
		case INL_T:
			matchToken(INL_T, NO_ATTR);
			break;
		case FPL_T:
			matchToken(FPL_T, NO_ATTR);
			break;
		case CHL_T:
			matchToken(CHL_T, NO_ATTR);
			break;
		case VID_T:
			matchToken(VID_T, NO_ATTR);
			break;
		case LVID_T:
			matchToken(LVID_T, NO_ATTR);
			break;
		default:
			; /* There are cases where empty string is okay here */
			break;	
	}
	printf("%s%s\n", STR_LANGNAME, ": Numeric value parsed");
}

/* Bitwise Expressions */
pheonix_void bitwise_expr() {


}

pheonix_void left_bitshift() {


}

pheonix_void left_bitshift_prime() {


}

pheonix_void right_bitshift() {


}

pheonix_void right_bitshift_prime() {


}

pheonix_void bitwise_or() {


}

pheonix_void bitwise_and() {


}


/* Logical Expressions */
pheonix_void conditional_expr() {


}

pheonix_void logical_or_expr() {


}

pheonix_void logical_or_expr_prime() {


}

pheonix_void logical_and_expr() {


}

pheonix_void logical_and_expr_prime() {


}

pheonix_void logical_not_expr() {


}

pheonix_void relational_expr() {


}

pheonix_void relational_expr_prime() {


}

pheonix_void inner_conditional_op() {


}

pheonix_void bitwise_byte_expr() {


}
