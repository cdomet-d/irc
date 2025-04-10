#!/bin/bash

# Registration
cat <<EOF > test_input.txt
USER c 0 * c
NICK chacham
PASS 0
PASS fff
USER c 0 * c
NICK alex
NICK alex
PASS 0
USER c 0 * c
EOF

timeout 2s nc 0.0.0.0 4444 < test_input.txt > outputs/output.txt
