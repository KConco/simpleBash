#include "s21_cat.h"
#include <string.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
  cat_flags flags = {0, 0, 1};

  parse_flags(argc, argv, &flags);

  if (flags.file_arg_index >= argc) {
    printf("No file specified\n");
    return 1;
  }

  FILE *file = open_file(argv[flags.file_arg_index]);
  if (!file) {
    return 1;
  }
  print_file(file, &flags);
  fclose(file);
  return 0;
}

void parse_flags(int argc, char *argv[], cat_flags *flags) {
  int opt;
  static struct option long_options[] = {
    {"number-nonblank", 0, 0, 'b'},
    {"number", 0, 0, 'n'},
    {0, 0, 0, 0}
  };

  while ((opt = getopt_long(argc, argv, "bn", long_options, NULL)) != -1) {
    switch (opt) {
      case 'b':
        flags->number_nonblank = 1;
        break;
      case 'n':
        flags->number_all = 1;
        break;
      case '?':
      default:
        printf("Unknown flag\n");
    }
  }

  if (flags->number_nonblank) {
    flags->number_all = 0;
  }

  flags->file_arg_index = optind;
}

FILE *open_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    printf("No such file\n");
  }
  return file;
}

void print_file(FILE *file, const cat_flags *flags) {
  int c;
  int line_number = 1;
  int at_line_start = 1;
  while ((c = fgetc(file)) != EOF) {
    if (at_line_start) {
      if (flags->number_nonblank && c != '\n') {
        printf("%6d\t", line_number++);
      } else if (flags->number_all) {
        printf("%6d\t", line_number++);
      }
      at_line_start = 0;
    }
    putchar(c);
    if (c == '\n') {
      at_line_start = 1;
    }
  }
}
