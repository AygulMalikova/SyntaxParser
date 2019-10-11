%define parse.error verbose
%{
    #include <stdio.h>
    #include "Tree.h"
    int yylex();
    void yyerror(const char *s);
    struct compilation_unit* root;
%}

//definitions
%union {
    char *string;
    char character;
    int integer;
    float float_value;

    struct variable_declaration *variable_declaration;
    struct global_declaration *global_declaration;
    struct include_files *include_files;
    struct param_name *param_name;
    struct typechain *typechain;
    struct StructDef *StructDef;
    struct inline_initial_declaration *inline_initial_declaration;
    struct initial_declaration *initial_declaration;
    struct math_expr *math_expr;
    struct cast *cast;
    struct value *value;
    struct r_value *r_value;
    struct l_value *l_value;
    struct literal *literal;
    struct array_declaration *array_declaration;
    struct list_initializer *list_initializer;
    struct FunctionCall *FunctionCall;
    struct args_list *args_list;
    struct StructCall *StructCall;
    struct logic_expr *logic_expr;
    struct field_list *field_list;
    struct field *field;
    struct inline_field_names *inline_field_names;
    struct field_name *field_name;
    struct FunctionDef *FunctionDef;
    struct param_list *param_list;
    struct Body *Body;
    struct ComplexBody *ComplexBody;
    struct else_body *else_body;
    struct Statement *Statement;
    struct Expression *Expression;
    struct assignment *assignment;
    struct short_math *short_math;
    struct inc_and_dec *inc_and_dec;
    struct if_statement *if_statement;
    struct for_statement *for_statement;
    struct for_init *for_init;
    struct ExpressionList *ExpressionList;
    struct for_condition *for_condition;
    struct for_actions *for_actions;
    struct while_statement *while_statement;
    struct typedef_declaration *typedef_declaration;
    struct list_identifiers *list_identifiers;
    struct types_list *types_list;
    struct param *param;
    struct Return *Return;
    struct pointer *pointer;
    struct index *index;
    struct compilation_unit *compilation_unit;
}

%token SIZEOF INCLUDE ENUMERATION_CONSTANT
%token PTR_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME DOUBLE_QUOTE HASH DOT  NULL_

%token TYPEDEF EXTERN STATIC AUTO REGISTER INLINE RESTRICT TYPEDEF_NAME

%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%token LBRACE      //  {
%token RBRACE      //  }
%token LPAREN      //  (
%token RPAREN      //  )

%token <integer> CONSTANT INTEGER_CONSTANT
%token <float_value> FLOAT_CONSTANT
%token <string> IDENTIFIER INC_OP DEC_OP
%token <string> SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID BOOL
%token <string> FILE_LITERAL STRING_LITERAL
%token <character> CHAR


%type  <string> types file
%type  <variable_declaration> variable_declaration
%type  <typechain> typechain
%type  <global_declaration> global_declaration
%type  <compilation_unit> compilation_unit
%type  <StructDef> StructDef
%type  <include_files> include_files
%type  <initial_declaration> initial_declaration
%type  <inline_initial_declaration> inline_initial_declaration
%type  <math_expr> math_expr
%type  <array_declaration> array_declaration
%type  <pointer> pointer
%type  <cast> cast
%type  <value> value
%type  <l_value> l_value
%type  <r_value> r_value
%type  <literal> literal
%type  <list_initializer> list_initializer
%type  <FunctionCall> FunctionCall
%type  <args_list> args_list
%type  <StructCall> StructCall
%type  <logic_expr> logic_expr
%type  <field_list> field_list
%type  <field> field
%type  <inline_field_names> inline_field_names
%type  <field_name> field_name
%type  <FunctionDef> FunctionDef
%type  <param_list> param_list
%type  <Body> Body
%type  <param_name> param_name
%type  <ComplexBody> ComplexBody
%type  <else_body> else_body
%type  <Statement> Statement
%type  <Expression> Expression
%type  <assignment> assignment
%type  <short_math> short_math
%type  <inc_and_dec> inc_and_dec
%type  <if_statement> if
%type  <for_statement> for
%type  <for_init> for_init
%type  <ExpressionList> ExpressionList
%type  <for_condition> for_condition
%type  <for_actions> for_actions
%type  <while_statement> while
%type  <typedef_declaration> typedef_declaration
%type  <list_identifiers> list_identifiers
%type  <types_list> types_list
%type  <param> param
%type  <Return> Return
%type  <index> index


