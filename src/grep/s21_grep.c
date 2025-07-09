#include "s21_grep.h"
#include <stdio.h>
#include <getopt.h>
#include <regex.h>

int main(int argc, char *argv[]) {

    grep_flags flags = {0, 0, 0, 0, 0, 0, 0, NULL};
    if (argc < 3) flags.error = 1;
    parse_flags(argc, argv, &flags);
    if (flags.error) return flags.error;

    char *pattern = argv[optind];
    char *filename = argv[optind + 1];

    regex_t regex;
    int reti = regcomp(&regex, pattern, 0);
    if (reti) {
        return 1;
    }

    FILE *f = fopen(filename, "r");
    if (!f) {
        regfree(&regex);
        return 1;
    }

    char line[4096];
    while (fgets(line, sizeof(line), f)) {
        if (regexec(&regex, line, 0, NULL, 0) == 0) {
            printf("%s", line);
        }
    }
    fclose(f);
    regfree(&regex);
    return 0;
}

void parse_flags(int argc, char *argv[], grep_flags *flags) {
    int opt;
    flags->pattern = argv[optind];
    while ((opt = getopt(argc, argv, "n")) != -1) {
        switch (opt) {
            case 'n':
                flags->n = 1;
                break;
            default:
                flags->error = 1;
        }
    }
}
