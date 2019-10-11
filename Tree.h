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

struct variable_declaration {
    struct typechain typechain;
    struct inline_declaration inline_declaration;
};

struct inline_declaration {
    char *name;
    struct assignment;
    struct array_declaration;
    struct inline_declaration* inline_declaration;
    struct list_initializer list_initializer;
};

struct typechain {
    char *types;
    struct StructDef StructDef;
    char pointers[];
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

struct cast {
    struct r_value r_value;
    char *type;
    struct cast* cast;
};

struct r_value {
    struct value value;
    char *NULL;
    struct math_expr math_expr;
    struct logic_expr logic_expr;
};

struct l_value {
    char pointers[];
    char *name;
    struct StructCall StructCall;
};

struct literal {
    int int_value;
    float float_value;
    char char_value;
    char *string_value;
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

struct value {
    struct l_value l_value;
    char address;
    struct literal;
    struct FunctionCall;
};

struct math_expr {
    char sing;
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

struct variable_declaration *variable_declaration(char *type);

struct typechain *typechain();

struct StructDef *StructDef();
struct math_expr *math_expr();

#endif //SYNTAXPARSER_TREE_H