%start compilation_unit

%%
//rules
compilation_unit
    : global_declaration        { $$ = compilation_unit($1, NULL); root = $$;}
    | compilation_unit global_declaration   { $$ = compilation_unit($2, $1); root = $$;}
	;

global_declaration
    : include_files             { $$ = global_declaration($1, NULL, NULL, NULL, NULL); }
    | FunctionDef               { $$ = global_declaration(NULL, NULL, $1, NULL, NULL); }
    | variable_declaration ';'  { $$ = global_declaration(NULL, $1, NULL, NULL, NULL); }
    | StructDef ';'             { $$ = global_declaration(NULL, NULL, NULL, NULL, $1); }
    | typedef_declaration ';'   { $$ = global_declaration(NULL, NULL, NULL, $1, NULL); }
    ;

include_files
	: HASH INCLUDE file         { $$ = include_files($3); }
	;

file
    : FILE_LITERAL              { $$ = "FILE_NAME"; }        //#include <header.h>
	| STRING_LITERAL 			{ $$ = "FILE_NAME"; }  	    //#include "header.h"
    ;

typedef_declaration
    : TYPEDEF typechain list_identifiers                              { $$ = typedef_declaration($2, $3); }
    ;

list_identifiers
	: list_identifiers ',' IDENTIFIER                                 { $$ = list_identifiers($1, 0, "IDENTIFIER", NULL, NULL); }
	| list_identifiers ',' '(' '*' IDENTIFIER ')' '('')'             { $$ = list_identifiers($1, 1, "IDENTIFIER", NULL, NULL); }
	| list_identifiers ',' '(' '*' IDENTIFIER ')' '('types_list')'   { $$ = list_identifiers($1, 1, "IDENTIFIER", $8, NULL); }
	| list_identifiers ',' '(' '*' IDENTIFIER ')' '('param_list')'   { $$ = list_identifiers($1, 1, "IDENTIFIER", NULL, $8); }
	| '(' '*' IDENTIFIER ')' '('')'                                  { $$ = list_identifiers(NULL, 1, "IDENTIFIER", NULL, NULL); }
	| '(' '*' IDENTIFIER ')' '('types_list')'                        { $$ = list_identifiers(NULL, 1, "IDENTIFIER", $6, NULL); }
	| '(' '*' IDENTIFIER ')' '('param_list')'                        { $$ = list_identifiers(NULL, 1, "IDENTIFIER", NULL, $6); }
	| IDENTIFIER                                                      { $$ = list_identifiers(NULL, 0, "IDENTIFIER", NULL, NULL); }
	;

types_list
	: types_list ',' typechain                                       { $$ = types_list($1, $3, 0, NULL); }
	| types_list ',' typechain '[' ']'                               { $$ = types_list($1, $3, 1, NULL); }
	| types_list ',' typechain '[' index ']'                         { $$ = types_list($1, $3, 1, $5); }
	| typechain '[' ']'                                              { $$ = types_list(NULL, $1, 1, NULL); }
	| typechain '[' index ']'                                        { $$ = types_list(NULL, $1, 1, $3); }
	| typechain                                                      { $$ = types_list(NULL, $1, 0, NULL); }
	;

variable_declaration
    : typechain inline_initial_declaration                          { $$ = variable_declaration($1, $2); }
    ;

inline_initial_declaration
    : initial_declaration                                           { $$ = inline_initial_declaration($1, NULL); }
    | inline_initial_declaration ',' initial_declaration            { $$ = inline_initial_declaration($3, $1); }
    ;

initial_declaration
	: IDENTIFIER assignment                                         { $$ = initial_declaration("IDENTIFIER", $2, NULL, NULL); }               // primitives
	| array_declaration                                             { $$ = initial_declaration(NULL, NULL, $1, NULL); }               // arrays
	| IDENTIFIER list_initializer                                   { $$ = initial_declaration("IDENTIFIER", NULL, NULL, $2); }
	;

