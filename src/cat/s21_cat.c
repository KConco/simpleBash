#include "s21_cat.h"
#include <getopt.h>

int main(int argc, char *argv[]) {
  cat_flags flags = {0, 0, 0, 0, 0, 0, 0};

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

  while ((opt = getopt_long(argc, argv, "bnsevtET", long_options, NULL)) != -1) {
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
      case 'v':
        flags->v = 1;
        break;
      case 'e':
        flags->e = 1;
        flags->v = 1;
        break;
      case 'E':
        flags->e = 1;
        break;
      case 't':
        flags->t = 1;
        flags->v = 1;
        break;
      case 'T':
        flags->t = 1;
        break;
      case '?':
      default:
        flags->error = 1;
    }
  }
  if (flags->b) flags->n = 0;

  if (optind >= argc) {
    printf("No file specified\n");
    flags->error = 1;
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

  int c, prev = '\n';
  int line_number = 1;
  int blank_count = 0;

  while ((c = fgetc(file)) != EOF) {
    if (c == '\n' && prev == '\n' && flags->s) {
      blank_count++;
      if (blank_count > 0) continue;
    } else if (c != '\n') {
      blank_count = -1; 
    }

    if ((prev == '\n') && ((flags->b && c != '\n') || flags->n)) {
      printf("%6d\t", line_number++);
    }

    if ((flags->e) && c == '\n') putchar('$');
    if (flags->t && c == '\t') {
      putchar('^');
      putchar('I');
    } else if (flags->v && c != '\n' && c != '\t') {
      print_visible(c);
    } else {
      putchar(c);
    }
    prev = c;
  }
  fclose(file);
}

void print_visible(int c) {
  if (c >= 0 && c < 32) {
    putchar('^');
    putchar(c + 64);
  } else if (c == 127) {
    putchar('^');
    putchar('?');
  } else if (c >= 128 && c <= 159) {
    printf("M-^");
    putchar(c - 64);
  } else if (c >= 160) {
    printf("M-");
    putchar(c - 128);
  } else {
    putchar(c);
  }
}