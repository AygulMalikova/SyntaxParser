#ifndef SYNTAXPARSER_TREE_H
#define SYNTAXPARSER_TREE_H

//DONE
struct compilation_unit {
  struct global_declaration* global_declaration;
  struct compilation_unit* compilation_unit;
};

void to_str_compilation_unit(int number, struct compilation_unit* compilation_unit);

//DONE
struct global_declaration {
    struct include_files *include_files;
    struct variable_declaration *var_declaration;
    struct FunctionDef *func_declaration;
    struct typedef_declaration *typedef_declaration;
    struct StructDef *struct_declaration;

};

void to_str_global_declaration(int number, struct global_declaration* global_declaration);

struct include_files {
    char *name_of_file;
};

void to_str_include_files(int number, struct include_files* include_files);

//DONE
struct variable_declaration {
    struct typechain *typechain;
    struct inline_initial_declaration *inline_initial_declaration;
};

void to_str_variable_declaration(int number, struct variable_declaration* variable_declaration);

//DONE
struct inline_initial_declaration {
    struct initial_declaration *initial_declaration;
    struct inline_initial_declaration* inline_initial_declaration;
};

void to_str_inline_initial_declaration(int number, struct inline_initial_declaration* inline_initial_declaration);

struct initial_declaration {
    char *identifier;
    struct assignment *assignment;
    struct array_declaration *array_declaration;
    struct list_initializer *list_initializer;
};

void to_str_initial_declaration(int number, struct initial_declaration* initial_declaration);

//DONE
struct cast {
  struct r_value * r_value;
  struct typechain * typechain;
  struct cast * cast;
};

void to_str_cast(int number, struct cast* cast);

//DONE
struct typechain {
    char *type;
    struct StructDef *StructDef;
    struct pointer *pointer;
};

void to_str_typechain(int number, struct typechain* typechain);

//DONE
struct r_value {
  struct value * value;
  int is_null;
  struct math_expr * math_expr;
  struct logic_expr * logic_expr;
};

void to_str_r_value(int number, struct r_value* r_value);

//DONE
struct value {
  struct literal* literal;
  struct l_value* l_value;
  int address;
  struct FunctionCall* functionCall;
};

void to_str_value(int number, struct value* value);

//DONE
struct literal {
  char * str_value;
  char char_value;
  float float_value;
  int int_value;
};

void to_str_literal(int number, struct literal* literal);

//DONE
struct l_value{
    struct pointer *pointer;
    struct field_name *name;
    struct StructCall *StructCall;
};

void to_str_l_value(int number, struct l_value* l_value);

//DONE
struct pointer{
  struct pointer* pointer;
};

void to_str_pointer(int number, struct pointer* pointer);

//DONE
struct array_declaration {
    char *name;
    struct index* index;
    struct list_initializer *list_initializer;
};

void to_str_array_declaration(int number, struct array_declaration* array_declaration);

//DONE
struct list_initializer {
    struct args_list* args_list;
};

void to_str_list_initializer(int number, struct list_initializer* list_initializer);

//DONE
struct FunctionCall {
    char *name;
    struct args_list* args_list;
};

void to_str_FunctionCall(int number, struct FunctionCall* FunctionCall);

//DONE
struct args_list {
    struct cast* arg;
    struct args_list* args_list;
};

void to_str_args_list(int number, struct args_list* args_list);

//DONE
struct StructCall {
    struct StructCall* StructCall;
    struct field_name* field_name;
    char* op;
    struct field_name* dest_field_name;
};

void to_str_StructCall(int number, struct StructCall* StructCall);

//DONE
struct field_name {
  char * name;
  struct index * index;
};

void to_str_field_name(int number, struct field_name* field_name);

//DONE
struct index {
  int integer;
  char * identifier;
};

void to_str_index(int number, struct index* index);

//DONE
struct math_expr {
    char* sign;
    struct math_expr *l;
    struct math_expr *r;
    struct value* value;
};

void to_str_math_expr(int number, struct math_expr* math_expr);

//DONE
struct logic_expr {

    char* sign;
    struct logic_expr *l;
    struct logic_expr *r;
    struct math_expr* value;
};

void to_str_logic_expr(int number, struct logic_expr* logic_expr);

//DONE
struct StructDef {
    char *name;
    struct field_list *field_list;
};

void to_str_StructDef(int number, struct StructDef* StructDef);

//DONE
struct field_list {
    struct field *field;
    struct field_list *field_list;
};

void to_str_field_list(int number, struct field_list* field_list);

//DONE
struct field {
    struct typechain *typechain;
    struct inline_field_names *inline_field_names;
};

void to_str_field(int number, struct field* field);

//DONE
struct inline_field_names {
    struct inline_field_names *inline_field_names;
    struct field_name *field_name;
};