array_declaration
    : IDENTIFIER '[' ']' list_initializer                           { $$ = array_declaration("IDENTIFIER", NULL, $4); }
    | IDENTIFIER '[' index ']' list_initializer                     { $$ = array_declaration("IDENTIFIER", $3, $5); } // int array[10];
	| IDENTIFIER '[' index ']'                                      { $$ = array_declaration("IDENTIFIER", $3, NULL); }
    ;

list_initializer
	: '=' '{' args_list '}'                                         { $$ = list_initializer($3); }
	| '=' '{' '}'                                                   { $$ = list_initializer(NULL); }
	;

assignment
    :                                                               { $$ = NULL; }
    | '=' cast                                                      { $$ = assignment($2); }
    ;

typechain
    : types                 { $$ = typechain($1, NULL, NULL); }
	| StructDef             { $$ = typechain(NULL, $1, NULL); }
	| types pointer         { $$ = typechain($1, NULL, $2); }
	| StructDef pointer     { $$ = typechain(NULL, $1, $2); }
    ;

types
	: CHAR          { $$ = "char"; }
	| SHORT         { $$ = "short"; }
	| INT           { $$ = "int"; }
	| LONG          { $$ = "long"; }
	| FLOAT         { $$ = "float"; }
	| DOUBLE        { $$ = "double"; }
	| SIGNED        { $$ = "signed"; }
	| UNSIGNED      { $$ = "unsigned"; }
	| BOOL          { $$ = "bool"; }
	| VOID          { $$ = "void"; }
	| IDENTIFIER    { $$ = "IDENTIFIER"; }
	;

pointer
    : pointer '*'   { $$ = pointer($1); }
    | '*'           { $$ = pointer(NULL); }
    ;

cast
	: r_value                       { $$ = cast($1, NULL, NULL); }
	| '(' typechain ')' cast        { $$ = cast(NULL, $2, $4); }
	;

args_list
    : args_list ',' cast            { $$ = args_list($3, $1); }
	| cast                          { $$ = args_list($1, NULL); }
    ;

Body
	: '{' ComplexBody '}'           { $$ = Body($2, NULL);}
	| Statement                     { $$ = Body(NULL, $1);}
	;

ComplexBody
	: Statement ComplexBody         { $$ = ComplexBody($1, $2);}
	|                               { $$ = NULL; }
	;

Return
    : RETURN cast                   { $$ = Return($2); }
    | RETURN                        { $$ = Return(NULL); }
    ;

Statement
	: variable_declaration ';'      { $$ = Statement($1, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL); }
	| Expression ';'                { $$ = Statement(NULL, $1, NULL, NULL, NULL, NULL, NULL, NULL, NULL); }
	| if                            { $$ = Statement(NULL, NULL, $1, NULL, NULL, NULL, NULL, NULL, NULL); }
	| for                           { $$ = Statement(NULL, NULL, NULL, $1, NULL, NULL, NULL, NULL, NULL); }
	| while                         { $$ = Statement(NULL, NULL, NULL, NULL, $1, NULL, NULL, NULL, NULL); }
	| FunctionCall ';'              { $$ = Statement(NULL, NULL, NULL, NULL, NULL, $1, NULL, NULL, NULL); }
	| StructDef ';'                 { $$ = Statement(NULL, NULL, NULL, NULL, NULL, NULL, $1, NULL, NULL); }
	| typedef_declaration ';'       { $$ = Statement(NULL, NULL, NULL, NULL, NULL, NULL, NULL, $1, NULL); }
	| Return ';'                    { $$ = Statement(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, $1); }
	| ';'                           { $$ = Statement(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL); }
	;

literal
    : STRING_LITERAL                { $$ = literal($1, (char) 0, 0, 0); }
    | CHAR                          { $$ = literal(NULL, $1, 0, 0); }
    | FLOAT_CONSTANT                { $$ = literal(NULL, (char) 0, $1, 0); }
    | CONSTANT                      { $$ = literal(NULL, (char) 0, 0, $1); }
    | INTEGER_CONSTANT              { $$ = literal(NULL, (char) 0, 0, $1); }
    ;

