#!/bin/bash

# Registration
cat <<EOF > test_input.txt
USER c 0 * c
NICK chacham
PASS 0
PASS 0
USER c 0 * c
USER c 0 * c
PASS 0
NICK cha
EOF

timeout 2s nc 0.0.0.0 6667 < test_input.txt > outputs/output.txt

cat <<EOF > test_input.txt
pass 0
nick cha
nick cha
pass 0
user c 0 * c
EOF

timeout 2s nc 0.0.0.0 6667 < test_input.txt >> outputs/output.txt
