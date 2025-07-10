#ifndef S21_GREP_H
#define S21_GREP_H

#include <regex.h>
#include <stdio.h>

typedef struct {
  int e, i, v, c, l, n, error;
  char *pattern;
} grep_flags;

void parse_args(int argc, char *argv[], grep_flags *flags);
void compile_pattern(grep_flags *flags, regex_t *regex);
FILE *open_file(const char *filename, grep_flags *flags);
void process_file(grep_flags *flags, regex_t *regex, FILE *file,
                  const char *filename);

#endif