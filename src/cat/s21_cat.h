#ifndef S21_CAT_H
#define S21_CAT_H

#include <stdio.h>

typedef struct {
  int number_nonblank;
  int number_all;
  int file_arg_index;
} cat_flags;

FILE *open_file(const char *filename);
void print_file(FILE *file, const cat_flags *flags);
void parse_flags(int argc, char *argv[], cat_flags *flags);

#endif