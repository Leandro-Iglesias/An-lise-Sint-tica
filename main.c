#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "scan.h"
int lineno=0;
FILE *source;
FILE *target;
int main(){
    setlocale(LC_ALL, "pt_BR.UTF-8");
    source = fopen( "source.tiny", "r" );
    target = fopen( "target.tiny", "w" );
    if ( source == NULL || target == NULL ){
        printf( "Erro na abertura de arquivos.\n" );
        fclose( source );
        fclose( target );
        return 1;
    }

    TokenType current_token;

    do {
        current_token = getToken();
        //printf("%s\n", tokenString);
        if ( current_token == ERROR ){
            printf( "Houve um erro léxico no código.\n" );
            break;
        } else if ( current_token == ENDFILE ){
            printf( "Fim do arquivo.\n" );
        } else if(current_token == ID){
            printf( "ID\n" );
        } else if(current_token == NUM){
            printf(  "NUM\n" );
        } else if(current_token == ASSIGN){
            printf(  "ASSIGN\n" );
        } else if(current_token == WRITE){
            printf( "WRITE\n" );
        } else if(current_token == READ){
            printf(  "READ\n" );
        } else if(current_token == PLUS){
            printf(  "PLUS\n" );
        } else if(current_token == TIMES){
            printf( "TIMES\n" );
        }  
        else {
            printf( "Houve um comportamento inesperado!\n" );
            break;
        }
    } while ( current_token != ENDFILE );

    fclose( source );
    fclose( target );
    return 0;
}