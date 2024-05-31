#include"globals.h"
#include "scan.h"

static struct
    { char* str;
      TokenType tok;
    } reservedWords[MAXRESERVED]
   = {{"read",READ},
      {"write",WRITE}};

char tokenString[MAXTOKENLEN+1];      
static char lineBuf[ BUFLEN ];      
static int buf_size =0;
static int line_pos = 0;
static int EOF_flag = false;
static char get_next_char( void ){
    if ( !( line_pos < buf_size ) ){
        lineno++;
        if ( fgets(lineBuf, BUFLEN - 1, source ) ){
            buf_size = strlen(lineBuf );
            line_pos = 0;
            printf("%s\n", lineBuf);
            return lineBuf[ line_pos++ ];
        } else {
            printf("EOF\n");
            EOF_flag=true;
            return EOF;
        }
    } else {
        return lineBuf[ line_pos++ ];
    }
}

static void ungetNextChar( void ){

    line_pos--;
    
}

static TokenType reservedLookup (char * s)
{ int i;
  for (i=0;i<MAXRESERVED;i++)
    if (!strcmp(s,reservedWords[i].str))
      return reservedWords[i].tok;
  return ID; 
}
void printTokenType(TokenType token) {
    switch(token) {
        case ENDFILE:
            printf("ENDFILE\t ");
            break;
        case ERROR:
            printf("ERROR \t");
            break;
        case ID:
            printf("ID \t");
            break;
        case NUM:
            printf("NUM \t");
            break;
        case ASSIGN:
            printf("ASSIGN \t");
            break;
        case WRITE:
            printf("WRITE\t ");
            break;
        case READ:
            printf("READ \t");
            break;
        case PLUS:
            printf("PLUS ");
            break;
        case TIMES:
            printf("TIMES ");
            break;
        default:
            printf("Unknown TokenType\t ");
            break;
    }
}

TokenType getToken( void ){
    int tokenStringIndex = 0;


    TokenType current_token;
    StateType state = START;

    int save;

    while ( state != DONE ){
        char c = get_next_char();
        //printf( "%c : linepos: %d tokenStringIndex %d\n", c, line_pos, tokenStringIndex);
        save = true;

        switch ( state ){
            
            case START:
                if ( isdigit( c ) ){
                    current_token=NUM;
                    state = IN_NUM;
                } else if( c == ' ' || c == '\t' || c == '\n' ){
                    save = false;
                }else if( isalpha( c ) ){
                    current_token = ID;
                    state = IN_ID;}
                else if(c=='+' || c=='*'){
                    current_token = (c == '+') ? PLUS : TIMES;
                    state = DONE;
                    }
                else if(c==':'){
                    state = IN_ASSIGN;
                    }
                 else {    
                    state = DONE;
                    switch ( c ){
                        case EOF:
                            save = false;
                            current_token = ENDFILE;
                            break;
                            default:
                                current_token = ERROR;  // Adicione esta linha para lidar com caracteres desconhecidos
                                break;
                    }
                }
                break;
            case IN_NUM:
                if ( isdigit(c) ){
                    state = IN_NUM;
                    current_token = NUM;
                } else {
                    state = DONE;
                    save=false;
                    ungetNextChar();
                    tokenStringIndex--;
                }
                break;
            case IN_ID:
                if (!isalpha(c) ){
                    state = DONE;
                    save=false;
                    ungetNextChar();
                    tokenStringIndex--;
                }
                break;
            case IN_ASSIGN:
                if ( c == '=' ){
                    state = DONE;
                    current_token=ASSIGN;
                } else {
                    save=false;
                    state = DONE;
                    current_token=ERROR;
                    ungetNextChar();
                    tokenStringIndex--; 
                }
                break;
            default:
                printf( "Scanner Bug: state = %d\n", state );
                state = DONE;
                current_token = ERROR;
                break;
        }
        if ( ( save == true ) && ( tokenStringIndex <= MAXTOKENLEN ) ){
            tokenString[ tokenStringIndex++ ] = c;}
        if ( state == DONE ){
            tokenString[ tokenStringIndex+1] = '\0';
            
            if (current_token == ID)
         current_token = reservedLookup(tokenString);
            }
            //printTokenType(current_token);
    }    
    return current_token;
}