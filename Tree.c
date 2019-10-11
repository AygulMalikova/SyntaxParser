#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>

extern void yyerror(char const *s);

void print_margine(int number) {
  printf("\n");
  for (int i = 0; i < number; i++)
    printf("--");
}

struct compilation_unit *
compilation_unit(struct global_declaration *global_declaration,
                 struct compilation_unit *compilation_unit) {
  struct compilation_unit *node = malloc(sizeof(struct compilation_unit));
  if (!node) {
    yyerror("out of space");
    exit(0);
  }
  node->compilation_unit = compilation_unit;
  node->global_declaration = global_declaration;
  return node;
}

void to_str_compilation_unit(int number,
                             struct compilation_unit *compilation_unit) {
  if (compilation_unit == NULL)
    return;
  to_str_compilation_unit(number, compilation_unit->compilation_unit);
  print_margine(number);
  printf("Compilation unit");
  to_str_global_declaration(number + 1, compilation_unit->global_declaration);

}

struct global_declaration *
global_declaration(struct include_files *include_files,
                   struct variable_declaration *var_declaration,
                   struct FunctionDef *func_declaration,
                   struct typedef_declaration *typedef_declaration,
                   struct StructDef *struct_declaration) {

  struct global_declaration *node = malloc(sizeof(struct global_declaration));
  if (!node) {
    yyerror("out of space");
    exit(0);
  }
  node->include_files = include_files;
  node->var_declaration = var_declaration;
  node->func_declaration = func_declaration;
  node->struct_declaration = struct_declaration;
  node->typedef_declaration = typedef_declaration;
  return node;
}

void to_str_global_declaration(int number,
                               struct global_declaration *global_declaration) {
  if (global_declaration == NULL)
    return;
  print_margine(number);
  printf("Global Declaration");
  to_str_include_files(number + 1, global_declaration->include_files);
  to_str_typedef_declaration(number + 1,
                             global_declaration->typedef_declaration);
  to_str_variable_declaration(number + 1, global_declaration->var_declaration);
  to_str_FunctionDef(number + 1, global_declaration->func_declaration);
  to_str_StructDef(number + 1, global_declaration->struct_declaration);
}

struct include_files *include_files(char name_of_file[]) {
  struct include_files *node = malloc(sizeof(struct include_files));
  if (!node) {
    yyerror("out of space");
    exit(0);
  }
  node->name_of_file = name_of_file;
  return node;
}

void to_str_include_files(int number, struct include_files *include_files) {
  if (include_files == NULL)
    return;
  print_margine(number);
  printf("include");
  if ( include_files->name_of_file != NULL) {
    print_margine(number + 1);
    printf("%s", include_files->name_of_file);
  }
}

struct variable_declaration *variable_declaration(
    struct typechain *typechain,
    struct inline_initial_declaration *inline_initial_declaration) {
  struct variable_declaration *node =
      malloc(sizeof(struct variable_declaration));
  if (!node) {
    yyerror("out of space");
    exit(0);
  }
  node->typechain = typechain;
  node->inline_initial_declaration = inline_initial_declaration;
  return node;
}

void to_str_variable_declaration(
    int number, struct variable_declaration *variable_declaration) {
  if (variable_declaration == NULL)
    return;
  print_margine(number);
  printf("Variable declaration");
  to_str_typechain(number + 1, variable_declaration->typechain);
  to_str_inline_initial_declaration(
      number + 1, variable_declaration->inline_initial_declaration);
}

struct inline_initial_declaration *inline_initial_declaration(
    struct initial_declaration *initial_declaration,
    struct inline_initial_declaration *inline_initial_declaration) {
  struct inline_initial_declaration *node =
      malloc(sizeof(struct inline_initial_declaration));
  if (!node) {
    yyerror("out of space");
    exit(0);
  }
  node->inline_initial_declaration = inline_initial_declaration;
  node->initial_declaration = initial_declaration;
  return node;
}

void to_str_inline_initial_declaration(
    int number, struct inline_initial_declaration *inline_initial_declaration) {

  if (inline_initial_declaration == NULL)
    return;
  to_str_inline_initial_declaration(
      number, inline_initial_declaration->inline_initial_declaration);
  print_margine(number);
  printf("Inline initial declaration");
  to_str_initial_declaration(number + 1,
                             inline_initial_declaration->initial_declaration);
}

