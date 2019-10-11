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
    char *type;
//    struct inline_declaration inline_declaration;
};

struct global_declaration *global_decl();
struct include_files *include_files(char *name_of_file);

struct variable_declaration *variable_declaration(char *type);

#endif //SYNTAXPARSER_TREE_H
