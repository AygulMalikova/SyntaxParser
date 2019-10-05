%{
    int yylex();
    void yyerror(const char *s);
%}

//definitions

%token IDENTIFIER CONSTANT STRING_LITERAL SIZEOF INCLUDE ENUMERATION_CONSTANT FILE_NAME CHAR INTEGER_CONSTANT
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
	: types IDENTIFIER assignment       // primitives
	| types array_declaration
	;

array_declaration
    : IDENTIFIER '[' ']' list_initializer
    | IDENTIFIER '[' INTEGER_CONSTANT ']'
    | IDENTIFIER '[' INTEGER_CONSTANT ']' list_initializer
    ;

//Aygul ToDO
ArrayUsage
    :
    ;

list_initializer
    : '=' '{' comma_separation '}'
    | designated_initializer
    ;

designated_initializer
    : '=' '{' '[' CONSTANT ' .'' .'' .' CONSTANT ']' '=' CONSTANT '}'
    | '=' '{' '[' CONSTANT ' .'' .'' .' CONSTANT ']' '=' CHAR '}'
    ;

comma_separation
    :
    | literal
    | CHAR
    | comma_separation ',' literal
    | comma_separation ',' CHAR
    ;

assignment
    :
    | '=' literal
    | '=' CHAR
    | '=' IDENTIFIER //check
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
    : types IDENTIFIER '(' parameter_list ')' '{' FunctionBody Return '}'
    | VOID IDENTIFIER '(' parameter_list ')' '{' FunctionBody '}'
    | types IDENTIFIER '(' VOID ')' '{' FunctionBody Return'}'
    | types IDENTIFIER '('  ')' '{' FunctionBody Return'}'
    ;

FunctionCall //check
    : IDENTIFIER '(' args_list ')' ';'
    | IDENTIFIER '(' ')' ';'
    ;

args_list
    : args_list ',' IDENTIFIER
    | IDENTIFIER
    ;

parameter_list
    : parameter_list ',' arg
    | arg
    ;

arg
    : types IDENTIFIER

FunctionBody
	: variable_declaration ';'
	| Expression';'
	| if ';'
	| for ';'
	| while ';'
	| FunctionCall ';'
    | ArrayUsage ';'
    | types ArrayUsage ';'
    | StructStmt ';'
    | Return ';'
    | FunctionBody
    ;

Return
    : RETURN '(' IDENTIFIER ')' ';'
    | RETURN IDENTIFIER ';'
    | RETURN value ';'
    | RETURN '(' value ')' ';'
    | RETURN ';'
    ;

value
	: CHAR
	| SHORT
	| INT
	| LONG
	| FLOAT
	| DOUBLE
	| SIGNED
	| UNSIGNED
	| BOOL
	| pointer
	| address
	;

literal
    : CONSTANT
    | INTEGER_CONSTANT
    ;

//TODO
address
    :
    ;
//TODO
pointer
    :
    ;

Relation
	:
	;

Statement
	: variable_declaration ';'
	| Expression
	| if ';'
	| for ';'
	| while ';'
	| FunctionCall ';'
    | ArrayUsage ';'
    | types ArrayUsage ';'
    | StructStmt ';'
    | FunctionDef ';'
    | Statement
    ;


//Lisa ToDO
StructStmt
    :
    ;

//Check
Expression
	: IDENTIFIER assignment ';'

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