%{
    #include <stdio.h>
    #include "Tree.c"

    #ifndef YYSTYPE
    # define YYSTYPE char*
    #endif
    int yylex();
    void yyerror(const char *s);
%}

//definitions
%union {
    char *string;
    struct variable_declaration *variable_declaration;
    struct global_declaration *global_decl;
    struct include_files *include_files;
    struct typechain *typechain;
    struct StructDef *StructDef;
    struct initial_declaration *initial_declaration;
}

%token CONSTANT SIZEOF INCLUDE ENUMERATION_CONSTANT INTEGER_CONSTANT FLOAT_CONSTANT
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME DOUBLE_QUOTE HASH DOT  NULL_

%token TYPEDEF EXTERN STATIC AUTO REGISTER INLINE RESTRICT TYPEDEF_NAME
%token <string> IDENTIFIER
%token <string> CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID BOOL
%token <string> FILE_LITERAL STRING_LITERAL


%type  <string> types file
%type  <variable_declaration> variable_declaration
%type  <typechain> typechain
%type  <global_declaration> compilation_unit
%type  <StructDef> StructDef
%type  <include_files> include_files
%type  <initial_declaration> initial_declaration

%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%token LBRACE      //  {
%token RBRACE      //  }
%token LPAREN      //  (
%token RPAREN      //  )

%start compilation_unit

%%
//rules
compilation_unit
    : global_declaration        { $$ = global_decl(); }
    | compilation_unit global_declaration
	;

global_declaration
    : include_files
    | FunctionDef
    | variable_declaration ';'
    | StructDef ';'
    | typedef_declaration ';'
    ;

include_files
	: HASH INCLUDE file                 { $$ = include_files($3); }
	;

file
    : FILE_LITERAL                      //#include <header.h>
	| STRING_LITERAL 				    //#include "header.h"
    ;

typedef_declaration
    : TYPEDEF typechain list_identifiers
    ;

list_identifiers
	: list_identifiers ',' IDENTIFIER
	| list_identifiers ',' '(' '*' IDENTIFIER ')' '('')'
	| list_identifiers ',' '(' '*' IDENTIFIER ')' '('types_list')'
	| list_identifiers ',' '(' '*' IDENTIFIER ')' '('param_list')'
	| '(' '*' IDENTIFIER ')' '('')'
	| '(' '*' IDENTIFIER ')' '('types_list')'
	| '(' '*' IDENTIFIER ')' '('param_list')'
	| IDENTIFIER
	;

types_list
	: types_list ',' typechain
	| types_list ',' typechain '[' ']'
	| types_list ',' typechain '[' index ']'
	| typechain '[' ']'
	| typechain '[' index ']'
	| typechain
	;

variable_declaration
    : typechain inline_initial_declaration               { $$ = variable_declaration($1, $2); }
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
	| IDENTIFIER '[' index ']'
    ;

list_initializer
	: '=' '{' args_list '}'
	| '=' '{' '}'
	;

assignment
    :
	| '=' cast
    ;

typechain
    : types         { $$ = $1;}
	| StructDef     { $$ = $1;}
	| types pointer { $$ = $1;}
	| StructDef pointer     { $$ = $1;}
    ;

types
	: CHAR          { $$ = $1; }
	| SHORT         { $$ = $1; }
	| INT           { $$ = $1; }
	| LONG          { $$ = $1; }
	| FLOAT         { $$ = $1; }
	| DOUBLE        { $$ = $1; }
	| SIGNED        { $$ = $1; }
	| UNSIGNED      { $$ = $1; }
	| BOOL          { $$ = $1; }
	| VOID          { $$ = $1; }
	| IDENTIFIER    { $$ = $1; }
	;

pointer
    : pointer '*'
    | '*'
    ;

cast
	: r_value
	| '(' typechain ')' cast
	;

args_list
    : args_list ',' cast
	| cast
    ;

Body
	: '{' ComplexBody '}'
	| Statement
	;

