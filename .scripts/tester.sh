#!/bin/bash

#registration test
(
echo "USER c c c c"
echo "NICK chacham"
echo "PASS wrongpassword"
echo "PASS 0"
echo "PASS fff"
echo "USER c c c c"
echo "NICK alex"
echo "NICK alex"
echo "PASS 0"
echo "USER c c c c"
) | nc 0.0.0.0 4444

