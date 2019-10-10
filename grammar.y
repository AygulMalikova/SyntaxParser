%{
    int yylex();
    void yyerror(const char *s);
%}

//definitions

%token IDENTIFIER CONSTANT STRING_LITERAL SIZEOF INCLUDE ENUMERATION_CONSTANT INTEGER_CONSTANT FLOAT_CONSTANT
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME DOUBLE_QUOTE HASH DOT FILE_LITERAL NULL_

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
    : global_declaration
    | compilation_unit global_declaration
	;

global_declaration
    : include_files
    | FunctionDef
    | variable_declaration
    | StructDef ';'
    | typedef_declaration
    ;

include_files
	: HASH INCLUDE file ';'
	;

file
    : FILE_LITERAL                         //#include <header.h>; TODO: #include "header.h";
    ;

//var declaration
variable_declaration
    : typechain inline_initial_declaration ';'
    ;

inline_initial_declaration
    : initial_declaration
    | inline_initial_declaration ',' initial_declaration
    ;

initial_declaration
	: IDENTIFIER assignment                               // primitives
	| array_declaration                                   // arrays
	| IDENTIFIER list_initializer
	;

array_declaration
    : IDENTIFIER '[' ']' list_initializer
    | IDENTIFIER '[' index ']' list_initializer      // int array[10];
    ;

typedef_declaration
    :
    ;

list_initializer
    : '=' '{' args_list '}'
	|
    ;

assignment
    :
	| '=' NULL_
    | '=' cast literal
    | '=' cast CHAR
    | '=' cast STRING_LITERAL       // "123Hello"
    | '=' cast IDENTIFIER
    | '=' cast '&' IDENTIFIER                        // address
    | '=' cast pointer IDENTIFIER                        // address
    | '=' cast FunctionCall
    | '=' cast StructCall
    | '=' cast math_expr
    ;

typechain
    : types
	| StructDef
	| types pointer
	| StructDef pointer
    ;

types
	: CHAR
	| SHORT
	| INT
	| LONG
	| FLOAT
	| DOUBLE
	| SIGNED
	| UNSIGNED
	| BOOL
	;

pointer
    : pointer '*'
    | '*'
    ;

cast
	: '(' typechain ')'
	|
	;

FunctionDef
    : VOID IDENTIFIER '(' parameter_list ')' CompoundStmt
    | typechain IDENTIFIER '(' parameter_list ')' CompoundStmt
    | typechain IDENTIFIER '(' VOID ')' CompoundStmt
    | typechain IDENTIFIER '('  ')' CompoundStmt
    | typechain IDENTIFIER '(' ')' ';'
    ;

CompoundStmt
	: '{' FunctionBody '}'
	| '{' FunctionBody Return '}'
	;

args_list
    : args_list ',' cast arg
    | cast arg
    ;

arg
	: IDENTIFIER
	| literal
	| StructCall
	| FunctionCall
	;

FunctionCall
    : IDENTIFIER '(' args_list ')'
    | IDENTIFIER '(' ')'
    ;

parameter_list
    : parameter_list ',' param
    | param
    ;

param
    : typechain IDENTIFIER
    | typechain array_declaration
    | cast StructInit
    ;

FunctionBody
	: FunctionBody FunctPart
	| FunctPart
	;

FunctPart
	: variable_declaration
	| Expression
	| if
	| for
	| while
	| FunctionCall
	| StructCall
	| ';'
	;


Return
    : RETURN cast arg ';'
    | RETURN ';'
    ;

literal
    : CONSTANT
    | INTEGER_CONSTANT
	| FLOAT_CONSTANT
	| CHAR
	| STRING_LITERAL
    ;

Relation
	:
	;

Statement
	: variable_declaration ';'
	| Expression ';'
	| if ';'
	| for ';'
	| while ';'
	| FunctionCall ';'
	| StructDef ';'
	| StructInit ';'
	| FunctionDef ';'
	;

StructParam
    : typechain IDENTIFIER ';'
    | typechain array_declaration ';'
    | StructInit ';'
    ;

fields_list
    : fields_list StructParam
    | StructParam
	;

StructDef
	: STRUCT IDENTIFIER '{' fields_list '}'
	| STRUCT '{' fields_list '}'
	| STRUCT IDENTIFIER
    ;

StructInit
	: STRUCT IDENTIFIER IDENTIFIER '=' '{' args_list '}'
	| STRUCT IDENTIFIER IDENTIFIER
	;

//p.lastname
StructCall
	: StructName DOT StructField
	| StructName "->" StructField
	;

StructName
	: IDENTIFIER
	;

StructField
	: IDENTIFIER
	;

Expression
	: IDENTIFIER assignment ';'
	| StructCall assignment ';'
	| IDENTIFIER '[' index ']' assignment ';'
	;

index
	: INTEGER_CONSTANT
	| IDENTIFIER
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
	| variable_declaration
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
	;

math_expr
 : math_expr '+' math_expr
  | math_expr '-' math_expr
  | math_expr '*' math_expr
  | math_expr '/' math_expr
  | math_expr '%' math_expr
  | '('math_expr')'
  | arg
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