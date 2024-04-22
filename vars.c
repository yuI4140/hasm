#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Variable {
    char *tag;
    char *value;
};
struct Variable new_Variable(const char *tag, const char *value) {
    struct Variable var;
    var.tag = strdup(tag);
    var.value = strdup(value);
    return var;
}

void free_Variable(struct Variable *var) {
    free(var->tag);
    free(var->value);
}

struct Variables {
    struct Variable *list;
    size_t size;
    size_t capacity;
};

struct Variables init_Variables() {
    struct Variables vars;
    vars.list = NULL;
    vars.size = 0;
    vars.capacity = 0;
    return vars;
}

int exists_Variables(const struct Variables *vars, const char *tag) {
    for (size_t i = 0; i < vars->size; ++i) {
        if (strcmp(vars->list[i].tag, tag) == 0) {
            return 1;
        }
    }
    return 0;
}

void push_Variables(struct Variables *vars, struct Variable var) {
    if (exists_Variables(vars, var.tag)) {
        fprintf(stderr, "Err: variable in list exists\n");
        exit(1);
    }

    if (vars->size == vars->capacity) {
        size_t new_capacity = vars->capacity == 0 ? 1 : vars->capacity * 2;
        vars->list = realloc(vars->list, new_capacity * sizeof(struct Variable));
        if (!vars->list) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        vars->capacity = new_capacity;
    }

    vars->list[vars->size++] = var;
}
