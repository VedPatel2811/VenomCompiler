/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2023
* Author: TO_DO
* Professors: Paulo Sousa
************************************************************
=---------------------------------------=
|  COMPILERS - ALGONQUIN COLLEGE (F23)  |
=---------------------------------------=
|              ....                     |
|          ........::.::::::.           |
|        .:........::.:^^^~~~:          |
|        :^^::::::^^^::^!7??7~^.        |
|       .:^~~^!77777~~7?YY?7??7^.       |
|       :.^~!??!^::::^^~!?5PY??!~.      |
|       ~!!7J~.:::^^^^~!!~~?G5J?~       |
|       :^~?!~7?Y57^^?PP5YJ!J5Y?:       |
|       .~!!.:^!7!:.:7JYYJ7~7Y7^        |
|       .~77..    . .~^:^^^~7?:         |
|       .^!^~:::.:^!7?~^~!77J:          |
|        ^^!Y~^^^^~?YJ77??7JJ^          |
|       .^7J?~^~~^~7??7??7JY?~:         |
|        ::^^~^7?!^~~!7???J?J7~:.       |
|         ^~~!.^7YPPPP5Y?7J7777~.       |
|        ..:~..:^!JPP5YJ?!777!^.        |
| .~?JJJJJJJJJJYYYYYPPPPPPPPPPPP5PPYY~  |
|  :!Y5GGG.___ YYYYYY__._.PPGGGGGG5!.   |
|   :!Y5G / __| ___ / _(_)__ _ PGP5.    |
|    :~75 \__ \/ _ \  _| / _` | 5?.     |
|     7~7 |___/\___/_| |_\__,_| Y5?.    |
|    .^~!~.....................P5YY7.   |
|   .:::::::::::::?JJJJYYYYYYYYYJJJJ7.  |
|                                       |
=---------------------------------------=
*/

/*
************************************************************
* File name: Scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define the number of tokens */
#define NUM_TOKENS 29

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token (start: &) */
	INL_T,		/*  2: Integer literal token */
	STR_T,		/*  3: String literal token */
	LPR_T,		/*  4: Left parenthesis token */
	RPR_T,		/*  5: Right parenthesis token */
	LBR_T,		/*  6: Left brace token */
	RBR_T,		/*  7: Right brace token */
	KW_T,		/*  8: Keyword token */
	EOS_T,		/*  9: End of statement (semicolon) */
	RTE_T,		/* 10: Run-time error token */
	SEOF_T,		/* 11: Source end-of-file token */
	CMT_T,		/* 12: Comment token */
	DIV_T,		/* 13: Divide token*/
	MULT_T,		/* 14: Multiplying token */
	ASN_T,		/* 15: Assignment operator token */
	PRINT_T,	/* 16: Print function token */
	COL_T,		/* 17: Colon token */
	OR_T,		/* 18: Logical OR operator token */
	EQ_T,		/* 19: Equality operator token */
	NEQ_T,		/* 20: Not equal to operator token */
	INC_T,		/* 21: Increment operator token */
	MLSTR_T,	/* 22: Multi-line string literal token */
	DQT_T,		/* 23: Double quote token */
	VID_T,		/* 24: Variable token */
	GRO_T,		/* 25: Grater-than operator token */
	LEO_T,		/* 26: Less-than operator token */ 
	ADD_T,		/* 27: Addition operator token */
	SUB_T		/* 27: Subtraction operator token */
};

/* TO_DO: Define the list of keywords */
static string tokenStrTable[NUM_TOKENS] = {
	"ERR_T",
	"MNID_T",
	"INL_T",
	"STR_T",
	"LPR_T",
	"RPR_T",
	"LBR_T",
	"RBR_T",
	"KW_T",
	"EOS_T",
	"RTE_T",
	"SEOF_T",
	"CMT_T",
	"DIV_T",
	"MULT_T",
	"ASN_T",
	"PRINT_T",
	"COL_T",
	"OR_T",
	"EQ_T",
	"NEQ_T",
	"INC_T",
	"MLSTR_T",
	"DQT_T",
	"VID_T",
	"GRO_T",
	"LEO_T",
	"ADD_T",
	"SUB_T"
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	int codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	int intValue;				/* integer literal attribute (value) */
	int keywordIndex;			/* keyword index in the keyword table */
	int contentString;			/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	float floatValue;				/* floating-point literal attribute (value) */
	char idLexeme[VID_LEN + 1];	/* variable identifier token attribute */
	char errLexeme[ERR_LEN + 1];	/* error token attribite */
	char vidLexeme[VID_T + 1];
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	byte flags;			/* Flags information */
	union {
		int intValue;				/* Integer value */
		float floatValue;			/* Float value */
		string stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	int code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

/* Scanner */
typedef struct scannerData {
	int scanHistogram[NUM_TOKENS];	/* Statistics of chars */
} ScannerData, * pScanData;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner:
 *  LPR_T, RPR_T, LBR_T, RBR_T, EOS_T, SEOF_T and special chars used for tokenis include _, & and ' */

 /* TO_DO: Define lexeme FIXED classes */
 /* These constants will be used on nextClass */
#define CHRCOL2 '_'
#define CHRCOL3 '\"'
#define CHRCOL4 '\n'
#define CHRCOL6 '#'
#define CHRCOL7 '\''
#define CHRCOL8 '\='

/* These constants will be used on VID / MID function */
#define MNID_SUF '('
#define COMM_SYM '#'

/* TO_DO: Error states and illegal state */
#define ESNR	10		/* Error state with no retract */
#define ESWR	10		/* Error state with retract */
#define FS		10		/* Illegal state */

 /* TO_DO: State transition table definition */
#define NUM_STATES		11 //rows
#define CHAR_CLASSES	12 //columns

/* TO_DO: Transition table - type of states defined in separate table */
static int transitionTable[NUM_STATES][CHAR_CLASSES] = {
	/*    [A-z],[0-9],    ,   ",   \n', SEOF,   #,    (,    '        other    =
		   L(0), D(1), U(2), M(3), Q(4), E(5), C(6), O(7),    O(8)    O(9)    O(10)    */
		{     1,    6, ESNR,    8,    4, ESWR,    4, ESNR,     4,        ESNR,    ESNR},    // S0: NOAS
		{     1,    1,    3,    3,    3,    3,    3,    2,     3,          3,		3},    // S1: NOAS
		{    FS,   FS,   FS,   FS,   FS,   FS,     FS,   FS,    FS,        FS,        FS},    // S2: ASNR (MVID)
		{    FS,   FS,   FS,   FS,   FS,   FS,     FS,   FS,    FS,        FS,        FS},    // S3: ASWR (KEY)
		{     4,    4,    4,    4,    5, ESWR,     4,      4,    4,        4,        4},    // S4: NOAS
		{    FS,   FS,   FS,   FS,   FS,   FS,     FS,   FS,    FS,        FS,        FS},    // S5: ASNR (Comment)
		{     7,    6,    7,    7,    7,    7,     7,     7,    7,         7,        7},    // S6: NOAS
		{    FS,   FS,   FS,   FS,   FS,   FS,     FS,   FS,    FS,        FS,        FS},    // S7: ASNR (COM)
		{     8,    8,    8,    9,    8,    8,      8,    8,     8,         8,         8},    // S8: ASNR (ES)
		{    FS,   FS,   FS,   FS,   FS,   FS,     FS,   FS,    FS,        FS,        FS},  // S9: ASWR (ER)
		{    FS,   FS,   FS,   FS,   FS,   FS,     FS,   FS,    FS,        FS,        FS}/* // S10: Error without Retract
		{11,   10,   11,   11,   11,   11,     11,   11,    11,        10,    11},    // S10: ASWR (IL)
		{    FS,   FS,   FS,   FS,   FS,   FS,     FS,   FS,    FS,        FS,        FS} // S11: ASWR (FL)*/
};


/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static int stateType[NUM_STATES] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSNR, /* 02 (MID) - Methods */
	FSWR, /* 03 (KEY) */
	NOFS, /* 04 */
	FSNR, /* 05 (SL) */
	NOFS, /* 06 (int literal) */
	FSNR, /* 07 (COM) */
	NOFS, /* 08 (Err1 - no retract) */
	FSNR, /* 09 (Err2 - retract) */
	FSNR/*, /* 10 (Err1 - no retract)
	FSNR  /* 11 (int literal)*/
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
int			startScanner(BufferPointer psc_buf);
static int	nextClass(char c);					/* character class function */
static int	nextState(int, char);		/* state machine function */
void			printScannerData(ScannerData scData);
Token				tokenizer(void);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(string lexeme);

/* Declare accepting states functions */
Token funcSL(string lexeme);
Token funcIL(string lexeme);
Token funcID(string lexeme);
Token funcCMT(string lexeme);
Token funcKEY(string lexeme);
Token funcErr(string lexeme);
Token funcVID(string lexeme);

/*
 * Accepting function (action) callback table (array) definition
 * If you do not want to use the typedef, the equvalent declaration is:
 */

 /* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[NUM_STATES] = {
	NULL,      /* -    [00] */
	NULL,      /* -    [01] */
	funcID,    /* MNID [02] */
	funcKEY,   /* KEY  [03] */
	NULL,      /* -    [04] */
	funcCMT,    /* SL   [05] */
	NULL,      /* -    [06] */
	funcIL,   /* COM  [07] */
	NULL,   /* [08] */
	funcSL,   /* ERR2 [09] */
	funcErr	 /* ERR1 */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 12

/* TO_DO: Define the list of keywords */
static string keywordTable[KWT_SIZE] = {
	"func",		/* KW00 */ //data
	"long",		/* KW01 */ //code
	"int",		/* KW02 */
	"float",	/* KW03 */ //real
	"string",	/* KW04 */
	"if",		/* KW05 */
	"elif",	    /* KW06 */ //then
	"else",		/* KW07 */
	"while",	/* KW08 */
	"or",		/* KW09 */
	"and",	    /* KW10 */
	"for",		/* KW11 */
};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

 /* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	char indentationCharType;
	int indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
int numScannerErrors;

/* Scanner data */
ScannerData scData;

#endif
