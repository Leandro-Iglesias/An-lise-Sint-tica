#ifndef _SCAN_H_
#define _SCAN_H_
#define MAXTOKENLEN 40
#define BUFLEN 256
#define MAXRESERVED 2

/*************************************************/
/******************** Tokens *********************/
/*************************************************/

typedef enum _state_type_{
    START,IN_ID, IN_NUM, IN_ASSIGN, DONE
} StateType;
extern char tokenString[ MAXTOKENLEN + 1 ];
TokenType getToken( void );



void printToken( TokenType );


TokenType getToken( void );

#endif