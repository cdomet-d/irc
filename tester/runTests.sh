#!/bin/bash

# List of arguments to test
args=(
  reg
  pass
  nick
  user
  invite
  join
  kick
  mode
  part
  quit
  msg
  topic
  who
  trail
)

# Loop through each argument and run ./tester with it
for arg in "${args[@]}"; do
  echo "=== Running: ./tester $arg ==="
  ./tester "$arg"
  echo "=== Finished: ./tester $arg ==="
  echo
done
