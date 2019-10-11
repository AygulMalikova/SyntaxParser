#include <stdio.h>
#include "Tree.h"


struct global_declaration *global_decl() {
    struct global_declaration *node = malloc(sizeof(struct global_declaration));
    if(!node) {
        yyerror("out of space");
        exit(0); }
    return node;
}

struct include_files *include_files(char name_of_file[]) {
    struct include_files *node = malloc(sizeof(struct include_files));
    if(!node) {
        yyerror("out of space");
        exit(0);
    }
    node->name_of_file = name_of_file;
    printf("STROKA1 %s \n", name_of_file);
    return node;
}

struct variable_declaration *variable_declaration(char *type) {
    struct variable_declaration *node = malloc(sizeof(struct variable_declaration));
    if(!node) {
        yyerror("out of space");
        exit(0);
    }
    node->type = type;
//    printf("STROKA4 %s \n", type);
    return node;
}

struct  math_expr *math_expr(char sign, struct ast *l, struct ast *r) {
    struct  math_expr *math_expr = malloc(sizeof(struct math_expr));
    if(!math_expr) {
        yyerror("out of space");
        exit(0); }
    math_expr->nodetype = nodetype;
    math_expr->l = l;
    math_expr->r = r;
    return math_expr;
}

//
//struct variable_declaration {
//    char *type;
//    struct inline_declaration inline_declaration;
//};
//
//struct inline_declaration {
//    char *type;
//    char *name;
//    char *pointer_to;
//    struct assignment;
//    struct array_declaration;
//    struct inline_declaration* inline_declaration;
//};
//
//struct array_declaration {
//    char *name;
//    int size;
//    struct list_initializer list_initializer;
//    struct array_declaration array_declaration;
//};
//
//struct assignment {
//    struct cast cast;
//};
//
//struct cast {
//    struct r_value r_value;
//    char *type;
//    struct cast* cast;
//};
//
//struct r_value {
//    struct value value;
//    char *NULL;
//    struct math_expr math_expr;
//    struct logic_expr logic_expr;
//};
//
//struct value {
//    struct literal literal;
//
//};
//
//struct literal {
//    char character;
//    int num;
//    float num;
//
//};
//
//
//struct function_declaration {
//    char *return_type;
//    char *name;
//    struct param_list;
//    struct function_body;
//};
//
//struct list_initializer {
//    char values[];
//};
//
//struct struct_declaration {
//    char *name;
//    struct struct_fields;
//
//};
//struct typedef_declaration {
//    char *type;
//    char *name;
//};
//
//struct struct_fields {
//    char *type;
//    char *name;
//    struct struct_declaration* struct_declaration;
//};
//
//struct param_list {
//    struct parameter_declaration parameter_declaration[10]; //  тут надо как-то задать размер массива параметров
//};
//
//struct parameter_declaration {
//    char *type;
//    char *name;
//};
//
//struct function_body {
//    struct variable_declaration;
//    struct expression;
//    struct if_statement;
//    struct for_loop;
//    struct while_loop;
//    struct function_call;
//    struct array_usage;
//};
//
//struct expression {
//
//};
//
//struct if_statement {
//
//};
//
//struct for_loop {
//
//};
//
//struct while_loop {
//
//};
//
//struct function_call {
//
//};
//
//struct array_usage {
//
//};