Expression
	: l_value assignment             { $$ = Expression($1, $2, NULL, NULL); }
	| l_value short_math             { $$ = Expression($1, NULL, $2, NULL); }
	| inc_and_dec                    { $$ = Expression(NULL, NULL, NULL, $1); }
	;

index
	: INTEGER_CONSTANT              { $$ = indexx($1, NULL); }
	| IDENTIFIER                    { $$ = indexx(0, "IDENTIFIER"); }
	;

// function
FunctionDef
    : typechain IDENTIFIER '(' param_list ')' Body      { $$ = FunctionDef($1, "IDENTIFIER", $4, $6); }
    | typechain IDENTIFIER '(' VOID ')' Body            { $$ = FunctionDef($1, "IDENTIFIER", NULL, $6); }
    | typechain IDENTIFIER '(' ')' Body                 { $$ = FunctionDef($1, "IDENTIFIER", NULL, $5); }
    ;

param_list
    : param_list ',' param                   { $$ = param_list(NULL, NULL, $1, $3); }
    | typechain param_name                   { $$ = param_list($1, $2, NULL, NULL); }
	;

param
    : typechain param_name                   { $$ = param($1, $2); }
	| param_name                             { $$ = param(NULL, $1); }
    ;

param_name
	: field_name                             { $$ = param_name(NULL, $1); }
	| IDENTIFIER '['']'                      { $$ = param_name("IDENTIFIER", NULL); }
	;

FunctionCall
    : IDENTIFIER '(' args_list ')'          { $$ = FunctionCall("IDENTIFIER", $3); }
	| IDENTIFIER '(' ')'                    { $$ = FunctionCall("IDENTIFIER", NULL); }
    ;

// struct
StructDef
	: STRUCT IDENTIFIER '{' field_list '}'                  { $$ = StructDef("IDENTIFIER", $4); }
	| STRUCT '{' field_list '}'                             { $$ = StructDef(NULL, $3); }
	| STRUCT IDENTIFIER                                     { $$ = StructDef("IDENTIFIER", NULL); }
    ;

StructCall
	: StructCall DOT field_name                 { $$ = StructCall($1, NULL, ".", $3); }
	| StructCall PTR_OP field_name              { $$ = StructCall($1, NULL, "->", $3); }
	| field_name DOT field_name                 { $$ = StructCall(NULL, $1, ".", $3); }
	| field_name PTR_OP field_name              { $$ = StructCall(NULL, $1, "->", $3); }
	;

field_list
    : field ';' field_list              { $$ = field_list($1, $3); }
    |                                   { $$ = NULL; }
	;

field
    : typechain inline_field_names       { $$ = field($1, $2); }
    ;

inline_field_names
    : inline_field_names ',' field_name     { $$ = inline_field_names($1, $3); }
    | field_name                            { $$ = inline_field_names(NULL, $1); }
    ;

field_name
	: IDENTIFIER                            { $$ = field_name("IDENTIFIER", NULL); }
	| IDENTIFIER '[' index ']'              { $$ = field_name("IDENTIFIER", $3); }
	;

// if statement
if
	: IF '(' logic_expr ')' Body else_body                              { $$ = if_statement($3, $5, $6); }
	;

else_body
	:                                                                   { $$ = NULL; }
	| ELSE Body                                                         { $$ = else_body($2); }
	;

// while loop
while
	: WHILE '(' logic_expr ')' Body                                     { $$ = while_statement($3, $5); }
	;

// for loop
for
	: FOR '(' for_init ';' for_condition ';' for_actions ')' Body       { $$ = for_statement($3, $5, $7, $9); }
	;

ExpressionList
    : ExpressionList ',' Expression                                     { $$ = ExpressionList($1, $3); }
    | Expression                                                        { $$ = ExpressionList(NULL, $1); }
    ;

for_init
	:                                                                   { $$ = NULL; }
	| variable_declaration                                              { $$ = for_init($1, NULL); }
	| ExpressionList                                                    { $$ = for_init(NULL, $1); }
	;