struct typechain *typechain(char *type, struct StructDef *structdef,
                            struct pointer *pointer) {
  struct typechain *node = malloc(sizeof(struct typechain));
  if (!node) {
    yyerror("out of space");
    exit(0);
  }
  node->type = type;
  node->StructDef = structdef;
  node->pointer = pointer;
  return node;
}

void to_str_typechain(int number, struct typechain *typechain) {

  if (typechain == NULL)
    return;
  print_margine(number);
  printf("Type chain");
  to_str_pointer(number + 1, typechain->pointer);
  if (typechain->StructDef != NULL) {
    to_str_StructDef(number + 1, typechain->StructDef);
  } else if (typechain->type != NULL){
    print_margine(number + 1);
    printf("%s", typechain->type);
  }
}

struct array_declaration *
array_declaration(char *name, struct index *index,
                  struct list_initializer *list_initializer) {
  struct array_declaration *node = malloc(sizeof(struct array_declaration));
  if (!node) {
    yyerror("out of space");
    exit(0);
  }
  node->name = name;
  node->index = index;
  node->list_initializer = list_initializer;
  return node;
}

void to_str_array_declaration(int number,
                              struct array_declaration *array_declaration) {

  if (array_declaration == NULL)
    return;

  print_margine(number);
  printf("Array declaration");
  if (array_declaration->name != NULL) {
    print_margine(number + 1);
    printf("%s", array_declaration->name);
  }

  to_str_index(number + 1, array_declaration->index);
  to_str_list_initializer(number + 1, array_declaration->list_initializer);
}

struct initial_declaration *
initial_declaration(char *identifier, struct assignment *assignment,
                    struct array_declaration *array_declaration,
                    struct list_initializer *list_initializer) {
  struct initial_declaration *node = malloc(sizeof(struct initial_declaration));
  if (!node) {
    yyerror("out of space");
    exit(0);
  }
  node->identifier = identifier;
  node->assignment = assignment;
  node->array_declaration = array_declaration;
  node->list_initializer = list_initializer;
  return node;
}

void to_str_initial_declaration(
    int number, struct initial_declaration *initial_declaration) {

  if (initial_declaration == NULL)
    return;

  print_margine(number);
  printf("Initial declaration");
  if (initial_declaration->array_declaration != NULL) {
    to_str_array_declaration(number + 1,
                             initial_declaration->array_declaration);
  } else if (initial_declaration->identifier != NULL){
    print_margine(number + 1);
    printf("%s", initial_declaration->identifier);

    if (initial_declaration->assignment != NULL) {
      to_str_assignment(number + 1, initial_declaration->assignment);
    } else {
      to_str_list_initializer(number + 1,
                              initial_declaration->list_initializer);
    }
  }
}

struct assignment *assignment(struct cast *cast) {
  struct assignment *node = malloc(sizeof(struct assignment));
  if (!node) {
    yyerror("out of space");
    exit(0);
  }
  node->cast = cast;
  return node;
}

void to_str_assignment(int number, struct assignment *assignment) {

  if (assignment == NULL)
    return;
  print_margine(number);
  printf("Assignment");
  to_str_cast(number + 1, assignment->cast);
}

struct cast *cast(struct r_value *r_value, struct typechain *typechain,
                  struct cast *cast) {
  struct cast *node = malloc(sizeof(struct cast));
  if (!node) {
    yyerror("out of space");
    exit(0);
  }
  node->typechain = typechain;
  node->r_value = r_value;
  node->cast = cast;
  return node;
}

void to_str_cast(int number, struct cast *cast) {

  if (cast == NULL)
    return;
  print_margine(number);
  printf("Cast");
  if (cast->r_value) {
    to_str_r_value(number + 1, cast->r_value);
  } else {
    to_str_cast(number + 1, cast->cast);
    to_str_typechain(number + 1, cast->typechain);
  }
}

struct r_value *r_value(struct value *value, int is_null,
                        struct math_expr *math_expr,
                        struct logic_expr *logic_expr) {
  struct r_value *node = malloc(sizeof(struct r_value));
  if (!node) {
    yyerror("out of space");
    exit(0);
  }
  node->value = value;
  node->is_null = is_null;
  node->math_expr = math_expr;
  node->logic_expr = logic_expr;
  return node;
}

