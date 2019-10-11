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

};

struct FunctionCall {

};

struct StructCall {

};

struct value {
    struct l_value l_value;
    char address;
    struct literal;
    struct FunctionCall;
};

struct math_expr {

};

struct logic_expr {

};

struct StructDef {

};

//
struct global_declaration *global_decl();
struct include_files *include_files(char *name_of_file);

struct variable_declaration *variable_declaration(char *type);

struct typechain *typechain();

struct StructDef *StructDef();

#endif //SYNTAXPARSER_TREE_H
