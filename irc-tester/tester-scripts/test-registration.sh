#!/bin/bash

# Registration
cat <<EOF > test_input.txt
USER c c c c
NICK chacham
PASS 0
PASS fff
USER c c c c
NICK alex
NICK alex
PASS 0
USER c c c c
EOF

timeout 2s nc 0.0.0.0 4444 < test_input.txt > output.txt
