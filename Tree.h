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
    struct inline_declaration *inline_declaration;
};

//DONE
struct inline_declaration {
    struct inline_declaration *inline_declaration;
    struct initial_declaration *initial_declaration;
};

//DONE
struct initial_declaration {
    char* identifier;
    struct assignment * assignment;
    struct array_declaration * array_declaration; // develop
    struct list_initializer * list_initializer; // develop
};

//DONE
struct assignment {
    struct cast* cast;
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
    struct StructDef *StructDef; //develop
    struct pointer *pointer; //develop
};

//DONE
struct r_value {
  struct value * value;
  int is_null;
  struct math_expr * math_expr; // develop
  struct logic_expr * logic_expr; //develop
};

//DONE
struct value {
  struct literal* literal;
  struct l_value* l_value; //develop
  int address;
  struct FunctionCall* functionCall; //develop
};

//DONE
struct literal {
  char * str_value;
  char char_value;
  float float_value;
  int int_value;
};

struct l_value{
  //develop
};

struct array_declaration {
    char *name;
    char index;
    struct list_initializer list_initializer;
};

struct list_initializer {
    struct cast;
    struct list_initializer *list_initializer;
};

struct l_value {
    char pointers[];
    char *name;
    struct StructCall StructCall;
};

struct FunctionCall {
    char *name;
    struct args_list;
};

struct args_list {
    struct cast list[];
};

struct StructCall {
    char *name;
    char *field;
    struct StructCall *structCall;
};

struct math_expr {
    char sign;
    struct math_expr *l;
    struct math_expr *r;
};

struct logic_expr {
    char sing;
    struct logic_expr *l;
    struct logic_expr *r;
};


struct StructDef {

};

//
struct global_declaration *global_decl();

struct include_files *include_files(char *name_of_file);

struct variable_declaration *variable_declaration(struct typechain *typechain, struct inline_declaration *inline_declaration);
struct typechain *typechain(char* type, struct StructDef* structdef, struct pointer *pointer);
struct inline_declaration *inline_declaration( struct inline_declaration *inline_declaration, struct initial_declaration *initial_declaration);
struct initial_declaration *initial_declaration(char* identifier, struct assignment * assignment, struct array_declaration * array_declaration, struct list_initializer * list_initializer);
struct assignment * assignment(struct cast* cast);
struct cast* cast(struct r_value * r_value, struct typechain * typechain, struct cast * cast);
struct r_value* r_value(struct value * value, int is_null, struct math_expr * math_expr, struct logic_expr * logic_expr);
struct value * value(struct literal* literal, struct l_value* l_value, int address, struct FunctionCall* functionCall);
struct literal * literal(  char * str_value, char char_value, float float_value, int int_value);

struct StructDef *StructDef();
struct math_expr *math_expr();

#endif //SYNTAXPARSER_TREE_H
