#!/bin/bash

#NICK
cat <<EOF > test_input.txt
PASS 0
NICK
NICK :charlotte sweeting
EOF

timeout 2s nc 0.0.0.0 4444 < test_input.txt > output.txt
