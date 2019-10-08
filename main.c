#include <stdio.h>

struct global_declaration {
    struct include_files include_files;
    struct variable_declaration var_declaration;
    struct function_declaration func_declaration;
    struct variable_declaration var_declaration;
    struct struct_declaration struct_declaration;
};

struct include_files {
    char *name_of_file;
};

struct variable_declaration {
    struct inline_declaration inline_declaration;
    struct typedef_declaration typedef_declaration;
};

struct inline_declaration {
    char *type;
    char *name;
    char *pointer_to;
    struct assignment;
    struct array_declaration;
    struct inline_declaration* inline_declaration;
};

struct array_declaration {
    char *name;
    int size;
    struct list_initializer;
};

struct assignment {
    //TODO: нужно дописать
    char *cast;
};

struct function_declaration {
    char *return_type;
    char *name;
    struct param_list;
    struct function_body;
};

struct list_initializer {
    char values[];
};

struct struct_declaration {
    char *name;
    struct struct_fields;

};
struct typedef_declaration {
    char *type;
    char *name;
};

struct struct_fields {
    char *type;
    char *name;
    struct struct_declaration* struct_declaration;
};

struct param_list {
    struct car arr_car[10];
    struct parameter_declaration parameter_declaration[10]; //  тут надо как-то задать размер массива параметров
};

struct parameter_declaration {
    char *type;
    char *name;
};

struct function_body {
    struct variable_declaration;
    struct expression;
    struct if_statement;
    struct for_loop;
    struct while_loop;
    struct function_call;
    struct array_usage;
};

struct expression {

};

struct if_statement {

};

struct for_loop {

};

struct while_loop {

};

struct function_call {

};

struct array_usage {

};

int main() {
    printf("Hello, World!\n");
    int a, b = 2, c = 5;
    printf("%d %d %d", a, b, c);
    return 0;
}