void to_str_r_value(int number, struct r_value *r_value) {

  if (r_value == NULL)
    return;
  print_margine(number);
  printf("R VALUE");
  if (r_value->is_null) {
    print_margine(number + 1);
    printf("NULL");
  } else {
    if (r_value->value != NULL) {
      to_str_value(number + 1, r_value->value);
    } else if (r_value->math_expr != NULL) {
      to_str_math_expr(number + 1, r_value->math_expr);
    } else {
      to_str_logic_expr(number + 1, r_value->logic_expr);
    }
  }
}

struct value *value(struct literal *literal, struct l_value *l_value,
                    int address, struct FunctionCall *functionCall) {
  struct value *node = malloc(sizeof(struct value));
  if (!node) {
    yyerror("out of space");
    exit(0);
  }
  node->literal = literal;
  node->l_value = l_value;
  node->address = address;
  node->functionCall = functionCall;
  return node;
}

void to_str_value(int number, struct value *value) {

  if (value == NULL)
    return;

  print_margine(number);
  printf("VALUE");
  if (value->functionCall != NULL) {
    to_str_FunctionCall(number + 1, value->functionCall);
  } else if (value->literal != NULL) {
    to_str_literal(number + 1, value->literal);
  } else {
    if (value->address) {
      print_margine(number + 1);
      printf("&");
    }
    to_str_l_value(number + 1, value->l_value);
  }
}

struct literal *literal(char *str_value, char char_value, float float_value,
                        int int_value) {
  struct literal *node = malloc(sizeof(struct literal));
  if (!node) {
    yyerror("out of space");
    exit(0);
  }
  node->str_value = str_value;
  node->char_value = char_value;
  node->float_value = float_value;
  node->int_value = int_value;
  return node;
}

void to_str_literal(int number, struct literal *literal) {

  if (literal == NULL)
    return;

  print_margine(number);
  printf("Literal");
  print_margine(number + 1);
  if (literal->str_value != NULL) {
    printf("%s", literal->str_value);
  } else if (literal->char_value != (char)0) {
    printf("%c", literal->char_value);
  } else if (literal->float_value != 0) {
    printf("%f", literal->float_value);
  } else {
    printf("%d", literal->int_value);
  }
}

struct l_value *l_value(struct pointer *pointer, struct field_name *name,
                        struct StructCall *StructCall) {
  struct l_value *node = malloc(sizeof(struct l_value));
  if (!node) {
    yyerror("out of space");
    exit(0);
  }
  node->name = name;
  node->pointer = pointer;
  node->StructCall = StructCall;
  return node;
}

void to_str_l_value(int number, struct l_value *l_value) {

  if (l_value == NULL)
    return;

  print_margine(number);
  printf("L VALUE");
  to_str_pointer(number + 1, l_value->pointer);
  if (l_value->StructCall != NULL){
    to_str_StructCall(number + 1, l_value->StructCall);
  } else {
    to_str_field_name(number+1, l_value->name);
  }
}

struct pointer *pointer(struct pointer *pointer) {
  struct pointer *node = malloc(sizeof(struct pointer));
  if (!node) {
    yyerror("out of space");
    exit(0);
  }
  node->pointer = pointer;
  return node;
}

// not_sure
void to_str_pointer(int number, struct pointer *pointer) {
  if (pointer == NULL)
    return;
  print_margine(number);
  printf("*");
  to_str_pointer(number, pointer->pointer);
}

struct StructCall *StructCall(struct StructCall *StructCall,
                              struct field_name *field_name, char *op,
                              struct field_name *dest_field_name) {
  struct StructCall *node = malloc(sizeof(struct StructCall));
  if (!node) {
    yyerror("out of space");
    exit(0);
  }
  node->StructCall = StructCall;
  node->dest_field_name = dest_field_name;
  node->field_name = field_name;
  node->op = op;

  return node;
}