void to_str_inline_field_names(int number, struct inline_field_names* inline_field_names);

//DONE
struct FunctionDef {
    struct typechain *typechain;
    char *name;
    struct param_list *param_list;
    struct Body *Body;
};

void to_str_FunctionDef(int number, struct FunctionDef* FunctionDef);

//DONE
struct param_list {
    struct typechain *typechain;
    struct param_name *param_name;
    struct param_list *param_list;
    struct param *param;
};

void to_str_param_list(int number, struct param_list* param_list);

//DONE
struct Body {
    struct ComplexBody *ComplexBody;
    struct Statement *Statement;
};

void to_str_Body(int number, struct Body* Body);

//DONE
struct ComplexBody {
    struct Statement *Statement;
    struct ComplexBody *ComplexBody;
};

void to_str_ComplexBody(int number, struct ComplexBody* ComplexBody);

//DONE
struct else_body {
    struct Body *Body;
};

void to_str_else_body(int number, struct else_body* else_body);

//DONE
struct Statement {
    struct variable_declaration *variable_declaration;
    struct Expression *Expression;
    struct if_statement *if_statement;
    struct for_statement *for_statement;
    struct while_statement *while_statement;
    struct FunctionCall *FunctionCall;
    struct StructDef *StructDef;
    struct typedef_declaration *typedef_declaration;
    struct Return *Return;
};

void to_str_Statement(int number, struct Statement* Statement);

//DONE
struct Expression {
    struct l_value *l_value;
    struct assignment *assignment;
    struct short_math *short_math;
    struct inc_and_dec *inc_and_dec;
};

void to_str_Expression(int number, struct Expression* Expression);

//DONE
struct assignment {
    struct cast *cast;
};

void to_str_assignment(int number, struct assignment* assignment);

//DONE
struct short_math {
    char sign;
    struct r_value *r_value;
};

void to_str_short_math(int number, struct short_math* short_math);

//DONE
struct inc_and_dec {
    char *operand;
    int post;
    struct l_value *l_value;
};

void to_str_inc_and_dec(int number, struct inc_and_dec* inc_and_dec);

//DONE
struct if_statement {
    struct logic_expr *logic_expr;
    struct Body *Body;
    struct else_body *else_body;
};

void to_str_if_statement(int number, struct if_statement* if_statement);

//DONE
struct for_statement {
    struct for_init *for_init;
    struct for_condition *for_condition;
    struct for_actions *for_actions;
    struct Body *Body;
};

void to_str_for_statement(int number, struct for_statement* for_statement);

//DONE
struct for_init {
    struct variable_declaration *variable_declaration;
    struct ExpressionList *ExpressionList;
};

void to_str_for_init(int number, struct for_init* for_init);

//DONE
struct ExpressionList {
    struct ExpressionList *ExpressionList;
    struct Expression *Expression;
};

void to_str_ExpressionList(int number, struct ExpressionList* ExpressionList);

//DONE
struct for_condition {
    struct logic_expr *logic_expr;
};

void to_str_for_condition(int number, struct for_condition* for_condition);

//DONE
struct for_actions {
    struct ExpressionList *ExpressionList;
};

void to_str_for_actions(int number, struct for_actions* for_actions);

//DONE
struct while_statement {
    struct logic_expr *logic_expr;
    struct Body *Body;
};

void to_str_while_statement(int number, struct while_statement* while_statement);

//DONE
struct typedef_declaration {
    struct typechain *typechain;
    struct list_identifiers *list_identifiers;
};

void to_str_typedef_declaration(int number, struct typedef_declaration* typedef_declaration);

//DONE
struct list_identifiers {
    struct list_identifiers *list_identifiers;
    int pointer;
    char *name;
    struct types_list *types_list;
    struct param_list *param_list;
};

void to_str_list_identifiers(int number, struct list_identifiers* list_identifiers);

//DONE
struct types_list {
    struct types_list *types_list;
    struct typechain *typechain;
    int is_arr;
    struct index* index;
};

void to_str_types_list(int number, struct types_list* types_list);

//DONE
struct param {
    struct typechain *typechain;
    struct param_name *param_name;
};

void to_str_param(int number, struct param* param);

//DONE
struct param_name{
  char* empty_array_name;
  struct field_name* field_name;
};

void to_str_param_name(int number, struct param_name* param_name);

//DONE
struct Return {
    struct cast *cast;
};

void to_str_Return(int number, struct Return* Return);

//
struct compilation_unit* compilation_unit(struct global_declaration* global_declaration, struct compilation_unit* compilation_unit);

struct global_declaration* global_declaration(struct include_files *include_files,  struct variable_declaration *var_declaration,  struct FunctionDef *func_declaration,  struct typedef_declaration *typedef_declaration, struct StructDef *struct_declaration);

struct include_files *include_files(char *name_of_file);