for_condition
	:                                                   { $$ = NULL; }
	| logic_expr                                        { $$ = for_condition($1); }
	;

for_actions
	:                                                   { $$ = NULL; }
	| ExpressionList                                    { $$ = for_actions($1); }
	;

// math

inc_and_dec
	: INC_OP l_value                     { $$ = inc_and_dec("++", 0, $2); }
	| DEC_OP l_value                     { $$ = inc_and_dec("--", 0, $2); }
	| l_value INC_OP                     { $$ = inc_and_dec("++", 1, $1); }
	| l_value DEC_OP                     { $$ = inc_and_dec("--", 1, $1); }
	;

l_value
	: pointer field_name                { $$ = l_value($1, $2, NULL); }
	| field_name                        { $$ = l_value(NULL, $1, NULL); }
	| pointer StructCall                { $$ = l_value($1, NULL, $2); }
	| StructCall                        { $$ = l_value(NULL, NULL, $1); }
	;

r_value
	: value                             { $$ = r_value($1, 0, NULL, NULL); }
	| NULL_                             { $$ = r_value(NULL, 1, NULL, NULL); }
	| math_expr                         { $$ = r_value(NULL, 0, $1, NULL); }
	| logic_expr                        { $$ = r_value(NULL, 0, NULL, $1); }
	;

value
    : literal                           { $$ = value($1, NULL, 0, NULL); }
    | l_value                           { $$ = value(NULL, $1, 0, NULL); }
    | '&' l_value                       { $$ = value(NULL, $2, 1, NULL); }
    | FunctionCall                      { $$ = value(NULL, NULL, 0, $1); }
	;

short_math
	: ADD_ASSIGN r_value                 { $$ = short_math('+', $2); }
	| SUB_ASSIGN r_value                 { $$ = short_math('-', $2); }
	| MUL_ASSIGN r_value                 { $$ = short_math('*', $2); }
	| DIV_ASSIGN r_value                 { $$ = short_math('/', $2); }
	;

math_expr
 	: '('math_expr')'                   { $$ = $2; }
 	| math_expr '+' math_expr           { $$ = math_expr("+", $1, $3, NULL); }
	| math_expr '-' math_expr           { $$ = math_expr("-", $1, $3, NULL); }
	| math_expr '*' math_expr           { $$ = math_expr("*", $1, $3, NULL); }
	| math_expr '/' math_expr           { $$ = math_expr("/", $1, $3, NULL); }
	| math_expr '%' math_expr           { $$ = math_expr("%", $1, $3, NULL); }
	| value                             { $$ = math_expr(NULL, NULL, NULL, $1); }
 	;

logic_expr
	: '(' logic_expr ')'                { $$ = $2; }
	| '!' logic_expr                    { $$ = logic_expr("!", $2, NULL, NULL); }
	| logic_expr AND_OP logic_expr      { $$ = logic_expr("&&", $1,$3, NULL); }
	| logic_expr OR_OP logic_expr       { $$ = logic_expr("||", $1,$3, NULL); }
	| logic_expr LE_OP logic_expr       { $$ = logic_expr("<=", $1,$3, NULL); }
	| logic_expr GE_OP logic_expr       { $$ = logic_expr(">=", $1,$3, NULL); }
	| logic_expr EQ_OP logic_expr       { $$ = logic_expr("==", $1,$3, NULL); }
	| logic_expr NE_OP logic_expr       { $$ = logic_expr("!=", $1,$3, NULL); }
	| logic_expr '<' logic_expr         { $$ = logic_expr("<", $1, $3, NULL); }
	| logic_expr '>' logic_expr         { $$ = logic_expr(">", $1, $3, NULL); }
	| math_expr                         { $$ = logic_expr(NULL, NULL, NULL, $1); }
	;
%%
//subroutines

#include <stdio.h>

extern char yytext[];
extern int column;

int main(int argc, char **argv){
    yyparse();
    if (root != NULL) to_str_compilation_unit(0, root);
    return 0;
}



void yyerror(char const *s){
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}
