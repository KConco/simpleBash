#ifndef S21_GREP_H
#define S21_GREP_H

typedef struct {
  int e, i, v, c, l, n, error;
  char *pattern, *filename;
} grep_flags;

void parse_args(int argc, char *argv[], grep_flags *flags);
void compile_pattern(grep_flags *flags, regex_t *regex);
FILE *open_file(grep_flags *flags);
void process_file(grep_flags *flags, regex_t *regex, FILE *file);

#endif