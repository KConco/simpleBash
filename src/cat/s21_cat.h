#ifndef S21_CAT_H
#define S21_CAT_H

#include <stdio.h>

typedef struct {
  int b, n, s, error;
} cat_flags;

FILE *open_file(const char *filename, cat_flags *flags);
void print_file(FILE *file, const cat_flags *flags);
void parse_flags(int argc, char *argv[], cat_flags *flags);

#endif