#ifndef S21_GREP_H
#define S21_GREP_H

typedef struct {
  int e, i, v, c, l, n, error;
  char *pattern;
} grep_flags;

void parse_flags(int argc, char *argv[], grep_flags *flags);

#endif