void to_str_StructCall(int number, struct StructCall *StructCall) {

  if (StructCall == NULL)
    return;

  print_margine(number);
  printf("Struct Call");
  if (StructCall->StructCall != NULL)
  {
    to_str_StructCall(number, StructCall->StructCall);
  }
  else {
    to_str_field_name(number, StructCall->field_name);
  }
  if (StructCall->op != NULL) {
    print_margine(number);
    printf("%s", StructCall->op);
  }

  to_str_field_name(number, StructCall->dest_field_name);
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
  return node;
}

// Done
void to_str_field_name(int number, struct field_name* field_name){
  if (field_name == NULL) return;
  print_margine(number);
  printf("field name");

  if ( field_name->name != NULL) {
    print_margine(number+1);
    printf("%s", field_name->name);
  }

  to_str_index(number+1, field_name->index);
}

// Done
struct index* indexx(int integer, char * identifier){
  struct index *node = malloc(sizeof(struct index));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->integer = integer;
  node->identifier = identifier;
  return node;
}

// Done
void to_str_index(int number, struct index* index){
  if (index == NULL) return;
  print_margine(number);
  printf("index");

  if (index->identifier) {
    print_margine(number+1);
    printf("%s", index->identifier);
  }
  else {
    print_margine(number+1);
    printf("%d", index->integer);
  }
}

// Done
struct FunctionCall* FunctionCall(char *name, struct args_list* args_list) {
  struct FunctionCall *node = malloc(sizeof(struct FunctionCall));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->name = name;
  node->args_list = args_list;
  return node;
}

// Done
void to_str_FunctionCall(int number, struct FunctionCall* FunctionCall){
  if (FunctionCall == NULL) return;
  print_margine(number);
  printf("FunctionCall");

  if (FunctionCall->name != NULL) {
    print_margine(number+1);
    printf("%s",  FunctionCall->name);
  }

  to_str_args_list(number+1, FunctionCall->args_list);
}

// Done
struct args_list* args_list(struct cast* arg, struct args_list* args_list){
  struct args_list *node = malloc(sizeof(struct args_list));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->arg = arg;
  node->args_list = args_list;
  return node;
}

// Done
void to_str_args_list(int number, struct args_list* args_list){
  if (args_list == NULL) return;
  print_margine(number);
  printf("args list");

  to_str_cast(number+1, args_list->arg);
  to_str_args_list(number+1, args_list->args_list);
}

// Done
struct math_expr* math_expr (char* sign,  struct math_expr *l,  struct math_expr *r,  struct value* value) {
  struct math_expr *node = malloc(sizeof(struct math_expr));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->value = value;
  node->l = l;
  node->r = r;
  node->sign = sign;
  return node;
}

// Done
void to_str_math_expr(int number, struct math_expr* math_expr){
  if (math_expr == NULL) return;
  print_margine(number);
  printf("math expr");

  to_str_math_expr(number+1, math_expr->l);

  if(math_expr->sign != NULL)
  {
    print_margine(number+1);
    printf("%s", math_expr->sign);
  }

  to_str_math_expr(number+1, math_expr->r);
  to_str_value(number+1, math_expr->value);
}

// Done
struct list_initializer* list_initializer(struct args_list* args_list)
{
  struct list_initializer *node = malloc(sizeof(struct list_initializer));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->args_list = args_list;
  return node;
}

// Done
void to_str_list_initializer(int number, struct list_initializer* list_initializer){
  if (list_initializer == NULL) return;
  print_margine(number);
  printf("list initializer");
  to_str_args_list(number+1, list_initializer->args_list);
}

// Done
struct logic_expr* logic_expr(char *sign, struct logic_expr *l, struct logic_expr *r, struct math_expr* value){
  struct logic_expr *node = malloc(sizeof(struct logic_expr));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->sign = sign;
  node->l = l;
  node->r = r;
  node->value = value;
  return node;
}

// Done
void to_str_logic_expr(int number, struct logic_expr* logic_expr){
  if (logic_expr == NULL) return;
  print_margine(number);
  printf("logic expr");

  to_str_logic_expr(number+1, logic_expr->l);

  if(logic_expr->sign != NULL)
  {
    print_margine(number+1);
    printf("%s", logic_expr->sign);
  }

  to_str_logic_expr(number+1, logic_expr->r);

  to_str_math_expr(number+1, logic_expr->value);
}

