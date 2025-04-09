#!/bin/bash

CLANG_FORMAT=.clang-format.yaml

find . -type f \( -name "*.cpp" -o -name "*.hpp"\) -exec $CLANG_FORMAT -i {} +