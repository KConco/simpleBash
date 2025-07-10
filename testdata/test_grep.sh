#!/bin/bash

MY_GREP="../src/grep/s21_grep"
SYS_GREP="grep"

TEST_FILE="test.txt"
PATTERNS=("Line" "a" "sc21" "foo")
FLAGS=("" "-n" "-i" "-c" "-v" "-vc" "-v -c" "-vic")

cd "$(dirname "$0")"

pass=0
fail=0

: > tests_failed.txt

for pattern in "${PATTERNS[@]}"; do
  for flag in "${FLAGS[@]}"; do
    diff <($MY_GREP $flag "$pattern" "$TEST_FILE") <($SYS_GREP $flag "$pattern" "$TEST_FILE") > /dev/null
    if [ $? -eq 0 ]; then
      ((pass++))
    else
      ((fail++))
      echo "FAIL: $flag $pattern $TEST_FILE" >> tests_failed.txt
    fi
  done
done

echo "Passed: $pass"
echo "Failed: $fail" 