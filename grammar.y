%{
    int yylex();
    void yyerror(const char *s);
%}

//definitions

%token FILE_NAME
%token IDENTIFIER CONSTANT STRING_LITERAL SIZEOF INCLUDE
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME DOUBLE_QUOTE HASH DOT

%token TYPEDEF EXTERN STATIC AUTO REGISTER INLINE RESTRICT
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token BOOL COMPLEX IMAGINARY
%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%start compilation_unit

%%
//rules

compilation_unit
    : include_files
	| compilation_unit include_files
	;

include_files
	: HASH INCLUDE file ';'
	;

file
    : '<' FILE_NAME '>'                         //#include <header.h>;
    | DOUBLE_QUOTE FILE_NAME DOUBLE_QUOTE       //#include "header.h";
    ;


%%
//subroutines

#include <stdio.h>

extern char yytext[];
extern int column;

int main(int argc, char **argv){
    yyparse();
    return 0;
}

void yyerror(char const *s){
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}