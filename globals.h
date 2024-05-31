#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#ifndef FALSE
#define false 0
#endif

#ifndef TRUE
#define true 1
#endif

/*************************************************/
/******************* Arquivos ********************/
/*************************************************/
extern FILE* source;
extern FILE* target;

extern int lineno;

/*************************************************/
/******************** Tokens *********************/
/*************************************************/
typedef enum _token_type_{
    ENDFILE, ERROR,
    GENERIC,
    ID,NUM,
    ASSIGN, WRITE, READ, PLUS, TIMES
} TokenType;
extern FILE* source; /* source code text file */
extern FILE* listing; /* listing output text file */
extern int lineno; 
#endif
