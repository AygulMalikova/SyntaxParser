#ifndef SYNTAXPARSER_TREE_H
#define SYNTAXPARSER_TREE_H

struct global_declaration {
//    struct include_files *include_files;
//    struct variable_declaration *var_declaration;
//    struct function_declaration *func_declaration;
//    struct typedef_declaration *typedef_declaration;
//    struct struct_declaration *struct_declaration;
};

struct include_files {
    char *name_of_file;
};

//DONE
struct variable_declaration {
    struct typechain *typechain;
    struct inline_initial_declaration *inline_initial_declaration;
};

//DONE
struct inline_initial_declaration {
    struct inline_declaration *inline_declaration;
    struct inline_initial_declaration* inline_initial_declaration;
};

//DONE
struct inline_declaration {
    char *name;
    struct assignment *assignment;
    struct array_declaration *array_declaration;

    struct list_initializer *list_initializer;
};

//DONE
struct cast {
  struct r_value * r_value;
  struct typechain * typechain;
  struct cast * cast;
};

//DONE
struct typechain {
    char *type;
    struct StructDef *StructDef;
    struct pointer *pointer;
};

//DONE
struct r_value {
  struct value * value;
  int is_null;
  struct math_expr * math_expr;
  struct logic_expr * logic_expr;
};

//DONE
struct value {
  struct literal* literal;
  struct l_value* l_value;
  int address;
  struct FunctionCall* functionCall;
};

//DONE
struct literal {
  char * str_value;
  char char_value;
  float float_value;
  int int_value;
};

//DONE
struct l_value{
    struct pointer *pointer;
    char *name;
    struct StructCall *StructCall;
};

//DONE
struct pointer{
  struct pointer* pointer;
};

//DONE
struct array_declaration {
    char *name;
    struct index* index;
    struct list_initializer *list_initializer;
};

//DONE
struct list_initializer {
    struct args_list* args_list;
};

//DONE
struct FunctionCall {
    char *name;
    struct args_list* args_list;
};

//DONE
struct args_list {
    struct cast* arg;
    struct args_list* args_list;
};

//DONE
struct StructCall {
    struct StructCall* StructCall;
    struct field_name* field_name;
    char* op;
    struct field_name* dest_field_name;
};

//DONE
struct field_name {
  char * name;
  struct index * index;
};

//DONE
struct index {
  int integer;
  char * identifier;
};

//DONE
struct math_expr {
    char sign;
    struct math_expr *l;
    struct math_expr *r;
    struct value* value;
};

//DONE
struct logic_expr {
    char sign;
    struct logic_expr *l;
    struct logic_expr *r;
    struct math_expr* value;
};

struct StructDef {
    char *name;
    struct field_list *field_list;

};

struct field_list {
    struct field *field;
    struct field_list *field_list;
};

struct field {
    struct typechain *typechain;
    struct inline_field_names *inline_field_names;
};

struct inline_field_names {
    struct inline_field_names *inline_field_names;
    struct field_name *field_name;
};

struct FunctionDef {
    struct typechain *typechain;
    char *name;
    struct param_list *param_list;
    struct Body;
};

struct param_list {
    struct typechain *typechain;
    char *name;
    struct param_list *param_list;
};

struct Body {
    struct ComplexBody *ComplexBody;
    struct Statement *Statement;
};

struct ComplexBody {
    struct Statement *Statement;
    struct ComplexBody *ComplexBody;
};

struct else_body {
    struct Body *Body;
};

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

struct Expression {
    struct l_value *l_value;
    struct assignment *assignment;
    struct short_math *short_math;
    struct inc_and_dec *inc_and_dec;
};

struct assignment {
    struct cast *cast;
};

struct short_math {
    char sing;
    struct r_value *r_value;
};

struct inc_and_dec {
    char *operand;
    int post;
    struct l_value *l_value;
};

struct if_statement {
    struct logic_expr *logic_expr;
    struct Body *Body;
    struct else_body *else_body;
};

struct for_statement {
    struct for_init *for_init;
    struct for_condition *for_condition;
    struct for_actions *for_actions;
    struct Body *Body;
};

struct for_init {
    struct variable_declaration *variable_declaration;
    struct ExpressionList *ExpressionList;
};

struct ExpressionList {
    struct ExpressionList *ExpressionList;
    struct Expression *Expression;
};

struct for_condition {
    struct logic_expr *logic_expr;
};

struct for_actions {
    struct ExpressionList *ExpressionList;
};

struct while_statement {
    struct logic_expr *logic_expr;
    struct Body *Body;
};

struct typedef_declaration {
    struct typechain *typechain;
    struct list_identifiers *list_identifiers;
};

struct list_identifiers {
    struct list_identifiers *list_identifiers;
    char pointer;
    char *name;
    struct types_list *types_list;
    struct param_list *param_list;
};

struct types_list {
    struct types_list *types_list;
    struct typechain *typechain;
    char index;
};

struct param_list {
    struct param_list *param_list;
    struct param *param;
    char *name;
};

struct param {
    struct types_list *types_list;
    struct param_name *param_name;
};

struct Return {
    struct cast *cast;
};


//
struct global_declaration *global_decl();

struct include_files *include_files(char *name_of_file);

struct variable_declaration *variable_declaration(struct typechain *typechain, struct inline_declaration *inline_declaration);
struct typechain *typechain(char* type, struct StructDef* structdef, struct pointer *pointer);
struct inline_initial_declaration* inline_initial_declaration(struct inline_declaration *inline_declaration, struct inline_initial_declaration* inline_initial_declaration);
struct inline_declaration *inline_declaration( struct inline_declaration *inline_declaration, struct initial_declaration *initial_declaration);
struct initial_declaration *initial_declaration(char* identifier, struct assignment * assignment, struct array_declaration * array_declaration, struct list_initializer * list_initializer);
struct assignment * assignment(struct cast* cast);
struct cast* cast(struct r_value * r_value, struct typechain * typechain, struct cast * cast);
struct r_value* r_value(struct value * value, int is_null, struct math_expr * math_expr, struct logic_expr * logic_expr);
struct value * value(struct literal* literal, struct l_value* l_value, int address, struct FunctionCall* functionCall);
struct literal * literal(  char * str_value, char char_value, float float_value, int int_value);
struct l_value* l_value(struct pointer *pointer, char *name, struct StructCall *StructCall);
struct pointer* pointer(struct pointer * pointer);
struct StructCall* StructCall(  struct StructCall* StructCall,  struct field_name* field_name,  char* op,  struct field_name* dest_field_name);
struct field_name* field_name (char * name, struct index * index);
struct index* index(int integer, char * identifier);
struct FunctionCall* FunctionCall(char *name, struct args_list* args_list);
struct args_list* args_list(struct cast* arg, struct args_list* args_list);
struct math_expr* math_expr (char sign,  struct math_expr *l,  struct math_expr *r,  struct value* value);
struct array_declaration* array_declaration(char *name,  struct index* index, struct list_initializer *list_initializer);
struct list_initializer* list_initializer(struct args_list* args_list);
struct logic_expr* logic_expr(char sign, struct logic_expr *l, struct logic_expr *r, struct math_expr* value);

struct StructDef *StructDef();

#endif //SYNTAXPARSER_TREE_H
