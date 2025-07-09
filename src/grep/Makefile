flags = -Wall -Werror -Wextra -std=c11

s21_grep:
	gcc $(flags) s21_grep.c -o s21_grep

clean:
	rm -r s21_grep

test:
	../../testdata/test_grep.sh

rebuild: clean s21_grep
