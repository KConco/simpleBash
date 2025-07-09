#ifndef S21_CAT_H
#define S21_CAT_H

#include <stdio.h>

#define ASCII_MIN 0
#define ASCII_MAX 31
#define ASCII_DEL 127
#define ASCII_EXT_MIN 128
#define ASCII_EXT_MAX 159
#define ASCII_EXT2_MIN 160

typedef struct {
  int b, n, s, e, v, t, error;
} cat_flags;

FILE *open_file(const char *filename, cat_flags *flags);
void print_file(FILE *file, const cat_flags *flags);
void parse_flags(int argc, char *argv[], cat_flags *flags);
void print_visible(int c);

#endif