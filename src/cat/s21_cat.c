#include <stdio.h>
#include <string.h>
#include <getopt.h>

typedef struct {
  int number_nonblank;
  int number_all;
  int file_arg_index;
} CatFlags;

FILE *open_file(const char *filename);
void print_file(FILE *file, const CatFlags *flags);
void parse_flags(int argc, char *argv[], CatFlags *flags);

int main(int argc, char *argv[]) {
  CatFlags flags = {0, 0, 1};

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

void parse_flags(int argc, char *argv[], CatFlags *flags) {
  int opt;

  while ((opt = getopt(argc, argv, "bn")) != -1) {
    switch (opt) {
      case 'b':
        flags->number_nonblank = 1;
        break;
      case 'n':
        flags->number_all = 1;
        break;
      case '?':
      default:
        printf("Unknown flag: -%c\n", optopt);
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

void print_file(FILE *file, const CatFlags *flags) {
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
