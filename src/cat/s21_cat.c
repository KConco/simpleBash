#include "s21_cat.h"

#include <getopt.h>
#include <string.h>

int main(int argc, char *argv[]) {
  cat_flags flags = {0, 0, 0, 0};

  parse_flags(argc, argv, &flags);

  FILE *file = open_file(argv[optind], &flags);

  print_file(file, &flags);

  return flags.error;
}

void parse_flags(int argc, char *argv[], cat_flags *flags) {
  int opt;
  static struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                         {"number", 0, 0, 'n'},
                                         {"squeeze-blank", 0, 0, 's'},
                                         {0, 0, 0, 0}};

  while ((opt = getopt_long(argc, argv, "bns", long_options, NULL)) != -1) {
    switch (opt) {
      case 'b':
        flags->b = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case '?':
      default:
        printf("Unknown flag\n");
        flags->error = 1;
    }
  }

  if (optind >= argc) {
    printf("No file specified\n");
    flags->error = 1;
  }

  if (flags->b) {
    flags->n = 0;
  }
}

FILE *open_file(const char *filename, cat_flags *flags) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    printf("No such file\n");
    flags->error = 1;
  }
  return file;
}

void print_file(FILE *file, const cat_flags *flags) {
  if (flags->error) {
    return;
  }

  int c;
  int line_number = 1;
  int at_line_start = 1;
  int blank_count = 0;
  
  while ((c = fgetc(file)) != EOF) {
    if (c == '\n') {
      if (flags->s) {
        if (at_line_start) {
          blank_count++;
          if (blank_count > 1) {
            continue;
          }
        } else {
          blank_count = 1;
        }
      }
    } else {
      blank_count = 0;
    }
    if (at_line_start) {
      if (flags->b && c != '\n') {
        printf("%6d\t", line_number++);
      } else if (flags->n) {
        printf("%6d\t", line_number++);
      }
      at_line_start = 0;
    }
    putchar(c);
    if (c == '\n') {
      at_line_start = 1;
    }
  }
  fclose(file);
}
