#!/bin/bash

MY_CAT="../src/cat/s21_cat"
SYS_CAT="cat"

TEST_FILE="test.txt"
FLAGS=("" "-b" "-n" "-b -n" "-n -b" "-bn" "-nb" "--number-nonblank"
 "--number-nonblank -n" "--number" "--number --number-nonblank" "--number -b" "-s" "-s -b" 
 "-s -n" "-s -b -n" "-s --number-nonblank" "-s --number-nonblank -n")

cd "$(dirname "$0")"

pass=0
fail=0

: > tests_failed.txt

for flag in "${FLAGS[@]}"; do
  diff <($MY_CAT $flag "$TEST_FILE") <($SYS_CAT $flag "$TEST_FILE") > /dev/null
  if [ $? -eq 0 ]; then
    ((pass++))
  else
    ((fail++))
    echo "FAIL: $flag $TEST_FILE" >> tests_failed.txt
  fi
done

echo "Passed: $pass"
echo "Failed: $fail"