// Done
struct StructDef* StructDef(char *name, struct field_list *field_list){
  struct StructDef *node = malloc(sizeof(struct StructDef));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->name = name;
  node->field_list = field_list;
  return node;
}

// Done
void to_str_StructDef(int number, struct StructDef* StructDef){
  if (StructDef == NULL) return;
  print_margine(number);
  printf("Struct Def");

  if (StructDef->name != NULL) {
    print_margine(number+1);
    printf("%s", StructDef->name);
  }
  to_str_field_list(number+1, StructDef->field_list);
}

// Done
struct field_list* field_list(struct field *field, struct field_list *field_list){
  struct field_list *node = malloc(sizeof(struct field_list));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->field = field;
  node->field_list = field_list;
  return node;
}

// Done
void to_str_field_list(int number, struct field_list* field_list){
  if (field_list == NULL) return;
  print_margine(number);
  printf("field list");
  to_str_field(number+1, field_list->field);
  to_str_field_list(number, field_list->field_list);
}

// Done
struct field * field(struct typechain *typechain, struct inline_field_names *inline_field_names){
  struct field *node = malloc(sizeof(struct field));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->typechain = typechain;
  node->inline_field_names = inline_field_names;
  return node;
}

// Done
void to_str_field(int number, struct field* field){
  if (field == NULL) return;
  print_margine(number);
  printf("field");
  to_str_typechain(number+1, field->typechain);
  to_str_inline_field_names(number+1, field->inline_field_names);
}

// Done
struct inline_field_names * inline_field_names (struct inline_field_names *inline_field_names, struct field_name *field_name) {
  struct inline_field_names *node = malloc(sizeof(struct inline_field_names));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->inline_field_names = inline_field_names;
  node->field_name = field_name;
  return node;
}

// Done
void to_str_inline_field_names(int number, struct inline_field_names* inline_field_names){
  if (inline_field_names == NULL) return;
  print_margine(number);
  printf("inline field names");
  to_str_field_name(number+1, inline_field_names->field_name);
  to_str_inline_field_names(number, inline_field_names->inline_field_names);
}

// Done
struct FunctionDef* FunctionDef(struct typechain *typechain, char *name, struct param_list *param_list, struct Body *Body){
  struct FunctionDef *node = malloc(sizeof(struct FunctionDef));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->typechain = typechain;
  node->name = name;
  node->param_list = param_list;
  node->Body = Body;
  return node;
}

// Done
void to_str_FunctionDef(int number, struct FunctionDef* FunctionDef){
  if (FunctionDef == NULL) return;
  print_margine(number);
  printf("Function Def");

  to_str_typechain(number+1, FunctionDef->typechain);

  if (FunctionDef->name != NULL) {
    print_margine(number+1);
    printf("%s", FunctionDef->name);
  }

  to_str_param_list(number+1, FunctionDef->param_list);
  to_str_Body(number+1, FunctionDef->Body);
}

// Done
struct param_list* param_list(  struct typechain *typechain,  struct param_name *param_name,  struct param_list *param_list,  struct param *param) {
  struct param_list *node = malloc(sizeof(struct param_list));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->typechain = typechain;
  node->param_name = param_name;
  node->param_list = param_list;
  node->param = param;
  return node;
}

// Done
void to_str_param_list(int number, struct param_list* param_list){
  if (param_list == NULL) return;
  print_margine(number);
  printf("param list");
  to_str_param_list(number, param_list->param_list);
  to_str_typechain(number+1, param_list->typechain);
  to_str_param_name(number+1, param_list->param_name);
  to_str_param(number+1, param_list->param);
}

// Done
struct Body* Body(struct ComplexBody *ComplexBody, struct Statement *Statement){
  struct Body *node = malloc(sizeof(struct Body));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->ComplexBody = ComplexBody;
  node->Statement = Statement;
  return node;
}

// Done
void to_str_Body(int number, struct Body* Body){
  if (Body == NULL) return;
  print_margine(number);
  printf("Body");
  to_str_ComplexBody(number+1, Body->ComplexBody);
  to_str_Statement(number+1, Body->Statement);
}

