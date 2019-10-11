#include <stdio.h>
#include "Tree.h"


struct global_declaration *global_decl() {
    struct global_declaration *node = malloc(sizeof(struct global_declaration));
    if(!node) {
        yyerror("out of space");
        exit(0);
    }
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

struct variable_declaration *variable_declaration(struct typechain *typechain, struct inline_declaration *inline_declaration) {
    struct variable_declaration *node = malloc(sizeof(struct variable_declaration));
    if(!node) {
        yyerror("out of space");
        exit(0);
    }
    node->typechain = typechain;
    node->inline_declaration = inline_declaration;
//    printf("STROKA4 %s \n", type);
    return node;
}


struct inline_initial_declaration* inline_initial_declaration(struct inline_declaration *inline_declaration, struct inline_initial_declaration* inline_initial_declaration){
  struct inline_initial_declaration *node = malloc(sizeof(struct inline_initial_declaration));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->inline_initial_declaration = inline_initial_declaration;
  node->inline_declaration = inline_declaration;
//    printf("STROKA4 %s \n", type);
  return node;
}

struct typechain *typechain(char* type, struct StructDef* structdef, struct pointer *pointer) {
  struct typechain *node = malloc(sizeof(struct typechain));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->type = type;
  node->StructDef = structdef;
  node->pointer = pointer;
//    printf("STROKA4 %s \n", type);
  return node;
}

struct inline_declaration *inline_declaration( struct inline_declaration *inline_declaration, struct initial_declaration *initial_declaration) {
  struct inline_declaration *node = malloc(sizeof(struct inline_declaration));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->initial_declaration = initial_declaration;
  node->inline_declaration = inline_declaration;
//    printf("STROKA4 %s \n", type);
  return node;
}

struct initial_declaration *initial_declaration(char* identifier, struct assignment * assignment, struct array_declaration * array_declaration, struct list_initializer * list_initializer){
  struct initial_declaration *node = malloc(sizeof(struct initial_declaration));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->identifier = identifier;
  node->assignment = assignment;
  node->array_declaration = array_declaration;
  node->list_initializer = list_initializer;
//    printf("STROKA4 %s \n", type);
  return node;
}

struct assignment * assignment(struct cast* cast){
  struct assignment *node = malloc(sizeof(struct assignment));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->cast = cast;
//    printf("STROKA4 %s \n", type);
  return node;
}

struct cast* cast(struct r_value * r_value, struct typechain * typechain, struct cast * cast){
  struct cast *node = malloc(sizeof(struct cast));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->typechain = typechain;
  node->r_value = r_value;
  node->cast = cast;
//    printf("STROKA4 %s \n", type);
  return node;
}

struct r_value* r_value(struct value * value, int is_null, struct math_expr * math_expr, struct logic_expr * logic_expr){
  struct r_value *node = malloc(sizeof(struct r_value));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->value = value;
  node->is_null = is_null;
  node->math_expr = math_expr;
  node->logic_expr = logic_expr;
//    printf("STROKA4 %s \n", type);
  return node;
}

struct value * value(struct literal* literal, struct l_value* l_value, int address, struct FunctionCall* functionCall){
  struct value *node = malloc(sizeof(struct value));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->literal = literal;
  node->l_value = l_value;
  node->address = address;
  node->functionCall = functionCall;
//    printf("STROKA4 %s \n", type);
  return node;
}

struct literal * literal(char * str_value, char char_value, float float_value, int int_value){
  struct literal *node = malloc(sizeof(struct literal));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->str_value = str_value;
  node->char_value = char_value;
  node->float_value = float_value;
  node->int_value = int_value;
//    printf("STROKA4 %s \n", type);
  return node;
}

struct l_value* l_value(struct pointer *pointer, char *name, struct StructCall *StructCall){
  struct l_value *node = malloc(sizeof(struct l_value));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->name = name;
  node->pointer = pointer;
  node->StructCall = StructCall;
//    printf("STROKA4 %s \n", type);
  return node;
}

struct pointer* pointer(struct pointer * pointer){
  struct pointer *node = malloc(sizeof(struct pointer));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->pointer = pointer;
//    printf("STROKA4 %s \n", type);
  return node;
}

struct StructCall* StructCall(  struct StructCall* StructCall,  struct field_name* field_name,  char* op,  struct field_name* dest_field_name)
{
  struct StructCall *node = malloc(sizeof(struct StructCall));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->StructCall = StructCall;
  node->dest_field_name = dest_field_name;
  node->field_name = field_name;
  node->op = op;
//    printf("STROKA4 %s \n", type);
  return node;
}

struct field_name* field_name (char * name, struct index * index)
{
  struct field_name *node = malloc(sizeof(struct field_name));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->name = name;
  node->index = index;
//    printf("STROKA4 %s \n", type);
  return node;
}

struct index* index(int integer, char * identifier){
  struct index *node = malloc(sizeof(struct index));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->integer = integer;
  node->identifier = identifier;
//    printf("STROKA4 %s \n", type);
  return node;
}

struct FunctionCall* FunctionCall(char *name, struct args_list* args_list)
{
  struct FunctionCall *node = malloc(sizeof(struct FunctionCall));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->name = name;
  node->args_list = args_list;
//    printf("STROKA4 %s \n", type);
  return node;
}

struct args_list* args_list(struct cast* arg, struct args_list* args_list){
  struct args_list *node = malloc(sizeof(struct args_list));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->arg = arg;
  node->args_list = args_list;
//    printf("STROKA4 %s \n", type);
  return node;
}

struct math_expr* math_expr (char sign,  struct math_expr *l,  struct math_expr *r,  struct value* value)
{
  struct math_expr *node = malloc(sizeof(struct math_expr));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->value = value;
  node->l = l;
  node->r = r;
  node->sign = sign;
//    printf("STROKA4 %s \n", type);
  return node;
}

struct list_initializer* list_initializer(struct args_list* args_list)
{
  struct list_initializer *node = malloc(sizeof(struct list_initializer));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->args_list = args_list;
//    printf("STROKA4 %s \n", type);
  return node;
}

struct logic_expr* logic_expr(char sign, struct logic_expr *l, struct logic_expr *r, struct math_expr* value){
  struct logic_expr *node = malloc(sizeof(struct logic_expr));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->sign = sign;
  node->l = l;
  node->r = r;
  node->value = value;
//    printf("STROKA4 %s \n", type);
  return node;
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