struct variable_declaration *variable_declaration(struct typechain *typechain, struct inline_initial_declaration *inline_initial_declaration);
struct typechain *typechain(char* type, struct StructDef* structdef, struct pointer *pointer);
struct inline_initial_declaration* inline_initial_declaration(struct initial_declaration *initial_declaration, struct inline_initial_declaration* inline_initial_declaration);
struct initial_declaration *initial_declaration(char* identifier, struct assignment * assignment, struct array_declaration * array_declaration, struct list_initializer * list_initializer);
struct assignment * assignment(struct cast* cast);
struct cast* cast(struct r_value * r_value, struct typechain * typechain, struct cast * cast);
struct r_value* r_value(struct value * value, int is_null, struct math_expr * math_expr, struct logic_expr * logic_expr);
struct value * value(struct literal* literal, struct l_value* l_value, int address, struct FunctionCall* functionCall);
struct literal * literal(  char * str_value, char char_value, float float_value, int int_value);
struct l_value* l_value(struct pointer *pointer,  struct field_name *name, struct StructCall *StructCall);
struct pointer* pointer(struct pointer * pointer);
struct StructCall* StructCall(  struct StructCall* StructCall,  struct field_name* field_name,  char* op,  struct field_name* dest_field_name);
struct field_name* field_name (char * name, struct index * index);
struct index* indexx(int integer, char * identifier);
struct FunctionCall* FunctionCall(char *name, struct args_list* args_list);
struct args_list* args_list(struct cast* arg, struct args_list* args_list);
struct math_expr* math_expr (char* sign,  struct math_expr *l,  struct math_expr *r,  struct value* value);
struct array_declaration* array_declaration(char *name,  struct index* index, struct list_initializer *list_initializer);
struct list_initializer* list_initializer(struct args_list* args_list);
struct logic_expr* logic_expr(char* sign, struct logic_expr *l, struct logic_expr *r, struct math_expr* value);
struct StructDef* StructDef(char *name, struct field_list *field_list);
struct field_list* field_list(struct field *field, struct field_list *field_list);
struct field * field(struct typechain *typechain, struct inline_field_names *inline_field_names);
struct inline_field_names * inline_field_names (struct inline_field_names *inline_field_names, struct field_name *field_name);
struct FunctionDef* FunctionDef(struct typechain *typechain, char *name, struct param_list *param_list, struct Body *Body);
struct param_list* param_list(  struct typechain *typechain,  struct param_name *param_name,  struct param_list *param_list,  struct param *param);
struct Body* Body(struct ComplexBody *ComplexBody, struct Statement *Statement);
struct ComplexBody* ComplexBody(  struct Statement *Statement,  struct ComplexBody *ComplexBody);
struct else_body* else_body(struct Body *Body);
struct Statement* Statement (struct variable_declaration *variable_declaration,  struct Expression *Expression,  struct if_statement *if_statement,  struct for_statement *for_statement,  struct while_statement *while_statement,  struct FunctionCall *FunctionCall,  struct StructDef *StructDef,  struct typedef_declaration *typedef_declaration,  struct Return *Return);
struct param* param(  struct typechain *typechain,  struct param_name *param_name);
struct param_name* param_name(  char* empty_array_name,  struct field_name* field_name);
struct Expression* Expression(  struct l_value *l_value,  struct assignment *assignment,  struct short_math *short_math,  struct inc_and_dec *inc_and_dec);
struct short_math* short_math (  char sign,  struct r_value *r_value);
struct inc_and_dec* inc_and_dec(  char *operand,  int post,  struct l_value *l_value  );
struct if_statement* if_statement(  struct logic_expr *logic_expr,  struct Body *Body,  struct else_body *else_body);
struct for_statement* for_statement(struct for_init *for_init,  struct for_condition *for_condition,  struct for_actions *for_actions, struct Body *Body);
struct for_init* for_init(  struct variable_declaration *variable_declaration,  struct ExpressionList *ExpressionList);
struct ExpressionList* ExpressionList(  struct ExpressionList *ExpressionList,  struct Expression *Expression);
struct for_condition* for_condition( struct logic_expr *logic_expr);
struct for_actions* for_actions(  struct ExpressionList *ExpressionList);
struct while_statement* while_statement(struct logic_expr *logic_expr,  struct Body *Body);
struct typedef_declaration* typedef_declaration(struct typechain *typechain,  struct list_identifiers *list_identifiers);
struct list_identifiers* list_identifiers(  struct list_identifiers *list_identifiers,  int pointer,  char *name,  struct types_list *types_list, struct param_list *param_list);
struct types_list* types_list(  struct types_list *types_list,  struct typechain *typechain,  int is_arr,  struct index* index);
struct Return* Return(struct cast *cast);

#endif //SYNTAXPARSER_TREE_H