// Done
struct ComplexBody* ComplexBody(  struct Statement *Statement,  struct ComplexBody *ComplexBody){
  struct ComplexBody *node = malloc(sizeof(struct ComplexBody));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->ComplexBody = ComplexBody;
  node->Statement = Statement;
  return node;
}

// Done
void to_str_ComplexBody(int number, struct ComplexBody* ComplexBody){
  if (ComplexBody == NULL) return;
  print_margine(number);
  printf("Complex Body");
  to_str_Statement(number+1, ComplexBody->Statement);
  to_str_ComplexBody(number, ComplexBody->ComplexBody);
}


// Done
struct else_body* else_body(struct Body *Body){
  struct else_body *node = malloc(sizeof(struct else_body));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->Body = Body;
  return node;
}


// Done
void to_str_else_body(int number, struct else_body* else_body){
  if (else_body == NULL) return;
  print_margine(number);
  printf("Else body");
  to_str_Body(number+1, else_body->Body);
}


// Done
struct Statement* Statement (struct variable_declaration *variable_declaration,  struct Expression *Expression,  struct if_statement *if_statement,  struct for_statement *for_statement,  struct while_statement *while_statement,  struct FunctionCall *FunctionCall,  struct StructDef *StructDef,  struct typedef_declaration *typedef_declaration,  struct Return *Return){
  struct Statement *node = malloc(sizeof(struct Statement));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->variable_declaration = variable_declaration;
  node->Expression = Expression;
  node->if_statement = if_statement;
  node->for_statement = for_statement;
  node->while_statement = while_statement;
  node->FunctionCall = FunctionCall;
  node->StructDef = StructDef;
  node->typedef_declaration = typedef_declaration;
  node->Return = Return;
  return node;
}


// Done
void to_str_Statement(int number, struct Statement* Statement){
  if (Statement == NULL) return;
  print_margine(number);
  printf("Statement");
  to_str_variable_declaration(number+1, Statement->variable_declaration);
  to_str_Expression(number+1, Statement->Expression);
  to_str_if_statement(number+1, Statement->if_statement);
  to_str_for_statement(number+1, Statement->for_statement);
  to_str_while_statement(number+1, Statement->while_statement);
  to_str_FunctionCall(number+1, Statement->FunctionCall);
  to_str_StructDef(number+1, Statement->StructDef);
  to_str_typedef_declaration(number+1, Statement->typedef_declaration);
  to_str_Return(number+1, Statement->Return);
}


// Done
struct param* param(  struct typechain *typechain,  struct param_name *param_name){
  struct param *node = malloc(sizeof(struct param));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->typechain = typechain;
  node->param_name = param_name;
  return node;
}


// Done
void to_str_param(int number, struct param* param){
  if (param == NULL) return;
  print_margine(number);
  printf("Param");
  to_str_typechain(number+1, param->typechain);
  to_str_param_name(number+1, param->param_name);
}

// Done
struct param_name* param_name(  char* empty_array_name,  struct field_name* field_name){
  struct param_name *node = malloc(sizeof(struct param_name));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->empty_array_name = empty_array_name;
  node->field_name = field_name;
  return node;
}

// Done
void to_str_param_name(int number, struct param_name* param_name){
  if (param_name == NULL) return;
  print_margine(number);
  printf("Param name");
  if(param_name->empty_array_name != NULL)
  {
    print_margine(number+1);
    printf("%s", param_name->empty_array_name);

  }
  to_str_field_name(number+1, param_name->field_name);
}

// Done
struct Expression* Expression(  struct l_value *l_value,  struct assignment *assignment,  struct short_math *short_math,  struct inc_and_dec *inc_and_dec){
  struct Expression *node = malloc(sizeof(struct Expression));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->l_value = l_value;
  node->assignment = assignment;
  node->short_math = short_math;
  node->inc_and_dec = inc_and_dec;
  return node;
}

// Done
void to_str_Expression(int number, struct Expression* Expression){
  if (Expression == NULL) return;
  print_margine(number);
  printf("Expression");

  to_str_l_value(number+1, Expression->l_value);
  to_str_assignment(number+1, Expression->assignment);
  to_str_short_math(number+1, Expression->short_math);
  to_str_inc_and_dec(number+1, Expression->inc_and_dec);
}

