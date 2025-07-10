#include <stdio.h>
#include <getopt.h>
#include <regex.h>

#include "s21_grep.h"

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
    while ((opt = getopt(argc, argv, "n")) != -1) {
        switch (opt) {
            case 'n':
                flags->n = 1;
                break;
            default:
                flags->error = 1;
        }
    }

    flags->pattern = argv[optind];
    flags->filename = argv[optind + 1];
}

void compile_pattern(grep_flags *flags, regex_t *regex) {
    if (flags->error) return;
    if (regcomp(regex, flags->pattern, 0)) {
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
    while (fgets(line, sizeof(line), file)) {
        if (regexec(regex, line, 0, NULL, 0) == 0) {
            printf("%s", line);
        }
    }
    fclose(file);
}
