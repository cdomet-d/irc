#!/bin/bash

CLANG_FORMAT=clang-format

find . -type f \( -name "*.cpp" -o -name "*.hpp" \) -exec $CLANG_FORMAT -i {} +