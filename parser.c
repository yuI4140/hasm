#include "./utils.c"
#include <stdbool.h>
#include <stdio.h>
typedef struct Command {
  union Instruction {
    Triple ins;
    char *base;
  } Instruction;
} Command;
typedef struct Parser {
  struct Filesystem fs;
} Parser;
Tuple is_instruction_with_operator(const char *s) {
  static const struct {
    char operator;
    const char *instruction;
  } operators[] = {{'=', "mov"}, {'^', "xor"}, {'+', "add"}, {'-', "sub"}};

  Tuple result = init_tuple();

  for (size_t i = 0; i < sizeof(operators) / sizeof(operators[0]); ++i) {
    if (strchr(s, operators[i].operator) != NULL) {
      new_tuple(&result, (char *)operators[i].instruction,
                (char *)&operators[i].operator);
      return result;
    }
  }
  return result;
}
Parser init_parser(const char *filename) {
  Parser new = {0};
  new.fs = new_filesystem(filename);
  return new;
}
void parse(Parser *parser) {
  Filesystem fs = parser->fs;
  char *content = read_file(&fs);
  int lcount = count_lines_of_file(&fs);
  char **lines = split_into_lines(content, &lcount);
  for (int i = 0; i < lcount; ++i) {
    char *line = lines[i];
    Tuple t = is_instruction_with_operator(line);
    check_tuple(&t);
    char *ins = (char *)t.v1;
    char op = *(char *)t.v2;
    printf("{%s,%c}\n", ins, op);
    printf("Line:%d -> %s\n", i, line);
    t = chop_by_delimiter(line, op);
    check_tuple(&t);
    printf("{%s,%s}\n", (char *)t.v1, (char *)t.v2);
  }
}
