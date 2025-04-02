#!/bin/bash

#PASS
cat <<EOF > test_input.txt
PASS
PASS wrongpassword
PASS 0
NICK chacham
USER c c c c
PASS
PASS 0
EOF

timeout 2s nc 0.0.0.0 4444 < test_input.txt > outputs/output.txt

#TODO: check if already registered before enoughParams ?