// Done
struct short_math* short_math (  char sign,  struct r_value *r_value){
  struct short_math *node = malloc(sizeof(struct short_math));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->sign = sign;
  node->r_value = r_value;
  return node;
}

// Done
void to_str_short_math(int number, struct short_math* short_math){
  if (short_math == NULL) return;
  print_margine(number);
  printf("Short math");
  if (short_math->sign != (char) 0) {
    print_margine(number+1);
    printf("%c=", short_math->sign);
  }

  to_str_r_value(number+1, short_math->r_value);
}

// Done
struct inc_and_dec* inc_and_dec(  char *operand,  int post,  struct l_value *l_value  ){
  struct inc_and_dec *node = malloc(sizeof(struct inc_and_dec));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->operand = operand;
  node->post = post;
  node->l_value = l_value;
  return node;
}

// Done
void to_str_inc_and_dec(int number, struct inc_and_dec* inc_and_dec) {
  if (inc_and_dec == NULL) return;
  print_margine(number);
  printf("Increment and Decrement");
  if (inc_and_dec->post) {
    to_str_l_value(number + 1, inc_and_dec->l_value);
    print_margine(number+1);
    printf("%s",  inc_and_dec->operand);
  } else {
    print_margine(number+1);
    printf("%s",  inc_and_dec->operand);
    to_str_l_value(number + 1, inc_and_dec->l_value);
  }
}
// Done
struct if_statement* if_statement(  struct logic_expr *logic_expr,  struct Body *Body,  struct else_body *else_body){
  struct if_statement *node = malloc(sizeof(struct if_statement));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->logic_expr = logic_expr;
  node->Body = Body;
  node->else_body = else_body;
  return node;
}

// Done
void to_str_if_statement(int number, struct if_statement* if_statement){
  if (if_statement == NULL) return;
  print_margine(number);
  printf("If");
  to_str_logic_expr(number+1, if_statement->logic_expr);
  to_str_Body(number+1, if_statement->Body);
  to_str_else_body(number+1, if_statement->else_body);
}

// Done
struct for_statement* for_statement(struct for_init *for_init,  struct for_condition *for_condition,  struct for_actions *for_actions, struct Body *Body){
  struct for_statement *node = malloc(sizeof(struct for_statement));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->for_init = for_init;
  node->for_actions = for_actions;
  node->for_condition = for_condition;
  node->Body = Body;
  return node;
}

// Done
void to_str_for_statement(int number, struct for_statement* for_statement){
  if (for_statement == NULL) return;
  print_margine(number);
  printf("For statement");
  to_str_for_init(number+1, for_statement->for_init);
  to_str_for_actions(number+1, for_statement->for_actions);
  to_str_for_condition(number+1, for_statement->for_condition);
}

// Done
struct for_init* for_init(  struct variable_declaration *variable_declaration,  struct ExpressionList *ExpressionList){
  struct for_init *node = malloc(sizeof(struct for_init));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->variable_declaration = variable_declaration;
  node->ExpressionList = ExpressionList;
  return node;
}

// Done
void to_str_for_init(int number, struct for_init* for_init){
  if (for_init == NULL) return;
  print_margine(number);
  printf("For init");
  to_str_variable_declaration(number+1, for_init->variable_declaration);
  to_str_ExpressionList(number+1, for_init->ExpressionList);
}

// Done
struct ExpressionList* ExpressionList(  struct ExpressionList *ExpressionList,  struct Expression *Expression){
  struct ExpressionList *node = malloc(sizeof(struct ExpressionList));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->Expression = Expression;
  node->ExpressionList = ExpressionList;
  return node;
}

// Done
void to_str_ExpressionList(int number, struct ExpressionList* ExpressionList){
  if (ExpressionList == NULL) return;
  print_margine(number);
  printf("Expression list");
  to_str_Expression(number+1, ExpressionList->Expression);
  to_str_ExpressionList(number, ExpressionList->ExpressionList);
}

// Done
struct for_condition* for_condition( struct logic_expr *logic_expr){
  struct for_condition *node = malloc(sizeof(struct for_condition));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->logic_expr = logic_expr;
  return node;
}

// Done
void to_str_for_condition(int number, struct for_condition* for_condition){
  if (for_condition == NULL) return;
  print_margine(number);
  printf("For condition");
  to_str_logic_expr(number+1, for_condition->logic_expr);
}