ComplexBody
	: Statement ComplexBody
	|
	;

Return
    : RETURN cast
    | RETURN
    ;

Statement
	: variable_declaration ';'
	| Expression ';'
	| if
	| for
	| while
	| FunctionCall ';'
	| StructDef ';'
	| typedef_declaration ';'
	| Return ';'
	| ';'
	;

literal
    : CONSTANT
    | INTEGER_CONSTANT
	| FLOAT_CONSTANT
	| CHAR
	| STRING_LITERAL
    ;

Expression
	: l_value assignment
	| l_value short_math
	| inc_and_dec
	;

index
	: INTEGER_CONSTANT
	| IDENTIFIER
	;

// function
FunctionDef
    : typechain IDENTIFIER '(' param_list ')' Body
    | typechain IDENTIFIER '(' VOID ')' Body
    | typechain IDENTIFIER '(' ')' Body
    ;

param_list
    : param_list ',' param
    | typechain field_name
	;

param
    : typechain param_name
	| param_name
    ;

param_name
	: field_name
	| IDENTIFIER '['']'
	;

FunctionCall
    : IDENTIFIER '(' args_list ')'
	| IDENTIFIER '(' ')'
    ;

// struct
StructDef
	: STRUCT IDENTIFIER '{' field_list '}'
	| STRUCT '{' field_list '}'
	| STRUCT IDENTIFIER
	//| TYPEDEF STRUCT IDENTIFIER '{' field_list '}'
	//| TYPEDEF STRUCT '{' '}' IDENTIFIER
	//| TYPEDEF STRUCT '{'field_list '}' IDENTIFIER
    ;

StructCall
	: StructCall DOT field_name
	| StructCall PTR_OP field_name
	| field_name DOT field_name
	| field_name PTR_OP field_name
	;

field_list
    : field ';' field_list
    |
	;

field
    : typechain inline_field_names
    ;

inline_field_names
    : inline_field_names ',' field_name
    | field_name
    ;

field_name
	: IDENTIFIER
	| IDENTIFIER '[' index ']'
	;

// if statement
if
	: IF '(' logic_expr ')' Body else_body
	;

else_body
	:
	| ELSE Body
	;

// while loop
while
	: WHILE '(' logic_expr ')' Body
	;

// for loop
for
	: FOR '(' for_init ';' for_condition ';' for_actions ')' Body
	;

ExpressionList
    : ExpressionList ',' Expression
    | Expression
    ;

for_init
	:
	| variable_declaration
	| ExpressionList
	;

for_condition
	:
	| logic_expr
	;

for_actions
	:
	| ExpressionList
	;

// math

inc_and_dec
	: INC_OP l_value
	| DEC_OP l_value
	| l_value INC_OP
	| l_value DEC_OP
	;

l_value
	: pointer field_name
	| field_name
	| pointer StructCall
	| StructCall
	;

r_value
	: value
	| NULL_
	| math_expr
	| logic_expr
	;

value
	: literal
    | l_value
    | '&' l_value                        // address
    | FunctionCall
	;

short_math
	: ADD_ASSIGN r_value
	| SUB_ASSIGN r_value
	| MUL_ASSIGN r_value
	| DIV_ASSIGN r_value
	;

math_expr
 	: '('math_expr')'
 	| math_expr '+' math_expr
	| math_expr '-' math_expr
	| math_expr '*' math_expr
	| math_expr '/' math_expr
	| math_expr '%' math_expr
	| value
 	;

logic_expr
	: '(' logic_expr ')'
	| '!' logic_expr
	| logic_expr AND_OP logic_expr
	| logic_expr OR_OP logic_expr
	| logic_expr LE_OP logic_expr
	| logic_expr GE_OP logic_expr
	| logic_expr EQ_OP logic_expr
	| logic_expr NE_OP logic_expr
	| logic_expr '<' logic_expr
	| logic_expr '>' logic_expr
	| value
	| math_expr
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