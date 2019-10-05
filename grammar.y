%{
    int yylex();
    void yyerror(const char *s);
%}

//definitions

%token IDENTIFIER CONSTANT STRING_LITERAL SIZEOF INCLUDE ENUMERATION_CONSTANT FILE_NAME
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME DOUBLE_QUOTE HASH DOT

%token TYPEDEF EXTERN STATIC AUTO REGISTER INLINE RESTRICT TYPEDEF_NAME
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID BOOL
%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%token LBRACE      //  {
%token RBRACE      //  }
%token LPAREN      //  (
%token RPAREN      //  )

%start compilation_unit

%%
//rules

//include
compilation_unit
    : include_files
    | variable_declaration
    | Statement
	| compilation_unit include_files
	| compilation_unit variable_declaration
	| compilation_unit Statement
	;

include_files
	: HASH INCLUDE file ';'
	;

file
    : '<' FILE_NAME '>'                         //#include <header.h>;
    | DOUBLE_QUOTE FILE_NAME DOUBLE_QUOTE       //#include "header.h";
    ;

//var declaration
variable_declaration
    : inline_initial_declaration ';'
    ;

inline_initial_declaration
    : initial_declaration
    | inline_initial_declaration ',' initial_declaration
    ;

initial_declaration
	: types IDENTIFIER assignment
	;


assignment
    :
    | '=' IDENTIFIER
    | '=' CONSTANT
    ;

types
	: VOID
	| CHAR
	| SHORT
	| INT
	| LONG
	| FLOAT
	| DOUBLE
	| SIGNED
	| UNSIGNED
	| BOOL
	;

FunctionDef
    : types IDENTIFIER LPAREN parameter_list RPAREN LBRACE FunctBody RBRACE

FunctionCall //проверить Лиза
    : IDENTIFIER LPAREN args_list  RPAREN ';'
    | IDENTIFIER LPAREN RPAREN ';'
    ;

args_list
    : args_list ',' IDENTIFIER
    | IDENTIFIER
    | IDENTIFIER assignment //приравнять парам функции чему-то - ТАК МОЖНО?
    ;

parameter_list
    : parameter_list COMMA arg
    | arg
    | arg assignment //уточнить может ли быть назначение параметра в Си ТАК МОЖНО?
    ;

arg
    : types IDENTIFIER

FuctionBody
	: variable_declaration ';'
	| for ';'
	| FunctionCall ';'
    | ArrayUsage ';'
    | Type ArrayUsage ';'
    | StructStmt ';'
    ;

Relation
	:
	;

Statement
	: variable_declaration ';'
	| for ';'
	| FunctionCall ';'
    | ArrayUsage ';'
    | Type ArrayUsage ';'
    | StructStmt ';'
    | FunctionDef ';'
    ;

//AYGUL ToDO
ArrayUsage
    :
    ;

//Lisa ToDO
StructStmt
    :
    ;

Expression
	:
	;

else_body
	:
	| ELSE Statement
	;

if
	: IF '(' Relation ')' Statement else_body
	;

while
	: WHILE '(' Relation ')' Statement
	;

zaglushka
    :
    ;

ArgumentList
    :                    Expression
    | ArgumentList ',' Expression
    ;

for_init
	:
	| initial_declaration
	;

for_condition
	:
	| Relation
	;

for_actions
	:
	| ArgumentList
	;

for
	: FOR '(' for_init ';' for_condition ';' for_actions ')' Statement



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