// Done
struct for_actions* for_actions(  struct ExpressionList *ExpressionList){
  struct for_actions *node = malloc(sizeof(struct for_actions));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->ExpressionList = ExpressionList;
  return node;
}

// Done
void to_str_for_actions(int number, struct for_actions* for_actions){
  if (for_actions == NULL) return;
  print_margine(number);
  printf("For action");
  to_str_ExpressionList(number+1, for_actions->ExpressionList);
}

// Done
struct while_statement* while_statement(struct logic_expr *logic_expr,  struct Body *Body){
  struct while_statement *node = malloc(sizeof(struct while_statement));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->logic_expr = logic_expr;
  node->Body = Body;
  return node;
}

// Done
void to_str_while_statement(int number, struct while_statement* while_statement){
  if (while_statement == NULL) return;
  print_margine(number);
  printf("While");
  to_str_logic_expr(number+1, while_statement->logic_expr);
  to_str_Body(number+1, while_statement->Body);
}

// Done
struct typedef_declaration* typedef_declaration(struct typechain *typechain,  struct list_identifiers *list_identifiers){
  struct typedef_declaration *node = malloc(sizeof(struct typedef_declaration));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->typechain = typechain;
  node->list_identifiers = list_identifiers;
  return node;
}

// Done
void to_str_typedef_declaration(int number, struct typedef_declaration* typedef_declaration){
  if (typedef_declaration == NULL) return;
  print_margine(number);
  printf("TypeDef");
  to_str_typechain(number+1, typedef_declaration->typechain);
  to_str_list_identifiers(number+1, typedef_declaration->list_identifiers);
}

// Done
struct list_identifiers* list_identifiers(  struct list_identifiers *list_identifiers,  int pointer,  char *name,  struct types_list *types_list, struct param_list *param_list){
  struct list_identifiers *node = malloc(sizeof(struct list_identifiers));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->pointer = pointer;
  node->list_identifiers = list_identifiers;
  node->param_list = param_list;
  node->name = name;
  node->types_list = types_list;
  return node;
}

// Done
void to_str_list_identifiers(int number, struct list_identifiers* list_identifiers){
  if (list_identifiers == NULL) return;
  print_margine(number);
  printf("List identifiers");
  if (list_identifiers->pointer) {
    print_margine(number+1);
    printf("*");

    if (list_identifiers->name != NULL) {
      print_margine(number+1);
      printf("%s", list_identifiers->name);
    }

    if (list_identifiers->types_list) {
      to_str_types_list(number+1, list_identifiers->types_list);
    }
    else if (list_identifiers->param_list) {
      to_str_param_list(number+1, list_identifiers->param_list);
    }
  }
  else if (list_identifiers->name != NULL){
    print_margine(number+1);
    printf("%s", list_identifiers->name);
  }

  to_str_list_identifiers(number, list_identifiers->list_identifiers);
}

// Done
struct types_list* types_list(  struct types_list *types_list,  struct typechain *typechain,  int is_arr,  struct index* index){
  struct types_list *node = malloc(sizeof(struct types_list));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->typechain = typechain;
  node->index = index;
  node->is_arr = is_arr;
  node->types_list = types_list;
  return node;
}

// Done
void to_str_types_list(int number, struct types_list* types_list){
  if (types_list == NULL) return;
  print_margine(number);
  printf("Types list");
  to_str_typechain(number+1, types_list->typechain);
  to_str_index(number+1, types_list->index);
  if (types_list->is_arr) {
    print_margine(number+1);
    printf("Array");
    to_str_typechain(number+2, types_list->typechain);
  }
  else {
    to_str_typechain(number+1, types_list->typechain);
  }
  to_str_types_list(number, types_list->types_list);
}

//Done
struct Return* Return(struct cast *cast){
  struct Return *node = malloc(sizeof(struct Return));
  if(!node) {
    yyerror("out of space");
    exit(0);
  }
  node->cast = cast;
  return node;
}

//Done
void to_str_Return(int number, struct Return* Return){
  if (Return == NULL) return;
  print_margine(number);
  printf("Return");
  to_str_cast(number+1, Return->cast);
}
