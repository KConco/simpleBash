#include "s21_grep.h"

#include <getopt.h>

int main(int argc, char *argv[]) {
  grep_flags flags = {0, 0, 0, 0, 0, 0, 0, NULL, NULL};
  regex_t regex;
  if (argc < 3) {
    printf("Missing arguments\n");
    flags.error = 1;
  }

  parse_args(argc, argv, &flags);
  compile_pattern(&flags, &regex);
  FILE *file = open_file(&flags);
  process_file(&flags, &regex, file);

  regfree(&regex);
  return flags.error;
}

void parse_args(int argc, char *argv[], grep_flags *flags) {
  if (flags->error) return;
  int opt;
  while ((opt = getopt(argc, argv, "e:nicv")) != -1) {
    switch (opt) {
      case 'n':
        flags->n = 1;
        break;
      case 'i':
        flags->i = REG_ICASE;
        break;
      case 'c':
        flags->c = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      case 'e':
        flags->e = 1;
        flags->pattern = optarg;
        break;
      default:
        flags->error = 1;
    }
  }

  if (flags->pattern != NULL) {
    flags->filename = argv[optind];
  } else {
    flags->pattern = argv[optind];
    flags->filename = argv[optind + 1];
  }
}

void compile_pattern(grep_flags *flags, regex_t *regex) {
  if (flags->error) return;
  if (regcomp(regex, flags->pattern, flags->i) != 0) {
    printf("Invalid regex pattern\n");
    flags->error = 1;
  }
}

FILE *open_file(grep_flags *flags) {
  if (flags->error) return NULL;
  FILE *file = fopen(flags->filename, "r");
  if (!file) {
    printf("Could not open file\n");
    flags->error = 1;
  }
  return file;
}

void process_file(grep_flags *flags, regex_t *regex, FILE *file) {
  if (flags->error) return;
  char line[4096];
  int line_number = 1;
  int match_count = 0;
  while (fgets(line, sizeof(line), file)) {
    int match = (regexec(regex, line, 0, NULL, 0) == 0);
    if ((match && !flags->v) || (!match && flags->v)) {
      match_count++;
      if (!flags->c) {
        if (flags->n) {
          printf("%d:%s", line_number, line);
        } else {
          printf("%s", line);
        }
      }
    }
    line_number++;
  }
  if (flags->c) {
    printf("%d\n", match_count);
  }
  fclose(file);
}
