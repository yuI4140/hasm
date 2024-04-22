#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "./base.c"
typedef struct Filesystem {
    const char *filename;
}Filesystem;
typedef struct Tuple {
    void *v1;
    void *v2;
}Tuple;
typedef struct Trriple {
    void *v1;
    void *v2;
    void *v3;
}Triple;
Triple init_triple(void){
    Triple new={0};
    new.v1=malloc(256);
    new.v2=malloc(256);
    new.v3=malloc(256);
    return new;
}
Tuple init_tuple(void){
    Tuple new={0};
    new.v1=malloc(256);
    new.v2=malloc(256);
    return new;
}
char* get_base(const char* filename);
void throw_err_s(const char*filename, size_t line, const char *msg);
void check_tuple(Tuple *t);
void check_triple(Triple *t);
#define throw_err(msg) throw_err_s(get_base(__FILE__),__LINE__,msg)
void throw_err_s(const char*filename, size_t line, const char *msg) {
    fprintf(stderr, "Parser -> Err|%s:%zu -> %s\n",filename, line + 1, msg);
    exit(1);
}
void new_tuple(Tuple *t,void *v1,void *v2){
    check_tuple(t);
    t->v1=v1;t->v2=v2;
}
void new_triple(Triple *t,void *v1,void *v2,void *v3){
    check_triple(t);
    t->v1=v1;t->v2=v2;
}
void check_triple(Triple *t){
    if (t->v1==NULL||t->v2==NULL||t->v3==NULL) {
        throw_err("Err: Invalid value in new_tuple");
    }
}
void check_tuple(Tuple *t){
    if (t->v1==NULL||t->v2==NULL) {
        throw_err("Err: Invalid value in new_tuple");
    }
}
const char *get_extension(struct Filesystem *fs) {
    const char *dot = strrchr(fs->filename, '.');
    if (!dot || dot == fs->filename) return NULL;
    return dot + 1;
}
struct Filesystem new_filesystem(const char *filename) {
    struct Filesystem fs={0};
    fs.filename = filename;
    return fs;
}
const char *get_filename(const struct Filesystem *fs) {
    return fs->filename;
}
char* get_base(const char* filename) {
    const char* last_dot = strrchr(filename, '.');
    if (last_dot == NULL || last_dot == filename)
        return (char*)filename;
    size_t base_length = last_dot - filename;
    char* base_filename = (char*)malloc(base_length + 1);
    strncpy(base_filename, filename, base_length);
    base_filename[base_length] = '\0';
    return base_filename;
}
char *read_file(const struct Filesystem *fs) {
    FILE *file = fopen(fs->filename, "r");
    if (!file) {
        throw_err("Unable to open file");
    }
    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *content = (char *)malloc(length + 1);
    if (!content) {
        fclose(file);
        throw_err("Memory allocation failed");
    }
    size_t bytes_read = fread(content, 1, length, file);
    if (bytes_read != length) {
        fclose(file);
        free(content);
        throw_err("Error reading file");
    }
    content[length] = '\0';
    fclose(file);
    return content;
}
int count_lines_of_file(const struct Filesystem *fs) {
    FILE *file = fopen(fs->filename, "r");
    if (!file) {
        throw_err("Unable to open file");
    }
    int lineCount = 0;int ch=0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lineCount++;
        }
    }
    fclose(file);
    return lineCount;
}
bool is_instruction(const char *needle) {
    for (size_t i = 0; i < sizeof(INSTRUCTIONS) / sizeof(*INSTRUCTIONS); ++i) {
        if (strcmp(INSTRUCTIONS[i], needle) == 0) {
            return true;
        }
    }
    return false;
}
bool is_register(const char *needle) {
    for (size_t i = 0; i < sizeof(REGISTERS) / sizeof(*REGISTERS); ++i) {
        if (strcmp(REGISTERS[i], needle) == 0) {
            return true;
        }
    }
    return false;
}
bool is_syscall(int n) {
    for (size_t i = 0; i < sizeof(SYSCALLS) / sizeof(*SYSCALLS); ++i) {
        if (SYSCALLS[i].value == n) {
            return true;
        }
    }
    return false;
}
char** split_into_lines(char* content, int* lineCount) {
    size_t len = strlen(content);
    while (len > 0 && (content[len - 1] == '\n' || content[len - 1] == '\r')) {
        content[--len] = '\0';
    }
    char** lines = malloc(4086 * sizeof(char*));
    char* line = strtok(content, "\n");
    *lineCount = 0;
    while (line != NULL) {
        lines[(*lineCount)++] = line;
        line = strtok(NULL, "\n");
    }
    return lines;
}
Tuple chop_by_delimiter(const char* input, char delimiter) {
    Tuple t=init_tuple();
    char* before={0};char* after={0};
    const char* delimiter_pos = strchr(input, delimiter);
    if (delimiter_pos != NULL) {
        int before_length = delimiter_pos - input;
        before = malloc((before_length + 1) * sizeof(char));
        strncpy(before, input, before_length);
        before[before_length] = '\0';
        after = strdup(delimiter_pos + 1);
    } else {
        before = NULL;
        after = NULL;
    }
    new_tuple(&t,before,after);
    return t;
}
