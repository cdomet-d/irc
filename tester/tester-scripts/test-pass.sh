#!/bin/bash

#PASS
cat <<EOF > test_input.txt
PASS
PASS wrongpassword
PASS 0
PASS 0
NICK chacham
PASS 0
USER c 0 * c
PASS
PASS 0
EOF

timeout 2s nc 0.0.0.0 6667 < test_input.txt > outputs/output.txt

cat <<EOF > test_input.txt
PASS 0
USER c 0 * c
PASS 0
NICK chacham
EOF

timeout 2s nc 0.0.0.0 6667 < test_input.txt >> outputs/output.txt

