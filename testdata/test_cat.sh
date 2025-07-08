#!/bin/bash

MY_CAT="../a.out"
SYS_CAT="cat"

TEST_FILE="test.txt"
FLAGS=("" "-b" "-n" "-b -n" "-n -b" "-bn" "-nb")

cd "$(dirname "$0")"

pass=0
fail=0

: > test_failed.txt

for flag in "${FLAGS[@]}"; do
  diff <($MY_CAT $flag "$TEST_FILE") <($SYS_CAT $flag "$TEST_FILE") > /dev/null
  if [ $? -eq 0 ]; then
    ((pass++))
  else
    ((fail++))
    echo "FAIL: $flag $TEST_FILE" >> test_failed.txt
  fi
done

echo "Passed: $pass"
echo "Failed: $fail"